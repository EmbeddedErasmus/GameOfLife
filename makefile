CFLAGS=-g -lm -Wall -Wextra 
LDLIBS=-lncurses -lmenu

game_of_life: main.o cell.o configuration.o
	gcc cell.o main.o configuration.o -o bin/game_of_life -lncurses -lmenu
	
cell.o: cell.c cell.h

configuration.o: configuration.c configuration.h

main.o : main.c 



