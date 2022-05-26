#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include "Contact.h"

using namespace std;

inline bool onlyNumbers(string st) {						// Check if the given string has any non-digit characters
	for (int i = 0; i < st.length(); i++) {
		if (st[i] < '0' || st[i] > '9')
			return false;
	}
	return true;
}

inline bool invalidCharacter(string st) {						// Check if the given string has a "~" character
	for (int i = 0; i < st.length(); i++) {
		if (st[i] == '~')
			return true;
	}
	return false;
}

struct sortContactPointers
{
	bool operator()(const Contact* left, const Contact* right) const
	{
		return *left < *right;
	}
};

enum class optionValues {									// Enum values for the main menu options
	add,
	print,
	edit,
	removeC,
	help,
	exitPrg
};

inline optionValues getOption(string opt) {												// Return an integer based on a list of strings
	if (opt == "exit" || opt == "0" || opt == "close") return optionValues::exitPrg;
	if (opt == "add" || opt == "1") return optionValues::add;
	if (opt == "print" || opt == "2") return optionValues::print;
	if (opt == "edit" || opt == "3") return optionValues::edit;
	if (opt == "remove" || opt == "4") return optionValues::removeC;
	if (opt == "help" || opt == "5" || opt == "menu") return optionValues::help;
}

enum class editValues {																	// Edit values for the edit menu
	name,
	addNumber,
	editNumber,
	removeNumber,
	address,
	cancel,
	invalid
};

inline editValues getEditOption(string opt) {															// Return an integer based on a list of strings
	if (opt == "exit" || opt == "0" || opt == "close" || opt == "cancel") return editValues::cancel;
	if (opt == "name" || opt == "1") return editValues::name;
	if (opt == "an" || opt == "2") return editValues::addNumber;
	if (opt == "en" || opt == "3") return editValues::editNumber;
	if (opt == "rn" || opt == "4") return editValues::removeNumber;
	if (opt == "address" || opt == "5") return editValues::address;
	return editValues::invalid;
}

inline int findNameInFile(istream& file, string st) {							// Check if the given "name" is found in the file
	string temp;																// The name is the first substring before a "~" character
	int curLine = 1;
	while (getline(file, temp)) {
		if (temp.substr(0, temp.find("~")) == st) {
			return curLine;
		}
		curLine++;
	}
	return 0;
}

inline bool numberAlreadyExists(istream& file, string st) {						// Check if the phone number already exists in the file
	string temp;																// because we can't access the information from a contact by calling another's contact methods
	while (getline(file, temp)) {
		string numberCount = temp.substr(temp.find("~") + 1, 1);				// Find the Number Count member (immediately after the first "~"
		string numbers = temp.substr(temp.find("~") + 3, temp.back());			// Make a substring containing every number (the length is given by the Number Count member)
		numbers = numbers.substr(0, 11 * stoi(numberCount));

		for (int i = 0; i < stoi(numberCount); i++) {
			string curNo = numbers.substr(0, numbers.find("~"));				// Cut out the first number in the string (again, up to the first "~"
			if (curNo == st) {
				return true;													// Check if it's equal to the given name parameter 
			}
			else {
				numbers.erase(0, numbers.find("~") + 1);						// If it's not equal, cut the current number from the numbers string and repeat the cycle
			}
		}
	}
	return false;
}

inline int contactExists(vector<Contact*> list, string name) {					// Input the list of contacts to check if there is any contact with the given name
	for (auto i = list.begin(); i != list.end(); i++) {							// Used in the option menu switch
		if ((*i)->getName() == name) {											// Iterate through every contact and check its name
			return distance(list.begin(), i);									// Return its index if it's found or -1 otherwise
		}
	}
	return -1;
}

//OPTIONS FUNCTIONS

inline void addToList(vector<Contact*>& list) {
	list.push_back(new Contact);												// Add a new Contact at the end of the vector
	system("cls");
	int succes = list.back()->read();											// Call the method to read the contact's info (it returns false if the contact is already in the list)
	if (succes) {
		system("cls");
		cout << "\n\n\n\n\t\t\t\t ------ CONTACT ADDED SUCCESFULLY ------ ";
		cout << "\n\n\t\t\t\t\t          ";
		for (int i = 0; i < 3; i++) {
			cout << "* ";
			Sleep(750);
		}
	}
	else {
		list.pop_back();														// If the method returned false remove the contact from the back
	}

	std::sort(list.begin(), list.end(), sortContactPointers());
}

inline void displayAll(vector<Contact*>& list) {								// Print all the contacts using their method
	system("cls");

	for (auto i = list.begin(); i != list.end(); i++) {
		cout << "\n\t\t\tContact nr " << distance(list.begin(), i) + 1 << ") " << endl;
		(*i)->print();
		Sleep(100);
	}
}

inline int editContact(Contact& contact) {								// Replace the main switch with one for editing a contact
	string option;
	while (true)
	{
		cin >> option;
		switch (getEditOption(option))
		{
		case editValues::cancel:
			return 0;
			break;
		case editValues::invalid:
			cout << "\n\t\t\t\t\t  Invalid option! Try again: ";
			break;
		default:
			contact.edit(option);										// If the user typed a valid command, call the edit method with the said command as a parameter
			return 0;
		}
	}
}

inline void updateFile(vector<Contact*>& list) {						// Update the file after e=any action (addition, edit & removal)
	fstream temp;
	temp.open("temp.txt", ios::out);											// Create and open a temporary file
	for (auto contact = list.begin(); contact != list.end(); contact++) {		// Print all the contact's information in the file
		temp << (*contact)->getName() << "~"
			<< (*contact)->getCount() << "~";
		for (int i = 0; i < (*contact)->getCount(); i++)						// Based on the count of phone numbers, write them all
			temp << (*contact)->getNumber(i) << "~";
		temp << (*contact)->getCountry() << "~"									// Write the rest of the information (in this case, the address)
			<< (*contact)->getCity() << "~"
			<< (*contact)->getStreetName() << "~"
			<< (*contact)->getStreetNr() << "~" << endl;
	}
	temp.close();																// Close the temporary file
	remove("book.txt");															// Remove the original file and replace it with the temporary one
	rename("temp.txt", "book.txt");
	remove("temp.txt");															// Delete the temp file
}