
inv:src/inventory.o src/simlib.o
	gcc src/inventory.o src/simlib.o -lm -o inv

inventory:src/inventory.c
	gcc src/inventory.c -c

simlib:src/simlib.c src/simlibdefs.h src/simlib.h
	gcc src/simlib.c -c
