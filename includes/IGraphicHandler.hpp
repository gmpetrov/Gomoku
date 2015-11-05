#ifndef IGRAPHIC_HANDLER_HPP
# define IGRAPHIC_HANDLER_HPP

# include <iostream>
# include <Enums.hpp>

# define BLOCK_SIZE 30
# define GRID_SIZE 19

class IGraphicHandler{

public:
	virtual ~IGraphicHandler(void) {};

	virtual void createWindow(void) = 0;
	virtual eKeys getKeyPressed(void) = 0;
	virtual void clearWindow(void) = 0;
	virtual void draw(void) = 0;
	virtual void show(void) = 0;
	virtual void close(void) = 0;
	virtual void animationLogo(void) = 0;
	virtual eChoice drawMenu(void) = 0;
	virtual std::pair<int, int>	mouseMove() = 0;
	virtual std::pair<int, int> play(eTurn) = 0;
	virtual void drawPawn(int, int, eColor) = 0;
	virtual void drawInfos(eTurn, int, int) = 0;
	virtual void setTurn(eTurn) = 0;
	virtual eKeys modalShow(std::string msg) = 0;
};

#endif // IGRAPHIC_HANDLER_HPP