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


int main(int argc, char * argv[])
{
	int count = 0;
	
	for (int b = 4; b < 10; b++) {
		for (int c = b; c < 10; c++) {
			for (int d = c; d < 10; d++) {
				for (int e = d; e < 10; e++) {
					for (int f = e; f < 10; f++) {
						if ((b == c && c != d) || ( c == d && (d != e && b != c)) || ( d == e && (c != d && e != f)) || (d != e && e == f)){
							if (b == 4) {
								if (c >= 7) {
									cout << b << c << d << e << f << endl;
									count++;
								}
							}
							else {
								count++;
								cout << b << c << d << e << f << endl;
							}
						}
					}
				}
			}
		}
	}

	for (int a = 4; a < 8; a++) {
		for (int b = a; b < 10; b++) {
			for (int c = b; c < 10; c++) {
				for (int d = c; d < 10; d++) {
					for (int e = d; e < 10; e++) {
						for (int f = e; f < 10; f++){
							if ((a == b && b != c) || (b == c && c != d && a != b) || (c == d && (d != e && b != c)) || (d == e && (c != d && e != f)) || (d != e && e == f)) {
								count++;
							}
						}
					}
				}
			}
		}
	}

	cout << "final solution is: " << count << "\n";
}