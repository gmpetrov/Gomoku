
#ifndef AI_HPP
# define AI_HPP

# include <iostream>
# include <vector>
# include <chrono>
# include <ctime>
# include <time.h>
# include <set>
# include <thread>
# include <mutex>

# include <Enums.hpp>
# include <State.hpp>
# include <Heuristic.hpp>


# define ALGO_DEPTH 2

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
		void				getPossibleMoves(State &, eTurn &, std::vector<State> &);
		eTurn				notTurn(eTurn);
		std::pair<int, int>	_minMax(GRID_REF);

		std::recursive_mutex			algoMutex;
		std::recursive_mutex			mtx;
		RulesChecker					_checker;

	private:
		/* Methods */
		int					_basicHeuristic(std::vector<std::vector<eBlock>> &);

		void				_printSet(std::set<State>) const;
		unsigned int		_scaleDepth(unsigned int, GRID_REF, eTurn &);

		int					_calcMax(GRID_REF, eTurn, int depth, int alpha, int beta);
		int					_calcMin(GRID_REF, eTurn, int depth, int alpha, int beta);
		void				_play(GRID_REF, eTurn, int x, int y);
		void				_cancelPlay(GRID_REF, int x, int y);

		int					_evaluateGrid(GRID_REF);
		bool				_closeToOpponentPawn(GRID_REF grid, eBlock opponent, int x, int y);


		/* Attrs */
		eTurn				_turn;
		double				_elapsedTime;
		// RulesChecker		_checker;
		Heuristic			_heur;

};

#endif // AI_HPP