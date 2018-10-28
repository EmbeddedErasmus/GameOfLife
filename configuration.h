char *configuration_choices[] = {
                        "The R-Pentomino",
                        "Diehard",
                        "Acorn",
                        "Exit",
                  };

int display_configuration(int configuration, cell **field);

void display(WINDOW *win, cell **area, int startx, int starty, int endx, int endy);