# Locations of gcc and g++ compilers are assigned to CC and CXX variables
CC  = /usr/bin/gcc
CXX = /usr/bin/g++ 

CXXFLAGS = -Wall -g -std=c++11

build_exec: main.o Linear_Spacing.o Matrix.o
	$(CXX) $(CXXFLAGS) -o build_exec main.o Matrix.o Linear_Spacing.o

Matrix.o : Matrix.hpp Matrix.cpp
	$(CXX) $(CXXFLAGS) -c Matrix.cpp

Linear_Spacing.o: Linear_Spacing.hpp Linear_Spacing.cpp
	$(CXX) $(CXXFLAGS) -c Linear_Spacing.cpp

main.o: main.cpp Matrix.o Linear_Spacing.o
	$(CXX) $(CXXFLAGS) -c main.cpp

run: build_exec
	./build_exec

clean: build_exec
	rm -rf *.o build_exec
