# Leon3_Simulator

<h2> A cycle accurate Leon3 simulator in C++ </h2>

The project at present, is a simple model of the main memory and registers. The model consists of a total of 32 word-addressable registers, and a byte-addressable  memory of size 2^14 (the required size is 2^32. The changes will be done in the course of development).

The inputs to the program are text files (in the "traces" folder), which contain 3 comma-separated columns- the first column contains 0 for load and 1 for store, and the second and third columns contain the addresses of the memory and register respectively. Consider a file containing the following 3 lines:<br>
0,1234,1<br>
1,2345,3<br>
0,2345,4<br>
The first line begins with a 0. So it represents a load. The load address is 1234, and the value read from memory will be placed in register r1.<br>
The second line begins with a 1. So it represents a store. The store address is 2345, and the value written to memory will be taken from register r3.<br>
The third line begins with a 0. So it represents a load. The load address is 2345, and the value read from memory will be placed in register r4.<br>

Files:

<ul> 
<li> traces: contains all the trace files which are given as an argument in the command line itself.</li>
<li> src: contains all the cpp files.</li>
<li> include: contains all the headers.</li>
<li> bin: contains the compiled binariy files.</li>
</ul>


The repository consists of a Makefile to compile the code. "make run" command after successful compilation runs the code for the first input file in the traces folder.
