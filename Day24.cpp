#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <list>

using namespace std;

int A[300][5][5];
int B[300][5][5];

vector<int> l;

int countNeighbors(int i, int j, int d) {
	if (i == 2 && j == 2) {//center square
		return 8;
	}
	int t = 0;
	
	if (j == 0) {//top line
		t += A[d + 1][2][1] + A[d][i][1];//add northern and southern neighbor 
		if (i == 0) {//top-left corner
			t += A[d + 1][1][2] + A[d][1][0];//add western and eastern neighbor
			return t;
		}
		if (i == 4) {//top-right corner
			t += A[d + 1][3][2] + A[d][3][0];//add western and eastern neighbor
			return t;
		}
		else {//elsewhere in the top line
			t += A[d][i-1][0] + A[d][i+1][0];//add western and eastern neighbor
			return t;
		}
	}

	if (j == 4) {//bottom line
		t += A[d + 1][2][3] + A[d][i][3];//add northern and southern neighbor 
		if (i == 0) {//bottom-left corner
			t += A[d + 1][1][2] + A[d][1][4];//add western and eastern neighbor
			return t;
		}
		if (i == 4) {//bottom-right corner
			t += A[d + 1][3][2] + A[d][3][4];//add western and eastern neighbor
			return t;
		}
		else {//elsewhere in the bottom line
			t += A[d][i - 1][4] + A[d][i + 1][4];//add western and eastern neighbor
			return t;
		}
	}

	if (i == 0) {//left edge, no corner
		return A[d + 1][1][2] + A[d][i + 1][j] + A[d][i][j-1] + A[d][i][j+1];
	}
	if (i == 4) {//right edge, no corner
		return A[d + 1][3][2] + A[d][i - 1][j] + A[d][i][j - 1] + A[d][i][j + 1];
	}

	if (i == 2 && j == 1) {//middle-top
		t = A[d][2][0] + A[d][1][1] + A[d][3][1];
		for (int k = 0; k < 5; k++) {
			t += A[d - 1][k][0];
		}
		return t;
	}
	if (i == 2 && j == 3) {//middle-bottom
		t = A[d][2][4] + A[d][1][3] + A[d][3][3];
		for (int k = 0; k < 5; k++) {
			t += A[d - 1][k][4];
		}
		return t;
	}
	if (i == 1 && j == 2) {//middle-left
		t = A[d][0][2] + A[d][1][1] + A[d][1][3];
		for (int k = 0; k < 5; k++) {
			t += A[d - 1][0][k];
		}
		return t;
	}
	if (i == 3 && j == 2) {//middle-right
		t = A[d][4][2] + A[d][3][1] + A[d][3][3];
		for (int k = 0; k < 5; k++) {
			t += A[d - 1][4][k];
		}
		return t;
	}

	//otherwise it's not adjacent to any internal or external edges
	return A[d][i - 1][j] + A[d][i + 1][j] + A[d][i][j - 1] + A[d][i][j + 1];

}

int main(int argc, char * argv[])
{


	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int j = 0;
		while (infile >> s) {
			int i = 0;
			while (i < s.size()) {
				char c = s[i];
				if (c == '#') {
					A[150][i][j] = 1;
				}
				else {
					A[150][i][j] = 0;
				}
				i++;
			}
			j++;
		}


		for(int steps = 0; steps < 200; steps++) {
			for (int d = 0; d < 300; d++) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						int t = countNeighbors(i, j, d);
						if (A[d][i][j] == 0 && (t == 1 || t == 2)) {
							B[d][i][j] = 1;
						}
						else if (A[d][i][j] == 1 && t != 1) {
							B[d][i][j] = 0;
						}
						else {
							B[d][i][j] = A[d][i][j];
						}
					}
				}
			}


			int count = 0;
			for (int d = 0; d < 300; d++) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						A[d][i][j] = B[d][i][j];
						count += A[d][i][j];
					}
				}
			}

			cout << "After " << steps+1 << " steps the bug count is " << count << endl;
		}



	}
	else {
		cout << "can't find file?\n";
	}
	return 0;
}