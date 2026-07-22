#include "../libs/Pzl.h"

#include <random> // for namdom_device and mt19937
#include <algorithm> // shuffle

Pzl::Pzl(){

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

	v = {
                { tile_num[0], tile_num[1], tile_num[2] },
                { tile_num[3], tile_num[4], tile_num[5] },
                { tile_num[6], tile_num[7], tile_num[8] }
	};

}

std::vector< std::vector<int> > Pzl::get_vec(){
	return this-> v;
}


void Pzl::shuffle_vec(){
	std::random_device r = std::random_device();
    std::mt19937 mt(r());
    std::shuffle(tile_num.begin(), tile_num.end(), mt);

	v = {
                { tile_num[0], tile_num[1], tile_num[2] },
                { tile_num[3], tile_num[4], tile_num[5] },
                { tile_num[6], tile_num[7], tile_num[8] }
    };
}


void Pzl::print_vec(std::vector<std::vector<int> > vec,int con_row,int line_start){
	for (int i = 0; i < 3; i++){		
		move((con_row+i),(line_start));
		clrtoeol();

		for (int j = 0; j < 3; j++){
			printw("%d ", vec[i][j]);
		}
		printw("\n");
	}
}


void Pzl::exec(){

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


void Pzl::zero(int* row, int* column){

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if ( this->v[i][j] == 0){
				*row = i;
				*column = j;
			}
		}
	}

}


void Pzl::move_err(){

	char s[] = "Can't move. There is no tile";
	int length_s = (sizeof(s)/sizeof(char)) - 1; 
	int foot_y = max_y - 1;
	int foot_x = (max_x - length_s)/2;

	move(foot_y, foot_x);
	printw("%s", s);

}


void Pzl::clr_move_err(){

	char s[] = "Can't move. There is no tile";
	int length_s = (sizeof(s)/sizeof(char)) - 1; 
	int foot_y = max_y - 1;
	int foot_x = (max_x - length_s)/2;

	move(foot_y, foot_x);
	clrtoeol();	

}


void Pzl::move_tile(int key){

	int r;
	int c;
	zero(&r, &c);

	getmaxyx(stdscr, max_y, max_x);

	switch (key) {
		case KEY_UP:
            if (r == 2){

				move_err();
            } else {
				clr_move_err();
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

				move_err();
			} else {
				clr_move_err();
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

				move_err();
			} else {
				clr_move_err();
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

				move_err();
			} else {
				clr_move_err();
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


void Pzl::swap_vec_position(int r1, int c1, int r2, int c2){

	this-> temp_for_swap = this-> v[r1][c1];
	this-> v[r1][c1] = this-> v[r2][c2];
	this-> v[r2][c2] = temp_for_swap;
	
}

void Pzl::puzzle_suffle(int n_size){
	// lets initialize the puzzle in correct order first. then we can make some random moves. (initialization is already sorted)
	int arr[n_size];
	
	std::random_device r = std::random_device();
    std::mt19937 mt(r());
    std::uniform_int_distribution vec_moves(1,4);


	for (int i = 0; i < n_size; i++){
		arr[i] = vec_moves(mt);
	}

	for (int j = 0; j < n_size; j++){
		switch (arr[j]){
			case 1 :
				move_tile(KEY_UP);
				break;
			case 2 :
				move_tile(KEY_DOWN);
				break;
			case 3 :
				move_tile(KEY_LEFT);
				break;
			case 4 :
				move_tile(KEY_RIGHT);
				break;
		}
	}
	clr_move_err();
}
