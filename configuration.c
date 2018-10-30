#include <curses.h>
#include "cell.h"
#include "menu_display.h"

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
	
	display(stdscr, field, 0,0,LINES-1, COLS-1);

	mvprintw(LINES - 1, 0, "Press F4 to Exit"); 
	mvprintw(LINES - 2, 0, "Press enter to start");
	mvprintw(LINES - 3, 0, "Press F2 to return");

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

	if(choice_Is_Made && back_to_menu)
	{
		display_menu(field);
	}
	else if(choice_Is_Made && start_Simulation)
	{
		start_Game(field);
	}

	return 0;
}

