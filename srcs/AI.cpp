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
	_heur.AIturn = turn;
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

				int tmp = _calcMin(grid, notTurn(_turn), ALGO_DEPTH - 1, alpha, beta);

				_cancelPlay(grid, i, j);

				if (tmp > alpha){
					alpha = tmp;
					xMax = i;
					yMax = j;
				}
			}
		}
	}
	return std::make_pair(xMax, yMax);
}

int		AI::_calcMin(GRID_REF grid, eTurn turn, int depth, int alpha, int beta){

	// Get opponent forbidden id
	eBlock	opponentPlayerForbidden = (turn == eTurn::TURN_PLAYER_1 ? PLAYER_2_FORBIDDEN : PLAYER_1_FORBIDDEN);

	// end of recursion
	if (depth == 0) {
		int res = _evaluateGrid(grid);
		// return _evaluateGrid(grid);
		// std::cout << "SCORE : " << res << std::endl;
		return res;
	}

	// Iterate through grid
	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){

			// Check for empty position
			if (grid[j][i] == eBlock::EMPTY || grid[j][i] == opponentPlayerForbidden){

				// We can play
				_play(grid, turn, i, j);

				// get max
				int tmp = _calcMax(grid, notTurn(turn), depth - 1, alpha, beta);

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

int		AI::_calcMax(GRID_REF grid, eTurn turn, int depth, int alpha, int beta){

	// Get opponent forbidden id
	eBlock	opponentPlayerForbidden = (turn == eTurn::TURN_PLAYER_1 ? PLAYER_2_FORBIDDEN : PLAYER_1_FORBIDDEN);

	// end of recursion
	if (depth == 0) {
		int res = _evaluateGrid(grid);
		// return _evaluateGrid(grid);
		// std::cout << "SCORE : " << res << std::endl;
		return res;
	}

	// Iterate through grid
	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){

			// Check for empty position
			if (grid[j][i] == eBlock::EMPTY || grid[j][i] == opponentPlayerForbidden){

				// We can play
				_play(grid, turn, i, j);

				// get min
				int tmp = _calcMin(grid, notTurn(turn), depth - 1, alpha, beta);

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
	eBlock playerPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1_SIM : eBlock::PLAYER_2_SIM);

	grid[y][x] = playerPawn;
}

void	AI::_cancelPlay(GRID_REF grid, int x, int y){
	grid[y][x] = eBlock::EMPTY;
}

int			AI::_evaluateGrid(GRID_REF grid){

//	===> Evaluation priority descending order

	// 1 - Win
	// 2 - Stop oppoenent alignement
	// 3 - Make alignement
	// 4 - Capture opponent
	// 4 - Random move

	eBlock player = (_turn == TURN_PLAYER_1 ? PLAYER_1 : PLAYER_2);
	eBlock playerSim = (_turn == TURN_PLAYER_1 ? PLAYER_1_SIM : PLAYER_2_SIM);
	eBlock opponent = (player == PLAYER_1 ? PLAYER_2 : PLAYER_1);
	eTurn opponentTurn = (_turn == TURN_PLAYER_1 ? TURN_PLAYER_2 : TURN_PLAYER_1);
	std::pair<PAIR_INT, PAIR_INT> *ptr;

	(void)opponent;
	(void)opponentTurn;
	(void)ptr;

	int score = 0;
	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){


			if (grid[j][i] == playerSim) {
				if (_checker.checkWin(i, j, grid, _turn)){
					score += EVAL_WIN;
				}
				if ((ptr = _checker.checkCapture(i, j, grid)) != NULL){
					delete ptr;
					score += EVAL_CAPTURE;
				}
				score += _heur.oneTwoShape(i, j, grid, opponent);
				score += _heur.oneThreeShape(i, j, grid, opponent);
				// score += _heur.makeAlign(i, j, grid);
				score += (_heur.checkCloseTo(i, j, grid, player));
			}
			else if (grid[j][i] == player){

			}

				// if (_heur.oneThreeShape(i, j, grid, opponent)){
 			// 		score += EVAL_ONE_THREE_SHAPE;
				// }
				// score += _heur.checkCloseTo(i, j, grid, opponent);

				// score += _heur.makeAlign(i, j, grid);
		}
	}
	return ((score == 0) ? rand() % 361 : score);
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
