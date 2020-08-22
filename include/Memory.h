#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string.h>

class Memory {
private:
	unsigned char memory[16384];
	
public:
	Memory();
	int getValue (int mem_address);// { return memory[mem_address];}
	void setValue (int mem_address, int value);
};

#endif