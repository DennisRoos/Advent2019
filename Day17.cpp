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

int runProgram(int input[]) {
	long long op;
	int incount = 0;
	int outcount = 0;
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
			int in = input[0];
			Mem[getWriteAddress(Mem[ip + 1])] = in;
			cout << "Asked for input\n";
			ip = ip + 2;
		}
		else if (op == 4) {//output
			int r = getReadValue(Mem[ip + 1]);
			ip = ip + 2;
			return r;
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
		int h = 0;
		int w = 0;
		int width = 41;
		int r = 0;
		while (true) {
			r = runProgram(0);
			if (r == -99) {
				break;
			}
			if (r == 10) {//new line
				h++;
				w = 0;
			}
			else {
				char c = static_cast<char>(r);
				A[h][w] = c;
				w++;
			}
		}
		int count = 0;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < width; j++) {
				cout << A[i][j];
				if (A[i][j] == '#' && A[i + 1][j] == '#' && A[i - 1][j] == '#' && A[i][j + 1] == '#' && A[i][j - 1] == '#') {
					count = count + (i*j);
				}

			}
			cout << endl;
		}

		cout << "The alignment parameters are " << count << endl;


	}
	else {
		cout << "can't find file?\n";
	}
}
