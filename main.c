/*
 * Project: Conway's Game of Life
 *
 * Course: Embedded and Real Time Systems
 * Author: Bernardo Amaral, José Conceição, Marceau Fillon, Aleksander Poverud Tokle
 *
 * Project Explanation: The universe of the Game of Life is an infinite two-dimensional
 * orthogonal grid of square cells. Each cell is in one of two possible states, alive 
 * or dead. Every cell interacts with its eight neighbours. At each step in time, the 
 * following transitions occur:
 * 1-> Any live cell withfewer than two live neighbours dies, as if caused by 
 * 	   under-population.
 * 2-> Any live cell with two or three live neighbours lives on to the next
 * 	   generation.
 * 3-> Any live cell with more than three live neighbours dies, as if by
 *     over-population.
 * 4-> Any dead cell with exactly three live neighbours becomes a live cell, as if by
 *     reproduction.
 *
 */

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>

#include "cell.h"
#include "menu_display.h"

#define CTRLD 	4

int main()
{
	// ***** Declaration of the variables *****
	char welcomeMessage[]="Welcome to the Game Of Life";		/* message to be appeared on the screen */
	char namesMessage[]="By Bernardo Amaral, José Conceição, Marceau Fillon, Aleksander Poverud Tokle";

	int i=0; // Number of choices for configuration and counter for for loop
	int fsize = 40;

	cell **field;
	initscr(); // Start curses mode

	// ********  Allocating a 2D array of cell *******
	field = calloc(LINES, sizeof(cell *)); // Allocale an array of pointers of cell type
	if (field == NULL ) // Detect memory leaks
		{return -1 ; }
	for(i = 0;i < LINES; i++) // Allocate an array of cells and assign to each of the pointers of the array of pointers
		field[i] = calloc(COLS, sizeof(cell));

	//*******************************************
	//Welcome window
	initscr();				/* start the curses mode */
	//First screen *******************************************************
	mvprintw(LINES/2,(COLS-strlen(welcomeMessage))/2,"%s",welcomeMessage);
	/* print the message at the center of the screen */                              	
	mvprintw(LINES/2 +1,(COLS-strlen(namesMessage))/2,"%s",namesMessage);

	refresh();
	getch(); //Just waiting for user to press something
	//*******************************************************************
	
	display_menu(field);

	// Freeing the memory reserved **************************************
	for (i = 0; i < fsize; ++i)
	{
	free(field[i]); //  free each array of cells d
	}

	free(field); // free the array of pointers field
	//*******************************************************************

	endwin(); // End curses mode	
	endwin();

 return 0;
}
