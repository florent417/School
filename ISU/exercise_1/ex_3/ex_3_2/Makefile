SOURCES=main.cpp part1.cpp part2.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.d))
CXXFLAGS=-I.
EXE=parts


#Making for host
# > make ARCH=host
ifeq (${ARCH},host)
CXX=g++
EXE_PROG=bin/host
BUILD_DIR=build/host
MKDIR=mkdir -p
endif

#Making for targets
# > make ARCH=target
ifeq (${ARCH},target)
CXX=arm-rpizw-g++
EXE_PROG=bin/target
BUILD_DIR=build/target
MKDIR=mkdir -p
endif

#.PHONY: clean all

all: $(EXE)
# << Check the $(DEPS) new dependency
$(EXE): $(DEPS) $(OBJECTS)
	$(MKDIR) $(EXE_PROG)
	$(CXX) $(CXXFLAGS) -o $(EXE_PROG)/$@ $(OBJECTS)

$(BUILD_DIR)/%.o: %.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) -c -o $@ $^

# Rule that describes how a .d
# (dependency) file is created from
# a .cpp file
# Similar to the assigment that you
# just completed %.cpp -> %.o
$(BUILD_DIR)/%.d: %.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) -MT $(addprefix $(BUILD_DIR)/, $(@:.d=.o)) -MM $(CXXFLAGS) $^ > $@

clean:
	rm -r build bin
	
ifneq (${MAKECMDGOALS},clean)
-include $(DEPS)
endif
