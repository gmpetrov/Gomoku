/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:44:42 by gpetrov           #+#    #+#             */
/*   Updated: 2015/10/10 13:09:45 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_HPP
# define BOARD_HPP

# include <iostream>
# include <string>
# include <Enums.hpp>
# include <vector>
# include <IGraphicHandler.hpp>
# include <stdlib.h>
# include <time.h>

# define GRID_SIZE 19

class Board{
	public:
		Board(eChoice choice);
		~Board(void);
		Board(const Board & src);
		Board &	operator=(Board const & rhs);

		void quit();
		std::vector<std::vector<eBlock>> getMap(void);
		void initMap(void);
		void updateMap(void);
		void move(void);
		void handleKey(eKeys, IGraphicHandler *graph);
		void drawPawns(std::vector<std::pair<int, int>>, IGraphicHandler *graph);
		void draw(IGraphicHandler *graph);

		bool isAlive;
	private:
		Board(void);
		void	_initGrid(void);
		bool	_isCaseEmpty(std::pair<int, int>);
		void 	_setMove(std::pair<int, int>);

		int	_width;
		int _height;
		eChoice		_choice;
		eTurn		_turn;

		std::vector<std::vector<eBlock>> 	_map;
		std::vector<std::pair<int, int>>	_pawnsPlayer1;
		std::vector<std::pair<int, int>>	_pawnsPlayer2;

		time_t _elapsedTime;

		std::vector<std::vector<eBlock>>   _grid;
};

#endif