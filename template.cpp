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
		int answer;
		while (infile >> num)
		{
			//dostuff with numbers
		}
		//calculate final answer
		cout << Final answer is << " answer << "\n";
	}
	else {

		cout << "can't find file?\n";
	}



}