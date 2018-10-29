typedef struct {
	int current_state;
	int next_state;
}cell;

void check_neighboors(cell **field, int i, int j);
void start_Game(cell **field);
void clear_field(cell **field);
void update_field(cell **field);