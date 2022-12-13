#pragma once
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>

using namespace std;

void login()
{
	string password, myPassword = "password";
	char ch;

	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*";
	cout << "\n\t\t\t\t\t *~*~*~*   Enter the password  *~*~*~*";
	cout << "\n\t\t\t\t\t                ";

	while (true)
	{
		ch = _getch();
		if (ch == 13) {
			break;
		}
		else if (ch == 8 && password.length() != 0) {
			cout << "\b \b";
			password.pop_back();
			continue;
		}
		else if (ch == 8 && password.length() == 0)
			continue;
		password.push_back(ch);
		cout << "*";
	}

	if (password == myPassword) {

		cout << "\n\n\n\t\t\t\t\t  .(~*~*~*~*~*~*~*^&^*~*~*~*~*~*~*~).";
		cout << "\n\t\t\t\t\t  %|                               |%";
		cout << "\n\t\t\t\t\t  %|   The password is correct!    |%";
		cout << "\n\t\t\t\t\t  %|                               |%";
		cout << "\n\t\t\t\t\t  %|&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&|%\n";
		cout << "\n\n\t\t\t\t\t                  <3\n";
		cout << "\n\n\t\t\t\t\t                ";
		//cin.clear();
		for (int i = 0; i < 3; i++) {
			cout << "* ";
			Sleep(500);
		}
		system("cls");
		return;
	}
	else {
		cout << endl << "\n\t\t\t\t\t *~*~*~* Incorrect password !!! ~*~*~*" << endl << endl;
		for (int i = 0; i < 3; i++) {
			cout << "\n\t\t\t\t\t\t  Wait " << 3 - i << " seconds...";
			Sleep(1000);
		}
		system("cls");
		login();
	}
}