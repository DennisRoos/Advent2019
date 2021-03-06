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


struct chemical
{
	long long q;
	string name;

	chemical(long long quantity, string n) : q(quantity), name(n) {}
};

struct reaction
{
	vector<chemical> inputs;
	chemical output;

	reaction(vector<chemical> in, chemical out) : inputs(in), output(out) {}
};

vector<reaction> reactions;
vector<chemical> needed;
vector<chemical> leftover;

void addNeeded(long long amount, string n) {
	bool b = false;
	for (auto & element : needed) {
		if (element.name.compare(n) == 0) {//found it in the needed list already
			element.q = element.q + amount;//increase amount
			b = true;
			return;
		}
	}
	if (b == false) {//wasn't in the list yet
		for (auto i = leftover.begin(); i != leftover.end(); ++i) { //check if we have leftovers
			if (i->name.compare(n) == 0) {//found it
				long long surplus = i->q - amount;
				vector<chemical>::iterator it = i;
				if (surplus > 0) {//we still have chemicals left over
					i->q = surplus;
				}
				else if (surplus == 0) {//we had exactly enough chemicals leftover
					leftover.erase(i);
				}
				else {//not enough chemicals
					leftover.erase(i);
					chemical c = chemical(surplus*-1, n);
					needed.push_back(c);
				}
				return;
			}
		}
		//not in the leftover list
		chemical c = chemical(amount, n);
		needed.push_back(c);
	}
	return;
}

long long OreAmount(long long fuel) {
	needed.clear();//reset the lists
	leftover.clear();
	chemical c = chemical(0, "ORE");
	needed.push_back(c);//note that this puts ORE at the front of the list, and we'll keep popping from the back
	c = chemical(fuel, "FUEL");
	needed.push_back(c);
	while (needed.size() > 1) {//while there's something else than ORE in the needed list, continue looping
		c = needed.back(); //grab the last element we need more of
		needed.pop_back(); //remove this chemical from the needed list
		for (auto & element : reactions) {
			if (element.output.name.compare(c.name) == 0) {//found the reaction producing this;
				reaction r = element;
				float f = (float)c.q / element.output.q;
				long long times = ceil(f);//number of times the reaction must happen
				long long remnant = (element.output.q * times) - c.q; //amount of stuff left over
				for (auto & in : r.inputs) {
					addNeeded(times * in.q, in.name);
				}
				if (remnant > 0) {
					chemical l = chemical(remnant, c.name);
					leftover.push_back(l);
				}
				break;
			}
		}
	}
	return needed[0].q;
}


int main()
{
	ifstream infile;
	infile.open("data.txt");
	if (infile.is_open())
	{
		long long r = 0;
		string s;
		string n;
		while (infile >> s)//there's another reaction in the file
		{
			vector<chemical> in;
			infile >> n;
			long long q = stoi(s);
			chemical c = chemical(q, n);
			in.push_back(c);
			while (infile >> s) {
				if (s.compare("=>") == 0) {//reached the output for this reaction
					r++;
					infile >> s;
					infile >> n;
					long long q = stoi(s);
					chemical out = chemical(q, n);
					reaction reac = reaction(in, out);
					reactions.push_back(reac);
					break;
				}
				else {//another input
					infile >> n;
					long long q = stoi(s);
					chemical c = chemical(q, n);
					in.push_back(c);
				}
			}
		}
		cout << "The amount of fuel needed for 1 fuel is " << OreAmount(1) << endl;

		//part 2
		long long i = 1637800;//yeah, this part is ugly and mostly hardcoded, I know
		long long ore = 0;
		while (ore < 1000000000000) {
			i++;
			ore = OreAmount(i);
			cout << ore << endl;
		}

		cout << "We can make " << i - 1 << " fuel with a trillion ore!" << endl;

	}
	else {
		cout << "can't find file?\n";
	}
}
