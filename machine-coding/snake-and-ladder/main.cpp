#include <iostream>

class Player {};
class Board {};

class Dice {
public:
	Dice(int count) {
		this->die = count; 
	}	

	int Roll() {
		// add logic to roll all n dices and use a scoring function to calculate moves
		return rand() % 6; 
	}
private: 
	// number of die
	int die;	
};

int main() { 
	std::cout << "Hello World!" << std::endl;
}