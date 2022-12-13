#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include "Contact.h"

using namespace std;

// Check if the given string has any non-digit characters
inline bool onlyNumbers(string st) {
	for (int i = 0; i < st.length(); i++) {
		if (st[i] < '0' || st[i] > '9')
			return false;
	}
	return true;
}

// Check if the given string has a "~" character
inline bool invalidCharacter(string st) {
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

// Enum values for the main menu options
enum class optionValues {
	add,
	print,
	edit,
	removeC,
	help,
	exitPrg
};

// Return an integer based on a list of strings
inline optionValues getOption(string opt) {
	if (opt == "exit" || opt == "0" || opt == "close") return optionValues::exitPrg;
	if (opt == "add" || opt == "1") return optionValues::add;
	if (opt == "print" || opt == "2") return optionValues::print;
	if (opt == "edit" || opt == "3") return optionValues::edit;
	if (opt == "remove" || opt == "4") return optionValues::removeC;
	if (opt == "help" || opt == "5" || opt == "menu") return optionValues::help;
}

// Edit values for the edit menu
enum class editValues {
	name,
	addNumber,
	editNumber,
	removeNumber,
	address,
	cancel,
	invalid
};

// Return an integer based on a list of strings
inline editValues getEditOption(string opt) {
	if (opt == "exit" || opt == "0" || opt == "close" || opt == "cancel") return editValues::cancel;
	if (opt == "name" || opt == "1") return editValues::name;
	if (opt == "an" || opt == "2") return editValues::addNumber;
	if (opt == "en" || opt == "3") return editValues::editNumber;
	if (opt == "rn" || opt == "4") return editValues::removeNumber;
	if (opt == "address" || opt == "5") return editValues::address;
	return editValues::invalid;
}

// Check if the given "name" is found in the file
// The name is the first substring before a "~" character
inline int findNameInFile(istream& file, string st) {
	string temp;
	int curLine = 1;
	while (getline(file, temp)) {
		if (temp.substr(0, temp.find("~")) == st) {
			return curLine;
		}
		curLine++;
	}
	return 0;
}

// Check if the phone number already exists in the file
// because we can't access the information from a contact by calling another's contact methods
inline bool numberAlreadyExists(istream& file, string st) {
	string temp;
	while (getline(file, temp)) {
		// Find the Number Count member (immediately after the first "~"
		string numberCount = temp.substr(temp.find("~") + 1, 1);
		// Make a substring containing every number (the length is given by the Number Count member)
		string numbers = temp.substr(temp.find("~") + 3, temp.back());
		numbers = numbers.substr(0, 11 * stoi(numberCount));

		for (int i = 0; i < stoi(numberCount); i++) {
			// Cut out the first number in the string (again, up to the first "~"
			string curNo = numbers.substr(0, numbers.find("~"));
			if (curNo == st) {
				// Check if it's equal to the given name parameter 
				return true;
			}
			else {
				// If it's not equal, cut the current number from the numbers string and repeat the cycle
				numbers.erase(0, numbers.find("~") + 1);
			}
		}
	}
	return false;
}

// Input the list of contacts to check if there is any contact with the given name
// Used in the option menu switch
inline int contactExists(vector<Contact*> list, string name) {
	// Iterate through every contact and check its name
	for (auto i = list.begin(); i != list.end(); i++) {
		if ((*i)->getName() == name) {
			// Return its index if it's found or -1 otherwise
			return distance(list.begin(), i);
		}
	}
	return -1;
}

//OPTIONS FUNCTIONS

inline void addToList(vector<Contact*>& list) {
	// Add a new Contact at the end of the vector
	list.push_back(new Contact);
	system("cls");
	// Call the method to read the contact's info (it returns false if the contact is already in the list)
	int succes = list.back()->read();
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
		// If the method returned false remove the contact from the back
		list.pop_back();
	}

	std::sort(list.begin(), list.end(), sortContactPointers());
}

// Print all the contacts using their method
inline void displayAll(vector<Contact*>& list) {
	system("cls");

	for (auto i = list.begin(); i != list.end(); i++) {
		cout << "\n\t\t\tContact nr " << distance(list.begin(), i) + 1 << ") " << endl;
		(*i)->print();
		Sleep(100);
	}
}

// Replace the main switch with one for editing a contact
inline int editContact(Contact& contact) {
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
			// If the user typed a valid command, call the edit method with the said command as a parameter
			contact.edit(option);
			return 0;
		}
	}
}

	// Update the file after e=any action (addition, edit & removal)
inline void updateFile(vector<Contact*>& list) {
	fstream temp;
	// Create and open a temporary file
	temp.open("temp.txt", ios::out);
	// Print all the contact's information in the file
	for (auto contact = list.begin(); contact != list.end(); contact++) {	
		temp << (*contact)->getName() << "~"
			<< (*contact)->getCount() << "~";
		// Based on the count of phone numbers, write them all
		for (int i = 0; i < (*contact)->getCount(); i++)
			temp << (*contact)->getNumber(i) << "~";
		// Write the rest of the information (in this case, the address)
		temp << (*contact)->getCountry() << "~"
			<< (*contact)->getCity() << "~"
			<< (*contact)->getStreetName() << "~"
			<< (*contact)->getStreetNr() << "~" << endl;
	}
	temp.close();	// Close the temporary file
	remove("book.txt");		// Remove the original file and replace it with the temporary one
	rename("temp.txt", "book.txt");
	remove("temp.txt");		// Delete the temp file
}