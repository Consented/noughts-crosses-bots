#include <iostream> 
#include <vector>
#include <random>
#include <unordered_set>

void draw_board(std::vector<std::vector<int>> board){
	// 1) Iterate through 2d vector
	// 2) Represent numerical values by ascii characters (0 = " ", 1 = "O", 2 = "X")

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i][j] == 1){
				std::cout << "O";
			}
			else if (board[i][j] == 2){
				std::cout << "X";
			}
			else{
				std::cout << " ";
			}

			if (j < 2){
			std::cout << "|";
			}
		} 

		std::cout << "\n"; 
	} 
}

int user_input(std::unordered_set<int> occupied){
	// 1) Get next move location from user
	// 2) Ensure inserted value is between 1 and 9 (1 < x < 9)
	int location {0};

	while (location < 1 ||  location > 9 || occupied.count(location) == 1){
		std::cout << "Location: ";
		std::cin >> location;
		std::cout << "\n";
	}

	return location;
}

int alg1(std::unordered_set<int> occupied){
	// 1) Generate Random Number
	std::random_device rd;
	std::uniform_int_distribution<int> dist (1,9);
	int random_pos {dist(rd)};
	while (occupied.count(random_pos) == 1){
		random_pos = dist(rd);
	}
	return random_pos;
}


int main(){
	std::vector<std::vector<int>> board (3, std::vector<int>(3, 0));
	std::unordered_set<int> occupied {};


	int moves {0};

	while (moves < 9){
		draw_board(board);

		if (moves % 2 == 0){
			int location {user_input(occupied)};
			board[(location-1)/3][(location-1) % 3] = 2;
			occupied.insert(location);
		}

		else{
			int location {alg1(occupied)};
			board[(location-1)/3][(location-1) % 3] = 1;
			occupied.insert(location);
		}

		moves++;
		std::cout << "\n";
	}

	draw_board(board);

}
