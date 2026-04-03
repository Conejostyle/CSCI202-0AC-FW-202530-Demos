all: process.o
	g++ -pedantic-errors main.cpp process.o -g -o main
process.o: process.h process.cpp
	g++ -pedantic-errors process.cpp -g -o process.o -c