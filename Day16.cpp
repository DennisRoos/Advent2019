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

int A[530000];
int B[660];

int main(int argc, char * argv[])
{
	

	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		infile >> s;
		int offset = s[0] - '0';
		for (int i = 1; i < 7; i++) {
			offset = offset * 10;
			int t = s[i] - '0';
			offset += t;
		}

		string::size_type c = 0;
		int l = 0;
		while (c < s.size()) {
			int t = s[c] - '0';
			B[l] = t;
			c++;
			l++;
		}
		int numReps = ((l * 10000) - offset) / l;
		int remain = (offset % l);
		int t;
		for (t = 0; t < l - remain; t++) {
			A[t] = B[t + remain];
		}

		for (int i = 0; i < numReps; i++) {
			for (int j = 0; j < l; j++) {
				A[t] = B[j];
				t++;
			}
		}

		for (int s = 0; s < 100; s++) {//number of steps
			cout << s << endl;
			int num = 0;
			for (int i = t-1; i >= 0; i--) {//change each element starting from the back
				num += A[i];
				num = num % 10;
				A[i] = num;
			}
		}
		for (int i = 0; i < 8; i++) {
			cout << A[i];
		}
		cout << endl;
		

	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}