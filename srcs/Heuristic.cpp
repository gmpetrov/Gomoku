#include <Heuristic.hpp>

Heuristic::Heuristic(void){}

Heuristic::~Heuristic(void){}

Heuristic::Heuristic(const Heuristic & src){
	*this = src;
}

Heuristic & Heuristic::operator=(Heuristic const & src){
	(void)src;
	return *this;
}

// Check if there is an opponent's pawn close to player's pawn
bool	Heuristic::closeToPawn(GRID_REF grid, eBlock opponent, int x, int y){

	if (y - 1 >= 0 && grid[y - 1][x] == opponent)
		return true;
	else if (y - 1 >= 0 && x + 1 < GRID_SIZE && grid[y - 1][x + 1] == opponent)
		return true;
	else if (x + 1 < GRID_SIZE && grid[y][x + 1] == opponent)
		return true;
	else if (y + 1 < GRID_SIZE && x + 1 < GRID_SIZE && grid[y + 1][x + 1] == opponent)
		return true;
	else if (y + 1 < GRID_SIZE && grid[y + 1][x] == opponent)
		return true;
	else if (y + 1 < GRID_SIZE && x - 1 >= 0 && grid[y + 1][x - 1] == opponent)
		return true;
	else if (x - 1 >= 0 && grid[y][x - 1] == opponent)
		return true;
	else if (y - 1 >= 0 && x - 1 >= 0 && grid[y - 1][x + 1] == opponent)
		return true;
	return false;
}

// Check if the move is a capture
bool	Heuristic::checkCapture(std::pair<int, int> move, GRID_REF grid){

	std::pair<PAIR_INT, PAIR_INT>	*ptr;

	if ((ptr = _checker.checkCapture(move, grid)) != NULL){
		delete ptr;
		return true;
	}
	return false;
}

// Check if it's a winning move
bool	Heuristic::checkWin(std::pair<int, int> move, GRID_REF grid, eTurn & turn){
	return _checker.checkWin(move, grid, turn);
}

// Check if the move breaks an alignement
bool	Heuristic::stopALignement(std::pair<int, int> move, GRID_REF grid){

	int	lim = 4;
	int x = move.first;
	int y = move.second;
	int counter = 0;
	eBlock player = grid[y][x];
	eBlock opponent = (player == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	// Horizontal check
	for (int i = 1; (i <= lim) && ((x + i) < GRID_SIZE); i++){
		if (grid[y][x + i] == opponent)
			counter++;
		else
			break ;
	}

	if (counter >= 3) { return true; }

	counter = 0;

	for (int i = 1; (i <= lim) && ((x - i) >= 0); i++){
		if (grid[y][x - i] == opponent)
			counter++;
		else
			break ;
	}
	if (counter >= 3) { return true; }

	counter = 0;

	// Vertical check
	for (int i = 1; (i <= lim) && ((y - i) >= 0); i++){
		if (grid[y - i][x] == opponent)
			counter++;
		else
			break ;
	}
	if (counter >= 3) { return true; }

	counter = 0;

	for (int i = 1; (i <= lim) && ((y + i) < GRID_SIZE); i++){
		if (grid[y + i][x] == opponent)
			counter++;
		else
			break ;
	}
	if (counter >= 3) { return true; }

	counter = 0;

	// Diagonal check
	for (int i = 1; (i <= lim) && ((y - i) >= 0 && (x + i) < GRID_SIZE); i++){
		if (grid[y - i][x + i] == opponent)
			counter++;
		else
			break ;
	}
	if (counter >= 3) { return true; }

	counter = 0;

	for (int i = 1; (i <= lim) && ((y + i) < GRID_SIZE && (x + i) < GRID_SIZE); i++){
		if (grid[y + i][x + i] == opponent)
			counter++;
		else
			break ;
	}
	if (counter >= 3) { return true; }

	counter = 0;

	for (int i = 1; (i <= lim) && ((y + i) < GRID_SIZE && (x - i) >= 0); i++){
		if (grid[y + i][x - i] == opponent)
			counter++;
		else
			break ;
	}
	if (counter >= 3) { return true; }

	counter = 0;

	for (int i = 1; (i <= lim) && ((y - i) >= 0 && (x - i) >= 0); i++){
		if (grid[y - i][x - i] == opponent)
			counter++;
		else
			break ;
	}

	return false;
}