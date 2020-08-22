#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include "../include/Memory.h"

Memory::Memory () {
	for (int i=0; i < 16384; i++) {
		memory[i] = '0';
	}
}

int Memory::getValue (int mem_address) {
	int temp;
	std::string value_str;
	for(int i = mem_address; i < mem_address + 4; i++){
		temp = (int) memory[i];
		value_str = value_str + std::bitset<8>(temp).to_string();
	}
	int value = stoi(value_str, 0, 2);
	return value;
}

void Memory::setValue (int mem_address, int value) {
	std::string binary = std::bitset<32>(value).to_string();
	int k = -1;
	std::string stemp = "";
	for (int i = 0; i < 32; i++) {
		stemp = stemp + binary[i];
		if (i % 8 == 7) {
			k++;
			memory[mem_address + k] = static_cast<unsigned char>(std::bitset<8>(stemp).to_ulong());
			stemp = "";
		}
	}
}
