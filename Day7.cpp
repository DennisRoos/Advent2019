#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <chrono> 

using namespace std;
using namespace std::chrono;


int Mem[5][1000]; 
int Backup[1000];
int opcode;
int ip[5];
int amp;
int i;
int Phases[5];

int biggest;
int output;

int getValue(int parameter) {
	int value;
	if (opcode % 10 == 1) {
		value = parameter;
	}
	else {
		value = Mem[amp][parameter];
	}
	opcode = opcode / 10;
	return value;
}

int runProgram(int input1, int input2) {
	int op;
	bool inputUsed = false;
	while (true) {
		opcode = Mem[amp][ip[amp]] / 100;
		op = Mem[amp][ip[amp]] % 100;
		if (op == 1) {//addition
			Mem[amp][Mem[amp][ip[amp] + 3]] = getValue(Mem[amp][ip[amp] + 1]) + getValue(Mem[amp][ip[amp] + 2]);
			ip[amp] = ip[amp] + 4;
		}
		else if (op == 2) {//multiplication
			Mem[amp][Mem[amp][ip[amp] + 3]] = getValue(Mem[amp][ip[amp] + 1]) * getValue(Mem[amp][ip[amp] + 2]);
			ip[amp] = ip[amp] + 4;
		}
		else if (op == 3) {//input
			if (inputUsed) {
				Mem[amp][Mem[amp][ip[amp] + 1]] = input2;
			}
			else {
				Mem[amp][Mem[amp][ip[amp] + 1]] = input1;
				inputUsed = true;
			}
			ip[amp] = ip[amp] + 2;
		}
		else if (op == 4) {//output
			output = Mem[amp][Mem[amp][ip[amp] + 1]];
			ip[amp] = ip[amp] + 2;
			return 4;
		}
		else if (op == 5) {//jump if true
			if (getValue(Mem[amp][ip[amp] + 1]) != 0) {
				ip[amp] = getValue(Mem[amp][ip[amp] + 2]);
			}
			else {
				ip[amp] = ip[amp] + 3;
			}
		}
		else if (op == 6) {//jump if false
			if (getValue(Mem[amp][ip[amp] + 1]) == 0) {
				ip[amp] = getValue(Mem[amp][ip[amp] + 2]);
			}
			else {
				ip[amp] = ip[amp] + 3;
			}
		}
		else if (op == 7) {//less than
			if (getValue(Mem[amp][ip[amp] + 1]) < getValue(Mem[amp][ip[amp] + 2])) {
				Mem[amp][Mem[amp][ip[amp] + 3]] = 1;
			}
			else {
				Mem[amp][Mem[amp][ip[amp] + 3]] = 0;
			}
			ip[amp] = ip[amp] + 4;
		}
		else if (op == 8) {//equals
			if (getValue(Mem[amp][ip[amp] + 1]) == getValue(Mem[amp][ip[amp] + 2])) {
				Mem[amp][Mem[amp][ip[amp] + 3]] = 1;
			}
			else {
				Mem[amp][Mem[amp][ip[amp] + 3]] = 0;
			}
			ip[amp] = ip[amp] + 4;

		}

		else if (op == 99) {//end program
			//cout << "Program complete!\n";
			return 99;
		}
		else {
			cout << "Invalid opcode! " << op << endl;
			return -1;
		}
	}
}

void runLoop() {
	for (int j = 0; j < i; j++) {
		for (int k = 0; k < 5; k++) {
			Mem[k][j] = Backup[j];
		}
	}
	output = 0;
	int result = -1; 
	for (int k = 0; k < 5; k++) {//initial loop
		ip[k] = 0;
		amp = k;
		result = runProgram(Phases[k], output);
	}
	while (true) {
		for (int k = 0; k < 5; k++) {
			amp = k;
			result = runProgram(output, output);
			if (result == 99) {//final loop
				return;
			}
		}
	}
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		int num;
		i = 0;
		while (infile >> num)
		{
			Backup[i] = num;
			i++;
		}
		for (int k = 0; k < 5; k++) {
			Phases[k] = k+5;
		}
		biggest = -99999;
		do {
			runLoop(); 
			biggest = max(biggest, output);
		} while (next_permutation(Phases, Phases + 5));
		cout << "Biggest output is: " << biggest << endl;
	}
	else {
		cout << "can't find file?\n";
	}



}
