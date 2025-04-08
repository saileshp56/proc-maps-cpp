# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Filesystem library
LDFLAGS = -lstdc++fs

SRCS = main.cpp src/ProcessMap.cpp src/MapRange.cpp
OBJS = $(SRCS:.cpp=.o)

INCLUDES = -I.

TARGET = process_maps_test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

main.o: main.cpp include/proc_maps/ProcessMap.hpp include/proc_maps/MapRange.hpp
src/ProcessMap.o: src/ProcessMap.cpp include/proc_maps/ProcessMap.hpp include/proc_maps/MapRange.hpp
src/MapRange.o: src/MapRange.cpp include/proc_maps/MapRange.hpp

.PHONY: all clean test debug