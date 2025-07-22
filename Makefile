#compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

#files
TARGET = fsm_test
SRCS = fsm.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

#default rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

#clean rule
clean:
	rm -f $(OBJS) $(TARGET) *.o