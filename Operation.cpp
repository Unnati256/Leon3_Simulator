#include <iostream>
using namespace std;

class Operation {

public:
	bool isLoad (int instruction) {
		if (instruction == 0) {
			return true;
		}
		return false;
	}

	bool isStore (int instruction) {
		if (instruction == 1) {
			return true;
		}
		return false;
	}
};