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

	int Image[110][25][6];


	if (infile.is_open())
	{
		string s;
		infile >> s;
		string::size_type c = 0;
		int l = 0;
		while (c < s.size()) {
			for (int j = 0; j < 6; j++) {
				for (int i = 0; i < 25; i++) {
					int t = s[c] - '0';
					Image[l][i][j] = t;
					c++;
				}
			}
			l++;
		}
		int Final[25][6];

		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 6; j++) {
				Final[i][j] = 2;//set entire image to transparant initially
			}
		}

		for (int layer = 0; layer < l; layer++) {
			for (int i = 0; i < 25; i++){
				for (int j = 0; j < 6; j++) {
					if (Final[i][j] == 2) {//if currently transparant, replace with layer below (might be transparant as well)
						Final[i][j] = Image[layer][i][j];
					}
				}
			}
		}

		for (int j = 0; j < 6; j++) {//print image
			for (int i = 0; i < 25; i++) {
				if (Final[i][j] == 0) {
					cout << " ";
				}
				else {
					cout << "X";
				}
			}
			cout << endl;
		}




	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}