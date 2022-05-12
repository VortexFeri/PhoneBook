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