#include <iostream>
#include "../include/Memory.h"

Memory::Memory () {
	for (int i=0; i < 16384; i++) {
		memory[i] = i;
	}
}
int Memory::getValue (int mem_address) {
	return memory[mem_address];
}

void Memory::setValue (int mem_address, int value) {
	memory[mem_address] = value;
}
