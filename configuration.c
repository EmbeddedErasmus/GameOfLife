#include <curses.h>
#include "cell.h"
#include "menu_display.h"

/*
 * Function:  display
 * --------------------
 * Arguments:- WINDOW *win (Window to show the game)
 *			 - cell **area (2D array of cell with all the information of the field)
 *			 - startx (first x coordinate of the window)
 *			 - starty (first y coordinate of the window)
 *			 - endx (last x coordinate of the window)
 *			 - endy (last y coordinate of the window)
 *
 * This function is responsible for printing the current state of each cell in the window. 
 * If the cell is alive it will print an #, if not it will leave it empty.
 *
 */


void display(WINDOW *win, cell **area, int startx, int starty, int endx, int endy)
{	int i, j;
	wclear(win); // clear the window
	for(i = startx; i <= endx; ++i)
		for(j = starty;j <= endy; ++j)
			if(area[i][j].current_state == TRUE)
				mvwaddch(win, i, j, '#'); // move the cursor to the (i,j) coordinates and then print
	wrefresh(win); // show the result in the window
}


/*
 * Function:  display_configuration
 * --------------------
 * Arguments:- configuration (Number of the item that the user selected)
 *			 - cell **area (2D array of cell with all the information of the field)
 *
 * This function is responsible for setting the state of specific cells as alive forming
 * the initial configuration chosen by the user. After printing this configuration it waits
 * until the autorithazion of the user to start the game.
 *
 */

int display_configuration(int configuration, cell **field)
{
	wclear(stdscr);

	int middle_x=LINES/2;
	int middle_y=COLS/2;
	int key_played_on_menu=0;
	int choice_Is_Made =0, back_to_menu=0, start_Simulation=0;
	clear_field(field);

	if(configuration==0) //The R-Pentomino
	{
		field[middle_x][middle_y].next_state= 1;
		field[middle_x-1][middle_y].next_state=1;
		field[middle_x+1][middle_y].next_state=1;
		field[middle_x][middle_y-1].next_state=1;
		field[middle_x-1][middle_y+1].next_state=1;
	}

	if(configuration==1) //Die Hard
	{
		field[middle_x-1][middle_y+2].next_state=1;
		field[middle_x][middle_y-3].next_state= 1;
		field[middle_x][middle_y-4].next_state= 1;
		field[middle_x+1][middle_y-3].next_state=1;
		field[middle_x+1][middle_y+1].next_state=1;
		field[middle_x+1][middle_y+2].next_state=1;
		field[middle_x+1][middle_y+3].next_state=1;
	}

	if(configuration==2) //Acorn
	{
		field[middle_x][middle_y].next_state= 1;
		field[middle_x-1][middle_y-2].next_state=1;
		field[middle_x+1][middle_y-2].next_state=1;
		field[middle_x+1][middle_y-3].next_state=1;
		field[middle_x+1][middle_y+1].next_state=1;
		field[middle_x+1][middle_y+2].next_state=1;
		field[middle_x+1][middle_y+3].next_state=1;
	}

	update_field(field);
	
	display(stdscr, field, 0,0,LINES-1, COLS-1);  // Print the initial configuration in the screen

	// Comands to start or finish the game
	mvprintw(LINES - 1, 0, "Press F4 to Exit"); 
	mvprintw(LINES - 2, 0, "Press enter to start");
	mvprintw(LINES - 3, 0, "Press F2 to return");

	// Waits for the autoritazion of the user to start the game.
	while(choice_Is_Made!=1 &&((key_played_on_menu = getch()) != KEY_F(4)))
	{   switch(key_played_on_menu)
	    {	case KEY_F(2):
		        choice_Is_Made=1;
		        back_to_menu=1;
				break;

			case 10:	/* In case the user presses Enter */
			{	
				choice_Is_Made=1;
				start_Simulation=1;
			}
			break;
		}
	}

	// If the user choose to return, it goes back to the main menu
	if(choice_Is_Made && back_to_menu)
	{
		display_menu(field);
	}
	// User autorize the game to start
	else if(choice_Is_Made && start_Simulation)
	{
		start_Game(field);
	}

	return 0;
}

