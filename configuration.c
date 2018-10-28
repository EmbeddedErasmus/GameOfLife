#include <curses.h>

#include "cell.h"

void display(WINDOW *win, cell **area, int startx, int starty, int endx, int endy)
{	int i, j;
	wclear(win);
	for(i = startx; i <= endx; ++i)
		for(j = starty;j <= endy; ++j)
			if(area[i][j].current_state == TRUE)
				mvwaddch(win, i, j, '#');
	wrefresh(win);
}

int display_configuration(int configuration, cell **field)
{
	wclear(stdscr);
	int middle_x=LINES/2;
	int middle_y=COLS/2;

	if(configuration==0) //The R-Pentomino
	{
		field[middle_x][middle_y].current_state= TRUE;
		field[middle_x-1][middle_y].current_state=TRUE;
		field[middle_x+1][middle_y].current_state=TRUE;
		field[middle_x][middle_y-1].current_state=TRUE;
		field[middle_x-1][middle_y+1].current_state=TRUE;
	}

	if(configuration==1) //Die Hard
	{
		field[middle_x-1][middle_y+2].current_state=TRUE;
		field[middle_x][middle_y-3].current_state= TRUE;
		field[middle_x][middle_y-4].current_state= TRUE;
		field[middle_x+1][middle_y-3].current_state=TRUE;
		field[middle_x+1][middle_y+1].current_state=TRUE;
		field[middle_x+1][middle_y+2].current_state=TRUE;
		field[middle_x+1][middle_y+3].current_state=TRUE;
	}

	if(configuration==2) //Acorn
	{
		field[middle_x][middle_y].current_state= TRUE;
		field[middle_x+1][middle_y+1].current_state=TRUE;
		field[middle_x+1][middle_y+2].current_state=TRUE;
		field[middle_x+1][middle_y+3].current_state=TRUE;
	}
	
	display(stdscr, field, 0,0,LINES-1, COLS-1);

	mvprintw(LINES - 1, 0, "Press F4 to Exit"); 
	mvprintw(LINES - 2, 0, "Press enter to start");
	mvprintw(LINES - 3, 0, "Press F2 to return");

	return 0;
}

