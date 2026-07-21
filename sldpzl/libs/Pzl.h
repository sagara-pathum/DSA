#ifndef PZL_H
#define PZL_H

#include <iostream>
#include <vector>
#include <ncurses.h> // define this here so that it wont be trouble in the main

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

		Pzl();

		std::vector< std::vector<int> > get_vec(); // this returns the v

		void shuffle_vec();

		void print_vec(std::vector<std::vector<int> > vec,int con_row,int line_start);

		void exec(); // just a invent loop for Pzl terminal without grid

		void zero(int* row, int* column); // this is needed for move tile. it helps to find the zero before take the action

		void move_err(); // this is needed for move tile. when in constraints is met, it shows the message 'can't move'

		void clr_move_err(); // this is needed for move tile. it removes 'can't move' message , when meets a valid input again

		void swap_vec_position(int r1, int c1, int r2, int c2); // this is also used in move_tile to swap tiles according to input

		void move_tile(int key); // this is the function that moves the numbers

		void puzzle_suffle(int n_size); // shuffle_vec is random. it is not good for sldpzl. sometimes it makes the puzzle unsolvable. i write a function again

};

#endif
