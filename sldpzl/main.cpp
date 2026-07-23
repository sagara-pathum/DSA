#include <iostream>
#include "libs/Pzl.h"
#include "libs/Grid.h"

int main(){

	Menu m = Menu();
	m.loading();
	clear();
	int choice = m.run();
	if (choice == 1) {
		Grid g = Grid(12);
		g.gexec();
	}
	endwin();
	return 0;
}
