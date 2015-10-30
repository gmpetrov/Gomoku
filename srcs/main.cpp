#include <stdio.h>
#include <ctype.h>
#include <map>
#include <unistd.h>
#include <GraphSwitch.hpp>
#include <Board.hpp>

bool	pair_compare(std::pair<int, int> a, std::pair<int, int> b);

int main(void)
{

	std::pair<int, int> mouse_pos;
	std::pair<int, int> old_mouse_pos;

	srand (time(NULL));

	GraphSwitch graphic;

	graphic.setGraphic("sfml");

	graphic.graph->animationLogo();

	eChoice choice;

	// Launch the Menu
	if ((choice = graphic.graph->drawMenu()) == eChoice::QUIT){

		// The ESC key has been pressed while in menu
		graphic.graph->close();
		exit(EXIT_SUCCESS);
	}

	Board board(choice);

	while (board.isAlive){

		eKeys key = graphic.graph->getKeyPressed();
		try{
			board.handleKey(key, graphic.graph);
		}
		catch(std::string const & e){
			std::cout << e << std::endl;
			graphic.graph->close();
			exit(EXIT_SUCCESS);
		}
		mouse_pos = graphic.graph->mouseMove();
		if (!pair_compare(mouse_pos, old_mouse_pos)){

			// The mouse moved, we can draw
			board.draw(graphic.graph);

			old_mouse_pos = mouse_pos;
		}
	}
	graphic.graph->close();
	return (0);
}

bool	pair_compare(std::pair<int, int> a, std::pair<int, int> b)
{
	return (a.first == b.first && a.second == b.second);
}