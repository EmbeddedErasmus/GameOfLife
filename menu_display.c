#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>

#include "cell.h"
#include "configuration.h"
#include "menu_display.h"


// Names of the diferent intial configuration of the cells
char *configuration_choices[] = {
                        "The R-Pentomino",
                        "Diehard",
                        "Acorn",
                        "Exit",
                  };

/*
 * Function:  display_menu
 * --------------------
 * Argument: cell **field (2D array of cell with all the information of the field)
 * 
 * This function is responsible for showing the menu to choose which is the initial  configuration.
 * In the menu the user can choose between 3 different initial configurations: "The R-Pentomino",
 * "Diehard" and "Acorn".
 * 
 *
 */                  

void display_menu(cell **field)
{
	int i=0, choice_Is_Made = 0;
	int key_played_on_menu=0;	//Int to navigate in the menu
	int index_menu_item=0;
	int n_choices = ARRAY_SIZE(configuration_choices);

	ITEM **configurations_choice; // list of configuration choices
	ITEM *current_menu_item; 

	MENU *configuration_menu; //configuration menu pointer

	erase(); // clean the window
	cbreak(); // Line buffering disabled
	noecho(); // Don't echo()
	timeout(TIME_OUT); // set blocking read
	keypad(stdscr, TRUE); // Enable keys 


	// Alocatting an array for the ITEM 	
	configurations_choice = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
			if (configurations_choice == NULL) // detect memory leaks 
				{return; }

	// Specify a name for the items in the menu
	for(i = 0; i < n_choices; ++i)
		configurations_choice[i] = new_item(configuration_choices[i], configuration_choices[i]);
	configurations_choice[n_choices] = (ITEM *)NULL;

	// Create the menu 
	configuration_menu = new_menu((ITEM **)configurations_choice);

	mvprintw(LINES - 2, 0, "F4 to Exit"); //Print at the bottom how to quit the window to go back to the terminal
	post_menu(configuration_menu); //Display the menu
	refresh(); // refresh the window with the menu

	// Let the user choose the initial configuration******************************************************
	while(choice_Is_Made!=1 && ((key_played_on_menu = getch()) != KEY_F(4)))
	{   switch(key_played_on_menu)
	    {	case KEY_DOWN: 
		        menu_driver(configuration_menu, REQ_DOWN_ITEM); // Move the selection item to the the below
				break;

			case KEY_UP:
				menu_driver(configuration_menu, REQ_UP_ITEM);// Move the selection item to the the above
				break;

			case 10:	/* In case the user presses Enter */
			{	
				current_menu_item = current_item(configuration_menu); //Getting info about the selected item
				index_menu_item = item_index(current_menu_item);
				choice_Is_Made = 1;
			}
			break;
		}
	}
	// **************************************************************************************************


	// If the user have choosen an item the program continues to the display_configuration function 
	if(index_menu_item != n_choices-1 && choice_Is_Made)
	{
		display_configuration(index_menu_item, field); //Getting the index of the current item in the menu	
	}

	// Freeing the memory reserved **************************************
	for(i=0;i<n_choices ;i++)
	{
		free_item(configurations_choice[i]);
	}

	free_menu(configuration_menu);
	// ******************************************************************
}