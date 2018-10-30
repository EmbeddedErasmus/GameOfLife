CFLAGS=-Wall -Wextra -lm -pg 
LDLIBS=-lncurses -lmenu

game_of_life: main.o cell.o configuration.o menu_display.o
	gcc $(CFLAGS) cell.o main.o configuration.o menu_display.o -o bin/game_of_life $(LDLIBS)
	
cell.o: cell.c cell.h

configuration.o: configuration.c configuration.h

main.o : main.c 

menu_display.o: menu_display.c menu_display.h


clean:
	rm -rf bin/game_of_life 
	rm -rf *o game_of_life
  
