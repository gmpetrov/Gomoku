/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:45:21 by gpetrov           #+#    #+#             */
/*   Updated: 2015/10/10 13:09:01 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Board.hpp>

Board::Board(void){}

Board::Board(eChoice choice) : isAlive(true), _choice(choice), _turn(eTurn::TURN_PLAYER_1), _grid(GRID_SIZE, std::vector<eBlock>(GRID_SIZE)){
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
		throw std::string("You quit !");
	}
	else if (key == eKeys::MOUSE_LEFT){
		std::pair<int, int> index = graph->play(_turn);
		if (!_isCaseEmpty(index))
			return ;
		_setMove(index);
		if (_checkWin(index)){
			std::cout << "SOMEBODY WON" << std::endl;
			isAlive = false;
		}
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

	// Update turn
	_turn = (_turn == eTurn::TURN_PLAYER_1 ? eTurn::TURN_PLAYER_2 : eTurn::TURN_PLAYER_1);
}

void	Board::drawPawns(std::vector<std::pair<int, int>>	_pawns, eColor color,IGraphicHandler *graph){
	for (size_t i = 0; i < _pawns.size(); i++){
		graph->drawPawn(_pawns[i].first, _pawns[i].second, color);
	}
}

void 	Board::draw(IGraphicHandler *graph){

	graph->clearWindow();
	graph->draw();

	graph->drawInfos(_turn);

	drawPawns(_pawnsPlayer1, eColor::PLAYER_1_COLOR, graph);
	drawPawns(_pawnsPlayer2, eColor::PLAYER_2_COLOR, graph);

	graph->show();
}

/*
**	Take the last move as parameter and check if it's a win
*/

bool	Board::_checkWin(std::pair<int, int> pawn){

	int	x = pawn.first;
	int	y = pawn.second;

	return (_checkWinHorizontalCheck(x, y) || _checkWinVerticalCheck(x, y));
}

bool	Board::_checkWinHorizontalCheck(int x, int y){

	int counter = 0;
	eBlock playerPawn = _grid[y][x];

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

	return (counter >= 4);
}

bool	Board::_checkWinVerticalCheck(int x, int y){

	int counter = 0;
	eBlock playerPawn = _grid[y][x];

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

	return (counter >= 4);
}

bool	Board::_checkWinDiagonalCheck(int x, int y){

	int counter = 0;
	eBlock playerPawn = _grid[y][x];

	// Diagonal top right check
	for (int i = 1; (i +  x < GRID_SIZE) && (y - i >= 0); i++){

		if (_grid[y - i][x + i] == playerPawn)
			counter++;
		else
			break ;
	}

	// Diagonal bottom left check
	for (int i = 1; (i - x >= 0) && (y + i < GRID_SIZE); i++){

		if (_grid[y + i][x - i] == playerPawn)
			counter++;
		else
			break ;
	}

	if (counter >= 4) { return true ; }

	counter = 0;

	// Diagonal bottom right check
	for (int i = 1; (i + x < GRID_SIZE) && (y + i < GRID_SIZE); i++){

		if (_grid[y + i][x + i] == playerPawn)
			counter++;
		else
			break ;
	}

	// Diagonal top left check
	for (int i = 1; (i - x >= 0) && (y - i >= 0); i++){

		if (_grid[y - i][x - i] == playerPawn)
			counter++;
		else
			break ;
	}

	std::cout << "counter : " << counter << std::endl;
	return (counter >= 4);
}