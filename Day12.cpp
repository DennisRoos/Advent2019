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
	int Init[4][3];
	int Vel[4][3];
	long long cycle[3];
	
	if (infile.is_open())
	{
		for (int i = 0; i < 4; i++) {
			infile >> Pos[i][0];
			infile >> Pos[i][1];
			infile >> Pos[i][2];
			Vel[i][0] = 0;
			Vel[i][1] = 0;
			Vel[i][2] = 0;
			Init[i][0] = Pos[i][0];
			Init[i][1] = Pos[i][1];
			Init[i][2] = Pos[i][2];
		}
		long long numSteps = 0;
		for (int axis = 0; axis < 3; axis++) {
			bool repeat = true;
			long long steps = 0;
			while (repeat) {

				for (int i = 0; i < 3; i++) {//update velocities for all pairs of moons, and all axis
					for (int j = i + 1; j < 4; j++) {
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
				steps++;
				for (int i = 0; i < 4; i++) {//update position of each moon
					Pos[i][axis] += Vel[i][axis];
				}
				if (Pos[0][axis] == Init[0][axis] && Vel[0][axis] == 0 &&
					Pos[1][axis] == Init[1][axis] && Vel[1][axis] == 0 &&
					Pos[2][axis] == Init[2][axis] && Vel[2][axis] == 0 &&
					Pos[3][axis] == Init[3][axis] && Vel[3][axis] == 0) {
					repeat = false;
				}
			}
			cycle[axis] = steps;
		}

		cout << "The cycles are " << cycle[0] << "," << cycle[1] << "," << cycle[2] << endl;

		long long lcm1 = ((cycle[0] * cycle[1]) / gcd(cycle[0], cycle[1]));
		long long lcm = ((lcm1 * cycle[2]) / gcd(lcm1, cycle[2]));

		cout << "The result is " << lcm << endl;

		//all steps done, print results
		/*int energy = 0;
		for (int i = 0; i < 4; i++) {
			int pot = 0;
			int kin = 0;
			for (int axis = 0; axis < 3; axis++) {
				pot += abs(Pos[i][axis]);
				kin += abs(Vel[i][axis]);
			}
			energy += pot * kin;
		}

		cout << "The total energy in the system is " << energy << endl;*/


	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}