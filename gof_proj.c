#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
                        "The R-Pentomino",
                        "Diehard",
                        "Acorn",
                        "Exit",
                  };

// We need to define what are the parameters of our struct
typedef struct cells {
	int alive;
}cell;

int main()
{
	char welcomeMessage[]="Welcome to the Game Of Life";		/* message to be appeared on the screen */
	char namesMessage[]="By blabla1 blabla2 blabla3 blabla4";

	int inic_x =0;
	int inic_y =0;
	int final_x =0;
	int final_y =0;				/* to store the number of rows and *
						 * the number of colums of the screen */

	ITEM **configurations_choice;
	int c;				
	MENU *configuration_menu;
	int n_choices, i;
	ITEM *cur_item;

	initscr();				/* start the curses mode */
	getmaxyx(stdscr,final_x,final_y);		/* get the number of rows and columns */

	//First screen *******************************************************
	mvprintw(final_x/2,(final_y-strlen(welcomeMessage))/2,"%s",welcomeMessage);
	                                	/* print the message at the center of the screen */
	mvprintw(final_x/2 +1,(final_y-strlen(namesMessage))/2,"%s",namesMessage);

	refresh();
	getch(); //Just waiting for user to press something
	//********************************************************************
	erase();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
		
	n_choices = ARRAY_SIZE(choices);
	configurations_choice = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	if (configurations_choice == NULL)
		{return -1 ;}

	for(i = 0; i < n_choices; ++i)
		configurations_choice[i] = new_item(choices[i], choices[i]);
	configurations_choice[n_choices] = (ITEM *)NULL;

	configuration_menu = new_menu((ITEM **)configurations_choice);
	mvprintw(LINES - 2, 0, "F4 to Exit");
	post_menu(configuration_menu);
	refresh();

	while((c = getch()) != KEY_F(4))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(configuration_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(configuration_menu, REQ_UP_ITEM);
				break;
			case 10:	/* In case the user presses Enter */
			{	char temp[200];
				ITEM **items;

				items = menu_items(configuration_menu);
				temp[0] = '\0';
				for(i = 0; i < item_count(configuration_menu); ++i)
					if(item_value(items[i]) == TRUE)
					{	strcat(temp, item_name(items[i]));
						strcat(temp, " ");
					}
				move(20, 0);
				clrtoeol();
				mvprintw(20, 0, temp);
				refresh();
			}
			break;

		}
	}	

	for(i=0;i<n_choices;n++)
	{
		free_item(configurations_choice[i]);
	}
	
	free_menu(configuration_menu);
	endwin();
 
 endwin();

 return 0;
	/*initscr(); // Start curses mode
	raw();
	keypad(stdscr, TRUE); //Enable keys

	int inic_x=0; //first position of the screen
	int final_x=COLS; //COLS, LINES which are initialized to 
	int inic_y=0;
	int final_y=LINES;// the screen sizes after initscr()

	char answer = '0';

	// Allocating memory for a 2D array of cell type
	// Array of pointers
	int  fsize = 20;
	cell **  field = (cell  **)  malloc(fsize * sizeof(cell  *));

	int i=0;
	int j=0;

	// Array of cells
	for (i = 0; i < fsize; ++i)
		field[i] = (cell *)  malloc(fsize * sizeof(cell ));

	printf("Please indicate the intial configuration you would like to effect\n");
	printf("L :1\n");
	//raw();
	scanf("%c",&answer);
	printf("Answer is %c \n", answer);

	/*if(*answer=='1')
	{
		field[0][0].alive = 1;
		field[1][0].alive = 1;
		field[2][0].alive = 1;
	}*/

	//displayGrid(stdscr, field, inic_x, inic_y, final_x, final_y);
// Game: we need to update all the cells until the user press F1

/*
while(getch() != KEY_F(1))
	{	
		for(i = inic_x; i <= final_x; ++i)
		{
			for(j = inic_y; j <= final_y; ++j)
			{
				/* Verify all the rules
				Populated cells
					Each cell with one or no neighbors dies, as if by solitude.
					Each cell with four or more neighbors dies, as if by overpopulation.
					Each cell with two or three neighbors survives.

				Empty cells
					Each cell with three neighbors becomes populated.
				*/
				// Uptade the screen with the necessary changes 
			}	

/* To update the screen we need create a function that uses:
mvaddch(row,col,ch) -> is used to move the cursor to a given point, and then print
refresh();	-> Print it on to the real screen 


*/

/*
for (i = 0; i < fsize; ++i)
	free(field[i]); //  free each array of cells d
free(field); // free the array of pointers field
*/

