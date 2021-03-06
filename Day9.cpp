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
long long A[20000];
int opcode;

long long getReadValue(long long parameter) {
	long long value;
	if (opcode % 10 == 1) {//immediate mode
		value = parameter;
	}
	else if (opcode % 10 == 2) {//relative mode
		value = A[parameter+rel];
	}
	else {
		value = A[parameter];
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
			A[i] = num;
			i++;
		}
		long long ip = 0;
		long long op;
		while (true) {
			opcode = A[ip] / 100;
			op = A[ip] % 100;
			if (op == 1) {//addition
				A[getWriteAddress(A[ip + 3])] = getReadValue(A[ip + 1]) + getReadValue(A[ip + 2]);
				ip = ip + 4;
			}
			else if (op == 2) {//multiplication
				A[getWriteAddress(A[ip + 3])] = getReadValue(A[ip + 1]) * getReadValue(A[ip + 2]);
				ip = ip + 4;
			}
			else if (op == 3) {//input
				A[getWriteAddress(A[ip + 1])] = 2; //
				ip = ip + 2;
			}
			else if (op == 4) {//output
				cout << "Output: " << getReadValue(A[ip + 1]) << endl;
				ip = ip + 2;
			}
			else if (op == 5) {//jump if true
				if (getReadValue(A[ip + 1]) != 0) {
					ip = getReadValue(A[ip + 2]);
				}
				else {
					ip = ip + 3;
				}
			}
			else if (op == 6) {//jump if false
				if (getReadValue(A[ip + 1]) == 0) {
					ip = getReadValue(A[ip + 2]);
				}
				else {
					ip = ip + 3;
				}
			}
			else if (op == 7) {//less than
				if (getReadValue(A[ip + 1]) < getReadValue(A[ip + 2])) {
					A[getWriteAddress(A[ip + 3])] = 1;
				}
				else {
					A[getWriteAddress(A[ip + 3])] = 0;
				}
				ip = ip + 4;
			}
			else if (op == 8) {//equals
				if (getReadValue(A[ip + 1]) == getReadValue(A[ip + 2])) {
					A[getWriteAddress(A[ip + 3])] = 1;
				}
				else {
					A[getWriteAddress(A[ip + 3])] = 0;
				}
				ip = ip + 4;
			}
			else if (op == 9) {//change relative base
				rel = rel + getReadValue(A[ip + 1]);
				ip = ip + 2;
			}

			else if (op == 99) {//end program
				cout << "Program complete!\n";
				return 0;
			}
			else {
				cout << "Invalid opcode! " << op << endl;
				return 0;
			}
		}
	}
	else {
		cout << "can't find file?\n";
	}
}
