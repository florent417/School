# @all @program @clean @help
SOURCES = vectorMain.cpp Vector.cpp
LIBS =-lpthread
OBJECTS	= $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
DEPS	= $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.d))
EXEC = program
CXX = g++
CXXFLAGS = -I. -ggdb
BUILD_DIR =build
EXEC_DIR =bin
MKDIR = mkdir -p

.PHONY: clean all

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(MKDIR) $(EXEC_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJECTS) $(LIBS)

$(BUILD_DIR)/%d: %cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) -MT$(addprefix $(BUILD_DIR)/,$(@:.d=.o)) -MM $(CXXFLAGS) $^ > $@

$(BUILD_DIR)/%.o: %.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) -c -o $@ $^

clean:
	@rm -rfv $(BUILD_DIR) $(EXEC_DIR) *.d *.o $(EXEC)

help:
	@echo "Available targets@:"
	@echo "	all"
	@echo "	program"
	@echo "	clean"
	@echo "	help"

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif
