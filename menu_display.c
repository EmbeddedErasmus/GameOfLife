#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>

#include "cell.h"
#include "configuration.h"
#include "menu_display.h"

char *configuration_choices[] = {
                        "The R-Pentomino",
                        "Diehard",
                        "Acorn",
                        "Exit",
                  };

void display_menu(cell **field)
{
	int i=0;
	int key_played_on_menu=0;	//Int to navigate in the menu
	int index_menu_item=0;
	int n_choices = ARRAY_SIZE(configuration_choices);

	ITEM **configurations_choice; // list of configuration choices
	ITEM *current_menu_item; 

	MENU *configuration_menu; //configuration menu pointer

	erase();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
		
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
			{	
				current_menu_item = current_item(configuration_menu); //Getting info about the selected item
				index_menu_item = item_index(current_menu_item);
				goto exit_loop;
			}
			break;
		}
	}

	exit_loop:if(index_menu_item != n_choices-1)
	{
		display_configuration(index_menu_item, field); //Getting the index of the current item in the menu	
	}

	for(i=0;i<n_choices;i++)
	{
		free_item(configurations_choice[i]);
	}

	free_menu(configuration_menu);
}