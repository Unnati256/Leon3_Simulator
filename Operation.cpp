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

// int main() {
// 	int ins = 1;
// 	Operation op;
// 	if (op.isLoad(ins) == true) cout << "LOAD" << endl;
// 	if (op.isStore(ins)==true) cout << "STORE" << endl;
	
// 	// cout <<"AAA     " << op.isLoad(ins) << op.isStore(ins) << endl;
// 	cout << "done";
// }