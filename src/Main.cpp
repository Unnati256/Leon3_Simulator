#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "../include/Register.h"
#include "../include/Memory.h"
#include "../include/Operation.h"

int main (int argc, char** argv) {
	Register registers;
	Memory memory;
	Operation operation;
	
	ifstream input_file;	// takes text file as input
	input_file.open(argv[1]);

	int instruction, mem_addr, reg_addr;
	vector<string> row; // vector to store data of a row from the file
    string line, word; 

	while (true) { // reads the file one row at a time
		if (input_file.eof()) break; // break if eof is reached
		row.clear();
		getline(input_file, line); 
		stringstream s(line); 
		while (getline(s, word, ',')) { 
            row.push_back(word); 
        } 
        instruction = stoi(row[0]);
        mem_addr = stoi(row[1]);
        reg_addr = stoi(row[2]);

        // cout << "V  " << instruction << " " << mem_addr << " " << reg_addr << "\n";
        
        if (operation.isLoad(instruction)) { // if the instruction is load
        	registers.setValue(reg_addr, memory.getValue(mem_addr));
        }
        if (operation.isStore(instruction)) { // if the instruction is store
        	memory.setValue(mem_addr, registers.getValue(reg_addr));
        }

	}

	for (int i=0; i < 32; i++) { // displaying the contents of the register
		cout << "R" << i << ":  " << registers.getValue(i) << endl;
	}
}