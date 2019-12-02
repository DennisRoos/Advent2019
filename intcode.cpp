#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (infile.is_open())
	{
		int num;
		int i = 0;
		int A[1000];
		while (infile >> num)
		{
			A[i] = num;
			i++;
		}
		
		int op = 0;
		while (true) {
			if (A[op] == 1) {
				A[A[op + 3]] = A[A[op + 1]] + A[A[op + 2]];
			}
			else if (A[op] == 2) {
				A[A[op + 3]] = A[A[op + 1]] * A[A[op + 2]];
			}
			else if (A[op] == 99) {
				cout << "Final state is: " << A[0];
				for (int j = 1; j < i; j++) {
					cout << "," << A[j];
				}
				cout << "\n";
				return 0;
			}
			else {
				cout << "Invalid opcode!\n";
				return 0;
			}
			op = op + 4;
		}


	}
	else {

		cout << "can't find file?\n";
	}



}
