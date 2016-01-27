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

Board::Board(void){}

Board::Board(eChoice choice) : isAlive(true), _choice(choice), _turn(eTurn::TURN_PLAYER_1), _grid(GRID_SIZE, std::vector<eBlock>(GRID_SIZE)), _player1Captures(0), _player2Captures(0), _debug(false){
	_initGrid();

	if (_choice == eChoice::IA){
		int rnd = rand() % 100;

		eTurn turn = (rnd < 50 ? eTurn::TURN_PLAYER_1 : eTurn::TURN_PLAYER_2);

		_ai.setTurn(turn);
	}
	else{
		_suggestion.first = -42;
	}
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
		std::pair<int, int> index = (isAiTurn() ? _ai.play(_grid) : graph->play(_turn));

		// Check that the grid is empty at move's coordinates
		if (!_isCaseEmpty(index))
			return ;

		// Set the move on the grid
		_setMove(index);

		std::pair<PAIR_INT, PAIR_INT> *ptr;

		if ((ptr = _checker.checkCapture(index.first, index.second, _grid)) != NULL){
			// checkCapture will respond with a pointer on a pairs of coordinate of the pawns to remove in case of capture
			// Remember to delete the pointer after utilisation

			// Delete the pairs
			_checker.removePawnPair((*ptr).first, (*ptr).second, _getOpponentPawns(), _grid);

			// Update scores
			_updateCaptureScore();

			// Clean
			delete ptr;
		}
		else if (_checker.checkWin(index.first, index.second, _grid, _turn)){

			// Check if there is a possible end capture move
			if (!_checker.checkEndingCapture(index, _grid, _turn, _getOpponentScore(), _getOpponentPawns())){

				draw(graph);

				// It's a winner move
				throw std::string("win");
			}
		}

		_checker.checkDoubleThree(index, _grid, _turn);

		// Update turn obviously
		_updateTurn(graph);

		if (_choice == HUMAN){ _moveSuggestion(); }
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
	else if  (key == eKeys::D){
		setDebugMode(!_debug);
		std::cout << "Debug mode : " << _debug << std::endl;
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

	eBlock	opponentForbbiden = (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_2_FORBIDDEN : eBlock::PLAYER_1_FORBIDDEN);

	return _grid[index.second][index.first] == eBlock::EMPTY || _grid[index.second][index.first] == opponentForbbiden;
}

void	Board::_setMove(std::pair<int, int> index){

	eBlock	opponentForbidden = (_turn == eTurn::TURN_PLAYER_1 ? eBlock::PLAYER_2_FORBIDDEN : eBlock::PLAYER_1_FORBIDDEN);

	// if move is set on a opponent's forbidden move, remove adjacent opponent forbiddent moves
	if (_grid[index.first][index.second] == opponentForbidden)
		_removeAdjacentForbiddenMove(index, opponentForbidden);

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

	if (_choice == eChoice::IA)
		graph->drawAiStats(_ai.getElapsedTime());

	drawPawns(_pawnsPlayer1, eColor::PLAYER_1_COLOR, graph);
	drawPawns(_pawnsPlayer2, eColor::PLAYER_2_COLOR, graph);

	drawForbiddenMoves(graph);

	if (_choice == HUMAN && _suggestion.first >= 0)
		graph->drawPawn(_suggestion.first, _suggestion.second, eColor::GREEN);

	graph->show();
}

void	Board::drawForbiddenMoves(IGraphicHandler *graph){

	eBlock	forbidden = (_turn == eTurn::TURN_PLAYER_1 ? PLAYER_1_FORBIDDEN : PLAYER_2_FORBIDDEN);

	for (int j = 0; j < GRID_SIZE; j++){
		for (int i = 0; i < GRID_SIZE; i++){
			if (_grid[j][i] == forbidden){
				graph->drawPawn(i, j, eColor::PLAYER_FORBIDDEN);
			}
		}
	}
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

void	Board::_removeAdjacentForbiddenMove(std::pair<int, int> index, eBlock forbiddenMove){

	int	x = index.first;
	int y = index.second;

	if (y - 1 >= 0 && _grid[y - 1][x] == forbiddenMove)
		_grid[y - 1][x] = eBlock::EMPTY;
	else if (x + 1 < GRID_SIZE && _grid[y][x + 1] == forbiddenMove)
		_grid[y][x + 1] = eBlock::EMPTY;
	else if (y + 1 < GRID_SIZE && _grid[y + 1][x] == forbiddenMove)
		_grid[y + 1][x] = eBlock::EMPTY;
	else if (x - 1 >= 0 && _grid[y][x - 1] == forbiddenMove)
		_grid[y][x - 1] = eBlock::EMPTY;
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

void	Board::_moveSuggestion(void){
	_suggestion = _ai._minMax(_grid, _turn);
}

std::vector<std::pair<int, int>> & Board::_getCurrentPlayerPawns(void){
	return (_turn == eTurn::TURN_PLAYER_1 ? _pawnsPlayer1 : _pawnsPlayer2);
}

std::vector<std::pair<int, int>> & Board::_getOpponentPawns(void){
	return (_turn == eTurn::TURN_PLAYER_1 ? _pawnsPlayer2 : _pawnsPlayer1);
}

eTurn	Board::getTurn(){
	return _turn;
}

void						Board::setDebugMode(bool value){
	_debug = value;
	_ai.debug = value;
}

bool						Board::isAiTurn(void){
	return _choice == eChoice::IA && _turn == _ai.getTurn();
}

int							&Board::_getOpponentScore(void){
	return (_turn == eTurn::TURN_PLAYER_1 ? _player2Captures : _player1Captures);
}