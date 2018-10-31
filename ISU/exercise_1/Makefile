#Executable
EXE=hello

#Compiler
CXX=g++

#Avoids conflict with files
#of the same name
.PHONY: clean

all: $(EXE)

$(EXE): hello.cpp
			$(CXX) -cpp $< -o $@

clean:
			rm $(EXE) *.o

help:
			@echo "Available targets"
			@echo "hello"
