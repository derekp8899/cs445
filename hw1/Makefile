
sim:src/main.o src/server.o
	g++ src/main.o src/server.o -o sim

main.o: src/main.cpp
	g++ -c src/main.cpp

server.o: src/server.cpp src/server.h
	g++ -c src/server.cpp

all:
	g++ src/main.o src/server.h
