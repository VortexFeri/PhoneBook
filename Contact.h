#pragma once
#include <string>

using namespace std;

class Contact {
private:
	string name;

	struct {
		string country;
		string city;
		string street;
		int nr;
	} address;

	int numberCount;

	string numbers[5];	// any contact can have a maximum of 5 unique phone numbers

public:
	Contact();
	//Contact(string n, string a, int nc, string n1, string n2);
	~Contact() {};

	string getName() { return name; };
	string getCountry() { return address.country; };
	string getCity() { return address.city; };
	string getStreetName() { return address.street; };
	int getStreetNr() { return address.nr; };
	int getCount() { return numberCount; };
	string getNumber(int i) { return numbers[i]; };

	bool read(); // returns false if the operation had no succes (if the contact already exists)
	void print();
	void edit(string);	// takes as a string parameter, which is used to decide which component should be modified

	void readFromFile(istream&, int);	// read the information from a file. It has 2 parameters: the file it should read from and the number of the line it should read from

	bool addName();
	void addNumber(int);	// the parameter dictates the index in the numbers array where the method will store the new name	
	void addAnotherNumber();
	void addAddress();

	bool operator<(const Contact&) const;		// used for sorting
	bool contactAlreadyHasThisNumber(string nr);
};