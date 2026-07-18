#include <iostream>
#include <ctime> // this is for time() function
#include <cstdlib> // this is for srand() rand()
#include <vector> // for vector arrays
#include <random>
#include <algorithm> // shuffle
#include <ncurses.h> 
// this is a library for TUI applicatoin. it controls all the input and output. It allocate a memory in the ram. we use that space to write. then we update the screen
//https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5

class Pzl{
	private:
		std::vector<int> tile_num = {0,1,2,3,4,5,6,7,8};
		
		std::vector< std::vector<int> > v = {
			{1,2,3},
			{4,5,6},
			{7,8,0}
		};

		int temp_for_swap;

	public:
		Pzl(){

			initscr();
			
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

		void move_tile(int key){
        		int r;
        		int c;
        		zero(&r, &c);

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


int main(){

	//exec();
	//endwin();
	Pzl k = Pzl();



	k.exec();
	endwin();
	return 0;
}
