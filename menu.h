#pragma once
#include <iostream>

using namespace std;

void menu() {
	system("cls");
	cout << "\n\n\t\t\t\t\033[1;33m == == == == == == PHONEBOOK  APP == == == == == ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==       1 or 'add' -> Add a new contact        ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==     2 or 'print' -> Print all contacts       ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==   3 or 'edit' -> Edit an existing contact    ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==      4 or 'remove' -> Remove a contact       ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==        5 or 'help' -> Show this menu         ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==      0 or 'exit' -> Close the program        ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t == == == == == == == == == == == == == == == == ==";
	cout << "\n\n\t\t\t\t                Input your option: ";
}

void editMenu() {
	cout << "\n\n\t\t\t\t\033[1;33m = == == == == == EDIT  CONTACT == == == == == == =";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==        1 or 'add' -> Change the name         ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==        2 or 'an' -> Add a new number         ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==          3 or 'en' -> Edit a number          ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==         4 or 'rn' -> Remove a number         ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==      5 or 'adress' -> Change the adress      ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t ==      0 or 'exit' -> Cancel this action       ==";
	cout << "\n\t\t\t\t ==                                              ==";
	cout << "\n\t\t\t\t == == == == == == == == == == == == == == == == ==";
	cout << "\n\n\t\t\t\t                Input your option: ";
}