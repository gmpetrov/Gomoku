#ifndef HUMAN_HPP
# define HUMAN_HPP

# include <IPlayer.hpp>

class Human : public IPlayer {

	Human(void);
	~Human(void);
	Human(const Human & src);
	Human &	operator=(Human const & rhs);

};

#endif //HUMAN_HPP