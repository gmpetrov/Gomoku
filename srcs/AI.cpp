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

    std::chrono::duration<double> elapsed_seconds = end-start;

    _elapsedTime = elapsed_seconds.count();

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

std::pair<int, int>			AI::_minMax(GRID_REF grid){

	int xMax = 0;
	int yMax = 0;
	int alpha  = -42000;
	int beta   = 42000;

	eBlock	opponentPlayerForbidden = getOpponentPlayerForbidden();

	std::cout << "DEPTH : " << ALGO_DEPTH << std::endl;

	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){

			// Case is empty or forbidden for the opponent
			if (grid[j][i] == eBlock::EMPTY || grid[j][i] == opponentPlayerForbidden){

				_play(grid, _turn, i, j);

				int tmp = _calcMin(grid, notTurn(_turn), std::make_pair(i, j), ALGO_DEPTH - 1, alpha, beta);

				if (alpha < tmp){
					alpha = tmp;
					xMax = i;
					yMax = j;
				}

				_cancelPlay(grid, i, j);
			}
		}
	}
	return std::make_pair(xMax, yMax);
}

int		AI::_calcMin(GRID_REF grid, eTurn turn, std::pair<int, int> move, int depth, int alpha, int beta){

	// Get opponent forbidden id
	eBlock	opponentPlayerForbidden = (turn == eTurn::TURN_PLAYER_1 ? PLAYER_2_FORBIDDEN : PLAYER_1_FORBIDDEN);

	// end of recursion
	if (depth == 0) {
		int val = _evaluateGrid(grid, turn, move);
		// std::cout << "EVAL = " << val << std::endl;
		return val;
	}

	// Iterate through grid
	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){

			// Check for empty position
			if (grid[j][i] == eBlock::EMPTY || grid[j][i] == opponentPlayerForbidden){

				// We can play
				_play(grid, turn, i, j);

				// get max
				int tmp = _calcMax(grid, notTurn(turn), std::make_pair(i, j), depth - 1, alpha, beta);

				// Cancel previous move
				_cancelPlay(grid, i, j);

				// update beta value
				if (beta > tmp) { beta = tmp; }

				if (beta <= alpha) { return beta; }
			}
		}
	}
	return beta;
}

int		AI::_calcMax(GRID_REF grid, eTurn turn, std::pair<int, int> move, int depth, int alpha, int beta){

	// Get opponent forbidden id
	eBlock	opponentPlayerForbidden = (turn == eTurn::TURN_PLAYER_1 ? PLAYER_2_FORBIDDEN : PLAYER_1_FORBIDDEN);

	// end of recursion
	if (depth == 0) { return _evaluateGrid(grid, turn, move); }

	// Iterate through grid
	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){

			// Check for empty position
			if (grid[j][i] == eBlock::EMPTY || grid[j][i] == opponentPlayerForbidden){

				// We can play
				_play(grid, turn, i, j);

				// get min
				int tmp = _calcMin(grid, notTurn(turn), std::make_pair(i, j), depth - 1, alpha, beta);

				// Cancel previous move
				_cancelPlay(grid, i, j);

				// update min value
				if (alpha < tmp) { alpha = tmp; }

				if (beta <= alpha) { return alpha; }
			}
		}
	}
	return alpha;
}

void	AI::_play(GRID_REF grid, eTurn turn, int x, int y){
	eBlock playerPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);

	grid[y][x] = playerPawn;
}

void	AI::_cancelPlay(GRID_REF grid, int x, int y){
	grid[y][x] = eBlock::EMPTY;
}

int			AI::_evaluateGrid(GRID_REF grid, eTurn turn, std::pair<int, int> move){

//	===> Evaluation priority descending order
	// Close to opponent pawn ?
	// Break alignement ?
	// Make alignement ?
	// Capture ?
	// Win ?

	eBlock playerBlock = grid[move.second][move.first];
	eBlock opponentBlock = (playerBlock == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (_heur.checkWin(move, grid, turn)){
		return EVAL_WIN;
	}
	else if (_heur.stopALignement(move, grid)){
		return EVAL_STOP_ALIGN;
	}
	else if (_heur.checkCapture(move, grid)){
		return EVAL_CAPTURE;
	}
	else if (_heur.closeToPawn(grid, playerBlock, move.first, move.second)){
		return EVAL_ALIGN;
	}
	else if (_heur.closeToPawn(grid, opponentBlock, move.first, move.second)){
		return EVAL_CLOSE_OPPOENENT;
	}
	return rand() % 100;
}

void			AI::_printSet(std::set<State> states) const{
	for (std::set<State>::iterator it = states.begin(); it != states.end(); ++it){
		std::cout << "state rating : " << (*it).getRating() << ", x : " << (*it).getX() << ", y : " << (*it).getY() << std::endl;
	}
}

// Return the opposite turn
eTurn			AI::notTurn(eTurn turn){
	return (turn == TURN_PLAYER_1 ? TURN_PLAYER_2 : TURN_PLAYER_1);
}
