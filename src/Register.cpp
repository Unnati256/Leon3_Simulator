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

long Register::getDoubleValue (int reg_address) {
	long result = (long)registers[reg_address + 1] | (long)(registers[reg_address]) << 32; 
	return result;
}

void Register::setDoubleValue (int reg_address, long value) {
	int v1 = (int)(value >> 32);
    int v2 = (int)value;
    registers[reg_address] = v1;
    registers[reg_address+1] = v2;
}