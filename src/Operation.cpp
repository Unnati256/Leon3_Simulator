#include <iostream>
#include "../include/Operation.h"
using namespace std;

bool Operation::isLoad (int instruction) {
	if (instruction == 0) {
		return true;
	}
	return false;
}

bool Operation::isStore (int instruction) {
	if (instruction == 1) {
		return true;
	}
	return false;
}
