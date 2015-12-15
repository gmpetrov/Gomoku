
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

	private:
		/* Methods */
		int					_basicHeuristic(std::vector<std::vector<eBlock>> &);
		std::pair<int, int>	_minMax(std::vector<std::vector<eBlock>> &);
		void				_printSet(std::set<State>) const;
		void				_findPossibleMoves(State &);
		void				_evaluateChild(State &);

		/* Attrs */
		eTurn				_turn;
		float				_elapsedTime;
		RulesChecker		_checker;

};

#endif // AI_HPP