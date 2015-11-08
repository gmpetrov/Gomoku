/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:45:21 by gpetrov           #+#    #+#             */
/*   Updated: 2015/11/05 17:38:58 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Board.hpp>

bool	pair_compare(std::pair<int, int> a, std::pair<int, int> b);

Board::Board(void){}

Board::Board(eChoice choice) : isAlive(true), _choice(choice), _turn(eTurn::TURN_PLAYER_1), _grid(GRID_SIZE, std::vector<eBlock>(GRID_SIZE)), _player1Captures(0), _player2Captures(0){
	_initGrid();
}

Board::~Board(void){

}

Board::Board(const Board & src){
	*this = src;
}

Board &	Board::operator=(Board const & rhs){
	this->_width = rhs._width;
	this->_height = rhs._height;
	return *this;
}

void	Board::quit(void){
	std::cout << "You quit the game" << std::endl;
	exit(0);
}

std::vector<std::vector<eBlock>> Board::getMap(void){
	return _map;
}

void	Board::updateMap(void){
	if (!isAlive)
		return ;
}

void	Board::move(void){

}

void 	Board::handleKey(eKeys key, IGraphicHandler *graph){
	if (key == eKeys::ESC){

		// Exit the game
		throw std::string("quit");
	}
	else if (key == eKeys::MOUSE_LEFT){

		// Get the index of the current move
		std::pair<int, int> index = graph->play(_turn);

		// Check that the grid is empty at move's coordinates
		if (!_isCaseEmpty(index))
			return ;

		// Set the move on the grid
		_setMove(index);

		std::pair<PAIR_INT, PAIR_INT> *ptr;

		if ((ptr = _checkCapture(index)) != NULL){
			// checkCapture will respond with a pointer on a pairs of coordinate of the pawns to remove in case of capture
			// Remember to delete the pointer after utilisation

			// Delete the pairs
			_removePawnPair((*ptr).first, (*ptr).second);

			// Update scores
			_updateCaptureScore();

			// Clean
			delete ptr;
		}
		else if (_checkWin(index)){

			// Check if there is a possible end capture move
			if (!_checkEndingCapture(index)){
				// It's a winner move
				throw std::string("win");
			}
			std::cout << "POSSIBLE END CAPTURE" << std::endl;

		}

		// Update turn obviously
		_updateTurn(graph);
	}
	else if (key == eKeys::SPACE){

		// Pause
		eKeys k = graph->modalShow("PAUSE");

		// Key R pressed, re-run the game
		if (k == eKeys::R){
			reset(graph);
		}

		// draw the game, to close the modal
		draw(graph);
	}
}

void	Board::_initGrid(void){
	for (int j = 0; j < GRID_SIZE; j++){
		for (int i = 0; i < GRID_SIZE; i++){
			_grid[j][i] = eBlock::EMPTY;
		}
	}
}

bool	Board::_isCaseEmpty(std::pair<int, int> index){
	return _grid[index.second][index.first] == eBlock::EMPTY;
}

void	Board::_setMove(std::pair<int, int> index){

	// Update case value
	_grid[index.second][index.first] = (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);

	// Add a pawn to player's container
	if (_turn == eTurn::TURN_PLAYER_1){
		_pawnsPlayer1.push_back(index);
	}
	else if (_turn == eTurn::TURN_PLAYER_2){
		_pawnsPlayer2.push_back(index);
	}
}

void	Board::drawPawns(std::vector<std::pair<int, int>>	_pawns, eColor color,IGraphicHandler *graph){
	for (size_t i = 0; i < _pawns.size(); i++){
		graph->drawPawn(_pawns[i].first, _pawns[i].second, color);
	}
}

void 	Board::draw(IGraphicHandler *graph){

	graph->clearWindow();
	graph->draw();

	graph->drawInfos(_turn, _player1Captures, _player2Captures);

	drawPawns(_pawnsPlayer1, eColor::PLAYER_1_COLOR, graph);
	drawPawns(_pawnsPlayer2, eColor::PLAYER_2_COLOR, graph);

	graph->show();
}

/*
**	Reset the game
*/
void	Board::reset(IGraphicHandler *graph){

	// empty the grid
	_initGrid();

	// Clear pawns containers
	_pawnsPlayer1.clear();
	_pawnsPlayer2.clear();

	// Set turn to player 1
	_turn = eTurn::TURN_PLAYER_1;
	graph->setTurn(_turn);

	// Reset scores
	_player1Captures = 0;
	_player2Captures = 0;

	// isAlive to true
	isAlive = true;
}

/*
**	Take the last move as parameter and check if it's a win
*/

bool	Board::_checkWin(std::pair<int, int> pawn){

	int	x = pawn.first;
	int	y = pawn.second;

	return (_checkWinHorizontalCheck(x, y) || _checkWinVerticalCheck(x, y) || _checkWinDiagonalCheck(x, y));
}

bool	Board::_checkWinHorizontalCheck(int x, int y){

	int counter = 0;
	eBlock playerPawn = (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);

	if (_grid[y][x] == playerPawn){ counter++; }

	// Lateral right check
	// (x + 1) because we already know actual value at x position
	for (int i = x + 1; i < GRID_SIZE; i++){

		// right mate is current player pawn, we increment the counter
		if (_grid[y][i] == playerPawn)
			counter++;
		else
			break ;
	}

	// Lateral left check
	// (x - 1) because we already know actual value at x position
	for (int i = x - 1; i >= 0; i--){

		// left mate is current player pawn, we increment the counter
		if (_grid[y][i] == playerPawn)
			counter++;
		else
			break ;
	}

	return (counter >= 5);
}

bool	Board::_checkWinVerticalCheck(int x, int y){

	int counter = 0;
	eBlock playerPawn = (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);

	if (_grid[y][x] == playerPawn){ counter++; }

	// Vertical top check
	// (y - 1) because we already know actual value at y position
	for (int j = y - 1; j >= 0; j--){

		if (_grid[j][x] == playerPawn)
			counter++;
		else
			break ;
	}

	// Vertical bottom check
	// (y - 1) because we already know actual value at y position
	for (int j = y + 1; j < GRID_SIZE; j++){

		if (_grid[j][x] == playerPawn)
			counter++;
		else
			break ;
	}

	return (counter >= 5);
}

bool	Board::_checkWinDiagonalCheck(int x, int y){

	int counter = 0;
	eBlock playerPawn = (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);

	if (_grid[y][x] == playerPawn){ counter++; }

	// Diagonal top right check
	for (int i = 1; (x + i < GRID_SIZE) && (y - i >= 0); i++){

		if (_grid[y - i][x + i] == playerPawn)
			counter++;
		else
			break ;
	}

	// Diagonal bottom left check
	for (int i = 1; (x - i >= 0) && (y + i < GRID_SIZE); i++){

		if (_grid[y + i][x - i] == playerPawn)
			counter++;
		else
			break ;
	}

	if (counter >= 5) { return true ; }

	counter = 0;

	if (_grid[y][x] == playerPawn){ counter++; }

	// Diagonal bottom right check
	for (int i = 1; (x + i < GRID_SIZE) && (y + i < GRID_SIZE); i++){

		if (_grid[y + i][x + i] == playerPawn)
			counter++;
		else
			break ;
	}

	// Diagonal top left check
	for (int i = 1; (x - i >= 0) && (y - i >= 0); i++){

		if (_grid[y - i][x - i] == playerPawn)
			counter++;
		else
			break ;
	}

	return (counter >= 4);
}

std::pair<PAIR_INT, PAIR_INT>	 *Board::_checkCapture(std::pair<int, int> index){

	int x = index.first;
	int y = index.second;

	std::pair<PAIR_INT, PAIR_INT> *ptr;
	if ((ptr = _checkCaptureHorizontal(x, y)) != NULL)
		return ptr;
	else if ((ptr = _checkCaptureVertical(x, y)) != NULL)
		return ptr;
	else if ((ptr = _checkCaptureDiagonal(x, y)) != NULL)
		return ptr;
	return NULL ;
}

std::pair<PAIR_INT, PAIR_INT>	 *Board::_checkCaptureHorizontal(int x, int y){

	// get player pawn
	eBlock playerPawn = _grid[y][x];

	// get opponent pawn
	eBlock opponentPawn = (playerPawn == eBlock::PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);

	// Check bounds
	if (x + 3 < GRID_SIZE){

		// Check from left ro right
		if (_grid[y][x] == playerPawn &&
			_grid[y][x + 1] == opponentPawn &&
			_grid[y][x + 2] == opponentPawn &&
			_grid[y][x + 3] == playerPawn
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
		if (_grid[y][x] == playerPawn &&
			_grid[y][x - 1] == opponentPawn &&
			_grid[y][x - 2] == opponentPawn &&
			_grid[y][x - 3] == playerPawn
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

std::pair<PAIR_INT, PAIR_INT>	 *Board::_checkCaptureVertical(int x, int y){

	// get player pawn
	eBlock playerPawn = _grid[y][x];

	// get opponent pawn
	eBlock opponentPawn = (playerPawn == eBlock::PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);

	// Check if we are out of bounds
	if (y + 3 < GRID_SIZE){

		// Check from top to bottom
		if (_grid[y][x] == playerPawn &&
			_grid[y + 1][x] == opponentPawn &&
			_grid[y + 2][x] == opponentPawn &&
			_grid[y + 3][x] == playerPawn
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
		if (_grid[y][x] == playerPawn &&
			_grid[y - 1][x] == opponentPawn &&
			_grid[y - 2][x] == opponentPawn &&
			_grid[y - 3][x] == playerPawn
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

std::pair<PAIR_INT, PAIR_INT>  *	Board::_checkCaptureDiagonal(int x, int y){

	// get player pawn
	eBlock playerPawn = _grid[y][x];

	// get opponent pawn
	eBlock opponentPawn = (playerPawn == eBlock::PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);

	// Check if we are not out of bounds
	if (x + 3 < GRID_SIZE && y - 3 >= 0){

		// Check from bottom to top right
		if (_grid[y][x] == playerPawn &&
			_grid[y - 1][x + 1] == opponentPawn &&
			_grid[y - 2][x + 2] == opponentPawn &&
			_grid[y - 3][x + 3] == playerPawn
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
		if (_grid[y][x] == playerPawn &&
			_grid[y + 1][x + 1] == opponentPawn &&
			_grid[y + 2][x + 2] == opponentPawn &&
			_grid[y + 3][x + 3] == playerPawn
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
		if (_grid[y][x] == playerPawn &&
			_grid[y + 1][x - 1] == opponentPawn &&
			_grid[y + 2][x - 2] == opponentPawn &&
			_grid[y + 3][x - 3] == playerPawn
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
		if (_grid[y][x] == playerPawn &&
			_grid[y - 1][x - 1] == opponentPawn &&
			_grid[y - 2][x - 2] == opponentPawn &&
			_grid[y - 3][x - 3] == playerPawn
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

void	Board::_removePawn(std::vector<std::pair<int, int>> & container, std::pair<int, int> pawn){

	// Loop through the container
	for (std::vector<std::pair<int, int>>::iterator it = container.begin(); it != container.end(); ++it){

		if (pair_compare(*it, pawn)){
			// Compare the pawns to find the one to delete
			container.erase(it);
			_grid[pawn.second][pawn.first] = eBlock::EMPTY;
			return ;
		}
	}
}

void	Board::_removePawnPair(PAIR_INT a, PAIR_INT b)
{
	std::vector<std::pair<int, int>> & container = (_turn == eTurn::TURN_PLAYER_1 ? _pawnsPlayer2 : _pawnsPlayer1);

	// Delete the pawns
	_removePawn(container, a);
	_removePawn(container, b);
}

void	Board::_updateTurn(IGraphicHandler *graph){

	// Update turn
	_turn = (_turn == eTurn::TURN_PLAYER_1 ? eTurn::TURN_PLAYER_2 : eTurn::TURN_PLAYER_1);

	// Update the turn on the graphic interface (especially for the mouse to update his sprite)
	graph->setTurn(_turn);
}

void	Board::_updateCaptureScore(void){

	// Get the capture score of the current player
	int & captureScore = (_turn == eTurn::TURN_PLAYER_1 ? _player1Captures : _player2Captures);

	// increment the score
	captureScore += 2;

	// Check if it's a win
	if (captureScore >= 10) { throw std::string("win"); }
}

bool	Board::_checkEndingCapture(std::pair<int, int> index){

	std::pair<PAIR_INT, PAIR_INT> *ptr;

	// Get opponent block
	eBlock opponent = (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_2 : eBlock::PLAYER_1);
	// int opponentScore = (_turn == eTurn::TURN_PLAYER_1 ? _player2Captures : _player1Captures);

	// Iterate through grid
	for (int j = 0; j < GRID_SIZE; j++){
		for (int i = 0; i < GRID_SIZE; i++){

			// If the case is empty
			if (_grid[j][i] == eBlock::EMPTY){

				// we set the case at this index to be the opponent (needed by _checkCapture)
				_grid[j][i] = opponent;

				// if there is possible capture we return true, the game continue
				if ((ptr = _checkCapture(std::make_pair(i, j))) != NULL){

					bool res = false;
					if ((res = _checkIfCaptureBreaksAlignement(ptr, index))){
						std::cout << "BREAKS 5 STONES" << std::endl;
					}
					else{

						// get Opponent score
						int score = (_turn == eTurn::TURN_PLAYER_1 ? _player2Captures : _player1Captures);

						if (score >= 8) {
							res = true;
						}
					}

					// We set back the value at the index to empty
					_grid[j][i] = eBlock::EMPTY;

					// clean
					delete ptr;

					return res ;
				}

				// We set back the value at the index to empty
				_grid[j][i] = eBlock::EMPTY;
			}
		}
	}
	return false ;
}

bool	Board::_checkIfCaptureBreaksAlignement(std::pair<PAIR_INT, PAIR_INT> *captures, PAIR_INT last){

	// Get the captured pairs
	std::pair<int, int> a = (*captures).first;
	std::pair<int, int> b = (*captures).second;

	// Get captured's players's container
	std::vector<std::pair<int, int>> & container = (_turn == eTurn::TURN_PLAYER_1 ? _pawnsPlayer1 : _pawnsPlayer2);

	// remove the pawn for the check
	_removePawn(container, a);
	_removePawn(container, b);

	// check if it's a win, we want to return the opposite of the return value of checkWinm
	bool res = !_checkWin(last);

	// rollback
	container.push_back(a);
	container.push_back(b);

	eBlock blockCurrentPlayer = (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_1 : eBlock::PLAYER_2);
	_grid[a.second][a.first] = blockCurrentPlayer;
	_grid[b.second][b.first] = blockCurrentPlayer;

	return res;
}

std::vector<std::pair<int, int>> & Board::_getCurrentPlayerPawns(void){
	return (_turn == eTurn::TURN_PLAYER_1 ? _pawnsPlayer1 : _pawnsPlayer2);
}

std::vector<std::pair<int, int>> & Board::_getOpponentPawns(void){
	return (_turn == eTurn::TURN_PLAYER_1 ? _pawnsPlayer1 : _pawnsPlayer2);
}

std::pair<int, int>	Board::_createEmptyPair(void){
	return std::make_pair(-42, -42);
}

eTurn	Board::getTurn(){
	return _turn;
}

bool	pair_compare(std::pair<int, int> a, std::pair<int, int> b)
{
	return (a.first == b.first && a.second == b.second);
}