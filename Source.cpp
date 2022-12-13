#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Contact.h"

#include "password.h"
#include "utils.h"
#include "menu.h"

using namespace std;

int main() {
	login();
	menu();

	fstream file;
	vector<Contact*> list;

	string line;
	string contactToSearch;

	// GET ALL ITEMS ALREADY IN FILE AND STORE THEM IN THE VECTOR
	/*
		1. For each line in the file, we construct a new contact
		2. Assign each construced contact the information found on its particular line
	*/
	file.open("book.txt", ios::in);		// 1
	while (getline(file, line)) {
		list.push_back(new Contact);
	}
	file.close();

	for (int j = 0; j < list.size(); j++) { // 2
		file.open("book.txt", ios::in);
		list[j]->readFromFile(file, j + 1);
		file.close();
	}
	// The program automatically sorts the contact list alphabeitcally by name (uppercase first and then lowercase)
	// This is done by overloading the '<' operator to campare the name memebers of the contacts
	sort(list.begin(), list.end(), sortContactPointers());

	// SWITCH OPTIONS
	int i;
	string option;

	while (true) {
		// We have multiple possible strings assigned to any particular option
		cin >> option;
		// This is achieved with the help of the enumerators defined in "utils.h"
		switch (getOption(option)) {
		case optionValues::add:
			cout << "\n\t\t\t\t --- ADDING NEW CONTACT ---" << endl;

			// add a new contact to the list
			addToList(list);
			// sort the list
			sort(list.begin(), list.end(), sortContactPointers());

			// update the file "book.txt"
			updateFile(list);

			menu();
			break;

		case optionValues::print:
			displayAll(list);
			cout << "\n\t\t\tType your next command ('help' for options): ";
			break;

		case optionValues::edit:
			cout << "\n\t\t\t\Enter the name of the contact would you like to edit: " << endl;
			cout << "\n\t\t\t\t";
			cin.ignore();
			getline(cin, contactToSearch);
			// Search the list to find there is a contact with the given name
			i = contactExists(list, contactToSearch);
			// The function returns the index of the found contact or -1 if there is no contact with that name
			if (i != -1) {
				system("cls");
				cout << endl << endl;
				// Prints the information of the contact before the edit
				list[i]->print();
				// Displays a new menu, with options to edit different properties of the contact
				editMenu();
				// Asks the user what they would like to change and applies the changes
				editContact(*list[i]);
				// Sorts the list again
				sort(list.begin(), list.end(), sortContactPointers());

				// Updates the file with the new information
				updateFile(list);

				menu();
				break;
			}
			else
			{
				cout << "\n\t\t\tThis contact doesn't exist! ";
				cout << "\n\t\t\tType your next command ('help' for options): ";
				break;
			}

		case optionValues::removeC:
			cout << "\n\t\t\t\tWhich contact would you like to remove?" << endl;
			cout << "\n\t\t\t\t";
			cin.ignore();
			getline(cin, contactToSearch);
			// Checks if the contact actually exists
			i = contactExists(list, contactToSearch);
			if (i != -1)
			{
				// Prints the found contact
				list[i]->print();
				system("cls");

				cout << "\n\n\t\t\t\tAre you sure you want to remove this contact? (y/n): ";
				cin >> option;
				if (option == "y")
				{
					// Deletes the contact stored at the previously returned index
					list.erase(list.begin() + i);
					sort(list.begin(), list.end(), sortContactPointers());

					updateFile(list);
					menu();
					break;
				}
				else if (option == "n")
				{
					menu();
					break;
				}
				else
				{
					cout << "\n\t\t\t\t\t  Invalid option! Try again: ";
					break;
				}
			}
			else
			{
				cout << "\n\t\t\tThis contact doesn't exist! ";
				cout << "\n\t\t\tType your next command ('help' for options): ";
				break;
			}
			menu();
			break;

		// Displays the main menu
		case optionValues::help:
			menu();
			break;

		// Closes the program
		case optionValues::exitPrg:
			system("cls");
			return 0;

		default:
			cout << "\n\t\t\t\t\t  Invalid option! Try again: ";
			break;
		}
	}
}