#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include "../include/Memory.h"

Memory::Memory () {
	for (int i=0; i < 16384; i++) {
		memory[i] = "0";
	}
}

int getAddressMod4 (int mem_address) {
	if (mem_address % 4 == 1) mem_address = mem_address - 1;
	else if (mem_address % 4 == 2) mem_address = mem_address - 2;
	else if (mem_address % 4 == 3) mem_address = mem_address - 3;
	return mem_address;
}

int Memory::getValue (int mem_address) {
	mem_address = getAddressMod4(mem_address);
	std::string value_str = memory[mem_address] + memory[mem_address + 1] + memory[mem_address + 2] + memory[mem_address + 3];
	int value = stoi(value_str, 0, 2);
	return value;
}

void Memory::setValue (int mem_address, int value) {
	std::string binary = std::bitset<32>(value).to_string();
	mem_address = getAddressMod4(mem_address);
	int k = -1;
	for (int i = 0; i < 32; i++) {
		if (i % 8 == 0) {
			k++;
			memory[mem_address + k] = "";
		}
		memory[mem_address + k] = memory[mem_address + k] + binary[i];
	}
}
