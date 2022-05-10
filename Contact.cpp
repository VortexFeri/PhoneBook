#include "Contact.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Contact::Contact() {
    name[0] = 0;
    number[0] = 0;

}

void Contact::add() {
    cout << "Adding new contact:" << endl;
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

    ofstream phoneBook("phoneBook.txt", ios::app);
    phoneBook << "Name: " << name << endl;
    phoneBook << "Number: " << number << endl << endl;
    phoneBook.close();

    cout << "Contact added!" << endl;
}

void Contact::print() {
    cout << "Contact Info:" << "\t " << name << "\t\t" << number << endl << endl;
}

void Contact::addFromFile(int line_nr) {
    ifstream phoneBook("phoneBook.txt");
    string line;
    int i = 1;
    while (getline(phoneBook, line)) // count all the lines from the file
    {
        if (i == line_nr) {
            line = line.substr(6, 20);
            strcpy_s(name, line.c_str());
        }
        else if (i == line_nr + 1) {
            line = line.substr(8, 20);
            strcpy_s(number, line.c_str());
        }
        i++;
    }
    phoneBook.close();
}

void Contact::remove(int index) {
    ifstream phoneBook("phoneBook.txt");
    ofstream temp("temp.txt");

    string line;
    int i = 0;
    while (getline(phoneBook, line)) // count all the lines from the file
    {
        if (i == index || index == 3 * i - 2) {
            //line.replace(line.find(line), line.length(), "");
            strcpy_s(name, "");
            strcpy_s(number, "");
            temp << line << endl;
        }
        i++;
    }
    phoneBook.close();
    std::remove("phoneBook.txt");
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
    ifstream phoneBook("phoneBook.txt");

    while (getline(phoneBook, line)) // count all the lines from the file
    {
        if (i == index) {
            ofstream phoneBook("phoneBook.txt");
            phoneBook << "Name: " << name << endl;
            phoneBook << "Number: " << number << endl << endl;
            phoneBook.close();
        }
        i++;
    }
}

int Contact::search(char* nameToSeach, Contact* list) {
    cout << "size: " << sizeof(list);
    return 1;
}