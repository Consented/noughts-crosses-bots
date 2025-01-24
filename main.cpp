#include <iostream> 
#include <vector>
#include <random>
#include <unordered_set>
#include <unordered_map>

void draw_board(const std::vector<std::vector<int>> &board, const std::unordered_map<int, char> &symbols){
	// 1) Iterate through 2d vector
	// 2) Represent numerical values by ascii characters (0 = " ", 1 = "O", 2 = "X")

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			std::cout << symbols.at(board[i][j]);
			if (j < 2) { std::cout << "|"; }
		} 
		std::cout << "\n"; 
	} 
}

int user_input(const std::unordered_set<int> &occupied){
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


int alg1(const std::unordered_set<int> &occupied){
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
	std::vector<std::vector<int>> board (3, std::vector<int>(3, 0)); // Game board represented by 3x3 vector
	const std::unordered_map<int, char> symbols {{0, ' '}, {1, 'O'}, {2, 'X'}}; // Hash map used to convert board values into displayable characters
	std::unordered_set<int> occupied {}; // set used to store moves played previously


	bool player {true};

	while (occupied.size() < 9){

		draw_board(board, symbols);

		if (player){
			int location {user_input(occupied)}; 
			board[(location-1)/3][(location-1) % 3] = 2;
			occupied.insert(location);
		}
		else{
			int location {alg1(occupied)};
			board[(location-1)/3][(location-1) % 3] = 1;
			occupied.insert(location);
		}

		player = !player;
		std::cout << "\n";
	}

	draw_board(board, symbols);

}
