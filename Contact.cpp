#include <iostream>
#include <string>
#include <fstream>

#include "Contact.h"
#include "utils.h"


using namespace std;

Contact::Contact() {
	name = "\0";

	address.country = "\0";
	address.city = "\0";
	address.street = "\0";
	address.nr = 0;
	numberCount = 0;
	for (int i = 0; i < 5; i++) {
		numbers[i] = "\0";
	}
}

bool Contact::read() {
	string temp;

	cout << "\n\t\t\t\t --- ADDING NEW CONTACT ---" << endl;
	if (!addName()) return false;		// check if the contact already exists

	addNumber(0);						// add the first phone number

	int opt = 0;

	while (true)
	{
		cout << "\n\t\t\t\tWould you like to add another number?" << endl;	// prompt the user to add another phone number (max 5)
		cout << "\t\t\t\t ------ 1 = YES ------ 2 = NO ------" << endl;
		cout << "\t\t\t\t ";
		cin >> opt;
		if (opt == 1)
		{
			cin.clear();
			if (numberCount == 5) {
				cout << "\n\t\t\t\tMax number is 5!" << endl;
				break;
			}
			addAnotherNumber();
		}
		else if (opt == 2)
			break;
		else
			cout << "\n\t\t\t\t\t     Invalid option! Try again: ";
	}

	addAddress();
	return true;
}

void Contact::print() {
	cout << "\t\t\t\t\tName: " << name << endl;
	cout << "\t\t\t\t\tNumber(s): ";
	for (int k = 0; k < numberCount; k++) {
		if (k == 0)
			cout << numbers[k] << endl;
		else
			cout << "\t\t\t\t\t\t   " << numbers[k] << endl;
	}
	cout << "\t\t\t\t\tAddress: " << address.country << ", " << address.city << ", " << address.street << " " << address.nr << endl;
}

void Contact::edit(string elToEdit) {
	string i;
	cout << "\n\t\t\t\t--- EDITING CONTACT ---" << endl;

	switch (getEditOption(elToEdit))
	{
	case editValues::name:
		addName();			// call this method to replace the current name
		break;

	case editValues::addNumber:
		addAnotherNumber();
		break;

	case editValues::editNumber:
		cout << "\n\t\t\t\tSelect the number you want to edit (from 1 to " << numberCount << "): ";
		cin >> i;
		if (onlyNumbers(i) && stoi(i) >= 1 && stoi(i) <= numberCount)
		{
			addNumber(stoi(i) - 1);			// replace the number at the given position
		}
		else
		{
			cout << "\n\t\t\t\tInvalid option!";
			Sleep(1000);
		}
		break;

	case editValues::removeNumber:
		if (numberCount == 1) {
			cout << "\n\t\t\t\tYou need at least one number!";
			Sleep(1000);
		}
		else
		{
			cout << "\n\t\t\t\tSelect the number you want to remove (from 1 to " << numberCount << "): ";
			cin >> i;
			if (onlyNumbers(i) && stoi(i) >= 1 && stoi(i) <= numberCount)
			{
				for (int j = stoi(i); j < numberCount; j++)
				{
					numbers[j - 1] = numbers[j];		// move back every number's position starting with the index given by the user
				}
				numbers[numberCount] = "\0";			// remove the last number
				numberCount--;							// decrement the number count
			}
			else
			{
				cout << "\n\t\t\t\tInvalid option!";
				Sleep(1000);
			}
		}
		break;

	case editValues::address:
		addAddress();			// replace the address
		break;
	}
}

void Contact::readFromFile(istream& file, int lineNo) {
	int pos;
	int curLineNo = 0;
	string line;

	while (getline(file, line)) {
		curLineNo++;
		if (curLineNo == lineNo) {
			string lineSection;
			int curElementInLine = 1;
			while (true) {

				pos = line.find("~");
				lineSection = line.substr(0, pos);

				switch (curElementInLine)
				{
				case 1:
					name = lineSection;
					line.erase(0, pos + 1);
					break;
				case 2:
					numberCount = stoi(lineSection);
					line.erase(0, pos + 1);
					break;
				case 3:
					for (int i = 0; i < numberCount; i++) {
						pos = line.find("~");
						lineSection = line.substr(0, pos);
						numbers[i] = lineSection;
						line.erase(0, pos + 1);
					}
					break;
				case 4:
					lineSection = line.substr(0, pos);
					address.country = lineSection;
					line.erase(0, pos + 1);
					break;
				case 5:
					lineSection = line.substr(0, pos);
					address.city = lineSection;
					line.erase(0, pos + 1);
					break;
				case 6:
					lineSection = line.substr(0, pos);
					address.street = lineSection;
					line.erase(0, pos + 1);
					break;
				case 7:
					lineSection = line.substr(0, pos);
					address.nr = stoi(lineSection);
					line.erase(0, pos + 1);
					break;
				default:
					return;
					break;
				}
				curElementInLine++;
			}
		}
	}
}

/* ================================================== ADDING PARTICULAR MEMBERS TO THE CONTACT ================================================== */

bool Contact::addName()
{
	string temp;
	fstream file;

	cout << "\n\t\t\t\t  Name: ";
	cin.ignore();
	getline(cin, temp);

	while (true)
	{
		file.open("book.txt", ios::in);

		if (temp[0] >= '0' && temp[0] <= '9')
		{
			cout << "\n\t\t\t\tERROR: First character should be a letter! Try again!" << endl;		// make sure the name starts with a non-digit character
			cout << "\t\t\t\tName: ";
			getline(cin, temp);
		}
		else if (invalidCharacter(temp))															// make sure it doesn't contain a "~" character, because it would break the readFromFile function
		{
			cout << "\n\t\t\t\tERROR: You entered an invalid character! Try again!" << endl;
			cout << "\t\t\t\tName: ";
			getline(cin, temp);
		}
		else if (findNameInFile(file, temp) != 0)													// make sure the contact doesn't already exist
		{																							// if it exists abort the action
			file.close();
			cout << "\n\t\t\t\tERROR: Contact already exists!" << endl;
			Sleep(1000);
			return false;
		}
		else
		{
			file.close();
			name = temp;
			return true;
		}
	}
}

void Contact::addNumber(int pos) {
	string temp;
	fstream file;

	cout << "\n\t\t\t\tNumber: ";
	cin >> temp;

	if (numberCount == 5)
	{
		cout << "\n\t\t\t\tThe max count of phone numbers is 5!" << endl;							// make sure there is enough room to add another number
		cin.get();
		return;
	}
	else
	{
		while (true)
		{
			file.open("book.txt", ios::in);

			if (!onlyNumbers(temp) || invalidCharacter(temp))
			{
				cout << "\t\t\t\tERROR: You entered an invalid character! Try again!" << endl;			// make sure it doesn't contain a letter or a "~"
				cout << "\t\t\t\tNumber: ";
				cin >> temp;
			}
			else if (temp.length() != 10)
			{

				cout << "\t\t\t\tERROR: Numbers needs to be EXACTLY 10 characters long! Try again!" << endl;	// make sure it's exactly 10 digits long
				cout << "\t\t\t\tNumber: ";
				cin >> temp;
			}
			else if (numberAlreadyExists(file, temp))
			{
				cout << "\t\t\t\tERROR: This number is already registered! Try again!" << endl;			// make sure the number isn't already registered for another contact (searches in file)
				cout << "\t\t\t\tNumber: ";
				cin >> temp;
				file.close();
			}
			else
			{
				numbers[pos] = temp;
				numberCount++;
				file.close();
				break;
			}
		}
	}
}


void Contact::addAddress() {
	string temp;

	cout << "\n\t\t\t\tAddress: ";
	cin.ignore();
	cout << "\n\t\t\t\t\tCountry: ";
	getline(cin, temp);
	// ----------------------------------------------- Check conditions for address' country
	while (true)
	{
		if (temp[0] >= '0' && temp[0] <= '9')
		{
			cout << "\n\t\t\t\tERROR: First character should be a letter! Try again!" << endl;
			cout << "\t\t\t\tCountry: ";
			getline(cin, temp);
		}
		else if (invalidCharacter(temp))
		{
			cout << "\n\t\t\t\tERROR: You entered an invalid character! Try again!" << endl;
			cout << "\t\t\t\tName: ";
			getline(cin, temp);
		}
		else
		{
			address.country = temp;
			break;
		}
	}

	cout << "\n\t\t\t\t\tCity: ";
	getline(cin, temp);

	// ----------------------------------------------- Check conditions for address' city
	while (true)
	{
		if (temp[0] >= '0' && temp[0] <= '9')
		{
			cout << "\n\t\t\t\tERROR: First character should be a letter! Try again!" << endl;
			cout << "\t\t\t\City: ";
			getline(cin, temp);
		}
		else if (invalidCharacter(temp))
		{
			cout << "\n\t\t\t\tERROR: You entered an invalid character! Try again!" << endl;
			cout << "\t\t\t\tName: ";
			getline(cin, temp);
		}
		else
		{
			address.city = temp;
			break;
		}
	}

	cout << "\n\t\t\t\t\tStreet Name: ";
	getline(cin, temp);

	// ----------------------------------------------- Check conditions for address' street name
	while (true)
	{
		if (temp[0] >= '0' && temp[0] <= '9')
		{
			cout << "\n\t\t\t\tERROR: First character should be a letter! Try again!" << endl;
			cout << "\t\t\t\Street name: ";
			getline(cin, temp);
		}
		else if (invalidCharacter(temp))
		{
			cout << "\n\t\t\t\tERROR: You entered an invalid character! Try again!" << endl;
			cout << "\t\t\t\tName: ";
			getline(cin, temp);
		}
		else
		{
			address.street = temp;
			break;
		}
	}
	cout << "\n\t\t\t\t\tStreet Number: ";
	cin >> temp;

	// ----------------------------------------------- Check conditions for address' street number
	while (true)
	{
		if (!onlyNumbers(temp) || invalidCharacter(temp))
		{
			cout << "\t\t\t\tERROR: You entered an invalid character! Try again!" << endl;
			cout << "\t\t\t\tStreet Number: ";
			cin >> temp;
		}

		else
		{
			address.nr = stoi(temp);
			break;
		}
	}
}

void Contact::addAnotherNumber() {
	string temp;
	fstream file;

	if (numberCount == 5)
	{
		cout << "\n\t\t\t\tThe max count of phone numbers is 5!" << endl;
		cin.get();
		cin.get();
		return;
	}
	cout << "\n\t\t\t\t-- ADDING NEW NUMBER --";
	cout << "\n\t\t\t\tNumber: ";
	cin >> temp;
	// ------- Check conditions for adding another number (they are same as for the first number, plus checking if the contact already has this number)
	while (true)
	{

		file.open("book.txt", ios::in);

		if (!onlyNumbers(temp) || invalidCharacter(temp))
		{
			cout << "\t\t\t\tERROR: You entered an invalid character! Try again!" << endl;
			cin.clear();
			cout << "\t\t\t\tNumber: ";
			cin >> temp;
		}
		else if (temp.length() != 10)
		{
			cout << "\t\t\t\tERROR: Number needs to be EXACTLY 10 characters long! Try again!" << endl;
			cout << "\t\t\t\tNumber: ";
			cin >> temp;
		}
		else if (numberAlreadyExists(file, temp))
		{
			file.close();
			cout << "\t\t\t\tERROR: This number is already registered! Try again!" << endl;
			cout << "\t\t\t\tNumber: ";
			cin >> temp;
		}
		else if (contactAlreadyHasThisNumber(temp))
		{
			file.close();
			cout << "\t\t\t\tERROR: This number is already registered for this contact! Try again!" << endl;
			cout << "\t\t\t\tNumber: ";
			cin >> temp;
		}
		else
		{
			file.close();
			numbers[numberCount] = temp;
			numberCount++;
			break;
		}
	}
}

bool Contact::operator<(const Contact& c) const
{
	return name < c.name; // order by name
}

bool Contact::contactAlreadyHasThisNumber(string nr) {
	for (int i = 0; i < numberCount; i++) {
		if (numbers[i] == nr) {
			return true;
		}
	}
	return false;
}