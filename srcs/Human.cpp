#include <Human.hpp>

Human::Human(void){

}

Human::~Human(void){}

Human::Human(const Human & src){
	*this = src;
}

Human &	Human::operator=(Human const & rhs){
	(void)rhs;
	return *this;
}