CXXFLAGS=-std=c++11

sim:src/main.o src/server.o src/control.o src/patient.o
	g++ src/main.o src/server.o src/control.o src/patient.o -o sim

main.o: src/main.cpp
	g++ -c src/main.cpp

server.o: src/server.cpp src/server.h
	g++ -c src/server.cpp

control.o: src/control.cpp src/control.h
	g++ -c src/control.cpp

patient.o: src/patient.cpp src/patient.h
	g++ -c src/patient.cpp
all:
	g++ src/main.o src/server.h
