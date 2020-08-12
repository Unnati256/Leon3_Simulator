#include <iostream>
using namespace std;

class Memory {
private:
	int memory[16384];
	
public:	
	int getValue (int mem_address) {
		return memory[mem_address];
	}

	void setValue (int mem_address, int value) {
		memory[mem_address] = value;
	}
};
