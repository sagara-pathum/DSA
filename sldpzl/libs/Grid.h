#ifndef GRID_H
#define GRID_H

#include "../libs/Pzl.h" // Pzl.h has #include <vector> so i am not including it here

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

		Grid (int grid_size);

		void print_grid(); // print_grid function prints 3 by 3 grid on screen

		void add_vec(); // this is the function that add the vec_values of Pzl class on the drawn Grid

		void mvprintw(int x, int y, int n); // add_vec is a set of individual prints of numbers. those individuals n  is printed on x, y using this function

		void gexec(); // this is the evenloop that holds and updates the TUI grid interface.

		bool is_win(); // to check whether the goal is reached or not

		void screen_border();

		void print_over();

};

#endif
