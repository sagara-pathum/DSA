#include <iostream>
#include <ctime> // this is for time() function
#include <cstdlib> // this is for srand() rand()
#include <vector> // for vector arrays
#include <random>
#include <algorithm> // shuffle
#include <ncurses.h> 
// this is a library for TUI applicatoin. it controls all the input and output. It allocate a memory in the ram. we use that space to write. then we update the screen
//https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5

class Pzl
{
	protected:
		std::vector<int> tile_num = {0,1,2,3,4,5,6,7,8};
		
		std::vector< std::vector<int> > v = {
			{1,2,3},
			{4,5,6},
			{7,8,0}
		};

		int temp_for_swap;

		int max_y, max_x; //for screen dimensions

	public:
		Pzl(){

			initscr();

			getmaxyx(stdscr, max_y, max_x);

			
			// bug happens here. because terminal application usually runs in 'coocked' mode. which precisely 'line buffered mode'
			// when we press a button its characters is saved in the buffer until it meet a newline character
			// we need to remove the buffering and give the input character control to the application
			// we can do that using cbreak();
			// we when character is given, terminal tries to print the input to curser.
			// it may also causes bugs.
			// so it is better to use noecho() to stop that.
			// usually noecho is used followed by cbreak.
			cbreak();
			noecho();

        	keypad(stdscr, TRUE);

			this->shuffle_vec();

        	v = {
                	{ tile_num[0], tile_num[1], tile_num[2] },
                	{ tile_num[3], tile_num[4], tile_num[5] },
                	{ tile_num[6], tile_num[7], tile_num[8] }
        	};
		}

		std::vector< std::vector<int> > get_vec(){
			return this-> v;
		}


		void shuffle_vec(){
			std::random_device r = std::random_device();
            std::mt19937 mt(r());
            std::shuffle(tile_num.begin(), tile_num.end(), mt);

			v = {
                    { tile_num[0], tile_num[1], tile_num[2] },
                    { tile_num[3], tile_num[4], tile_num[5] },
                    { tile_num[6], tile_num[7], tile_num[8] }
            };
		}

		void print_vec(std::vector<std::vector<int> > vec,int con_row,int line_start){
        	for (int i = 0; i < 3; i++){		
				move((con_row+i),(line_start));
            	clrtoeol();

				for (int j = 0; j < 3; j++){
                	printw("%d ", vec[i][j]);
            	}
            	printw("\n");
        	}
		}


		void exec(){
		    int ch;
			// here is where the bug created. i was refreshing before moving. so that input is stays in buffer until refresh
			print_vec(this -> get_vec(), 5, 20);
			refresh();
        	while((ch=getch()) != 'q'){					
				// lets clean the things before writting.
				move(20, 20);
				clrtoeol();	
				move_tile(ch);
				print_vec(this -> get_vec(), 5, 20);
                refresh();
        		}	
		}

		void zero(int* row, int* column){
			for(int i = 0; i < 3; i++){
				for(int j = 0; j < 3; j++){
					if ( this->v[i][j] == 0){
						*row = i;
						*column = j;
					}
				}
			}
		}

		void move_err(){
			std::string s = "Can't move. There is no tile";
			int foot_y = max_y;
			int foot_x = (max_y - (s.length())/2);

			move(foot_y, foot_x);
			printw("%s", s);
		}

		void move_tile(int key){
        	int r;
        	int c;
        	zero(&r, &c);

			getmaxyx(stdscr, max_y, max_x);

        	switch (key) {
            	case KEY_UP:
                    if (r == 2){
                        move(20,20);
                        printw("Can't move. There is no tile");
                    } else {
						if (r == 1){
							switch (c){
								case 0:
									swap_vec_position(1,0,2,0);
									zero(&r, &c);
									break;
								case 1:
									swap_vec_position(1,1,2,1);
									zero(&r, &c);
									break;
								case 2:
									swap_vec_position(1,2,2,2);
									zero(&r, &c);
									break;
							}
							
						} else {
							switch (c){
								case 0:
									swap_vec_position(0,0,1,0);
									zero(&r, &c);
									break;
								case 1:
									swap_vec_position(0,1,1,1);
									zero(&r, &c);
									break;
								case 2:
									swap_vec_position(0,2,1,2);
									zero(&r, &c);
									break;
							}
						}
                    }
                    break;

                case KEY_DOWN:
					if (r == 0){
						move(20,20);
						printw("Can't move. There is no tile");
					} else {
						if (r == 1) {
							switch (c){
								case 0:
									swap_vec_position(1,0,0,0);
									zero(&r, &c);
									break;
								case 1:
									swap_vec_position(1,1,0,1);
									zero(&r, &c);
									break;
								case 2:
									swap_vec_position(1,2,0,2);
									zero(&r, &c);
									break;
							}
						} else {
							switch (c){
								case 0:
									swap_vec_position(2,0,1,0);
									zero(&r, &c);
									break;
								case 1:
									swap_vec_position(2,1,1,1);
									zero(&r, &c);
									break;
								case 2:
									swap_vec_position(2,2,1,2);
									zero(&r, &c);
									break;
							}
						}
					}
                    break;

                case KEY_LEFT:
					if (c == 2){
						move(20,20);
						printw("Can't move. There is no tile");
					} else {
						if (c == 1) {
							switch (r){
								case 0:
									swap_vec_position(0,1,0,2);
									zero(&r, &c);
									break;
								case 1:
									swap_vec_position(1,1,1,2);
									zero(&r, &c);
									break;
								case 2:
									swap_vec_position(2,1,2,2);
									zero(&r, &c);
									break;
							}
						} else {
							switch (r){
								case 0:
									swap_vec_position(0,0,0,1);
									zero(&r, &c);
									break;
								case 1:
									swap_vec_position(1,0,1,1);
									zero(&r, &c);
									break;
								case 2:
									swap_vec_position(2,0,2,1);
									zero(&r, &c);
									break;
							}
						}
					}
                    break;
                		
				case KEY_RIGHT:
					if (c == 0) {
						move(20,20);
						printw("Can't move. There is no tile");
					} else {
						if (c == 1){
							switch (r){
								case 0:
									swap_vec_position(0,1,0,0);
									zero(&r, &c);
									break;
								case 1:
									swap_vec_position(1,1,1,0);
									zero(&r, &c);
									break;
								case 2:
									swap_vec_position(2,1,2,0);
									zero(&r, &c);
									break;
							}
						} else {
							switch (r){
								case 0:
									swap_vec_position(0,2,0,1);
									zero(&r, &c);
									break;
								case 1:
									swap_vec_position(1,2,1,1);
									zero(&r, &c);
									break;
								case 2:
									swap_vec_position(2,2,2,1);
									zero(&r, &c);
									break;
							}
						}
					}
                    break;
        	}
		}

		void swap_vec_position(int r1, int c1, int r2, int c2){
			this-> temp_for_swap = this-> v[r1][c1];
			this-> v[r1][c1] = this-> v[r2][c2];
			this-> v[r2][c2] = temp_for_swap;
		}

		
};


class Grid : public Pzl
{
	private :
		std::vector< std::vector<int> >* v_ptr = &v;
		// i have to use those in tow functions so i made them local varibles for this class.
	    int n_rows;
	    int n_columns;
	    int row_jumps;
	    int col_jumps;          
	    int x_start;
	    int y_start;

		// int max_y, max_x; //for screen dimensions

	public :
		// constructor
		Grid (int grid_size){
			// getmaxyx(stdscr, max_y, max_x);
			
			n_rows = grid_size;
			n_columns = grid_size*2;
			row_jumps = n_rows/3;
			col_jumps = n_columns/3;

			x_start = (max_x - n_columns)/2;
			y_start = (max_y - n_rows)/2;
			
			//print_grid();
		}

		void mvprintw(int x, int y, int n){
        	move(y, x);
			if (n != 0) {
        		printw("%d ",n);
			} else {
				printw(" ");
			}
		}

		void add_vec(){
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
		
		void print_grid(){
			// initialize variables for maximum character lengths of the terminal
	        //int max_y, max_x;
			
			//these things are already initialized in superclass
	        //initscr();
	        //cbreak();
            //noecho();

            curs_set(0); // Hide the blinking cursor
		                    
	        //getmaxyx(stdscr, max_y, max_x); //getting the lengths in number of characters

			/*
	        // we need to define number of rows and characters for our drawing 
	        int n_rows = size;
	        int n_columns = size*2;
	        int row_jumps = n_rows/3;
	        int col_jumps = n_columns/3;
	        // we need a starting posision to draw
	                  
	        int x_start = (max_x - n_columns)/2;
	        int y_start = (max_y - n_rows)/2;
			*/
			
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

		void gexec(){
		    int ch;
			print_grid();
			add_vec();
			refresh();
        	while((ch=getch()) != 'q'){					
				// lets clean the things before writting.
				// move(20, 20);
				// clrtoeol();	
				move_tile(ch);
				add_vec();
                refresh();
        		}	
		}

};


int main(){

	Pzl p = Pzl();
	//p.exec();
	//print_grid(18);
	Grid g = Grid(12);
	g.gexec();
	// refresh();
	//g.add_vec();

	getch(); // holding the output. for temporary pourposes
	endwin();
	return 0;
}
