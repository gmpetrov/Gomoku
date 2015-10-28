#ifndef IGRAPHIC_HANDLER_HPP
# define IGRAPHIC_HANDLER_HPP

# include <iostream>
# include <Enums.hpp>

# define BLOCK_SIZE 10

class IGraphicHandler{

public:
	virtual ~IGraphicHandler(void) {};

	virtual void createWindow(void) = 0;
	virtual eKeys getKeyPressed(void) = 0;
	virtual void clearWindow(void) = 0;
	virtual void drawBlock(int, int, eColor) = 0;
	virtual void drawBonus(int) = 0;
	virtual void show(void) = 0;
	virtual void close(void) = 0;
};

#endif // IGRAPHIC_HANDLER_HPP