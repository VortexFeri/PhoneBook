#include <iostream>
#include <fstream>
#include <string>

#include "Contact.h"
#include "utilfunc.h"

#define contactNo 20

using namespace std;
//using namespace utilFunc;

int main() {
	Contact* list[contactNo];
	fstream file;
	string changeLine;
	int count, option, indexToChange, num;
	int i = 0;

	int number_of_lines = 0;
	string line;

	file.open("phoneBook.txt");
	while (getline(file, line)) {
		number_of_lines++;
		if (number_of_lines % 3 == 1) {
			list[i] = new Contact();
			list[i]->addFromFile(number_of_lines);
			i++;
		}
	}
	file.close();

	do {
		cout << "\n1) add" << endl << "2) delete" << endl << "3) edit" << endl << "4) print" << endl << "0) EXIT" << endl << "Your option: ";
		cin >> option;
		switch (option) {
		case 1:
			list[i] = new Contact();
			list[i]->add();
			i++;
			break;
		case 2:
			cout << "Enter the name of the contact you want to be removed: ";
			cin >> changeLine;
			num = searchInFile(changeLine, "phoneBook.txt");
			if (num != -1) {
				indexToChange = num / 3;
			}
			else {
				cout << "Contact not found!\n";
				break;
			}
			for (int j = indexToChange; j <= i-1; j++) {
				if (j < i) {
					list[j] = list[j + 1];
				}
			}
			list[i]->~Contact();
			i--;
			list[indexToChange]->deleteContact(num);
			break;
		case 3:
			cout << "Enter the name of the contact you want to modify: ";
			cin >> changeLine;
			num = searchInFile(changeLine, "phoneBook.txt");
			if (num != -1) {
				indexToChange = num / 3;
			}
			else {
				cout << "Contact not found!\n";
				break;
			}
			list[indexToChange]->edit(num);
			break;
		case 4:
			cout << "\nThere are " << i << " contacts\n";
			for (int j = 0; j < i; j++) {
				list[j]->print();
			}
			break;
		case 0: 
			break;
		default: 
			cout << "Invalid option!";
			break;
		}
	} while (option != 0);

	count = i;
	return 0;
}