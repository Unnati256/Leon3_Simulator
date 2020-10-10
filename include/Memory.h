#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string.h>
<<<<<<< HEAD
#include <fstream>

class Memory {
private:
	std::fstream myFile;

=======

class Memory {
private:
	unsigned char memory[16384];
>>>>>>> 4ef1193d0ea3f085577dc6dac1efeadd42318499
	
public:
	Memory();
	
	int getByte (int mem_address);// { return memory[mem_address];}
	void setByte (int mem_address, int value);

	int getHalfWord (int mem_address);
	void setHalfWord (int mem_address, int value);
	
	int getWord (int mem_address);
	void setWord (int mem_address, int value);
	
	int getDoubleWord (int mem_address);
	void setDoubleWord (int mem_address, int value);
};

#endif