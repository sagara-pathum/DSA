#include <iostream>
#include "libs/Pzl.h"
#include "libs/Grid.h"

int main(){

	Pzl p = Pzl();
	Grid g = Grid(12);
	g.gexec();
	endwin();
	return 0;
}
