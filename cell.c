#include "cell.h"
#include <curses.h>
#include <unistd.h>
#include "configuration.h"

/*
 * Function:  clear_field
 * --------------------
 * Arguments:- cell **field (2D array of cell with all the information of the field)
 *
 * This function is responsible for setting the state of all cells as dead to clean the field.
 *
 */

void clear_field(cell **field)
{
	int x=0, y=0;
	for(x=0;x<LINES;x++)
	{
		for(y=0;y<COLS;y++)
		{
			field[x][y].current_state=0;
			field[x][y].next_state=0;
		}
	}
}

/*
 * Function:  update_field
 * --------------------
 * Arguments:- cell **area (2D array of cell with all the information of the field)
 *			 
 *
 * This function is responsible for setting the current state of each cell equals to the next state
 * in order to be possivle to print the new configuration of the all the cells in the next iteration.
 *
 */

void update_field(cell **field)
{
	int x=0, y=0;
	for(x=0;x<LINES-1;x++)
	{
		for(y=0;y<COLS-1;y++)
		{
			field[x][y].current_state=field[x][y].next_state;
		}
	}
}

/*
 * Function:  check_neighboors
 * --------------------
 * Arguments:- cell **field (2D array of cell with all the information of the field)
 *			 - i (x coordinate of selected cell), 
 *			 - j (y coordinate of selected cell)
 *
 * This function is responsible for checking all the rules of the Conway's Game of life 
 * and set the next state of each cell according to that.
 *
 */

void check_neighboors(cell **field, int i, int j)
{
	int neighboors=0;

	if(j+1<COLS)
	{
		neighboors += field[i][j+1].current_state;
	}
	if(j-1>0)
	{
		neighboors += field[i][j-1].current_state;
	}
	if(i+1<LINES)
	{
		neighboors += field[i+1][j].current_state;
	} 
	if(i-1>0)
	{
		neighboors += field[i-1][j].current_state;
	} 
	if(i+1 < LINES && j+1 < COLS)
	{
		neighboors += field[i+1][j+1].current_state;
	}
	if(i+1 < LINES && j-1 > 0)
	{
		neighboors += field[i+1][j-1].current_state;
	}
	if(i-1 > 0 && j+1 < COLS)
	{
		neighboors += field[i-1][j+1].current_state;
	}
	if(i-1 > 0 && j-1 > 0)
	{
		neighboors += field[i-1][j-1].current_state;
	}

	if (field[i][j].current_state == 1)
	{
		if (neighboors<2 || neighboors > 3)
		{
			field[i][j].next_state=0;
		}
		else
		{
			field[i][j].next_state=1;
		}
	}
	else
	{
		if (neighboors==3)
		{
			field[i][j].next_state=1;
		}
	}
}

/*
 * Function:  start_Game
 * --------------------
 * Arguments:- cell **field (2D array of cell with all the information of the field)
 *
 *
 * This function is responsible for rolling the game. It runs the window and check 
 * for each cell the game rules. The game continues untilt the user press a key to 
 * stop.
 *
 */

void start_Game(cell **field)
{
	int key_played=0;
	int x=0, y=0;

	while((key_played = getch()) != KEY_F(4))
	{   
		display(stdscr, field, 0,0,LINES-1, COLS-1);
		for(x=0;x<LINES-1;x++)
		{
			for(y=0;y<COLS-1;y++)
			{
				check_neighboors(field, x,y); // check the game rules
			}
		}
		update_field(field); // update the state off all the cells and then print it in the window
	}
	
}