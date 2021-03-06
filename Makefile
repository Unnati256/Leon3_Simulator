CXX = g++
EXECUTABLE = exec
CXXFLAGS = -std=c++11 -Wall

INCDIR = include
OBJDIR = bin
SRCDIR = src

SRC = Register.cpp Operation.cpp MemoryCache.cpp
OBJS = $(SRC:.cpp=.o)
HEADER = $(SRC:.cpp=.h)

$(EXECUTABLE) : Main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJDIR)/Main.o $(OBJDIR)/Register.o $(OBJDIR)/Operation.o $(OBJDIR)/MemoryCache.o

Main.o : $(SRCDIR)/Main.cpp
	$(CXX) -std=c++11 -c -o $(OBJDIR)/$@ $<

%.o : $(SRCDIR)/%.cpp $(INCDIR)/%.h 
	$(CXX) -std=c++11 -c -o $(OBJDIR)/$@ $<

.PHONEY : clean run debug

clean:
	rm $(OBJDIR)/*.o $(EXECUTABLE)

run :
	./$(EXECUTABLE) traces/f1.txt

debug: CXXFLAGS += -D DEBUG -g
debug: $(EXECUTABLE)