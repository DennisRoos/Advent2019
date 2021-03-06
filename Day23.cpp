#include <iostream>
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include <cmath>
#include <queue>         
#include <chrono> 
using namespace std;
using namespace std::chrono;

long long B[2500];
int l;

long long NATx;
long long NATy;

struct message {
	long long x;
	long long y;
	message( long long xx, long long yy): x(xx), y(yy){}
};

class intcode {
public:
	int runProgram();
	void initialize(int id);

	bool idle;
	long long Mem[5000];
	queue<message> packets;
	int ID;

	intcode()//empty constructor
	{
		
	}
private:
	long long getReadValue(long long parameter);
	long long getWriteAddress(long long parameter);
	bool IDProvided;
	int opcode;
	long long ip;
	long long rel;
};

intcode network[50];

void intcode::initialize(int id) {
	ip = 0;
	rel = 0;
	ID = id;
	idle = false;
	IDProvided = false;
	for (int i = 0; i < l; i++) {
		Mem[i] = B[i];
	}
	cout << endl;
}

void sendPacket(int sender, int recipient, message packet) {
	cout << "NIC " << sender << " -> " << recipient << " x: " << packet.x << " y: " << packet.y << endl;
	if (recipient == 255) {//we found the message we wanted
		NATx = packet.x;
		NATy = packet.y;
	}
	else {
		network[recipient].packets.push(packet);
	}
	return;
}

long long intcode::getReadValue(long long parameter) {
	long long value;
	if (opcode % 10 == 1) {//immediate mode
		value = parameter;
	}
	else if (opcode % 10 == 2) {//relative mode
		value = Mem[parameter + rel];
	}
	else {
		value = Mem[parameter];
	}
	opcode = opcode / 10;
	return value;
}

long long intcode::getWriteAddress(long long parameter) {
	long long address;
	if (opcode % 10 == 0) {//just as before
		address = parameter;
	}
	else {
		address = parameter + rel;
	}
	opcode = opcode / 10;
	return address;
}

int intcode::runProgram() {
	idle = true;
	long long op;
	bool empty = false;
	bool Xprovided = false;
	int process = 0;
	int recipient;
	long long x;
	long long y;
	while (true) {
		opcode = Mem[ip] / 100;
		op = Mem[ip] % 100;
		if (op == 1) {//addition
			Mem[getWriteAddress(Mem[ip + 3])] = getReadValue(Mem[ip + 1]) + getReadValue(Mem[ip + 2]);
			ip = ip + 4;
		}
		else if (op == 2) {//multiplication
			Mem[getWriteAddress(Mem[ip + 3])] = getReadValue(Mem[ip + 1]) * getReadValue(Mem[ip + 2]);
			ip = ip + 4;
		}
		else if (op == 3) {//input
			if (IDProvided) {
				if (packets.empty()) {
					if (empty) {
						return -3;//pause and let other computers produce packages
					}
					else {//first request for input when queue is empty
						Mem[getWriteAddress(Mem[ip + 1])] = -1;
						empty = true;
					}
				}
				else {//there are packets available
					if (Xprovided) {
						Mem[getWriteAddress(Mem[ip + 1])] = packets.front().y;
						packets.pop();//packet handled, delete it from queue
					}
					else {
						Mem[getWriteAddress(Mem[ip + 1])] = packets.front().x;
					}
					Xprovided = !Xprovided;
				}
			}
			else {
				Mem[getWriteAddress(Mem[ip + 1])] = ID;
				IDProvided = true;
			}
			ip = ip + 2;
		}
		else if (op == 4) {//output
			long long r = getReadValue(Mem[ip + 1]);
			ip = ip + 2;
			if (process == 0) {
				recipient = r;
				process++;
			}
			else if (process == 1) {
				x = r;
				process++;
			}
			else {
				process = 0;
				y = r;
				message packet = message(x, y);
				sendPacket(ID, recipient, packet);
				idle = false;
			}
		}
		else if (op == 5) {//jump if true
			if (getReadValue(Mem[ip + 1]) != 0) {
				ip = getReadValue(Mem[ip + 2]);
			}
			else {
				ip = ip + 3;
			}
		}
		else if (op == 6) {//jump if false
			if (getReadValue(Mem[ip + 1]) == 0) {
				ip = getReadValue(Mem[ip + 2]);
			}
			else {
				ip = ip + 3;
			}
		}
		else if (op == 7) {//less than
			if (getReadValue(Mem[ip + 1]) < getReadValue(Mem[ip + 2])) {
				Mem[getWriteAddress(Mem[ip + 3])] = 1;
			}
			else {
				Mem[getWriteAddress(Mem[ip + 3])] = 0;
			}
			ip = ip + 4;
		}
		else if (op == 8) {//equals
			if (getReadValue(Mem[ip + 1]) == getReadValue(Mem[ip + 2])) {
				Mem[getWriteAddress(Mem[ip + 3])] = 1;
			}
			else {
				Mem[getWriteAddress(Mem[ip + 3])] = 0;
			}
			ip = ip + 4;
		}
		else if (op == 9) {//change relative base
			rel = rel + getReadValue(Mem[ip + 1]);
			ip = ip + 2;
		}

		else if (op == 99) {//end program
			cout << "Program complete!\n";
			return -99;
		}
		else {
			cout << "Invalid opcode! " << op << endl;
			return -1;
		}
	}
}

bool Idle() {
	for (int i = 0; i < 50; i++) {
		if (network[i].idle == false) {
			return false;
		}
	}

}

int main()
{
	ifstream infile;
	int sendY = -1;
	infile.open("data.txt");
	l = 0;
	if (infile.is_open())
	{
		long long num;
		while (infile >> num)
		{
			B[l] = num;
			l++;
		}
		for (int i = 0; i < 50; i++) {//initialize all computers
			network[i].initialize(i);
		}

		while (true) {
			for (int i = 0; i < 50; i++) {
				cout << "Running computer " << i << endl;
				network[i].runProgram();
			}
			if (Idle()) {
				if (NATy == sendY) {
					cout << "the first repeated Y is " << NATy << endl;
					return 0;
				}
				message m = message(NATx, NATy);
				sendPacket(255, 0 ,m);
				sendY = NATy;
			}
		}

	}
	else {
		cout << "can't find file?\n";
	}
}
