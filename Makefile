# Compiler settings - Use the system's default C++ compiler.
CXX ?= g++

# Use this line instead if you want to explicitly rely on environment variable `CXX`
# If not set, it will fall back to `g++`.
# CXX := $(or $(CXX),g++)

CXXFLAGS = -I./src -std=c++14 -Wall
# Test settings
TEST_TARGET = TestRunner
TEST_SOURCES = tests/main.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# To obtain object files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Test command to build and run tests
test: $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) $(OBJECTS) -o $(TEST_TARGET)
	./$(TEST_TARGET)


