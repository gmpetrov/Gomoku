#include <State.hpp>

State::State(std::vector<std::vector<eBlock>> grid) : parent(NULL), _grid(grid){

}

State::State(std::vector<std::vector<eBlock>> grid, State * parentPointer, int X, int Y) : parent(parentPointer), _grid(grid),_x(X), _y(Y){
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

void								State::addChild(State child){
	_children.insert(child);
}

std::set<State>					State::getChildren(void) const{
	return _children;
}

int									State::getX(void)const{
	return _x;
}

int									State::getY(void)const{
	return _y;
}