CXX = g++
CXXFLAGS = -Wall

.PHONY: all clean

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f main
