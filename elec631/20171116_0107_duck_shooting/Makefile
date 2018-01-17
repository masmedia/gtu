# Locations of gcc and g++ compilers are assigned to CC and CXX variables
CC  = /usr/bin/gcc
CXX = /usr/bin/g++

CXXFLAGS = -Wall -g -std=c++11

MKDIR_P = mkdir -p
DIRS = ./bin obj

COPYSOURCES = cp src/*.cpp . | cp include/*.hpp .
MOVEOBJECTS = mv *.o ./obj | mv build_exec ./bin

default: build_exec
	$(MAKE) run
	${MKDIR_P} ${DIRS}
	${MOVEOBJECTS}
	$(MAKE) clean

copy:
	${COPYSOURCES}

build_exec: copy main.o Monte_Carlo_Simulation.o
	$(CXX) $(CXXFLAGS) -o build_exec *.o

run: build_exec
	./build_exec

clean:
	rm -rf *.cpp *.hpp *.o build_exec

Matrix.o : Matrix.hpp Matrix.cpp
	$(CXX) $(CXXFLAGS) -c Matrix.cpp

Linear_Spacing.o: Linear_Spacing.hpp Linear_Spacing.cpp
	$(CXX) $(CXXFLAGS) -c Linear_Spacing.cpp

Monte_Carlo_Simulation.o : Monte_Carlo_Simulation.hpp Monte_Carlo_Simulation.cpp Linear_Spacing.o Matrix.o
	$(CXX) $(CXXFLAGS) -c Monte_Carlo_Simulation.cpp

main.o: main.cpp Monte_Carlo_Simulation.o
	$(CXX) $(CXXFLAGS) -c main.cpp
