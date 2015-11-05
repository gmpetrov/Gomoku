/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:44:42 by gpetrov           #+#    #+#             */
/*   Updated: 2015/11/05 16:09:58 by gpetrov          ###   ########.fr       */
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
# define PAIR_INT std::pair<int, int>

class Board{
	public:
		Board(eChoice choice);
		~Board(void);
		Board(const Board & src);
		Board &	operator=(Board const & rhs);

		void 								quit();
		std::								vector<std::vector<eBlock>> getMap(void);
		void 								initMap(void);
		void 								updateMap(void);
		void 								move(void);
		void 								handleKey(eKeys, IGraphicHandler *graph);
		void 								drawPawns(std::vector<std::pair<int, int>>, eColor,IGraphicHandler *);
		void 								draw(IGraphicHandler *graph);

		bool 								isAlive;
	private:
		Board(void);
		void								_initGrid(void);
		bool								_isCaseEmpty(std::pair<int, int>);
		void 								_setMove(std::pair<int, int>);

		bool								_checkWin(std::pair<int, int>);
		bool								_checkWinHorizontalCheck(int, int);
		bool								_checkWinVerticalCheck(int, int);
		bool								_checkWinDiagonalCheck(int, int);

		PAIR_INT							_createEmptyPair(void);

		// bool								_checkCapture(std::pair<int, int>);
		// bool								_checkCaptureHorizontal(int, int);
		// bool								_checkCaptureVertical(int, int);
		// bool								_checkCaptureDiagonal(int, int);

		std::pair<PAIR_INT, PAIR_INT>		*_checkCapture(std::pair<int, int>);
		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureHorizontal(int, int);
		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureVertical(int, int);
		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureDiagonal(int, int);

		void								_removePawn(std::vector<std::pair<int, int>> & container, std::pair<int, int> pawn);
		void								_removePawnPair(PAIR_INT, PAIR_INT);

		void								_reset(IGraphicHandler *);
		void								_updateTurn(IGraphicHandler *);

		int									_width;
		int 								_height;
		eChoice								_choice;
		eTurn								_turn;

		std::vector<std::vector<eBlock>> 	_map;
		std::vector<std::pair<int, int>>	_pawnsPlayer1;
		std::vector<std::pair<int, int>>	_pawnsPlayer2;

		time_t 								_elapsedTime;

		std::vector<std::vector<eBlock>>  	 _grid;

		int									_player1Captures;
		int									_player2Captures;
};

#endif