#include <iostream>
#include <thread>
#include <vector>
#include <thread>
#include <chrono>

class Player {
public:
	int get_pos() {
		return position;
	}

	void move(int cell) {
		this->position = cell;
	}

private:
	int position;
};


class Board {
public:
	// size x size board 
	Board(int size =10) {
		this->size = size;
	}

	int get_size() {
		return size; 
	}
private:
	int size;
};

class Dice {
public:
	Dice(int count=1) {
		this->die = count; 
	}	

	int Roll() {
		// TODO: add logic to roll all n dices and use a scoring function to calculate moves
		return rand() % 6; 
	}
private: 
	// number of die
	int die;	
};


enum GameState {
	RUN,
	END
};

class Game{
public:
	Game(int n_Players =2, int n_die = 1, int board_size=10): n_Players(n_Players) {
		this->state = GameState::RUN;
		this->board = Board(board_size);
		this->die = Dice(n_die);
		this->turn =0; 

		// create players
		for (int i=0; i < n_Players; i++) {
			this->players.push_back(Player());
		}

		// populate jump positions
		for (int i= 1; i < board_size * board_size; i++) {
			if (i % 4 == 0) {	// this should be random 
				if (rand() % 2) {
					// snake
					jumps[i] = rand() % i;
					std::cout << "Snake from " << i << " to " << jumps[i] << std::endl;
				} else {
					// ladder 
					jumps[i] = board_size * board_size - (rand() % i);
					std::cout << "Ladder from " << i << " to " << jumps[i] << std::endl;
				}
			}	
		}

		std::cout << "Game has been constructed" << std::endl;
	}

	void run() {
		std::cout << "Starting up the game..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		while (this->state == GameState::RUN) {
			// print_state();
			std::cout << "Player " << turn << " at position: " << players[turn].get_pos() << std::endl;
			auto& curr_player = players[turn];
			std::cout << "Rolling Die.." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(250));

			int moves= die.Roll();
			if (valid_pos(moves)) {
				move_player(moves);
			} 

			std::cout << "player moved to " << players[turn].get_pos() << std::endl;
			if (check_win()) {
				this->state = GameState::END;
				std::cout << "Game has finished! with Player " << turn << " " << "winning the game!" << std::endl;
			}
			// next player's turn
			turn = (turn + 1) % n_Players;
		}
	}

private:
	void move_player(int moves) {
		auto cell = this->players[turn].get_pos();

		// jump the player to the new position
		jump_player(cell + moves);
	}

	void jump_player(int pos) {
		if (jumps.count(pos)) {
			jump_player(jumps[pos]);
		} else {
			this->players[turn].move(pos);
		} 
	}

	bool valid_pos(int moves) {
		auto cell = this->players[turn].get_pos();
		int n = this->board.get_size();
		return cell + moves < n * n;
	}

	// check if the current player just won the game
	bool check_win() {
		auto cell = this->players[turn].get_pos();
		int n = this->board.get_size();

		return cell == (n * n - 1);
	}

	Dice die;
	Board board;
	std::vector<Player> players;
	GameState state;

	// ladders: smaller postion to higher positon
	// snakes: higher position to smaller position 
	std::unordered_map<int, int> jumps;

	int n_Players;	
	int turn;
};

int main() { 
	Game game;

	game.run();

	return 0;
}