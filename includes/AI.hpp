
#ifndef AI_HPP
# define AI_HPP

# include <iostream>
# include <Enums.hpp>
# include <vector>
# include <chrono>
# include <ctime>
# include <time.h>
# include <set>
# include <State.hpp>
# include <RulesChecker.hpp>

# define ALGO_DEPTH 4

class AI{
	public:
		AI(void);
		~AI(void);
		AI(const AI & src);
		AI &	operator=(AI const & rhs);

		std::pair<int, int>	play(std::vector<std::vector<eBlock>> &);
		void				setTurn(eTurn);
		eTurn				getTurn();
		float				getElapsedTime(void);
		eBlock				getCurrentPlayerForbidden(void);
		eBlock				getOpponentPlayerForbidden(void);
		std::vector<State>	getPossibleMoves(State &, eTurn &);

	private:
		/* Methods */
		int					_basicHeuristic(std::vector<std::vector<eBlock>> &);
		std::pair<int, int>	_minMax(GRID_REF);
		State				_minMaxExplorer(State &, eTurn &, bool, int);
		State				_getMax(std::set<State> &);
		State				_getMin(std::set<State> &);
		void				_printSet(std::set<State>) const;
		State				_findBestMove(State &);
		int					_evaluateChild(State &);
		unsigned int		_countEmptyCase(GRID_REF, eTurn &);
		unsigned int		_scaleDepth(unsigned int, GRID_REF, eTurn &);

		/* Attrs */
		eTurn				_turn;
		double				_elapsedTime;
		RulesChecker		_checker;

};

#endif // AI_HPP