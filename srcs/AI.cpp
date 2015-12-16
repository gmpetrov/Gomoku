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

	std::pair<int, int>	move = _minMax(grid);

	// End chrono
	end = std::chrono::system_clock::now();

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

	State chosen = _findBestMove(initial);

	return std::make_pair(chosen.getX(), chosen.getY());
}

State			AI::_findBestMove(State & state){

	eBlock	opponentPlayerForbidden = getOpponentPlayerForbidden();

	// will contain all results from minmax
	std::set<State> states;

	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){

			// Case is empty or forbidden for the opponent
			if (state.getGrid()[j][i] == eBlock::EMPTY || state.getGrid()[j][i] == opponentPlayerForbidden){

				// Copy the grid
				std::vector<std::vector<eBlock>> grid = state.getGrid();

				// Instanciate a new State
				State child(grid, &state, i, j);

				// result of minmax algo for the current node
				State result = _minMaxExplorer(child, _turn, false, ALGO_DEPTH);

				// add the result to the container
				states.insert(result);
			}
		}
	}

	// return the high rated state
	return _getMax(states);
}

std::vector<State>	AI::getPossibleMoves(State & state, eTurn & turn){

	eBlock	opponentPlayerForbidden = (turn == eTurn::TURN_PLAYER_1 ? PLAYER_2_FORBIDDEN : PLAYER_1_FORBIDDEN);

	std::vector<State>	container;

	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){

			// it's a possible move
			if (state.getGrid()[j][i] == eBlock::EMPTY || state.getGrid()[j][i] == opponentPlayerForbidden){
				// Copy the grid
				std::vector<std::vector<eBlock>> grid = state.getGrid();

				// Instanciate a new State
				State child(grid, &state, i, j);

				container.push_back(child);
			}
		}
	}
	return container;
}

State				AI::_minMaxExplorer(State & state, eTurn & turn, bool isMax, int depth){

	// eTurn opponentTurn = (turn == eTurn::TURN_PLAYER_1 ? eTurn::TURN_PLAYER_2 : eTurn::TURN_PLAYER_2);

	GRID grid = state.getGrid();

	std::cout << "DEPTH : " << depth << std::endl;

	if (_checker.checkWin(std::make_pair(state.getX(), state.getY()), grid, turn)){
		state.setRating(42000);
		return state;
	}
	// else if (_checker.checkWin(std::make_pair(state.getX(), state.getY()), grid, opponentTurn)){
	// 	state.setRating(-42000);
	// 	return state;
	// }
	// else if --> match null

	if (depth == 0){
		state.setRating(_evaluateChild(state));
		return state;
	}

	std::vector<State> moves = getPossibleMoves(state, turn);

	std::set<State> states;

	for (size_t i = 0; i < moves.size(); i++){
		states.insert(_minMaxExplorer(moves[i], turn, !isMax, depth - 1));
	}

	if (isMax)
		return _getMax(states);
	return _getMin(states);

}

int			AI::_evaluateChild(State & child){

	(void)child;

	int rnd = rand() % 100;

	return rnd;
}

State		AI::_getMax(std::set<State> & states){

	// Get iterator on last element
	std::set<State>::iterator it = std::prev(states.end());

	return *it;
}

State		AI::_getMin(std::set<State> & states){

	// Get iterator on last element
	std::set<State>::iterator it = states.begin();

	return *it;
}

void			AI::_printSet(std::set<State> states) const{
	for (std::set<State>::iterator it = states.begin(); it != states.end(); ++it){
		std::cout << "state rating : " << (*it).getRating() << ", x : " << (*it).getX() << ", y : " << (*it).getY() << std::endl;
	}
}
