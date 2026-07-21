#include <iostream>
#include <vector> // for vector arrays
#include <random>
#include <algorithm> // shuffle

#include "libs/Pzl.h"

#include <ncurses.h> 
// this is a library for TUI applicatoin. it controls all the input and output. It allocate a memory in the ram. we use that space to write. then we update the screen
//https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5


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

	public :

		Grid (int grid_size){
			
			n_rows = grid_size;
			n_columns = grid_size*2;
			row_jumps = n_rows/3;
			col_jumps = n_columns/3;

			x_start = (max_x - n_columns)/2;
			y_start = (max_y - n_rows)/2;
			
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

		void gexec(){
		    int ch;
			print_grid();
			add_vec();
			refresh();
        	while((ch=getch()) != 'q'){					
				move_tile(ch);
				add_vec();
                refresh();
        		}	
		}

};


int main(){

	Pzl p = Pzl();
	Grid g = Grid(12);
	g.gexec();
	getch(); // holding the output. for temporary pourposes
	endwin();
	return 0;
}
