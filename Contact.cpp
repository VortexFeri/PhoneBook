#include "Contact.h"
#include "util.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
fstream file;

Contact::Contact() {
    name[0] = 0;
    number[0] = 0;
}

void Contact::add() {
    cout << "Adding new contact:" << endl;
    
repeatName:
    cout << "Name: ";
    cin >> this->name;

    for (int i = 0; i < strlen(name); i++) {
        try {
            if (name[i] < 65 || name[i] > 122 || strlen(name) > 20)
                throw name[i];
        }
        catch (...) {
            cout << "\nThe name is invalid" << endl;
            goto repeatName;
        }
    }
repeatNumber:
    cout << "Number: ";
    cin >> this->number;

    for (int i = 0; i < strlen(number); i++) {
        try {
            if (number[i] < '0' || number[i]> '9' || strlen(number) != 10)
                throw number[i];
        }
        catch (...) {
            cout << "\nInvalid number! Try again" << endl;
            goto repeatNumber;
        }
    }

    file.open("phoneBook.txt", ios::app);
    file << name << endl;
    file << number << endl << endl;
    file.close();

    cout << "Contact added!" << endl;
}

void Contact::print() {
    cout << setw(20) << name;
    cout << setw(15) << number << endl;
}

void Contact::addFromFile(int line_nr) {
    file.open("phoneBook.txt");
    string line;
    int i = 1;

    while (getline(file, line)) // count all the lines from the file
    {
        if (i == line_nr) {
            strcpy_s(name, line.c_str());
        }
        else if (i == line_nr + 1) {
            strcpy_s(number, line.c_str());
        }
        i++;
    }
    file.close();
}

void Contact::deleteContact(int index) {
    file.open("phoneBook.txt");
    fstream temp;
    temp.open("temp.txt");

    string line;
    int i = 0;
    while (getline(file, line))
    {
        if (i == index || index == 3 * i - 2) {
            //line.replace(line.find(line), line.length(), "");
            strcpy_s(name, "");
            strcpy_s(number, "");
            temp << line << endl;
        }
        i++;
    }
    file.close();
    temp.close();
    remove("phoneBook.txt");
    cout << rename("temp.txt", "phoneBook.txt");
}

void Contact::edit(int index) {
    cout << "Editing contact:" << endl;
    cout << "Name : ";
    cin >> this->name;
repeat:
    cout << "Number: ";
    cin >> this->number;

    for (int i = 0; i < strlen(number); i++) {
        try {
            if (number[i] < '0' || number[i]> '9' || strlen(number) != 10)
                throw number[i];
        }
        catch (...) {
            cout << "\nInvalid number! Try again" << endl;
            goto repeat;
        }
    }


    string line;
    int i = 0;
    file.open("phoneBook.txt");

    while (getline(file, line)) // count all the lines from the file
    {
        if (i == index) {
            file << "Name: " << name << endl;
            file << "Number: " << number << endl << endl;
            file.close();
        }
        i++;
    }
}