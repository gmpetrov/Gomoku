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
	MOUSE_LEFT,
	R,
	D
};

enum eBlock {
	EMPTY = 0,
	PLAYER_1,
	PLAYER_2,
	PLAYER_1_FORBIDDEN,
	PLAYER_2_FORBIDDEN
};

enum eColor {
	BLACK = 0,
	RED,
	GREEN,
	BLUE,
	DARK_BLUE,
	VIOLET,
	ORANGE,
	PLAYER_1_COLOR,
	PLAYER_1_COLOR_TRANS,
	PLAYER_2_COLOR,
	PLAYER_2_COLOR_TRANS,
	PLAYER_FORBIDDEN
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

enum eAlgoValue{
	LOST = -42000,
	WIN  = 42000,
	DRAW = 0,
	AVERAGE
};

#endif // ENUMS_HPP