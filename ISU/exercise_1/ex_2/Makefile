# Source files
SOURCES=main.cpp part1.cpp part2.cpp
# Object files
OBJECTS=$(SOURCES:.cpp=.o)
# Dependency files
DEPS=$(SOURCES:.cpp=.d)
# Name og executable
EXE=prog
# Compiler flags
CXXFLAGS=-I.
# Compiler
CXX=g++
#.PHONY targets
#.PHONY: clean
# Default target
#all: $(EXE)
# Default target derivative
$(EXE): $(DEPS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)
# Uses compiler flags to get a list of the #included
# files inside the .cpp file (.h etc.)
%.d: %.cpp
	$(CXX) -MT $(@:.d=.o) -MM $(CXXFLAGS) $^ > $@
# Removes object files og executable while suppressing errors
clean:
	rm -f *.o *.d $(EXE)
# Outputs targets with descriptive text
help:
	@echo "Target\tDescription"
	@echo "all\tBuilds default target"
	@echo "clean\tRemoves object files, dependencies and executable"
	@echo "help\tPrints targets with description"
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif
