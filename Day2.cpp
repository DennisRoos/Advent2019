#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int A[10000];
int B[10000];


int runProgram(int noun, int verb) {
	int op = 0;
	A[1] = noun;
	A[2] = verb;
	while (true) {
		if (A[op] == 1) {
			A[A[op + 3]] = A[A[op + 1]] + A[A[op + 2]];
		}
		else if (A[op] == 2) {
			A[A[op + 3]] = A[A[op + 1]] * A[A[op + 2]];
		}
		else if (A[op] == 99) {
			return A[0];
		}
		else {
			cout << "Invalid opcode!\n";
			return -1;
		}
		op = op + 4;
	}
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		int num;
		int inputSize = 0;
		while (infile >> num)//load program into memory
		{
			B[inputSize] = num;
			inputSize++;
		}

		for (int noun = 0; noun < 100; noun++) {//try all nouns and verbs
			for (int verb = 0; verb < 100; verb++) {
				for (int i = 0; i < inputSize; i++) {//reset memory to initial state
					A[i] = B[i];
				}
				int answer = runProgram(noun, verb);
				if (answer == 19690720) {//found the right combination!
					cout << "Answer is... Noun: " << noun << ", verb: " << verb << "\n";
					return 0;
				}
			}
		}
		return 0;


	}
	else {

		cout << "can't find file?\n";
	}



}