#include <iostream>
#include <vector>
#include <fstream>
#include "Contact.h"

#define contactNo 20

using namespace std;

int main() {
	Contact* list[contactNo];
	fstream file;
	int option, removeLine, editLine;
	int i = 0;

	do {
		cout << "1) add" << endl << "2) delete" << endl << "3) edit" << endl << "4) print" << endl << "0) EXIT" << endl << "Your option: ";
		cin >> option;
		switch (option) {
		case 1:
			list[i] = new Contact();
			list[i]->add();
			i++;
			break;
		case 2:
			cout << "What to remove? ";
			cin >> removeLine;
			list[removeLine]->remove(removeLine);
			i++;
			break;
		case 3:
			cout << "What to edit? ";
			cin >> editLine;
			list[i]->edit(editLine);
			i++;
			break;
		case 4:
			for (int j = 0; j < i; j++) {

				list[j]->print();
			}
			break;
		case 0: break;
		}
	} while (i < i + 100 && option != 0);

	return 0;
}