#pragma once
#include <string>
#include <fstream>
using namespace std;
class util
{
	int searchInFile(string st, string fileName) {
		int curLine = 0;
		string line;
		fstream file(fileName);

		while (getline(file, line)) { // I changed this, see below
			curLine++;
			if (line == st) {
				return curLine;
			}
		}
		return -1;
	}
};

