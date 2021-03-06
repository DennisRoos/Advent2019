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
long long ip;
int G[37][25];
int score;
int ball;
int paddle;

void PrintScreen() {
	for (int j = 0; j < 25; j++) {
		for (int i = 0; i < 37; i++) {
			if (G[i][j] == 0) {
				cout << ' ';
			}
			else if (G[i][j] == 1) {
				cout << '#';
			}
			else if (G[i][j] == 2) {
				cout << 'X';
			}
			else if (G[i][j] == 3) {
				cout << '-';
			}
			else if (G[i][j] == 4) {
				cout << 'O';
			}
		}
		cout << endl;
	}
	return;
}

int getInput() {
	//PrintScreen();
	if (paddle > ball) {
		return 1;
	}
	if (ball > paddle) {
		return -1;
	}
	return 0;
}


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

int runProgram(int input[], int output[] ) {
	long long op;
	int incount = 0;
	int outcount = 0;
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
			int in = getInput();
			A[getWriteAddress(A[ip + 1])] = in;
			ip = ip + 2;
		}
		else if (op == 4) {//output
			output[outcount] = getReadValue(A[ip + 1]);
			ip = ip + 2;
			outcount++;
			if (outcount == 3) {
				return 4;
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
		A[0] = 2; //set initial memory to play for free


		int result;
		int In[3];
		int Out[3];

		while (true) {
			result = runProgram(In, Out);
			if (result == 99) {//program terminated
				break;
			}
			if (Out[0] == -1) { //score update!
				cout << "Score: " << Out[2] << endl;
				score = Out[2];
			}
			else {
				G[Out[0]][Out[1]] = Out[2];//update map
				if (Out[2] == 3) {//ball update
					ball = Out[0];
				}
				else if (Out[2] == 4) {//paddle update
					paddle = Out[0];
				}
			}
		}
		int count = 0; 
		for (int i = 0; i < 37; i++) {
			for (int j = 0; j < 25; j++) {
				if (G[i][j] == 2) {
					count++;
				}
			}
		}
		PrintScreen();
		cout << "The number of block tiles is " << count << endl;
		cout << "Score is " << score << endl;








	}
	else {
		cout << "can't find file?\n";
	}
}
