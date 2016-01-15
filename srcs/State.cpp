#include <State.hpp>

State::State(std::vector<std::vector<eBlock>> & grid) : _grid(grid){

}

State::State(std::vector<std::vector<eBlock>> & grid, int X, int Y) : _grid(grid),_x(X), _y(Y){
}

State::~State(){}

State::State(const State & src){
	*this = src;
}

State & State::operator=(State const & src){
	_grid = src.getGrid();
	_rating = src.getRating();
	_x = src.getX();
	_y = src.getY();
	return *this;
}

std::vector<std::vector<eBlock>>	State::getGrid(void) const{
	return _grid;
}

std::vector<std::vector<eBlock>>	&State::getGridRef(void){
	return _grid;
}

int									State::getRating(void) const{
	return _rating;
}

void								State::setGrid(std::vector<std::vector<eBlock>> & grid){
	_grid = grid;
}

void								State::setRating(int rating){
	_rating = rating;
}

bool  State::operator<(const State & rhs) const{
	return _rating < rhs.getRating();
}

int									State::getX(void)const{
	return _x;
}

int									State::getY(void)const{
	return _y;
}