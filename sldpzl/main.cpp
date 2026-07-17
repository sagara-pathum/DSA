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

	public:
		Pzl(){
			initscr();
        		keypad(stdscr, TRUE);

			this->shuffle_vec();


        		v = {
                		{ tile_num[0], tile_num[2], tile_num[3] },
                		{ tile_num[4], tile_num[5], tile_num[6] },
                		{ tile_num[7], tile_num[8], tile_num[0] }
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
                                { tile_num[0], tile_num[2], tile_num[3] },
                                { tile_num[4], tile_num[5], tile_num[6] },
                                { tile_num[7], tile_num[8], tile_num[0] }
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
			refresh();
		}


		void exec(){
		        int ch;
        		while((ch=getch()) != 'q'){
                		switch(ch) {

                        		case KEY_UP:
                                		printw("Up ebuwa utto");
                                		break;
                        		case KEY_DOWN:
						shuffle_vec();                               		
						print_vec(this -> get_vec(), 5, 20);
                                		break;
                        		case KEY_LEFT:
                                		break;
                        		case KEY_RIGHT:
                                		break;
                		}
        		}	
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
