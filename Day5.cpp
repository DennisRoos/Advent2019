#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int A[1000];
int opcode;

int getValue(int parameter) {
	int value;
	if (opcode % 10 == 1) {
		value = parameter;
	}
	else {
		value = A[parameter];
	}
	opcode = opcode / 10;
	return value;
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		int num;
		int i = 0;
		while (infile >> num)
		{
			A[i] = num;
			i++;
		}

		int ip = 0;
		int op;
		while (true) {
			opcode = A[ip] / 100;
			op = A[ip] % 100;
			if (op == 1) {//addition
				A[A[ip + 3]] = getValue(A[ip + 1]) + getValue(A[ip + 2]);
				ip = ip + 4;
			}
			else if (op == 2) {//multiplication
				A[A[ip + 3]] = getValue(A[ip + 1]) * getValue(A[ip + 2]);
				ip = ip + 4;
			}
			else if (op == 3) {//input
				A[A[ip + 1]] = 5; //NOTE, this is the input for day 5 specifically
				ip = ip + 2;
			}
			else if (op == 4) {//output
				cout << "Output: " << A[A[ip + 1]] << endl;
				ip = ip + 2;
			}
			else if (op == 5) {//jump if true
				if (getValue(A[ip + 1]) != 0) {
					ip = getValue(A[ip + 2]);
				}
				else {
					ip = ip + 3;
				}
			}
			else if (op == 6) {//jump if false
				if (getValue(A[ip + 1]) == 0) {
					ip = getValue(A[ip + 2]);
				}
				else {
					ip = ip + 3;
				}
			}
			else if (op == 7) {//less than
				if (getValue(A[ip + 1]) < getValue(A[ip + 2])) {
					A[A[ip + 3]] = 1;
				}
				else {
					A[A[ip + 3]] = 0;
				}
				ip = ip + 4;
			}
			else if (op == 8) {//equals
				if (getValue(A[ip + 1]) == getValue(A[ip + 2])) {
					A[A[ip + 3]] = 1;
				}
				else {
					A[A[ip + 3]] = 0;
				}
				ip = ip + 4;
			}

			else if (op == 99) {//end program
				cout << "Program complete!\n";
				return 0;
			}
			else {
				cout << "Invalid opcode!\n";
				return 0;
			}
		}
	}
	else {
		cout << "can't find file?\n";
	}



}
