#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include "../include/Memory.h"

Memory::Memory () {
	for (int i=0; i < 16384; i++) {
		memory[i] = '0';
	}
}

int Memory::getByte (int mem_address) {
	// int value = memory[mem_address];
	return memory[mem_address];
}

void Memory::setByte (int mem_address, int value) {
    memory[mem_address] = value & 0xFF;
}

int Memory::getHalfWord (int mem_address) {
	int value = memory[mem_address + 1] | (memory[mem_address] << 8);
	return value;
}

void Memory::setHalfWord (int mem_address, int value) {
    memory[mem_address] = (value >> 8) & 0xFF;
    memory[mem_address + 1] = value & 0xFF;
}

int Memory::getWord (int mem_address) {
	int value = memory[mem_address+3] | (memory[mem_address + 2] << 8) | (memory[mem_address + 1] << 16) | (memory[mem_address] << 24);
	return value;
}

void Memory::setWord (int mem_address, int value) {
	memory[mem_address] = (value >> 24) & 0xFF;
    memory[mem_address + 1] = (value >> 16) & 0xFF;
    memory[mem_address + 2] = (value >> 8) & 0xFF;
    memory[mem_address + 3] = value & 0xFF;
}
