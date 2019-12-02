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
		int fuel;
		int sum;
		int total = 0;
		int weight;
		while (infile >> weight)
		{
			sum = 0;
			cout << "Module weight is " << weight << " and requires fuel:";
			while (weight > 1) {
				fuel = weight / 3;
				fuel = fuel - 2;
				if (fuel < 1) {
					weight = 0;
				}
				else {
					cout << fuel << " + ";
					weight = fuel;
				}
				sum = sum + weight;
			}
			cout << " = " << sum << "\n";
			total = total + sum;
		}
		cout << "Total fuel is: " << total << "\n";
	}
	else {

		cout << "can't find file?\n";
	}



}