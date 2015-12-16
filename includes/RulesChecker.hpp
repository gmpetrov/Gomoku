/*
	GOMOKU rules checker
*/

#ifndef RULES_CHECKER_HPP
# define RULES_CHECKER_HPP

# include <iostream>
# include <Enums.hpp>
# include <vector>

# define GRID_SIZE 19
# define PAIR_INT std::pair<int, int>
# define CAPTURE_SCORE_WIN 10
# define GRID_REF std::vector<std::vector<eBlock>> &
# define PLAYER_PAWNS_REF std::vector<std::pair<int, int>> &

bool	pair_compare(std::pair<int, int> & a, std::pair<int, int> & b);

class RulesChecker{
	public:
		RulesChecker(void);
		~RulesChecker(void);
		RulesChecker(const RulesChecker & src);
		RulesChecker & operator=(RulesChecker const & src);

		bool								checkWin(std::pair<int, int>, GRID_REF, eTurn &);
		std::pair<PAIR_INT, PAIR_INT>		*checkCapture(std::pair<int, int>, GRID_REF);
		void								checkDoubleThree(std::pair<int, int>, GRID_REF, eTurn &);

		bool								checkEndingCapture(std::pair<int, int>, GRID_REF, eTurn &, int &, PLAYER_PAWNS_REF);
		void								removePawnPair(PAIR_INT, PAIR_INT, PLAYER_PAWNS_REF, GRID_REF);

	private:
		bool								_checkWinHorizontalCheck(int, int, GRID_REF, eTurn &);
		bool								_checkWinVerticalCheck(int, int, GRID_REF, eTurn &);
		bool								_checkWinDiagonalCheck(int, int, GRID_REF, eTurn &);

		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureHorizontal(int, int, GRID_REF);
		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureVertical(int, int, GRID_REF);
		std::pair<PAIR_INT, PAIR_INT>		*_checkCaptureDiagonal(int, int, GRID_REF);
		bool								_checkIfCaptureBreaksAlignement(std::pair<PAIR_INT, PAIR_INT> *captures, PAIR_INT last, GRID_REF, eTurn & turn, PLAYER_PAWNS_REF);

		bool								_isEmpty(int, int, GRID_REF);
		void								_swapInt(int &, int &);
		bool								_isPlayerPawn(int x, int y, GRID_REF, eTurn &);
		void								_removePawn(PLAYER_PAWNS_REF container, std::pair<int, int> pawn, GRID_REF);

		std::vector<std::pair<int, int>> 	*_compareThrees(std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>);
		std::vector<std::pair<int, int>> 	*_findThreeNearBy(std::pair<int, int>, std::pair<int, int>, GRID_REF, eTurn &);
		std::pair<int, int>					*_findAdjacentPawn(std::pair<int, int>, GRID_REF, eTurn &);
		std::vector<std::pair<int, int>>	*_checkIfThree(std::pair<int, int>, std::pair<int, int>, GRID_REF, eTurn &);
		void								_checkIfDoubleThree(std::pair<int, int> a, std::pair<int, int> b, GRID_REF, eTurn &);
		bool								_checkIfReallyForbidden(std::pair<int, int>, std::pair<int, int>, std::pair<int, int>, GRID_REF, eTurn &);
};

#endif // RULES_CHECKER_HPP