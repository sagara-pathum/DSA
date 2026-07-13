#include <iostream>

class Piece {
	private :
		short number;
	public :
		Piece(){
			this->number = 0;
		}

		Piece(short number){
			this->number = number;
		}

		void printNumber(){
			std::cout << this->number;
		}
};

class Board {

	public :
		Piece arr[9]; 	

		Board() {
	
		}

		// now i need to do is move the pieces
		void move(char c, Peice p) {
			switch(c){
				case 'u':
					//
					break;
				case 'd':
					//
					break;
				case 'l':
					//
					break;
				case 'r':
					//
					break;
			
			}
		}
};

int main() {
	Piece p1 = Piece(1);
	p1.printNumber();
	return 0;
}
