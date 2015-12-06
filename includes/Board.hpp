/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:44:42 by gpetrov           #+#    #+#             */
/*   Updated: 2015/11/05 17:34:34 by gpetrov          ###   ########.fr       */
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
# define CAPTURE_SCORE_WIN 10

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
		void 								draw(IGraphicHandler *graph);
		void 								drawPawns(std::vector<std::pair<int, int>>, eColor,IGraphicHandler *);
		void								drawForbiddenMoves(IGraphicHandler *);
		void								reset(IGraphicHandler *);
		eTurn								getTurn(void);

		bool 								isAlive;
	private:
		Board(void);
		void								_initGrid(void);
		bool								_isCaseEmpty(std::pair<int, int>);
		void 								_setMove(std::pair<int, int>);
		std::vector<std::pair<int, int>> &	_getCurrentPlayerPawns(void);
		std::vector<std::pair<int, int>> &	_getOpponentPawns(void);

		bool								_isEmpty(int, int);
		void								_swapInt(int &, int &);
		bool								_isPlayerPawn(int, int);

		bool								_checkWin(std::pair<int, int>);
		bool								_checkWinHorizontalCheck(int, int);
		bool								_checkWinVerticalCheck(int, int);
		bool								_checkWinDiagonalCheck(int, int);

		std::pair<PAIR_INT, PAIR_INT>		*_checkCapture(std::pair<int, int>);
		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureHorizontal(int, int);
		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureVertical(int, int);
		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureDiagonal(int, int);

		void								_checkDoubleThree(std::pair<int, int>);
		bool								_checkIfThree(std::pair<int, int>, std::pair<int, int>);
		void								_checkIfDoubleThree(std::pair<int, int> a, std::pair<int, int> b);
		std::pair<PAIR_INT, PAIR_INT>		*_doubleThreeAllCaseChecker(std::pair<int, int>, std::pair<int, int>);

		bool								_checkEndingCapture(std::pair<int, int>);
		bool								_checkIfCaptureBreaksAlignement(std::pair<PAIR_INT, PAIR_INT> *, PAIR_INT);

		void								_removePawn(std::vector<std::pair<int, int>> & container, std::pair<int, int> pawn);
		void								_removePawnPair(PAIR_INT, PAIR_INT);
		void								_removeAdjacentForbiddenMove(std::pair<int, int>, eBlock);

		void								_updateTurn(IGraphicHandler *);
		void								_updateCaptureScore(void);


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