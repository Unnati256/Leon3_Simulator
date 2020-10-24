CXX = g++
EXECUTABLE = exec
CXXFLAGS = -Wall

INCDIR = include
OBJDIR = bin
SRCDIR = src

SRC = Memory.cpp Register.cpp Operation.cpp MemoryCache.cpp
OBJS = $(SRC:.cpp=.o)
HEADER = $(SRC:.cpp=.h)

$(EXECUTABLE) : Main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJDIR)/Main.o $(OBJDIR)/Memory.o $(OBJDIR)/Register.o $(OBJDIR)/Operation.o $(OBJDIR)/MemoryCache.o

Main.o : $(SRCDIR)/Main.cpp
	$(CXX) -c -o $(OBJDIR)/$@ $<

%.o : $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CXX) -c -o $(OBJDIR)/$@ $<


.PHONEY : clean run debug

clean:
	rm $(OBJDIR)/*.o $(EXECUTABLE)

run :
	./$(EXECUTABLE) traces/trace_file1.txt

debug: CXXFLAGS += -D DEBUG -g
debug: $(EXECUTABLE)