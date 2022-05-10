#pragma once

class Contact {
private:
	char name[21];
	char number[11];
public:
	Contact();
	~Contact() {};

	int search(char*, Contact*);

	void add();
	void addFromFile(int);
	void print();

	char* getName() { return this->name; }
	char* getNumber() { return this->number; }

	void edit(int);
	void remove(int);
};