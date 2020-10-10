#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include <sstream> 
#include <fstream> 
#include "../include/Memory.h"

using namespace std;

Memory::Memory () {
	myFile.open("mem.bin", ios::in | ios::out | ios::binary);
}

int Memory::getByte (int mem_address) {
	unsigned char mem_content;
	myFile.seekg(mem_address, ios::beg); 
	myFile.read(reinterpret_cast< char *>(&mem_content), sizeof(mem_content));
	int value = mem_content;
	return value;
}

void Memory::setByte (int mem_address, int value) {
	unsigned char memory;
	myFile.seekp(mem_address, ios::beg);
    myFile.write(reinterpret_cast< char *>(&memory), sizeof(memory));
}

int Memory::getHalfWord (int mem_address) {
	unsigned char mem_contents[2];
	myFile.seekg(mem_address, ios::beg); 
	myFile.read(reinterpret_cast< char *>(mem_contents), sizeof(mem_contents));
	int value = mem_contents[1] | (mem_contents[0] << 8);
	return value;
}

void Memory::setHalfWord (int mem_address, int value) {
    unsigned char memory[2];
    memory[0] = (value >> 8) & 0xFF;
    memory[1] = value & 0xFF;
    for (int i = 0; i < 2; i++) {
    	myFile.seekp(mem_address, ios::beg);
    	myFile.write(reinterpret_cast< char *>(&memory[i]), sizeof(memory[0]));
    	mem_address++;
    }
}

int Memory::getWord (int mem_address) {
	unsigned char mem_contents[4];
	myFile.seekg(mem_address, ios::beg); 
	myFile.read(reinterpret_cast< char *>(mem_contents), sizeof(mem_contents));
	int value = mem_contents[3] | (mem_contents[2] << 8) | (mem_contents[1] << 16) | (mem_contents[0] << 24);
	return value;
}

void Memory::setWord (int mem_address, int value) {
	unsigned char memory[4];
	memory[0] = (value >> 24) & 0xFF;
    memory[1] = (value >> 16) & 0xFF;
    memory[2] = (value >> 8) & 0xFF;
    memory[3] = value & 0xFF;
    for (int i = 0; i < 4; i++) {
    	myFile.seekp(mem_address, ios::beg);
    	myFile.write(reinterpret_cast< char *>(&memory[i]), sizeof(memory[0]));
    	mem_address++;
    }
}
