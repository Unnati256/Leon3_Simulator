#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
	int memory[16384];
	
public:
	Memory();
	int getValue (int mem_address);// { return memory[mem_address];}
	void setValue (int mem_address, int value);
};

#endif