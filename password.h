#pragma once
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

void login()
{
	char password[20], my_password[20] = "password";
	int i = 0;
	char ch;

	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*";
	cout << "\n\t\t\t\t\t *~*~*~*   Enter the password  *~*~*~*";
	cout << "\n\t\t\t\t\t                ";

	do
	{
		ch = _getch();
		password[i] = ch;
		if (ch != 27 && ch != 13)
			_putch('*');
		else
			break;
		i++;
	} while (i < 19);
	password[i] = '\0';

	if (strcmp(password, my_password) == 0) {

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