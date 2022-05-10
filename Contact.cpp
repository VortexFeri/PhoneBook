#include "Contact.h"
#include "utilfunc.h"

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
    if (searchInFile(name, "phoneBook.txt") != -1) {
        cout << "Contact already exists!" << endl;
        goto repeatName;
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
    if (searchInFile(number, "phoneBook.txt") != -1) {
        cout << "This number is already registered!" << endl;
        goto repeatNumber;
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

void Contact::deleteContact(int line_no) {
    file.open("phoneBook.txt");
    fstream temp;
    temp.open("temp.txt", ios::app);

    string line;
    int curLine = 1;
    while (getline(file, line))
    {
        if (curLine > 3 && !(line_no >= curLine && line_no <= curLine + 2)) {
            temp << line << endl;
        }
        curLine++;
    }
    file.close();
    temp.close();
    remove("phoneBook.txt");
    rename("temp.txt", "phoneBook.txt");
    remove("temp.txt");
}

void Contact::edit(int line_no) {
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


    file.open("phoneBook.txt");
    fstream temp;
    temp.open("temp.txt", ios::app);

    string line;
    int curLine = 1;
    while (getline(file, line))
    {
        if (!(line_no >= curLine && line_no <= curLine + 2)) {
            temp << line << endl;
        }
        else {
            temp << this->name << endl;
            temp << this->number << endl << endl;
        }
        curLine++;
    }
    file.close();
    temp.close();
    remove("phoneBook.txt");
    rename("temp.txt", "phoneBook.txt");
    remove("temp.txt");
}