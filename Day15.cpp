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
int depth;

int x; 
int y;

int A[50][50];


void moveNorth(int l);
void moveSouth(int l);
void moveWest(int l);
void moveEast(int l);

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

int runProgram(int input) {
	long long op;
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
			Mem[getWriteAddress(Mem[ip + 1])] = input;
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
			return 99;
		}
		else {
			cout << "Invalid opcode! " << op << endl;
			return -1;
		}
	}
}


void moveNorth(int l) {
	if (l == depth) {// reached maximum depth, return the way you came
		return;
	}
	x--;
	A[x][y] = runProgram(1);
	int r = A[x][y];
	if (r == 0) {//hit a wall
		x++;
		return;
	}
	if (r == 2) {//found the oxygen unit!
		cout << "The oxygen unit is " << l << " steps away at (" << x << "," << y << ")" << endl;
	}
	moveWest(l + 1);
	moveNorth(l + 1);
	moveEast(l + 1);
	r = runProgram(2);//move back the way you came
	x++;
	return;
}

void moveSouth(int l) {
	if (l == depth) {// reached maximum depth, return the way you came
		return;
	}
	x++;
	A[x][y] = runProgram(2);
	int r = A[x][y];
	if (r == 0) {//hit a wall
		x--;
		return;
	}
	if (r == 2) {//found the oxygen unit!
		cout << "The oxygen unit is " << l << " steps away at (" << x << "," << y << ")" << endl;
	}
	moveWest(l + 1);
	moveSouth(l + 1);
	moveEast(l + 1);
	r = runProgram(1);//move back the way you came
	x--;
	return;
}

void moveEast(int l) {
	if (l == depth) {// reached maximum depth, return the way you came
		return;
	}
	y++; 
	A[x][y] = runProgram(4);
	int r = A[x][y];
	if (r == 0) {//hit a wall
		y--;
		return;
	}
	if (r == 2) {//found the oxygen unit!
		cout << "The oxygen unit is " << l << " steps away at (" << x << "," << y << ")" << endl;
	}
	moveEast(l + 1);
	moveSouth(l + 1);
	moveNorth(l + 1);
	r = runProgram(3);//move back the way you came
	y--;
	return;
}

void moveWest(int l) {
	if (l == depth) {// reached maximum depth, return the way you came
		return;
	}
	y--;
	int r = A[x][y];
	if (r == 0) {//hit a wall
		y++;
		return;
	}
	A[x][y] = runProgram(3);
	r = A[x][y];
	if (r == 0) {//hit a wall
		y++;
		return;
	}
	if (r == 2) {//found the oxygen unit!
		cout << "The oxygen unit is " << l << " steps away at (" << x << "," << y << ")" << endl;
	}
	moveNorth(l + 1);
	moveSouth(l + 1);
	moveWest(l + 1);
	r = runProgram(4);//move back the way you came
	y++;
	return;
}

int main()
{
	auto start = high_resolution_clock::now();
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

		for (int i = 0; i < 50; i++) {
			for( int j = 0; j < 50; j++){
				A[i][j] = -1;//unmapped
			}
		}

		ip = 0;
		depth = 500;
		A[25][25] = -2;
		x = 25;
		y = 25;
		moveNorth(1);
		moveSouth(1);
		moveEast(1);
		moveWest(1);

		/*for (int i = 0; i < 50; i++) { //prints the finished map
			for (int j = 0; j < 50; j++) {
				if (A[i][j] == -1) {
					cout << " ";
				}
				else if (A[i][j] == 0) {
					cout << "#";
				}
				else if (A[i][j] == 1) {
					cout << ".";
				}
				else if (A[i][j] == -2) {
					cout << "X";
				}
				else if (A[i][j] == 2) {
					cout << "O";
				}
			}
			cout << endl;
		}*/

		//part 2
		int minutes = 0;
		int B[50][50];

		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				B[i][j] = A[i][j];//copy A to B
			}
		}

		while (true) {

			bool b = false;
			for (int i = 0; i < 50; i++) {
				for (int j = 0; j < 50; j++) {
					if ( A[i][j] == 1 && (A[i][j - 1] == 2 || A[i][j + 1] == 2 || A[i + 1][j] == 2 || A[i - 1][j] == 2)) {//one of the neighbors has oxygen
						B[i][j] = 2;
						b = true; //at least one extra oxygen tile
					}
				}
			}

			if (!b) {//state is unchanged, so oxygen has filled the entire ship
				cout << "it took " << minutes << " minutes to fill the ship with oxygen!\n";

				auto stop = high_resolution_clock::now();	
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
				return 0;
			}

			for (int i = 0; i < 50; i++) {
				for (int j = 0; j < 50; j++) {
					A[i][j] = B[i][j];//copy B to A to initialize for next minute
					/*if (A[i][j] == -1) {
						cout << " ";
					}
					else if (A[i][j] == 0) {
						cout << "#";
					}
					else if (A[i][j] == 1) {
						cout << ".";
					}
					else if (A[i][j] == -2) {
						cout << "X";
					}
					else if (A[i][j] == 2) {
						cout << "O";
					}*/
				}
			}
			minutes++;
		}



	}
	else {
		cout << "can't find file?\n";
	}
}
