#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

string source[1100];
string target[1100];

int i;

int searchTree(string name, int &planets) {
	int orbits = 0;
	planets = 1;
	int p = 0;
	for (int j = 0; j < i; j++) {
		if (name.compare(source[j]) == 0) {//found a child of this planet
			orbits = orbits + searchTree(target[j], p);
			orbits = orbits + p;
			planets = planets + p;
		}
	}
	return orbits;
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		i = 0;
		while (infile >> source[i])
		{
			infile >> target[i];//build edgelist
			i++;
		}
		int p = 0;
		int answer = searchTree("COM", p);
		cout << "There are " << p << " planets with " << answer << " orbits\n";
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}