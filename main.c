#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>

#include "cell.h"
#include "configuration.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

int main()
{
	// ***** Declaration of the variables *****
	char welcomeMessage[]="Welcome to the Game Of Life";		/* message to be appeared on the screen */
	char namesMessage[]="By blabla1 blabla2 blabla3 blabla4";

	int inic_x =0; // to store the number of rows and 
	int inic_y =0; // the number of colums of the screen 
	int final_x =0;
	int final_y =0;
	int key_played_on_menu;	//Int to nagvigate in the menu
	int n_choices, i=0, j=0; // Number of choices for configuration and counter for for loop
	int fsize = 20;
						 

	ITEM **configurations_choice; // list of configuration choices
	ITEM *current_menu_item; 

	MENU *configuration_menu; //configuration menu pointer

	cell **field;
	initscr();
	getmaxyx(stdscr,final_x,final_y);
	printw("LINES: %d \n", LINES);
	printw("COLS: %d \n", COLS);
	field = calloc(LINES, sizeof(cell *));
	for(i = 0;i < LINES; i++)
		field[i] = calloc(COLS, sizeof(cell));

	//*******************************************
	//Welcome window

	initscr();				/* start the curses mode */
	getmaxyx(stdscr,final_x,final_y);		/* get the number of rows and columns */

	//First screen *******************************************************
	mvprintw(final_x/2,(final_y-strlen(welcomeMessage))/2,"%s",welcomeMessage);
	                                	/* print the message at the center of the screen */
	mvprintw(final_x/2 +1,(final_y-strlen(namesMessage))/2,"%s",namesMessage);

	refresh();
	getch(); //Just waiting for user to press something
	//*******************************************************************
	erase();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
		
	n_choices = ARRAY_SIZE(configuration_choices);
	configurations_choice = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

	for(i = 0; i < n_choices; ++i)
		configurations_choice[i] = new_item(configuration_choices[i], configuration_choices[i]);
	configurations_choice[n_choices] = (ITEM *)NULL;

	configuration_menu = new_menu((ITEM **)configurations_choice);
	mvprintw(LINES - 2, 0, "F4 to Exit"); //Print at the bottom how to quit the window to go back to the terminal
	post_menu(configuration_menu); //Display the menu
	refresh();

	while((key_played_on_menu = getch()) != KEY_F(4))
	{   switch(key_played_on_menu)
	    {	case KEY_DOWN:
		        menu_driver(configuration_menu, REQ_DOWN_ITEM); //Key down will 
				break;
			case KEY_UP:
				menu_driver(configuration_menu, REQ_UP_ITEM);
				break;
			case 10:	/* In case the user presses Enter */
			{	char temp[200];
				
				temp[0] = '\0';

				current_menu_item = current_item(configuration_menu); //Getting info about the selected item
				display_configuration(item_index(current_menu_item), field); //Getting the index of the current item in the menu

				mvprintw(20, 0, temp);
				refresh();
			}
			break;

		}
	}	

	for(i=0;i<n_choices;i++)
	{
		free_item(configurations_choice[i]);
	}

	for (i = 0; i < fsize; ++i)
		free(field[i]); //  free each array of cells d
	free(field); // free the array of pointers field
	
	free_menu(configuration_menu);
	endwin();
 
 endwin();

 return 0;
}
