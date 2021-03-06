#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>  
#include <limits>

typedef std::numeric_limits< double > dbl;

using namespace std;

const int deckSize = 10007;
int A[deckSize];

void Deal() {
	int j = deckSize - 1;
	for (int i = 0; i < j; i++) {
		int t = A[i];
		A[i] = A[j];
		A[j] = t;
		j--;
	}
}

void Cut(int n) {
	int B[deckSize];
	if (n > 0) {
		int j = 0;
		for (int i = n; i < deckSize; i++) {
			B[j] = A[i];
			j++;
		}
		for (int i = 0; i < n; i++) {
			B[j] = A[i];
			j++;
		}
	}
	else {//negative cut
		int j = 0;
		for (int i = deckSize + n; i < deckSize; i++) {
			B[j] = A[i];
			j++;
		}
		for (int i = 0; i < deckSize + n; i++) {
			B[j] = A[i];
			j++;
		}
	}
	for (int i = 0; i < deckSize; i++) {
		A[i] = B[i];
	}
}

void Increment(int n) {
	int pos = 0;
	int B[deckSize];
	for (int i = 0; i < deckSize; i++) {
		B[pos] = A[i];
		pos = (pos + n) % deckSize;
	}
	for (int i = 0; i < deckSize; i++) {
		A[i] = B[i];
	}
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	for (int i = 0; i < deckSize; i++) {//initialize factory-sorted deck
		A[i] = i;
	}
	string s;
	int num;


	if (infile.is_open())
	{
		while (infile >> s) {
			if (s.compare("cut") == 0){
				infile >> num;
				Cut(num);
			}
			else if (s.compare("deal") == 0) {
				infile >> s;
				if (s.compare("into") == 0) {
					infile >> s;
					infile >> s;
					Deal();
				}
				else {
					infile >> s;
					infile >> num;
					Increment(num);
				}
			}
		}
		for (int i = 0; i < deckSize; i++) {//print result
			if (A[i] == 2019) {
				cout << "the position of card 2019 is " << i << endl;
				return 0;
			}
		}
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}