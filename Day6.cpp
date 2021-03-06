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

string ancestors[1100];

int i;
int a;

string findParent(string name) {
	for (int j = 0; j < i; j++) {
		if (name.compare(target[j]) == 0) {//found the parent of this planet
			return source[j];
		}
	}
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
		string current = findParent("YOU");
		while (current.compare("COM") != 0) {//look through ancestors until COM
			ancestors[a] = current;
			a++;
			current = findParent(current);
		}
		current = findParent("SAN");
		int path = 0;
		while (true) {
			for (int k = 0; k < a; k++) {
				if (current.compare(ancestors[k]) == 0) {//found the first common ancestor
					cout << "Path to Santa is " << path + k << endl;
					return 0;
				}
			}
			//current is no ancestor of YOU
			path++;
			current = findParent(current);
		}

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}
