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
int P[1000][1000];
int opcode;
long long ip;

long long getReadValue(long long parameter) {
	long long value;
	if (opcode % 10 == 1) {//immediate mode
		value = parameter;
	}
	else if (opcode % 10 == 2) {//relative mode
		value = A[parameter + rel];
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

int runProgram(int input1, int input2, int &output1, int &output2) {
	long long op;
	bool input = false;
	bool output = false;
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
			if (input) {
				A[getWriteAddress(A[ip + 1])] = input2;
			}
			else {
				A[getWriteAddress(A[ip + 1])] = input1;
				input = true;
			}
			ip = ip + 2;
		}
		else if (op == 4) {//output
			if (output) {
				output2 = getReadValue(A[ip + 1]);
				ip = ip + 2;
				return 4;//return after second output
			}
			else {
				output1 = getReadValue(A[ip + 1]);
				output = true;
				ip = ip + 2;
			}
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
			return 99;
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
			A[i] = num;
			i++;
		}
		ip = 0;
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 1000; j++) {
				P[i][j] = 2;//2 indicates untouched black panel
			}
		}
		int x = 500;
		int y = 500;
		int direction = 0;// 0 is UP, 1 is RIGHT, 2 is DOWN, 3 is LEFT
		int result;
		int color;
		P[x][y] = 1;
		int o1;
		int o2;
		while (true) {
			color = P[x][y] % 2;
			result = runProgram(color, color, o1, o2);
			if (result == 99) {//program ends
				break;
			}
			//cout << o2 << " : " << o2 << endl;
			P[x][y] = o1;
			if (o2 == 1) {//change direction
				direction = (direction + 1) % 4;
			}
			else {
				direction = (direction - 1) % 4;
			}
			if (direction == -1) {
				direction = 3;
			}
			if (direction == 0) {//move
				y = y - 1;
			}
			else if (direction == 1) {
				x = x + 1;
			}
			else if (direction == 2) {
				y = y + 1;
			}
			else if (direction == 3) {
				x = x - 1;
			}
			cout << x << "," << y << endl;
		}
		int count = 0;
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 1000; j++) {
				if (P[i][j] != 2) {
					count++;
				}
			}
		}

		for (int j = 500; j < 506; j++) {
			for (int i = 500; i < 550; i++) {
				if (P[i][j] == 1) {
					cout << '#';
				}
				else {
					cout << ' ';
				}
			}
			cout << endl;
		}
		cout << "Number of painted panels is " << count << endl;


	}
	else {
		cout << "can't find file?\n";
	}
}
