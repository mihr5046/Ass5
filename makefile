# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -Wpedantic -g -std=c++17 -MMD -MP

# Target executable
TARGET = slm

# For deleting the target
TARGET_DEL = slm.exe

# Source files
SRCS = src/main.cpp src/textReader.cpp


# Object files
OBJS = $(SRCS:.cpp=.o)

# Dependency files
DEPS = $(OBJS:.o=.d)

# Default rule to build and run the executable
all: $(TARGET)

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to compile .cpp files into .o files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include automatically generated header dependencies
-include $(DEPS)

# Clean rule to remove generated files
clean:
	rm -f $(TARGET_DEL) $(OBJS) $(DEPS)

.PHONY: all clean
