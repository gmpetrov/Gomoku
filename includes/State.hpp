#ifndef STATE_HPP
# define STATE_HPP

# include <iostream>
# include <vector>
# include <Enums.hpp>
# include <set>

	class State{
		public:
			State(std::vector<std::vector<eBlock>> &);
			State(std::vector<std::vector<eBlock>> &, int , int);
			~State(void);
			State(const State & src);
			State & operator=(State const & src);
			bool  operator<(const State & state) const;

			/* Methods */
			int 								getRating(void) const;
			std::vector<std::vector<eBlock>>	getGrid(void) const;
			std::vector<std::vector<eBlock>>	&getGridRef(void);
			void								setRating(int);
			void								setGrid(std::vector<std::vector<eBlock>> &);
			int									getX(void) const;
			int									getY(void) const;

			/* Attrs */

		private:

			/* Methods */
			State(void);

			/* Attrs */
			std::vector<std::vector<eBlock>> 	_grid;
			int									_rating;
			int									_x;
			int									_y;
	};

#endif //STATE_HPP