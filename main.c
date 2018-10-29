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
	int fsize = 20;

	cell **field;
	initscr();

	field = calloc(LINES, sizeof(cell *));
	for(i = 0;i < LINES; i++)
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

	for (i = 0; i < fsize; ++i)
		free(field[i]); //  free each array of cells d
	free(field); // free the array of pointers field

	endwin();
 
 endwin();

 return 0;
}
