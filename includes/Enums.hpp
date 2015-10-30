#ifndef ENUMS_HPP
# define ENUMS_HPP

enum eKeys {
	UNKNOWN = -1,
	ESC,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ONE,
	TWO,
	THREE,
	SPACE,
	RETURN,
	MOUSE_LEFT
};

enum eBlock {
	EMPTY = 0,
	PLAYER_1,
	PLAYER_2
};

enum eColor {
	BLACK = 0,
	RED,
	GREEN,
	BLUE,
	DARK_BLUE,
	VIOLET,
	ORANGE
};

enum eChoice{
	HUMAN = 0,
	IA,
	QUIT
};

enum eTurn{
	TURN_PLAYER_1 = 0,
	TURN_PLAYER_2
};

#endif // ENUMS_HPP