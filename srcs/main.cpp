#include <stdio.h>
#include <ctype.h>
#include <map>
#include <unistd.h>
#include <GraphSwitch.hpp>
#include <Board.hpp>

bool	pair_compare(std::pair<int, int> & a, std::pair<int, int> & b);

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



	// Instanciate the board with selected choice
	Board board(choice);

	while (board.isAlive){

		// If it's AI turn simulate a mouse left key
		eKeys key = (board.isAiTurn() ? eKeys::MOUSE_LEFT : graphic.graph->getKeyPressed());

		try{
			board.handleKey(key, graphic.graph);
		}
		catch(std::string const & e){

			if (e.compare("quit") == 0){

				std::cout << e << std::endl;
				break ;
			}
			else if (e.compare("win") == 0){

				std::string winner = (board.getTurn() == eTurn::TURN_PLAYER_1 ? "Player 1 win" : "Player 2 win");

				eKeys k = graphic.graph->modalShow(winner);

				// Exit the game
				if (k != eKeys::R) { break ; }

				// Reset the game
				board.reset(graphic.graph);

				// draw the game, to close the modal
				board.draw(graphic.graph);
			}
		}
		mouse_pos = graphic.graph->mouseMove();
		if (!pair_compare(mouse_pos, old_mouse_pos) || key == eKeys::MOUSE_LEFT){

			// The mouse moved, we can draw
			board.draw(graphic.graph);

			old_mouse_pos = mouse_pos;
		}
	}
	graphic.graph->close();
	return (0);
}