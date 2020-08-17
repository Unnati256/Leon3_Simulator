COMPILER = g++
EXECUTABLE = exec


$(EXECUTABLE) : Main.o Memory.o Register.o Operation.o
	$(COMPILER) -o $(EXECUTABLE) bin/Main.o bin/Memory.o bin/Register.o bin/Operation.o

Main.o : src/Main.cpp
	$(COMPILER) -c -o bin/Main.o src/Main.cpp

Memory.o : src/Memory.cpp include/Memory.h
	$(COMPILER) -c -o bin/Memory.o src/Memory.cpp

Register.o : src/Register.cpp include/Register.h
	$(COMPILER) -c -o bin/Register.o src/Register.cpp

Operation.o : src/Operation.cpp include/Operation.h
	$(COMPILER) -c -o bin/Operation.o src/Operation.cpp 

.PHONEY : clean run

clean:
	rm bin/*.o $(EXECUTABLE)

run :
	./$(EXECUTABLE) traces/trace_file1.txt