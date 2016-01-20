#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# include <Enums.hpp>
# include <RulesChecker.hpp>

	class Heuristic{
		public:
			Heuristic();
			~Heuristic(void);
			Heuristic(const Heuristic & src);
			Heuristic & operator=(Heuristic const & src);

			/* Methods */
			bool closeToPawn(GRID_REF, eBlock, int x, int y);
			bool checkCapture(std::pair<int, int>, GRID_REF);
			bool checkWin(std::pair<int, int>, GRID_REF, eTurn &);
			bool stopALignement(std::pair<int, int> move, GRID_REF grid, eTurn);
			int stopALignement2(GRID_REF grid);
			int  checkAlign(int x, int y, GRID_REF grid, eBlock player);
			int checkCloseToOpponent(int x, int y, GRID_REF grid, eBlock player);

			eTurn 				AIturn;

		private:

			/* Methods */

			/* Attrs */
			RulesChecker		_checker;
	};

#endif //HEURISTIC_HPP