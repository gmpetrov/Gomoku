#include <AI.hpp>

AI::AI(void) : _elapsedTime(0){
	std::cout << "AI instanciated" << std::endl;
}

AI::~AI(void){}

AI::AI(const AI & src){
	*this = src;
}

AI &	AI::operator=(AI const & rhs){
	(void)rhs;
	return *this;
}

std::pair<int, int>		AI::play(std::vector<std::vector<eBlock>> & grid){

	std::chrono::time_point<std::chrono::system_clock> start, end;

	// Start chrono
	start = std::chrono::system_clock::now();

	sleep(2);


	// End chrono
	end = std::chrono::system_clock::now();

	_elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

	std::cout << "YOLO" << _elapsedTime << std::endl;

	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){
			if (grid[j][i] == eBlock::EMPTY)
				return std::make_pair(i, j);
		}
	}



	return std::make_pair(0, 0);
}

void	AI::setTurn(eTurn turn){
	_turn = turn;
}

eTurn	AI::getTurn(void){
	return _turn;
}

float	AI::getElapsedTime(void){
	return _elapsedTime;
}