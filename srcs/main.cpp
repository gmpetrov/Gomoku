#include <stdio.h>
#include <ctype.h>
#include <map>
#include <unistd.h>
#include <GraphSwitch.hpp>
#include <Board.hpp>

void	usage(void);
bool	isStringDigit(std::string s);
void 	checkArgs(std::string s1, std::string s2);

int main(int ac, char **av)
{
	if (ac != 3){
		usage();
	}
	checkArgs(std::string(av[1]), std::string(av[2]));

	srand (time(NULL));

	Board board(std::atoi(av[1]), std::atoi(av[2]));

	GraphSwitch graphic(std::atoi(av[1]), std::atoi(av[2]));

	graphic.setGraphic("sfml");

	while (board.isAlive){
		eKeys key = graphic.graph->getKeyPressed();
		try{
			board.handleKey(key);
		}
		catch(std::string const & e){
			std::cout << e << std::endl;
			graphic.graph->close();
			exit(EXIT_SUCCESS);
		}

		graphic.graph->clearWindow();
		board.drawMap(graphic.graph);
		graphic.graph->show();
	}
	graphic.graph->close();
	return (0);
}

void	usage(void)
{
	std::cout << "[Usage] : ./nibbler [ 10 <= WIDTH <= 300] [10 <= HEIGHT <= 300]" << std::endl;
	exit(EXIT_FAILURE);
}

bool	isStringDigit(std::string s){
	for (std::string::iterator it = s.begin(); it != s.end(); it++){
		if (!isdigit(*it)){
			return false;
		}
	}
	return true;
}

void 	checkArgs(std::string s1, std::string s2){
	if (!isStringDigit(s1) || !isStringDigit(s2)){
		usage();
	}
	else if (std::atoi(s1.c_str()) < 500 || std::atoi(s1.c_str()) > 2500 || std::atoi(s2.c_str()) < 500 || std::atoi(s2.c_str()) > 2500){
		usage();
	}
}