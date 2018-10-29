#include "cell.h"
#include <curses.h>
#include <unistd.h>
#include "configuration.h"

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

void start_Game(cell **field)
{
	int key_played=0;
	int x=0, y=0;

	while(1/*(key_played = getch()) != KEY_F(4)*/)
	{   
		display(stdscr, field, 0,0,LINES-1, COLS-1);
		for(x=0;x<LINES-1;x++)
		{
			for(y=0;y<COLS-1;y++)
			{
				check_neighboors(field, x,y);
			}
		}
		update_field(field);
		usleep(5000);
	}
	
}