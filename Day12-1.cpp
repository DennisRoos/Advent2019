#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>  
#include <limits>

using namespace std;


long long gcd(long long a, long long b)
{
	// Everything divides 0  
	if (a == 0)
		return b;
	if (b == 0)
		return a;

	// base case 
	if (a == b)
		return a;

	// a is greater 
	if (a > b)
		return gcd(a - b, b);
	return gcd(a, b - a);
}


int main(int argc, char * argv[])
{
	ifstream infile;
	infile.open("data.txt");
	int Pos[4][3];
	int Vel[4][3];

	
	if (infile.is_open())
	{
		for (int i = 0; i < 4; i++) {
			infile >> Pos[i][0];
			infile >> Pos[i][1];
			infile >> Pos[i][2];
			Vel[i][0] = 0;
			Vel[i][1] = 0;
			Vel[i][2] = 0;
		}
		long long numSteps = 100;
		for(int steps = 0; steps < numSteps; steps++)  {

			for (int i = 0; i < 3; i++) {//update velocities for all pairs of moons, and all axis
				for (int j = i + 1; j < 4; j++) {
					for (int axis = 0; axis < 3; axis++) {
						if (Pos[i][axis] < Pos[j][axis]) {
							Vel[i][axis]++;
							Vel[j][axis]--;
						}
						else if (Pos[i][axis] > Pos[j][axis]) {
							Vel[j][axis]++;
							Vel[i][axis]--;
						}
					}
				}
			}

			for (int i = 0; i < 4; i++) {//update position of each moon
				for (int axis = 0; axis < 3; axis++) {
					Pos[i][axis] += Vel[i][axis];
				}
			}

		}

		//all steps done, print results
		int energy = 0;
		for (int i = 0; i < 4; i++) {
			int pot = 0;
			int kin = 0;
			for (int axis = 0; axis < 3; axis++) {
				pot += abs(Pos[i][axis]);
				kin += abs(Vel[i][axis]);
			}
			energy += pot * kin;
		}

		cout << "The total energy in the system is " << energy << endl;


	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}