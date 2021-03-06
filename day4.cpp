#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <chrono> 

using namespace std;
using namespace std::chrono;

int main(int argc, char * argv[]){
	auto start = high_resolution_clock::now();

	int count = 0;
	for (int a = 3; a < 8; a++) {
		for (int b = a; b < 10; b++) {
			for (int c = b; c < 10; c++) {
				for (int d = c; d < 10; d++) {
					for (int e = d; e < 10; e++) {
						for (int f = e; f < 10; f++){
							if (((a == b && b != c) || (b == c && c != d && a != b) || (c == d && (d != e && b != c)) || 
								(d == e && (c != d && e != f)) || (d != e && e == f)) && (a*100 + b*10 + c >=347)) {
								count++;
							}
						}
					}
				}
			}
		}
	}
	auto stop = high_resolution_clock::now();
	cout << "final solution is: " << count << "\n";

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
}