# Leon3_Simulator

<h2> A cycle accurate Leon3 simulator in C++ </h2>

The project at present, is a simple model of the main memory and registers. The model consists of a total of 32 word-addressable registers, and a byte-addressable  memory of size 2^14 (the required size is 2^32. The changes will be done in the course of development).

The inputs to the program are text files (in the "traces" folder), which contain 4 comma-separated columns- the first column contains 0 for load and 1 for store, the second column contains the program counter address, the third ccolumn tells about the number of bytes requested from the memory, and the fouth column contains the address of the memory the data is to be fetched from. Consider a file containing the following 3 lines:<br>
0,0x428562,0x8,0x424360<br>
1,0x42857f,0x8,0x424368<br>
0,0x428603,0x8,0x424098<br>
The first line begins with a 0. So it represents a load. The load address is 0x424360, and the value read from memory will be placed in register r1.<br>
The second line begins with a 1. So it represents a store. The store address is 0x424368, and the value written to memory will be taken from register r1.<br>
The third line begins with a 0. So it represents a load. The load address is 0x424098, and the value read from memory will be placed in register r1.<br>

Files:

<ul> 
<li> traces: contains all the trace files which are given as an argument in the command line itself.</li>
<li> src: contains all the cpp files.</li>
<li> include: contains all the headers.</li>
<li> bin: contains the compiled binariy files.</li>
</ul>


The repository consists of a Makefile to compile the code. "make run" command after successful compilation runs the code for the first input file in the traces folder.
