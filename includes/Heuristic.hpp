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
			bool checkCapture(int, int, GRID_REF);
			int checkWin(GRID_REF, eTurn);
			bool stopALignement(int, int, GRID_REF grid, eTurn);
			int  checkAlign(int x, int y, GRID_REF grid, eBlock player);
			int checkCloseTo(int x, int y, GRID_REF grid, eBlock closeTo);
			int checkStopAlign(int x, int y, GRID_REF grid, eBlock player, int dirX, int dirY);
			int stopAlign(int, int, GRID_REF grid);
			int makeAlign(int, int, GRID_REF grid);
			int chekMakeAlign(int x, int y, GRID_REF grid, int dirX, int dirY);

			int		oneTwoShape(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneTwoShape1(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneTwoShape2(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneTwoShape3(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneTwoShape4(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneTwoShape5(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneTwoShape6(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneTwoShape7(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneTwoShape8(int i, int j, GRID_REF grid, eBlock opponent);

			int		oneThreeShape(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneThreeShape1(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneThreeShape2(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneThreeShape3(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneThreeShape4(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneThreeShape5(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneThreeShape6(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneThreeShape7(int i, int j, GRID_REF grid, eBlock opponent);
			bool	oneThreeShape8(int i, int j, GRID_REF grid, eBlock opponent);


			eTurn 				AIturn;

		private:

			/* Methods */

			/* Attrs */
			RulesChecker		_checker;
	};

#endif //HEURISTIC_HPP