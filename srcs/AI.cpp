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

	// sleep(2);


	// End chrono
	end = std::chrono::system_clock::now();

	std::pair<int, int>	move = _minMax(grid);

	_elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

	return move;
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

eBlock	AI::getCurrentPlayerForbidden(void){
	return (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1_FORBIDDEN : eBlock::PLAYER_2_FORBIDDEN);
}

eBlock	AI::getOpponentPlayerForbidden(void){
	return (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_2_FORBIDDEN : eBlock::PLAYER_1_FORBIDDEN);
}

std::pair<int, int>	AI::_minMax(std::vector<std::vector<eBlock>> & grid){

	State initial(grid);

	_findPossibleMoves(initial);

	std::set<State>::iterator it = std::prev(initial.getChildren().end());

	State chosen = *it;

	return std::make_pair(chosen.getX(), chosen.getY());
}

void			AI::_findPossibleMoves(State & state){

	eBlock	opponentPlayerForbidden = getOpponentPlayerForbidden();

	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){
			if (state.getGrid()[j][i] == eBlock::EMPTY || state.getGrid()[j][i] == opponentPlayerForbidden){

				// Copy the grid
				std::vector<std::vector<eBlock>> grid = state.getGrid();

				// Instanciate a new State
				State child(grid, &state, i, j);

				// Evaluate the child
				_evaluateChild(child);

				// Add the new state to current state's children
				state.addChild(child);
			}
		}
	}
}

void			AI::_evaluateChild(State & child){
	int rnd = rand() % 100;

	child.setRating(rnd);
}

void			AI::_printSet(std::set<State> states) const{
	for (std::set<State>::iterator it = states.begin(); it != states.end(); ++it){
		std::cout << "state rating : " << (*it).getRating() << ", x : " << (*it).getX() << ", y : " << (*it).getY() << std::endl;
	}
}
