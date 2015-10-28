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

Board::Board(int width, int height) : isAlive(true), _width(width), _height(height){

	// Init the map
	std::vector<std::vector<eBlock>> init(BOARD_SIZE, std::vector<eBlock>(BOARD_SIZE));
	_map = init;

	updateMap();

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

void 	Board::drawMap(IGraphicHandler *graph){
	(void)graph;
}

void	Board::move(void){

}

void 	Board::handleKey(eKeys key){
	if (key == eKeys::ESC){
		throw std::string("You quit !");
	}

	move();
}