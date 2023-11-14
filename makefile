CC=gcc
CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic
proj4.x: proj4_driver.o bst.h bst.hpp 
	$(CXX) $(CXXFLAGS) -o $@ proj4_driver.o

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f *.o *.x core.*

%.x : %.c
	$(CC) -o $@ $<
%.x : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


