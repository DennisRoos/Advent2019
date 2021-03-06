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

char A[115][115];
int shortestPath;


struct neighbor {
	int index;
	int distance;

	neighbor(int i, int d) : index(i), distance(d) {}
};

struct portal {
	int x1;
	int y1;
	int d1;
	string name;
	int other;//index of the counterpart portal in the vector v
	bool side;//false is outside, true is inside

	vector<neighbor> n;

	portal(int x, int y, int d, string s, bool b) : x1(x), y1(y), d1(d), name(s), side(b) {}
};

int current;
vector<portal> v;

void moveNorth(int l, int x, int y);
void moveSouth(int l, int x, int y);
void moveWest(int l, int x, int y);
void moveEast(int l, int x, int y);


void moveNorth(int l, int x, int y) {
	if (l > 5000) {//path too long
		return;
	}
	y--;
	char r = A[x][y];
	if (r == '#') {//hit a wall
		return;
	}
	if (r >= 'A' && r <= 'Z') {//hit a portal
		y++;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].x1 == x && v[i].y1 == y) {//found matching portal
				neighbor neigh = neighbor(i, l);
				v[current].n.push_back(neigh);
				return;
			}
		}
	}

	moveWest(l + 1, x, y);
	moveNorth(l + 1, x, y);
	moveEast(l + 1, x, y);
	return;
}

void moveSouth(int l, int x, int y) {
	if (l > 5000) {//path too long
		return;
	}
	y++;
	char r = A[x][y];
	if (r == '#') {//hit a wall
		return;
	}
	if (r >= 'A' && r <= 'Z') {//hit a portal
		y--;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].x1 == x && v[i].y1 == y) {//found matching portal
				neighbor neigh = neighbor(i, l);
				v[current].n.push_back(neigh);
				return;
			}
		}
	}

	moveWest(l + 1, x, y);
	moveSouth(l + 1, x, y);
	moveEast(l + 1, x, y);
	return;
}

void moveEast(int l, int x, int y) {
	if (l > 5000) {//path too long
		return;
	}
	x++;
	char r = A[x][y];
	if (r == '#') {//hit a wall
		return;
	}

	if (r >= 'A' && r <= 'Z') {//hit a portal
		x--;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].x1 == x && v[i].y1 == y) {//found matching portal
				neighbor neigh = neighbor(i, l);
				v[current].n.push_back(neigh);
				return;
			}
		}
	}

	moveSouth(l + 1, x, y);
	moveNorth(l + 1, x, y);
	moveEast(l + 1, x, y);
	return;
}

void moveWest(int l, int x, int y) {
	if (l > 5000) {//path too long
		return;
	}
	x--;
	char r = A[x][y];
	if (r == '#') {//hit a wall
		return;
	}

	if (r >= 'A' && r <= 'Z') {//hit a portal
		x++;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].x1 == x && v[i].y1 == y) {//found matching portal
				neighbor neigh = neighbor(i, l);
				v[current].n.push_back(neigh);
				return;
			}
		}
	}


	moveSouth(l + 1, x, y);
	moveNorth(l + 1, x, y);
	moveWest(l + 1, x, y);
	return;
}

void traverse(int c, int l, int depth) {

	if (depth == 34) {
		return;
	}
	if (depth < 0) {
		return;
	}
	if (l > shortestPath) {
		return;
	}
	for (int i = 0; i < v[c].n.size(); i++) {
		int in = v[c].n[i].index;
		if (v[in].name.compare("AA") == 0) {
		}
		else if (v[in].name.compare("ZZ") == 0) {//we found the exit
			if (depth == 0) {
				int length = l + v[c].n[i].distance;
				if (length < shortestPath) {
					std::cout << "Found a new shortest path from " << v[c].name << " of length " << length << endl;
					shortestPath = length;
				}
			}

		}
		else {
			if (v[in].side) {
				traverse(v[in].other, l + v[c].n[i].distance + 1, depth + 1);
			}
			else {
				traverse(v[in].other, l + v[c].n[i].distance + 1, depth - 1);
			}
		}
		
	}
	return;
}

int main(int argc, char * argv[])
{
	shortestPath = 6000;
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		string s;
		int j = 0;
		while (getline(infile, s)) {
			int i = 0;
			while (i < s.size()) {
				char c = s[i];
				A[i][j] = c;

				i++;
			}
			j++;
		}



		bool b = true;
		while (b) {
			b = false;
			for (int j = 1; j < 115; j++) {//close all dead ends, including gates leading to dead ends
				for (int i = 1; i < 115; i++) {
					if (A[i][j] == '.') {
						int k = 0;
						if (A[i + 1][j] == '#') {
							k++;
						}
						if (A[i - 1][j] == '#') {
							k++;
						}
						if (A[i][j + 1] == '#') {
							k++;
						}
						if (A[i][j - 1] == '#') {
							k++;
						}

						if (k >= 3) {
							A[i][j] = '#';
							b = true;
						}
					}
				}
			}
		}

		for (int j = 0; j < 115; j++) {
			for (int i = 0; i < 115; i++) {
				std::cout << A[i][j];
				char c = A[i][j];
				if (c >= 'A' && c <= 'Z' && (A[i + 1][j] == '.' || A[i][j + 1] == '.' || A[i - 1][j] == '.' || A[i][j - 1] == '.')) {//portal
					bool side;
					if (i >= 5 && i <= 105 && j >= 5 && j <= 105) {
						b = true;
					}
					else {
						b = false;
					}
					if (A[i + 1][j] == '.') {//portal is on the left
						string s;
						s += A[i - 1][j];
						s += c;
						portal p = portal(i + 1, j, 1, s, b);//1 is EAST
						v.push_back(p);
					}
					if (A[i - 1][j] == '.') {//portal is on the right
						string s;
						s += c;
						s += A[i + 1][j];
						portal p = portal(i - 1, j, 3, s, b);//3 is WEST
						v.push_back(p);
					}
					if (A[i][j - 1] == '.') {//portal is on the bottom
						string s;
						s += c;
						s += A[i][j + 1];
						portal p = portal(i, j - 1, 0, s, b);//0 is NORTH
						v.push_back(p);
					}
					if (A[i][j + 1] == '.') {//portal is on the top
						string s;
						s += A[i][j - 1];
						s += c;
						portal p = portal(i, j + 1, 2, s, b);//2 is SOUTH
						v.push_back(p);
					}
				}
			}
			std::cout << endl;
		}


		std::cout << endl;

		for (int i = 0; i < v.size(); i++) {//find neighbors
			current = i;
			portal p = v[i];
			if (p.d1 == 0) {
				moveNorth(0, p.x1, p.y1);
			}
			else if (p.d1 == 1) {
				moveEast(0, p.x1, p.y1);
			}
			else if (p.d1 == 2) {
				moveSouth(0, p.x1, p.y1);
			}
			else if (p.d1 == 3) {
				moveWest(0, p.x1, p.y1);
			}
			std::cout << "the portal " << p.name << " on the ";
			if (p.side) {
				std::cout << "inside";
			}
			else {
				std::cout << "outside";
			}
			std::cout << " has " << v[current].n.size() << " neighbors: ";
			for (int j = 0; j < v[current].n.size(); j++) {
				int index = v[current].n[j].index;
				std::cout << v[index].name << ":" << v[current].n[j].distance << " , ";
			}
			std::cout << endl;

		}
		int start;
		for (int i = 0; i < v.size(); i++) {//match portals
			if (v[i].name.compare("AA") == 0) {
				start = i;
			}

			for (int j = 0; j < v.size(); j++) {
				if (i != j && v[i].name.compare(v[j].name) == 0) {
					v[i].other = j;
				}
			}
		}
		std::cout << endl;
		traverse(start, 0, 0);
		std::cout << "The shortest path is " << shortestPath << endl;
	}
	else {
		std::cout << "can't find file?\n";
	}
	return 0;
}