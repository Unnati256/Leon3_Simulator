#include <iostream>
#include "../include/Register.h"

Register::Register() {
	for (int i=0; i < 32; i++) {	// assigning values to registers to check the program
		registers[i] = i;
	}
}
int Register::getValue (int reg_address) {
	return registers[reg_address];
}

void Register::setValue (int reg_address, int value) {
	registers[reg_address] = value;
}
