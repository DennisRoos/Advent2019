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
long long B[1000];
int opcode;
long long ip;



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

int runProgram(int input1, int input2) {
	long long op;
	bool in = true;
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
			if (in) {
				Mem[getWriteAddress(Mem[ip + 1])] = input1;
				in = false;
			}
			else {
				Mem[getWriteAddress(Mem[ip + 1])] = input2;
			}
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
			ip = 0;
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
		int l = 0;
		while (infile >> num)
		{
			B[l] = num;
			l++;
		}
		ip = 0;
		int count = 0;
		int i = 0;
		while(true) {
			for (int j = 0; j < i; j++) {//check in a triangle-ish formation
				for (int k = 0; k < l; k++) {
					Mem[k] = B[k];
				}
				ip = 0;
				rel = 0;
				int r = runProgram(j, i);
				if (r == 1) {
					for (int k = 0; k < l; k++) {
						Mem[k] = B[k];
					}
					ip = 0;
					rel = 0;
					int r2 = runProgram(j+99, i);
					if (r2 == 1) {
						for (int k = 0; k < l; k++) {
							Mem[k] = B[k];
						}
						ip = 0;
						rel = 0;
						int r2 = runProgram(j, i + 99);
						if (r2 == 1) {//found the first square
							cout << "The spot is at ( " << j << " , " << i << " )\n";
							return 0;
						}
					}
				}



			}
			i++;
		}

	}
	else {
		cout << "can't find file?\n";
	}
}
