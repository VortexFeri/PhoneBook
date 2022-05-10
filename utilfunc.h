#pragma once

#include <string>
#include <fstream>

using namespace std;


inline int searchInFile(string st, string fileName) {
	int curLine = 0;
	string line;
	fstream file(fileName);

	while (getline(file, line)) {
		curLine++;
		if (line == st) {
			file.close();
			return curLine;
		}
	}
	file.close();
	return -1;
}

inline bool isEmpty(string fileName) {
	int length = -1;
	fstream file(fileName);
	file.seekg(0, ios::end); // put the "cursor" at the end of the file
	length = (int)file.tellg(); // find the position of the cursor
	file.close();
	if (length == 0)
		return true;
	return false;
}