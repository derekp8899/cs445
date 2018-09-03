
sim:src/main.o src/server.o src/control.o
	g++ src/main.o src/server.o src/control.o -o sim

main.o: src/main.cpp
	g++ -c src/main.cpp

server.o: src/server.cpp src/server.h
	g++ -c src/server.cpp

control.o: src/control.cpp src/control.h
	g++ -c src/control.cpp

all:
	g++ src/main.o src/server.h
