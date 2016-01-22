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

// Check if the move is a capture
bool	Heuristic::checkCapture(int x, int y, GRID_REF grid){

	std::pair<PAIR_INT, PAIR_INT>	*ptr;

	if ((ptr = _checker.checkCapture(x, y, grid)) != NULL){
		delete ptr;
		return true;
	}
	return false;
}

int Heuristic::checkCloseTo(int x, int y, GRID_REF grid, eBlock closeTo){

	size_t counter = 0;

	for (size_t j = y - 1; j <= (size_t)(y + 1); j++){
		for (size_t i = x - 1; i <= (size_t)(x + 1); i++){

			if ((int)i >= 0 && (int)i < GRID_SIZE && (int)j >= 0 && (int)j < GRID_SIZE){

				if (grid[j][i] == closeTo) { counter++; }
			}
		}
	}

	return (int)counter;
}

int 	Heuristic::stopAlign(int i, int j, GRID_REF grid){
	eBlock player = (AIturn == TURN_PLAYER_1 ? PLAYER_1 : PLAYER_2);

	int sum = 0;

	sum += checkStopAlign(i, j, grid, player, i - 3, j - 3);
	sum += checkStopAlign(i, j, grid, player, i, j - 3);
	sum += checkStopAlign(i, j, grid, player, i + 3, j - 3);
	sum += checkStopAlign(i, j, grid, player, i + 3, j);
	sum += checkStopAlign(i, j, grid, player, i + 3, j + 3);
	sum += checkStopAlign(i, j, grid, player, i, j + 3);
	sum += checkStopAlign(i, j, grid, player, i - 3, j + 3);
	sum += checkStopAlign(i, j, grid, player, i - 3, j);
	return sum;
}

int	Heuristic::checkStopAlign(int x, int y, GRID_REF grid, eBlock player, int dirX, int dirY){
	eBlock opponent = (player == PLAYER_1 ? PLAYER_2 : PLAYER_1);
	(void)opponent;
	(void)grid;


	int signX = ((dirX - x) >= 0 ? 1 : -1);
	int signY = ((dirY - y) >= 0 ? 1 : -1);

	int counter = 0;

	for (int j = y; j != dirY; j += (1 * signY)){

		for (int i = x; i != dirX; i += (1 * signX)){

			if ((int)i >= 0 && (int)i < GRID_SIZE && (int)j >= 0 && (int)j < GRID_SIZE){
				if (grid[j][i] == opponent) { counter += 1; }
			}
		}
	}

	return (counter);
}

int	Heuristic::checkWin(GRID_REF grid, eTurn turn){

	eBlock player = (turn == TURN_PLAYER_1 ? PLAYER_1 : PLAYER_2);

	int sum = 0;
	for (size_t j = 0; j < GRID_SIZE; j++){
		for (size_t i = 0; i < GRID_SIZE; i++){
			if (grid[j][i] == player) {
				// sum += checkCloseToOpponent(i, j, grid, player);
				if (_checker.checkWin(i, j, grid, turn)){
					sum += 1000;
				}
			}
		}
	}
	return sum;
}

int Heuristic::makeAlign(int i, int j, GRID_REF grid){

	int sum = 0;

	sum += chekMakeAlign(i, j, grid, i - 3, j - 3);
	sum += chekMakeAlign(i, j, grid, i, j - 3);
	sum += chekMakeAlign(i, j, grid, i + 3, j - 3);
	sum += chekMakeAlign(i, j, grid, i + 3, j);
	sum += chekMakeAlign(i, j, grid, i + 3, j + 3);
	sum += chekMakeAlign(i, j, grid, i, j + 3);
	sum += chekMakeAlign(i, j, grid, i - 3, j + 3);
	sum += chekMakeAlign(i, j, grid, i - 3, j);

	return sum;
}

int Heuristic::chekMakeAlign(int x, int y, GRID_REF grid, int dirX, int dirY){

	eBlock player = (AIturn == TURN_PLAYER_1 ? PLAYER_1 : PLAYER_2);

	int signX = ((dirX - x) >= 0 ? 1 : -1);
	int signY = ((dirY - y) >= 0 ? 1 : -1);

	int counter = 0;

	for (int j = y; j != dirY; j += (1 * signY)){

		for (int i = x; i != dirX; i += (1 * signX)){

			if ((int)i >= 0 && (int)i < GRID_SIZE && (int)j >= 0 && (int)j < GRID_SIZE){
				if (grid[j][i] == player) { counter++; }
				else{
					if (counter <= 1)
						return 0;
					else
						return counter;
				}
			}
		}
	}

	return (counter);
}

//Check all variant of the shape [0][x][x][x][empty]
int Heuristic::oneThreeShape(int i, int j, GRID_REF grid, eBlock opponent){

	int sum = 0;
	if (oneThreeShape1(i, j, grid, opponent)) { sum += 10; }
	if (oneThreeShape2(i, j, grid, opponent)) { sum += 10; }
	if (oneThreeShape3(i, j, grid, opponent)) { sum += 10; }
	if (oneThreeShape4(i, j, grid, opponent)) { sum += 10; }
	if (oneThreeShape5(i, j, grid, opponent)) { sum += 10; }
	if (oneThreeShape6(i, j, grid, opponent)) { sum += 10; }
	if (oneThreeShape7(i, j, grid, opponent)) { sum += 10; }
	if (oneThreeShape8(i, j, grid, opponent)) { sum += 10; }

	return sum;
}

// [0][x][x][x][empty]
bool Heuristic::oneThreeShape1(int i, int j, GRID_REF grid, eBlock opponent){

	eBlock player = (opponent == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (i + 4 < GRID_SIZE){
		return 	grid[j][i + 1] == opponent &&
				grid[j][i + 2] == opponent &&
				grid[j][i + 3] == opponent &&
				grid[j][i + 4] == player;
	}
	return false;
}

// [0]
//	 [x]
//      [x]
//         [x]
//            [empty]
bool Heuristic::oneThreeShape2(int i, int j, GRID_REF grid, eBlock opponent){

	eBlock player = (opponent == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (i + 4 < GRID_SIZE && j + 4 < GRID_SIZE){
		return 	grid[j + 1][i + 1] == opponent &&
				grid[j + 2][i + 2] == opponent &&
				grid[j + 3][i + 3] == opponent &&
				grid[j + 4][i + 4] == player;
	}
	return false;
}

// [0]
// [x]
// [x]
// [x]
// [empty]
bool Heuristic::oneThreeShape3(int i, int j, GRID_REF grid, eBlock opponent){

	eBlock player = (opponent == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (j + 4 < GRID_SIZE){
		return 	grid[j + 1][i] == opponent &&
				grid[j + 2][i] == opponent &&
				grid[j + 3][i] == opponent &&
				grid[j + 4][i] == player;
	}
	return false;
}

//    	           [0]
//    	        [x]
//    	     [x]
//        [x]
// [empty]
bool Heuristic::oneThreeShape4(int i, int j, GRID_REF grid, eBlock opponent){

	eBlock player = (opponent == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (j + 4 < GRID_SIZE && i - 4 >= 0){
		return 	grid[j + 1][i - 1] == opponent &&
				grid[j + 2][i - 2] == opponent &&
				grid[j + 3][i - 3] == opponent &&
				grid[j + 4][i - 4] == player;;
	}
	return false;
}

// [empty][x][x][x][0]
bool Heuristic::oneThreeShape5(int i, int j, GRID_REF grid, eBlock opponent){

	eBlock player = (opponent == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (i - 4 >= 0){
		return 	grid[j][i - 1] == opponent &&
				grid[j][i - 2] == opponent &&
				grid[j][i - 3] == opponent &&
				grid[j][i - 4] == player;;
	}
	return false;
}

// [empty]
//        [x]
//           [x]
//              [x]
//                 [0]
bool Heuristic::oneThreeShape6(int i, int j, GRID_REF grid, eBlock opponent){

	eBlock player = (opponent == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (i - 4 >= 0 && j - 4 >= 0){
		return 	grid[j - 1][i - 1] == opponent &&
				grid[j - 2][i - 2] == opponent &&
				grid[j - 3][i - 3] == opponent &&
				grid[j - 4][i - 4] == player;
	}
	return false;
}

// [empty]
// [x]
// [x]
// [x]
// [0]
bool Heuristic::oneThreeShape7(int i, int j, GRID_REF grid, eBlock opponent){

	eBlock player = (opponent == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (j - 4 >= 0){
		return 	grid[j - 1][i] == opponent &&
				grid[j - 2][i] == opponent &&
				grid[j - 3][i] == opponent &&
				grid[j - 4][i] == player;
	}
	return false;
}

// 			   [empty]
// 		    [x]
//       [x]
// 	  [x]
// [0]
bool Heuristic::oneThreeShape8(int i, int j, GRID_REF grid, eBlock opponent){

	eBlock player = (opponent == PLAYER_1 ? PLAYER_2 : PLAYER_1);

	if (j - 4 >= 0 && i + 3 < GRID_SIZE){
		return 	grid[j - 1][i + 1] == opponent &&
				grid[j - 2][i + 2] == opponent &&
				grid[j - 3][i + 3] == opponent &&
				grid[j - 4][i + 4] == player;
	}
	return false;
}


//Check all variant of the shape [0][x][x][empty]
int Heuristic::oneTwoShape(int i, int j, GRID_REF grid, eBlock opponent){
	int sum = 0;

	if (oneTwoShape1(i, j, grid, opponent)) { sum += 10; }
	if (oneTwoShape2(i, j, grid, opponent)) { sum += 10; }
	if (oneTwoShape3(i, j, grid, opponent)) { sum += 10; }
	if (oneTwoShape4(i, j, grid, opponent)) { sum += 10; }
	if (oneTwoShape5(i, j, grid, opponent)) { sum += 10; }
	if (oneTwoShape6(i, j, grid, opponent)) { sum += 10; }
	if (oneTwoShape7(i, j, grid, opponent)) { sum += 10; }
	if (oneTwoShape8(i, j, grid, opponent)) { sum += 10; }

	return sum;
}

// [0][x][x][empty]
bool Heuristic::oneTwoShape1(int i, int j, GRID_REF grid, eBlock opponent){
	if (i + 3 < GRID_SIZE){
		return 	grid[j][i + 1] == opponent &&
				grid[j][i + 2] == opponent &&
				grid[j][i + 3] == eBlock::EMPTY;
	}
	return false;
}

// [0]
//	 [x]
//      [x]
//         [empty]
bool Heuristic::oneTwoShape2(int i, int j, GRID_REF grid, eBlock opponent){
	if (i + 3 < GRID_SIZE && j + 3 < GRID_SIZE){
		return 	grid[j + 1][i + 1] == opponent &&
				grid[j + 2][i + 2] == opponent &&
				grid[j + 3][i + 3] == eBlock::EMPTY;
	}
	return false;
}

// [0]
// [x]
// [x]
// [empty]
bool Heuristic::oneTwoShape3(int i, int j, GRID_REF grid, eBlock opponent){
	if (j + 3 < GRID_SIZE){
		return 	grid[j + 1][i] == opponent &&
				grid[j + 2][i] == opponent &&
				grid[j + 3][i] == eBlock::EMPTY;
	}
	return false;
}

//    	        [0]
//    	     [x]
//    	  [x]
// [empty]
bool Heuristic::oneTwoShape4(int i, int j, GRID_REF grid, eBlock opponent){
	if (j + 3 < GRID_SIZE && i - 3 >= 0){
		return 	grid[j + 1][i - 1] == opponent &&
				grid[j + 2][i - 2] == opponent &&
				grid[j + 3][i - 3] == eBlock::EMPTY;
	}
	return false;
}

// [empty][x][x][0]
bool Heuristic::oneTwoShape5(int i, int j, GRID_REF grid, eBlock opponent){
	if (i - 3 >= 0){
		return 	grid[j][i - 1] == opponent &&
				grid[j][i - 2] == opponent &&
				grid[j][i - 3] == eBlock::EMPTY;
	}
	return false;
}

// [empty]
//        [x]
//           [x]
//              [0]
bool Heuristic::oneTwoShape6(int i, int j, GRID_REF grid, eBlock opponent){
	if (i - 3 >= 0 && j - 3 >= 0){
		return 	grid[j - 1][i - 1] == opponent &&
				grid[j - 2][i - 2] == opponent &&
				grid[j - 3][i - 3] == eBlock::EMPTY;
	}
	return false;
}

// [empty]
// [x]
// [x]
// [0]
bool Heuristic::oneTwoShape7(int i, int j, GRID_REF grid, eBlock opponent){
	if (j - 3 >= 0){
		return 	grid[j - 1][i] == opponent &&
				grid[j - 2][i] == opponent &&
				grid[j - 3][i] == eBlock::EMPTY;
	}
	return false;
}

// 			[empty]
// 		 [x]
// 	  [x]
// [0]
bool Heuristic::oneTwoShape8(int i, int j, GRID_REF grid, eBlock opponent){
	if (j - 3 >= 0 && i + 3 < GRID_SIZE){
		return 	grid[j - 1][i + 1] == opponent &&
				grid[j - 2][i + 2] == opponent &&
				grid[j - 3][i + 3] == eBlock::EMPTY;
	}
	return false;
}
