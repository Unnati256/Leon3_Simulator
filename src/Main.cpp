#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "../include/Register.h"
#include "../include/Operation.h"
#include "../include/MemoryCache.h"

int main (int argc, char** argv) {
	Register registers;
	Operation operation;
	MemoryCache memoryCache;
	
	ifstream input_file;	// takes text file as input
	input_file.open(argv[1]);

    long num_instructions = 0; // to count the number of instructions

	int instruction, reg_addr = 1, bytes_read;
	long mem_addr, program_counter;
	vector<string> row; // vector to store data of a row from the file
    string line, word; 

	while (true) { // reads the file one row at a time
		if (input_file.eof()) break; // break if eof is reached
		row.clear();
		getline(input_file, line); 
		stringstream s(line); 
        if (line.empty())
        {
            continue;
        }
		while (getline(s, word, ',')) { 
            row.push_back(word); 
        } 
        instruction = stoi(row[0]);

        stringstream s1; 
    	s1 << std::hex << row[1]; 
    	s1 >> program_counter; 

        stringstream s2; 
    	s2 << std::hex << row[2]; 
    	s2 >> bytes_read;

    	stringstream s3; 
    	s3 << std::hex << row[3]; 
    	s3 >> mem_addr;

        // cout << "V  " << instruction << " " << mem_addr << " " << reg_addr << "\n";
        
        if (operation.isLoad(instruction)) { // if the instruction is load
        	// cout << "MAIN ISLOAD " << bytes_read << endl;
        	if (bytes_read == 8) {
        		registers.setDoubleValue(reg_addr, memoryCache.getDoubleWord(mem_addr));
        	}
        	else if (bytes_read == 4) {
        		registers.setValue (reg_addr, memoryCache.getWord(mem_addr));
        	}
        	else if (bytes_read == 2) {
        		registers.setValue (reg_addr, memoryCache.getHalfWord(mem_addr));
        	}
        	else if (bytes_read == 1) {
        		registers.setValue (reg_addr, memoryCache.getByte(mem_addr));
        	}
        }
        if (operation.isStore(instruction)) { // if the instruction is store
        	// cout << "MAIN ISSTORE " << bytes_read << endl;
        	if (bytes_read == 8) {
        		memoryCache.setDoubleWord(mem_addr, registers.getDoubleValue(reg_addr));
        	}
        	else if (bytes_read == 4) {
        		memoryCache.setWord (mem_addr, registers.getValue(reg_addr));
        	}
        	else if (bytes_read == 2) {
        		memoryCache.setHalfWord (mem_addr, registers.getValue(reg_addr));
        	}
        	else if (bytes_read == 1) {
        		memoryCache.setByte (mem_addr, registers.getValue(reg_addr));
        	}
        }
        num_instructions++;
	}

	memoryCache.WriteBackToMem();

	for (int i=0; i < 32; i++) { // displaying the contents of the register
		cout << "R" << i << ":  " << registers.getValue(i) << endl;
	}
	
    cout << "Total number of instructions:  " << num_instructions << endl;
	cout << "No. of hits:  " << memoryCache.GetHits() << endl;
	cout << "Total time taken: " << memoryCache.FindTimeTaken() << endl;

}