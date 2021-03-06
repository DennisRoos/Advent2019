#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

#include <cmath>

using namespace std;


int X[1000];
int Y[1000];

string wire1;
string wire2;

int shortestDistance = 99999;
string current;

void collision(int x, int y) {
	int distance = abs(x) + abs(y);
	if( distance < shortestDistance && distance > 0)
		shortestDistance = distance;
	return;
}

int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");

	if (!infile.is_open()){

		cout << "can't find file?\n";
		return 0;
	}

	infile >> wire1;
	infile >> wire2;

	X[0] = 0;
	Y[0] = 0;

	int x = 0;
	int y = 0;

	cout << "wire 1: " << wire1 << "\nwire 2: " << wire2 << "\n";
	int i = 1;
	regex re(R"([RUDL]\d+)");


	sregex_iterator iter(wire1.begin(), wire1.end(), re);
	sregex_iterator end;

	while (iter != end)
	{
		for (unsigned k = 0; k < iter->size(); ++k)
		{
			current = (*iter)[k];
			char d = current.at(0);
			current = current.erase(0, 1);
			int distance = stoi(current);
			if (d == 'R') {
				X[i] = X[i - 1] + distance;
				Y[i] = Y[i - 1];
			}
			else if (d == 'L') {
				X[i] = X[i - 1] - distance;
				Y[i] = Y[i - 1];
			}
			else if (d == 'D') {
				Y[i] = Y[i - 1] - distance;
				X[i] = X[i - 1];
			}
			else if (d == 'U') {
				Y[i] = Y[i - 1] + distance;
				X[i] = X[i - 1];
			}
			i++;
			
		}
		++iter;
	}
	sregex_iterator next(wire2.begin(), wire2.end(), re);
	while (next != end)
	{
		for (unsigned l = 0; l < next->size(); ++l)
		{
			current = (*next)[l];
			char d = current.at(0);
			current = current.erase(0, 1);
			int distance = stoi(current);
			for (int j = 1; j < i; j++) {
				if (d == 'U') {
					if ( ((X[j-1] <= x && X[j] >= x) || (X[j - 1] >= x && X[j] <= x)) 
						&& ((y <= Y[j] && y+distance >= Y[j]) || (y >= Y[j] && y + distance <= Y[j]))) {
							collision(x, Y[j]);
						}
				}
				else if (d == 'D') {
					if (((X[j - 1] <= x && X[j] >= x) || (X[j - 1] >= x && X[j] <= x))
						&& ((y <= Y[j] && y + distance >= Y[j]) || (y >= Y[j] && y - distance <= Y[j])
							)) {
						collision(x, Y[j]);
					}
				}
				else if (d == 'L') {
					if (((Y[j - 1] <= y && Y[j] >= y) || (Y[j - 1] >= y && Y[j] <= y))
						&& ((x <= X[j] && x - distance >= X[j]) || (x >= X[j] && x - distance <= X[j]))
							) {
						collision(X[j], y);
					}
				}
				else if (d == 'R') {
					if (((Y[j - 1] <= y && Y[j] >= y) || (Y[j - 1] >= y && Y[j] <= y))
						&& ((x <= X[j] && x + distance >= X[j]) || (x >= X[j] && x + distance <= X[j]))) {
						collision(X[j], y);
					}
				}

				
			}
			if (d == 'R') {
				x = x + distance;
			}
			else if (d == 'L') {
				x = x - distance;
			}
			else if (d == 'D') {
				y = y - distance;
			}
			else if (d == 'U') {
				y = y + distance;
			}
		}
		++next;
	}
	cout << "final solution is: " << shortestDistance << "\n";

}