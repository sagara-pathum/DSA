#include <iostream>
#include <ctime> // this is for time() function
#include <cstdlib> // this is for srand() rand()
#include <vector> // for vector arrays
#include <random>
#include <algorithm> // shuffle
#include <ncurses.h> 
// this is a library for TUI applicatoin. it controls all the input and output. It allocate a memory in the ram. we use that space to write. then we update the screen
//https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5

void print_vec(std::vector<std::vector<int> > vec){
	for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                        std::cout << vec[i][j] << " ";
                }
                std::cout << "\n";
        }
}

void exec(){
	int ch;
	while((ch=getch()) != 'q'){
		move(5,30);
		clrtoeol();
		switch(ch) {
			case KEY_UP:
				printw("Up ebuwa utto");
				break;
			case KEY_DOWNhttps://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5:https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5https://dev.to/tbhaxor/introduction-to-ncurses-part-1-1bk5
			}
	}
	refresh();
}

int main(){
	
	// 3 by 3 board
	//

	std::vector<int> tile_num = {0,1,2,3,4,5,6,7,8};


	std::random_device r = std::random_device();
        std::mt19937 mt(r());
        std::shuffle(tile_num.begin(), tile_num.end(), mt);


	std::vector< std::vector<int> > v = {
		{ tile_num[0], tile_num[2], tile_num[3] },
		{ tile_num[4], tile_num[5], tile_num[6] },
		{ tile_num[7], tile_num[8], tile_num[0] }	
	};

	initscr();
	keypad(stdscr, TRUE);
	exec();
	endwin();


	return 0;
}
