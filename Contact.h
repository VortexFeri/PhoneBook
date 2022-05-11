#pragma once

class Contact {
private:
	char name[21];
	char number[11];
public:
	Contact();
	~Contact() {};

	void add();
	void addFromFile(int);
	void print();

	char* getName() { return this->name; }
	char* getNumber() { return this->number; }

	void edit(int);
	void deleteContact(int);

	bool nameValid(char*, bool);
	bool numberValid(char*, bool);
};