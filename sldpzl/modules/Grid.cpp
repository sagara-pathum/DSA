#include "../libs/Grid.h"

Grid::Grid (int grid_size){
	
	n_rows = grid_size;
	n_columns = grid_size*2;
	row_jumps = n_rows/3;
	col_jumps = n_columns/3;

	x_start = (max_x - n_columns)/2;
	y_start = (max_y - n_rows)/2;
	
}

void Grid::mvprintw(int x, int y, int n){
	move(y, x);
	if (n != 0) {
		printw("%d ",n);
	} else {
		printw(" ");
	}
}

void Grid::add_vec(){
    int x1 = x_start + (col_jumps/2);
    int x2 = x_start + 3*(col_jumps/2);
	int x3 = x_start + 5*(col_jumps/2);

	int y1 = y_start + (row_jumps/2);
	int y2 = y_start + 3*(row_jumps/2);
	int y3 = y_start + 5*(row_jumps/2);

	mvprintw(x1, y1, (*v_ptr)[0][0]);
	mvprintw(x2, y1, (*v_ptr)[0][1]);
	mvprintw(x3, y1, (*v_ptr)[0][2]);

	mvprintw(x1, y2, (*v_ptr)[1][0]);
	mvprintw(x2, y2, (*v_ptr)[1][1]);
	mvprintw(x3, y2, (*v_ptr)[1][2]);

	mvprintw(x1, y3, (*v_ptr)[2][0]);
	mvprintw(x2, y3, (*v_ptr)[2][1]);
	mvprintw(x3, y3, (*v_ptr)[2][2]);

}

void Grid::print_grid(){


    curs_set(0); // Hide the blinking cursor
	
    // draw the horizontal lines
    for (int i = 0; i <= n_rows; i += row_jumps){
    	// ASC_HLINE is an unicode character we use to draw horizontal lines 
        // para : y, x, char, lonng 
        mvhline(y_start + i, x_start, ACS_HLINE, n_columns);
    }
    // draw the vertical lines
    for (int j = 0; j <= n_columns; j += col_jumps){
        mvvline(y_start, x_start + j, ACS_VLINE, n_rows);
    }
                  
    // we can smooth the corners by uing Alternative Character Set CORNERS
    // para : y , x, char
    mvaddch(y_start, x_start, ACS_ULCORNER);
    mvaddch(y_start, (x_start + n_columns), ACS_URCORNER);
    mvaddch((y_start + n_rows), x_start, ACS_LLCORNER);
    mvaddch((y_start + n_rows), (x_start + n_columns), ACS_LRCORNER);

    // now we can add ACS Tees for smooothing the middle lines on edges
    for (int i = col_jumps; i < n_columns; i += col_jumps){
        mvaddch(y_start, (x_start + i), ACS_TTEE); // TOP TEE
        mvaddch((y_start + n_rows), (x_start + i), ACS_BTEE); // BOTOM TEE
    }

    for (int j = row_jumps; j < n_rows; j += row_jumps){
        mvaddch((y_start + j), x_start, ACS_LTEE); //LEFT TEE
        mvaddch((y_start + j), (x_start + n_columns), ACS_RTEE); //RIGHT TEE
    }
}

void Grid::gexec(){
    int ch;

	puzzle_suffle(50);
	screen_border();
	print_grid();
	add_vec();
	refresh();
	while((ch=getch()) != 'q'){	
		
		screen_border();				
		move_tile(ch);
		add_vec();
        refresh();

		if (is_win()) {

			print_over();
			print_res_and_qui();
			screen_border();
			add_vec();
			refresh();
			while((ch=getch()) != 'q'){	
				if (ch == 'r') {
					clear();
					gexec();
					break;
				}
			}
			break; /// see here there is a bug
		}
			
	}

	

}

bool Grid::is_win(){

	std::vector< std::vector<int> > win = {
		{1,2,3},
		{4,5,6},
		{7,8,0}
	};
	
	if ((*v_ptr) == win) {
		return true;
	} else {
		return false;
	}
}


void Grid::print_over(){
	move(3,3);
	char s[] = " _______  _______  __   __  _______    _______  __   __  _______  ______    \n   |       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  \n   |    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  \n   |   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ \n   |   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |\n   |   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |\n   |_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|\n";

	printw("%s", s);
	refresh();

}

void Grid::print_res_and_qui(){
	int foot_y = max_y - 3;
	int foot_x1 = 3;
	int foot_x2 = max_x - 21;

	char s1[] = "Press 'r' to restart !";
	char s2[] = "Press 'q' to quit.";

	move(foot_y, foot_x1);
	printw("%s ", s1);
	move(foot_y, foot_x2);
	printw("%s ", s2);
}

void Grid::screen_border(){
	int x_left = 1;
	int y_top = 1;
	int x_right = max_x - 1;
	int y_bottom = max_y - 2;

	int x_long = max_x - 2;
	int y_long = max_y - 3; 

	mvhline(y_top, x_left, ACS_HLINE, x_long);
	mvhline(y_bottom, x_left, ACS_HLINE, x_long);
	mvvline(y_top, x_left, ACS_VLINE, y_long);
	mvvline(y_top, x_right, ACS_VLINE, y_long);

	mvaddch(y_top, x_left, ACS_ULCORNER);
    mvaddch(y_top, x_right, ACS_URCORNER);
    mvaddch(y_bottom, x_left, ACS_LLCORNER);
    mvaddch(y_bottom, x_right, ACS_LRCORNER);

}

