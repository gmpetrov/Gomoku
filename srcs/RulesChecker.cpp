#include <RulesChecker.hpp>

RulesChecker::RulesChecker(void){}

RulesChecker::~RulesChecker(void){}

RulesChecker::RulesChecker(const RulesChecker & src){
	*this = src;
}

RulesChecker & RulesChecker::operator=(RulesChecker const & src){
	(void)src;
	return *this;
}

/*
**	Take the last move as parameter and check if it's a win
*/

bool	RulesChecker::checkWin(int x, int y, std::vector<std::vector<eBlock>> & grid, eTurn & turn){

	return (_checkWinHorizontalCheck(x, y, grid, turn) || _checkWinVerticalCheck(x, y, grid, turn) || _checkWinDiagonalCheck(x, y, grid, turn));
}

bool	RulesChecker::_checkWinHorizontalCheck(int x, int y, std::vector<std::vector<eBlock>> & grid, eTurn & turn){

	int counter = 0;
	eBlock playerPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);

	if (grid[y][x] == playerPawn){ counter++; }

	// Lateral right check
	// (x + 1) because we already know actual value at x position
	for (int i = x + 1; i < GRID_SIZE; i++){

		// right mate is current player pawn, we increment the counter
		if (grid[y][i] == playerPawn)
			counter++;
		else
			break ;
	}

	// Lateral left check
	// (x - 1) because we already know actual value at x position
	for (int i = x - 1; i >= 0; i--){

		// left mate is current player pawn, we increment the counter
		if (grid[y][i] == playerPawn)
			counter++;
		else
			break ;
	}

	return (counter >= 5);
}

bool	RulesChecker::_checkWinVerticalCheck(int x, int y, std::vector<std::vector<eBlock>> & grid, eTurn & turn){

	int counter = 0;
	eBlock playerPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);

	if (grid[y][x] == playerPawn){ counter++; }

	// Vertical top check
	// (y - 1) because we already know actual value at y position
	for (int j = y - 1; j >= 0; j--){

		if (grid[j][x] == playerPawn)
			counter++;
		else
			break ;
	}

	// Vertical bottom check
	// (y - 1) because we already know actual value at y position
	for (int j = y + 1; j < GRID_SIZE; j++){

		if (grid[j][x] == playerPawn)
			counter++;
		else
			break ;
	}

	return (counter >= 5);
}

bool	RulesChecker::_checkWinDiagonalCheck(int x, int y, std::vector<std::vector<eBlock>> & grid, eTurn & turn){

	int counter = 0;
	eBlock playerPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);

	if (grid[y][x] == playerPawn){ counter++; }

	// Diagonal top right check
	for (int i = 1; (x + i < GRID_SIZE) && (y - i >= 0); i++){

		if (grid[y - i][x + i] == playerPawn)
			counter++;
		else
			break ;
	}

	// Diagonal bottom left check
	for (int i = 1; (x - i >= 0) && (y + i < GRID_SIZE); i++){

		if (grid[y + i][x - i] == playerPawn)
			counter++;
		else
			break ;
	}

	if (counter >= 5) { return true ; }

	counter = 0;

	if (grid[y][x] == playerPawn){ counter++; }

	// Diagonal bottom right check
	for (int i = 1; (x + i < GRID_SIZE) && (y + i < GRID_SIZE); i++){

		if (grid[y + i][x + i] == playerPawn)
			counter++;
		else
			break ;
	}

	// Diagonal top left check
	for (int i = 1; (x - i >= 0) && (y - i >= 0); i++){

		if (grid[y - i][x - i] == playerPawn)
			counter++;
		else
			break ;
	}

	return (counter >= 5);
}

/* Capture Checking */

std::pair<PAIR_INT, PAIR_INT>	 *RulesChecker::checkCapture(int x, int y, std::vector<std::vector<eBlock>> & grid){

	std::pair<PAIR_INT, PAIR_INT> *ptr;
	if ((ptr = _checkCaptureHorizontal(x, y, grid)) != NULL)
		return ptr;
	else if ((ptr = _checkCaptureVertical(x, y, grid)) != NULL)
		return ptr;
	else if ((ptr = _checkCaptureDiagonal(x, y, grid)) != NULL)
		return ptr;
	return NULL ;
}

std::pair<PAIR_INT, PAIR_INT>	 *RulesChecker::_checkCaptureHorizontal(int x, int y, std::vector<std::vector<eBlock>> & grid){

	// get player pawn
	eBlock playerPawn = grid[y][x];

	// get opponent pawn
	eBlock opponentPawn = (playerPawn == eBlock::PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);

	// Check bounds
	if (x + 3 < GRID_SIZE){

		// Check from left ro right
		if (grid[y][x] == playerPawn &&
			grid[y][x + 1] == opponentPawn &&
			grid[y][x + 2] == opponentPawn &&
			grid[y][x + 3] == playerPawn
			)
		{

			// Return the coordinates of the pawns
			std::pair<int, int> a(x + 1, y);
			std::pair<int, int> b(x + 2, y);
			return new std::pair<PAIR_INT, PAIR_INT>(a, b);
		}
	}

	if (x - 3 >= 0){

		// Check from right to left
		if (grid[y][x] == playerPawn &&
			grid[y][x - 1] == opponentPawn &&
			grid[y][x - 2] == opponentPawn &&
			grid[y][x - 3] == playerPawn
			)
		{

			// Return the coordinates of the pawns
			std::pair<int, int> a(x - 1, y);
			std::pair<int, int> b(x - 2, y);
			return new std::pair<PAIR_INT, PAIR_INT>(a, b);
		}
	}

	return NULL ;
}

std::pair<PAIR_INT, PAIR_INT>	 *RulesChecker::_checkCaptureVertical(int x, int y, std::vector<std::vector<eBlock>> & grid){

	// get player pawn
	eBlock playerPawn = grid[y][x];

	// get opponent pawn
	eBlock opponentPawn = (playerPawn == eBlock::PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);

	// Check if we are out of bounds
	if (y + 3 < GRID_SIZE){

		// Check from top to bottom
		if (grid[y][x] == playerPawn &&
			grid[y + 1][x] == opponentPawn &&
			grid[y + 2][x] == opponentPawn &&
			grid[y + 3][x] == playerPawn
			)
		{

			// Return the coordinates of the pawns
			std::pair<int, int> a(x, y + 1);
			std::pair<int, int> b(x, y + 2);
			return new std::pair<PAIR_INT, PAIR_INT>(a, b);
		}
	}

	if (y - 3 >= 0){

		// Check from bottom to top
		if (grid[y][x] == playerPawn &&
			grid[y - 1][x] == opponentPawn &&
			grid[y - 2][x] == opponentPawn &&
			grid[y - 3][x] == playerPawn
			)
		{

			// Return the coordinates of the pawns
			std::pair<int, int> a(x, y - 1);
			std::pair<int, int> b(x, y - 2);
			return new std::pair<PAIR_INT, PAIR_INT>(a, b);;
		}
	}
	return NULL;
}

std::pair<PAIR_INT, PAIR_INT>  *RulesChecker::_checkCaptureDiagonal(int x, int y, std::vector<std::vector<eBlock>> & grid){

	// get player pawn
	eBlock playerPawn = grid[y][x];

	// get opponent pawn
	eBlock opponentPawn = (playerPawn == eBlock::PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);

	// Check if we are not out of bounds
	if (x + 3 < GRID_SIZE && y - 3 >= 0){

		// Check from bottom to top right
		if (grid[y][x] == playerPawn &&
			grid[y - 1][x + 1] == opponentPawn &&
			grid[y - 2][x + 2] == opponentPawn &&
			grid[y - 3][x + 3] == playerPawn
			)
		{

			// Return the coordinates of the pawns
			std::pair<int, int> a(x + 1, y - 1);
			std::pair<int, int> b(x + 2, y - 2);
			return new std::pair<PAIR_INT, PAIR_INT>(a, b);
		}
	}

	// Check if we are not out of bounds
	if (x + 3 < GRID_SIZE && y + 3 < GRID_SIZE){

		// Check from top to bottom right
		if (grid[y][x] == playerPawn &&
			grid[y + 1][x + 1] == opponentPawn &&
			grid[y + 2][x + 2] == opponentPawn &&
			grid[y + 3][x + 3] == playerPawn
			)
		{

			// Return the coordinates of the pawns
			std::pair<int, int> a(x + 1, y + 1);
			std::pair<int, int> b(x + 2, y + 2);
			return new std::pair<PAIR_INT, PAIR_INT>(a, b);
		}
	}

	// Check if we are not out of bounds
	if (x - 3 >= 0 && y + 3 < GRID_SIZE){

		// Check from top to bottom left
		if (grid[y][x] == playerPawn &&
			grid[y + 1][x - 1] == opponentPawn &&
			grid[y + 2][x - 2] == opponentPawn &&
			grid[y + 3][x - 3] == playerPawn
			)
		{

			// Return the coordinates of the pawns
			std::pair<int, int> a(x - 1, y + 1);
			std::pair<int, int> b(x - 2, y + 2);
			return new std::pair<PAIR_INT, PAIR_INT>(a, b);
		}
	}

	// Check if we are not out of bounds
	if (x - 3 >= 0 && y - 3 >= 0){

		// Check from bottom to top left
		if (grid[y][x] == playerPawn &&
			grid[y - 1][x - 1] == opponentPawn &&
			grid[y - 2][x - 2] == opponentPawn &&
			grid[y - 3][x - 3] == playerPawn
			)
		{

			// Return the coordinates of the pawns
			std::pair<int, int> a(x - 1, y - 1);
			std::pair<int, int> b(x - 2, y - 2);
			return new std::pair<PAIR_INT, PAIR_INT>(a, b);
		}
	}

	return NULL;
}

bool	RulesChecker::checkEndingCapture(std::pair<int, int> index, GRID_REF grid, eTurn & turn, int & opponentScore, PLAYER_PAWNS_REF container){

	std::pair<PAIR_INT, PAIR_INT> *ptr;

	// Get opponent block
	eBlock opponent = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);
	// int opponentScore = (turn == eTurn::TURN_PLAYER_1 ? _player2Captures : _player1Captures);

	// Iterate through grid
	for (int j = 0; j < GRID_SIZE; j++){
		for (int i = 0; i < GRID_SIZE; i++){

			// If the case is empty
			if (grid[j][i] == eBlock::EMPTY){

				// we set the case at this index to be the opponent (needed by _checkCapture)
				grid[j][i] = opponent;

				// if there is possible capture we return true, the game continue
				if ((ptr = checkCapture(i, j, grid)) != NULL){

					bool res = false;
					if ((res = _checkIfCaptureBreaksAlignement(ptr, index, grid, turn, container))){
						std::cout << "BREAKS 5 STONES" << std::endl;
					}
					else{

						// check if the opponent can win with this capture
						if (opponentScore >= 8) {
							res = true;
						}
					}

					// We set back the value at the index to empty
					grid[j][i] = eBlock::EMPTY;

					// clean
					delete ptr;

					return res ;
				}

				// We set back the value at the index to empty
				grid[j][i] = eBlock::EMPTY;
			}
		}
	}
	return false ;
}

bool	RulesChecker::_checkIfCaptureBreaksAlignement(std::pair<PAIR_INT, PAIR_INT> *captures, PAIR_INT last, GRID_REF grid, eTurn & turn, PLAYER_PAWNS_REF container){

	// Get the captured pairs
	std::pair<int, int> a = (*captures).first;
	std::pair<int, int> b = (*captures).second;

	// Get captured's players's container
	// std::vector<std::pair<int, int>> & container = (turn == eTurn::TURN_PLAYER_1 ? _pawnsPlayer1 : _pawnsPlayer2);

	// remove the pawn for the check
	_removePawn(container, a, grid);
	_removePawn(container, b, grid);

	// check if it's a win, we want to return the opposite of the return value of checkWinm
	bool res = !checkWin(last.first, last.second, grid, turn);

	// rollback
	container.push_back(a);
	container.push_back(b);

	eBlock blockCurrentPlayer = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);
	grid[a.second][a.first] = blockCurrentPlayer;
	grid[b.second][b.first] = blockCurrentPlayer;

	return res;
}

/*
**	Take the current player's last move , if there is a possible double three, make further moves forbidden
*/
void	RulesChecker::checkDoubleThree(std::pair<int, int> index, std::vector<std::vector<eBlock>> & grid, eTurn & turn){

	eBlock	forbiddenMove = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1_FORBIDDEN : eBlock::PLAYER_2_FORBIDDEN);

	std::pair<int, int>	*secondPawn;

	if ((secondPawn = _findAdjacentPawn(index, grid, turn)) != NULL){

		std::vector<std::pair<int, int>> *three;

		// Checking if it's a possible three
		if ((three = _checkIfThree(index, *secondPawn, grid, turn)) != NULL){

			std::vector<std::pair<int, int>> *secondThree;

			if ((secondThree = _findThreeNearBy(index, *secondPawn, grid, turn)) != NULL){
				// We've find an other three

				std::vector<std::pair<int, int>> 	*matches;

				// Check if the threes are sharing one more pawns
				if ((matches = _compareThrees(*three, *secondThree)) != NULL){

					// Iterate through each match
					for (size_t i = 0; i < matches->size(); i++){
						int x = (*matches)[i].first;
						int y = (*matches)[i].second;

						if (_checkIfReallyForbidden(std::make_pair(x, y), index, *secondPawn, grid, turn)){

							// Make the match a forbidden move for the current player
							grid[y][x] = forbiddenMove;
						}
					}

					// clean
					delete matches;
					delete secondThree;

				}

			}

			// clean
			delete three;
		}
	}
}

/*
**	Take two pawn as parameter and if they form a possible three, return all possible moves for the third pawn
*/
std::vector<std::pair<int, int>>		*RulesChecker::_checkIfThree(std::pair<int, int> a, std::pair<int, int> b, std::vector<std::vector<eBlock>> & grid, eTurn & turn){

	int x1 = a.first;
	int y1 = a.second;
	int x2 = b.first;
	int y2 = b.second;

	if (!_isPlayerPawn(x1, y1, grid, turn) || !_isPlayerPawn(x2, y2, grid, turn))
		return NULL;

	if (x1 == x2 && y1 != y2){
		// It's a vertical alignement

		if (y2 < y1)
			_swapInt(y1, y2);

		if (y1 - 1 >= 0 && y2 + 1 < GRID_SIZE && _isEmpty(x1, y1 - 1, grid) && _isEmpty(x1, y2 + 1, grid)){

			std::vector<std::pair<int, int>> *v = new std::vector<std::pair<int, int>>();

			// Return a pointer on a vectore containing all possible third pawn for a three

			v->push_back(std::make_pair(x1, y1 - 1));
			v->push_back(std::make_pair(x1, y2 + 1));

			if (_isEmpty(x1, y1 - 2, grid))
				v->push_back(std::make_pair(x1, y2 - 2));
			if (_isEmpty(x1, y2 + 2, grid))
				v->push_back(std::make_pair(x1, y2 + 2));

			return v;
		}

	}
	else if (x1 != x2 && y1 == y2){
		// Horizontal alignement

		if (x2 < x1)
			_swapInt(x1, x2);

		if (x1 - 1 >= 0 && x2 + 1 < GRID_SIZE && _isEmpty(x1 - 1, y1, grid) && _isEmpty(x2 + 1, y2, grid)){

			std::vector<std::pair<int, int>> *v = new std::vector<std::pair<int, int>>();

			// Return a pointer on a vectore containing all possible third pawn for a three

			v->push_back(std::make_pair(x1 - 1, y1));
			v->push_back(std::make_pair(x2 + 1, y2));

			if (_isEmpty(x1 - 2, y1, grid))
				v->push_back(std::make_pair(x1 - 2, y1));
			if (_isEmpty(x2 + 2, y2, grid))
				v->push_back(std::make_pair(x2 + 2, y2));

			return v;
		}
	}
	else if (x1 != x2 && y1 != y2){
		// Diagonal alignement

		if ((x1 < x2 && y1 < y2) || (x2 < x1 && y2 < y1)){
			//  o
			//	  o

			if ((x2 < x1 && y2 < y1)){
				_swapInt(x1, x2);
				_swapInt(y1, y2);
			}

			if (x1 - 1 >= 0 && y1 - 1 >= 0 && x2 + 1 < GRID_SIZE && y2 + 1 < GRID_SIZE && _isEmpty(x1 - 1, y1 - 1, grid) && _isEmpty(x2 + 1, y2 + 1, grid)){

				// Return a pointer on a vectore containing all possible third pawn for a three

				std::vector<std::pair<int, int>> *v = new std::vector<std::pair<int, int>>();

				v->push_back(std::make_pair(x1 - 1, y1 - 1));
				v->push_back(std::make_pair(x2 + 1, y2 + 1));

				if (_isEmpty(x1 - 2, y1 - 2, grid))
					v->push_back(std::make_pair(x1 - 2, y1 - 2));
				if (_isEmpty(x2 + 2, y2 + 2, grid))
					v->push_back(std::make_pair(x2 + 2, y2 + 2));

				return v;
			}
		}
		else if ((x1 > x2 && y1 < y2) || (x2 > x1 && y2 < y1)){

			//    o
			//  o

			if ((x2 > x1 && y2 < y1)){
				_swapInt(x1, x2);
				_swapInt(y1, y2);
			}

			if (x1 + 1 < GRID_SIZE && y1 - 1 >= 0 && x2 - 1 >= 0 && y2 + 1 < GRID_SIZE && _isEmpty(x1 + 1, y1 - 1, grid) && _isEmpty(x2 - 1, y2 + 1, grid)){

				// Return a pointer on a vectore containing all possible third pawn for a three

				std::vector<std::pair<int, int>> *v = new std::vector<std::pair<int, int>>();

				v->push_back(std::make_pair(x1 + 1, y1 - 1));
				v->push_back(std::make_pair(x2 - 1, y2 + 1));

				if (_isEmpty(x1 + 2, y1 - 2, grid))
					v->push_back(std::make_pair(x1 + 2, y1 - 2));
				if (_isEmpty(x2 - 2, y2 + 2, grid))
					v->push_back(std::make_pair(x2 - 2, y2 + 2));

				return v;
			}
		}
	}

	return NULL;
}

/*
** Return a possible nearby a given possible three, return null otherwise
*/
std::vector<std::pair<int, int>> 	*RulesChecker::_findThreeNearBy(std::pair<int, int> ref1, std::pair<int, int>ref2, std::vector<std::vector<eBlock>> & grid, eTurn & turn){

	int RANGE = 8;

	int x_init = ref1.first;
	int y_init = ref1.second;

	int x = x_init - RANGE;
	int y = y_init - RANGE;

	// Get the pawn representing the current player
	eBlock	playerPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : PLAYER_2);

	for (int j = y; j < (y + 2 * RANGE); j++){
		for (int i = x; i < (x + 2 * RANGE); i++){

			// Check that we are not out of bounds
			if (j >= 0 && j < GRID_SIZE  && i >= 0 && i < GRID_SIZE){

				std::pair<int, int> tmp = std::make_pair(i, j);

				if (grid[j][i] == playerPawn && !pair_compare(tmp, ref1) && !pair_compare(tmp, ref2)){

					// THe pawn found, is not ref1 nor ref2

					std::pair<int, int> *match;

					if ((match =  _findAdjacentPawn(tmp, grid, turn)) != NULL){

						std::vector<std::pair<int, int>> *three;

						if ((three = _checkIfThree(tmp, *match, grid, turn)) != NULL){

							delete match;
							return three;
						}

						delete match;
					}

				}

			}

		}
	}
	return NULL;
}

/*
**	return a pair representing the position of an adjacent pawn
*/
std::pair<int, int>					*RulesChecker::_findAdjacentPawn(std::pair<int, int> init, std::vector<std::vector<eBlock>> & grid, eTurn & turn){

	int x = init.first;
	int y = init.second;

	// Get the pawn representing the current player
	eBlock	playerPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : PLAYER_2);

//  Looping to check all the possibilty around the given pawn
//  [ ][ ][ ]
//  [ ][][ ]
//  [ ][ ][ ]

	for (int tmp_y = y - 1; tmp_y <= y + 1; tmp_y++){
		for (int tmp_x = x - 1; tmp_x <= x + 1; tmp_x++){

			if (tmp_x == x && tmp_y == y)
				continue ;

			// Checking if we are out of bounds and if the position point to a player pawn
			if (tmp_x < GRID_SIZE && tmp_x >= 0 && tmp_y < GRID_SIZE && tmp_y >= 0 && grid[tmp_y][tmp_x] == playerPawn){

					std::pair<int, int>	*match = new std::pair<int, int>(std::make_pair(tmp_x, tmp_y));
					return match;
			}
		}
	}
	return NULL;
}

std::vector<std::pair<int, int>> 	*RulesChecker::_compareThrees(std::vector<std::pair<int, int>> a, std::vector<std::pair<int, int>> b){

	std::vector<std::pair<int, int>> *matches = new std::vector<std::pair<int, int>>();

	for (size_t i = 0; i < a.size(); i++){
		for (size_t k = 0; k < b.size(); k++){
			if (a[i].first == b[k].first && a[i].second == b[k].second){
				matches->push_back(a[i]);
			}
		}
	}

	if (matches->empty()){
		delete matches;
		return NULL;
	}

	return matches;
}

bool							RulesChecker::_checkIfReallyForbidden(std::pair<int, int> forbidden, std::pair<int, int> a, std::pair<int, int>b, GRID_REF grid, eTurn & turn){

	// Get the pawn representing the current player
	eBlock	opponentPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);

	int delta_x = abs(a.first - b.first);
	int delta_y = abs(a.second - b.second);

	int forbidden_x = forbidden.first;
	int forbidden_y = forbidden.second;

	int check_x = forbidden_x - delta_x;
	int check_y = forbidden_y - delta_y;

	if (check_x >= 0 && check_x < GRID_SIZE && check_y >= 0 && check_y < GRID_SIZE && grid[check_y][check_x] == opponentPawn)
		return false;

	check_x = forbidden_x + delta_x;
	check_y = forbidden_y + delta_y;

	if (check_x >= 0 && check_x < GRID_SIZE && check_y >= 0 && check_y < GRID_SIZE && grid[check_y][check_x] == opponentPawn)
		return false;

	return true;
}

bool	RulesChecker::_isEmpty(int x, int y, std::vector<std::vector<eBlock>> & grid){
	if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE)
		return false;
	return grid[y][x] == eBlock::EMPTY;
}


void	RulesChecker::_swapInt(int  & a, int & b){
	int tmp = a;

	a = b;
	b = tmp;
}

bool	RulesChecker::_isPlayerPawn(int x, int y, GRID_REF grid, eTurn & turn){

	// Get the pawn representing the current player
	eBlock	playerPawn = (turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : PLAYER_2);

	if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE)
		return false;
	return grid[y][x] == playerPawn;
}

void	RulesChecker::_removePawn(std::vector<std::pair<int, int>> & container, std::pair<int, int> pawn, GRID_REF grid){

	// Loop through the container
	for (std::vector<std::pair<int, int>>::iterator it = container.begin(); it != container.end(); ++it){
		if (pair_compare(*it, pawn)){

			std::cout << "PAWN REMOVED" << std::endl;
			// Compare the pawns to find the one to delete
			container.erase(it);
			grid[pawn.second][pawn.first] = eBlock::EMPTY;
			return ;
		}
	}
}

void	RulesChecker::removePawnPair(PAIR_INT a, PAIR_INT b, PLAYER_PAWNS_REF container, GRID_REF grid)
{
	// Delete the pawns
	_removePawn(container, a, grid);
	_removePawn(container, b, grid);
}

bool	pair_compare(std::pair<int, int> & a, std::pair<int, int> & b)
{
	return (a.first == b.first && a.second == b.second);
}

