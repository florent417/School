#Executable
EXE=main

#ALl sources
SOURCES= main.cpp #part1.cpp part2.cpp

#output filer
OBJECTS= $(SOURCES:.cpp=.o)

#Compiler
CXX=g++

#Avoids conflict with files
#of the same name
.PHONY: clean

all: $(EXE)

$(EXE): main.o #part1.o part2.o
	$(CXX) -o $(EXE) $^ -lncurses

main.o: $(SOURCES) #part1.h part2.h
	$(CXX) -c main.cpp -o $@

#part1.o: part1.cpp part1.h
#	$(CXX) -c part1.cpp -o $@

#part2.o: part2.cpp part2.h
#	$(CXX) -c part2.cpp -o $@

clean:
	rm -f $(EXE) *.o

help:
	@echo "Available targets"
	@echo "all"
	@echo "clean"
	@echo "help"
