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

typedef std::numeric_limits< double > dbl;

using namespace std;
#define pi 3.141592654


struct asteroid
{
	double angle;
	int x;
	int y;

	asteroid(double a, int xx, int yy) : angle(a), x(xx), y(yy) {}
};

struct less_than_angle
{
	inline bool operator() (const asteroid& a1, const asteroid& a2)
	{
		return (a1.angle < a2.angle);
	}
};

inline double wrapAngle(double angle)
{
	double twoPi = 2.0 * 3.141592865358979;
	double a2 = angle - twoPi * floor(angle / twoPi);
	return a2;
}

int gcd(int a, int b)
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

	bool A[50][50];
	bool B[50][50];
	bool C[50][50];

	vector < asteroid > vec;

	string s;
	int xmax = 0;
	int ymax = 0;
	if (infile.is_open())
	{
		while (infile >> s) {
			xmax = 0;
			while (xmax < s.size()) {
				if (s[xmax] == '#') {
					B[xmax][ymax] = true;
				}
				else {
					B[xmax][ymax] = false;
				}
				xmax++;
			}
			ymax++;
		}
		int bestAmount = 0;
		int deltaX;
		int deltaY;
		int amount;
		int bestX;
		int bestY;

		for (int stationX = 0; stationX < xmax; stationX++) {
			for (int stationY = 0; stationY < ymax; stationY++) {
				if (B[stationX][stationY] == true) {//found a potential station

					for (int i = 0; i < xmax; i++) {//copy asteroid map
						for (int j = 0; j < ymax; j++) {
							A[i][j] = B[i][j];
						}
					}
					for (int i = 0; i < xmax; i++) {
						for (int j = 0; j < ymax; j++) {
							if (A[i][j] == true && !(i == stationX && j == stationY)) {//find all other asteroids
								deltaX = i - stationX;
								deltaY = j - stationY;
								int divisor = gcd(abs(deltaX), abs(deltaY));
								deltaX = deltaX / divisor;
								deltaY = deltaY / divisor;

								int x = i + deltaX;
								int y = j + deltaY;
								while (x >= 0 && x < xmax && y >= 0 && y < ymax) {
									A[x][y] = false;
									x = x + deltaX;
									y = y + deltaY;
								}
							}
						}
					}
					amount = -1;
					for (int i = 0; i < xmax; i++) {//count remaining asteroids
						for (int j = 0; j < ymax; j++) {
							if (A[i][j] == true) {
								amount++;
							}
						}
					}
					if (stationX == 26 && stationY == 29) {
						for (int j = 0; j < ymax; j++) {
							for (int i = 0; i < xmax; i++) {
								C[i][j] = A[i][j];
							}
						}
					}
					//cout << stationX << "," << stationY << " : " << amount << endl;
					if (amount > bestAmount) {
						bestAmount = amount;
						bestX = stationX;
						bestY = stationY;
					}


				}
			}
		}
		cout << "Best asteroid was at (" << bestX << "," << bestY << ") with " << bestAmount << " Asteroids!\n";

		int stationX = 26;//yes, I just hardcoded the station because fuck recovering that
		int stationY = 29;
		C[26][29] = false;//remove station from map
		for (int i = 0; i < xmax; i++) {
			for (int j = 0; j < ymax; j++) {
				if (C[i][j] == true) {
					double offset = -0.5 * pi;
					double angle = wrapAngle((atan2(j - stationY, i - stationX) + offset + 2 * pi));
					angle = wrapAngle(angle + 3.141592865358979);
					asteroid a(angle, i, j);
					vec.push_back(a);
				}
			}
		}
		sort(vec.begin(), vec.end(), less_than_angle());

		cout << "200th asteroid is at (" << vec[198].x << "," << vec[198].y << ")\n";
	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}