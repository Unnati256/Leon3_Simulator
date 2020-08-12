#include <iostream>
using namespace std;

class Register {
private:
	int registers[32];

public:
	int getValue (int reg_address) {
		return registers[reg_address];
	}

	void setValue (int reg_address, int value) {
		registers[reg_address] = value;
	}
};