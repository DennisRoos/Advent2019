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

long long rel;
long long Mem[20000];
int opcode;
long long ip;
long long output;

char A[200][200];

long long getReadValue(long long parameter) {
	long long value;
	if (opcode % 10 == 1) {//immediate mode
		value = parameter;
	}
	else if (opcode % 10 == 2) {//relative mode
		value = Mem[parameter + rel];
	}
	else {
		value = Mem[parameter];
	}
	opcode = opcode / 10;
	return value;
}

long long getWriteAddress(long long parameter) {
	long long address;
	if (opcode % 10 == 0) {//just as before
		address = parameter;
	}
	else {
		address = parameter + rel;
	}
	opcode = opcode / 10;
	return address;
}

int runProgram(string input) {
	long long op;
	int incount = 0;
	int outcount = 0;
	string::size_type i = 0;
	while (true) {
		opcode = Mem[ip] / 100;
		op = Mem[ip] % 100;
		if (op == 1) {//addition
			Mem[getWriteAddress(Mem[ip + 3])] = getReadValue(Mem[ip + 1]) + getReadValue(Mem[ip + 2]);
			ip = ip + 4;
		}
		else if (op == 2) {//multiplication
			Mem[getWriteAddress(Mem[ip + 3])] = getReadValue(Mem[ip + 1]) * getReadValue(Mem[ip + 2]);
			ip = ip + 4;
		}
		else if (op == 3) {//input
			if (i < input.size()) {
				int in = input[i];
				cout << char(in);
				Mem[getWriteAddress(Mem[ip + 1])] = in;
				i++;
			}
			else {
				Mem[getWriteAddress(Mem[ip + 1])] = 10;
				ip = ip + 2;
				cout << " was inputted\n";
				return -3;
			}
			ip = ip + 2;
		}
		else if (op == 4) {//output
			int r = getReadValue(Mem[ip + 1]);
			ip = ip + 2;
			output = r;
			if (output < 256) {
				cout << char(output);
			}
			else {
				cout << "Hull damage is " << output << endl;
			}
		}
		else if (op == 5) {//jump if true
			if (getReadValue(Mem[ip + 1]) != 0) {
				ip = getReadValue(Mem[ip + 2]);
			}
			else {
				ip = ip + 3;
			}
		}
		else if (op == 6) {//jump if false
			if (getReadValue(Mem[ip + 1]) == 0) {
				ip = getReadValue(Mem[ip + 2]);
			}
			else {
				ip = ip + 3;
			}
		}
		else if (op == 7) {//less than
			if (getReadValue(Mem[ip + 1]) < getReadValue(Mem[ip + 2])) {
				Mem[getWriteAddress(Mem[ip + 3])] = 1;
			}
			else {
				Mem[getWriteAddress(Mem[ip + 3])] = 0;
			}
			ip = ip + 4;
		}
		else if (op == 8) {//equals
			if (getReadValue(Mem[ip + 1]) == getReadValue(Mem[ip + 2])) {
				Mem[getWriteAddress(Mem[ip + 3])] = 1;
			}
			else {
				Mem[getWriteAddress(Mem[ip + 3])] = 0;
			}
			ip = ip + 4;
		}
		else if (op == 9) {//change relative base
			rel = rel + getReadValue(Mem[ip + 1]);
			ip = ip + 2;
		}

		else if (op == 99) {//end program
			cout << "Program complete!\n";
			return -99;
		}
		else {
			cout << "Invalid opcode! " << op << endl;
			return -1;
		}
	}
}



int main()
{
	ifstream infile;
	infile.open("data.txt");
	rel = 0;
	if (infile.is_open())
	{
		long long num;
		int i = 0;
		while (infile >> num)
		{
			Mem[i] = num;
			i++;
		}
		ip = 0;
		int r;

		string s1 = "OR A J"; //formula is J = (NOT(A AND B AND C) AND D) AND (H OR E)
		string s2 = "AND B J";
		string s3 = "AND C J";
		string s4 = "NOT J J";
		string s5 = "AND D J";

		string s6 = "OR E T";
		string s7 = "OR H T";
		string s8 = "AND T J";

		string end = "RUN";

		r = runProgram(s1);
		r = runProgram(s2);
		r = runProgram(s3);
		r = runProgram(s4);
		r = runProgram(s5);
		r = runProgram(s6);
		r = runProgram(s7);
		r = runProgram(s8);

		r = runProgram(end);

		r = runProgram(" ");
	}
	else {
		cout << "can't find file?\n";
	}
}
