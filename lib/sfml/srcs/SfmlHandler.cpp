#include "SfmlHandler.hpp"

SfmlHandler::SfmlHandler(int width, int height) : _w(width), _h(height){

	this->_keyMap = {
		{ sf::Keyboard::Escape, eKeys::ESC },
		{ sf::Keyboard::Up, eKeys::UP },
		{ sf::Keyboard::Down, eKeys::DOWN },
		{ sf::Keyboard::Left, eKeys::LEFT },
		{ sf::Keyboard::Right, eKeys::RIGHT },
		{ sf::Keyboard::Num1, eKeys::ONE },
		{ sf::Keyboard::Num2, eKeys::TWO },
		{ sf::Keyboard::Num3, eKeys::THREE }
	};

	this->_colorMap = {
		{ eColor::BLACK, sf::Color(0, 0, 0) },
		{ eColor::DARK_BLUE, sf::Color(52, 73, 94) },
		{ eColor::BLUE, sf::Color(22, 160, 133) },
		{ eColor::RED, sf::Color(231, 76, 60) },
		{ eColor::GREEN, sf::Color(46, 204, 113) },
		{ eColor::VIOLET, sf::Color(224, 130, 131) },
		{ eColor::ORANGE, sf::Color(242, 121, 53) }

	};

	if (!_font.loadFromFile("fonts/Orbitron-Regular.ttf")){ exit(EXIT_FAILURE); }

	if (!_backgroundTexture.loadFromFile("imgs/wood_dark.jpg")){ std::cout << "Failt to load texture" << std::endl; exit(EXIT_FAILURE); }

	createWindow();

	_backgroundTexture.setSmooth(true);
	_backgroundSprite.setTexture(_backgroundTexture);
	_backgroundSprite.setColor(sf::Color(104, 195, 163));
}

SfmlHandler::~SfmlHandler(void){}

SfmlHandler::SfmlHandler(const SfmlHandler & src)
{
	*this = src;
}

SfmlHandler & SfmlHandler::operator=(const SfmlHandler & rhs)
{
	_w = rhs.getWidth();
	_h = rhs.getHeight();
	return *this;
}

int		SfmlHandler::getWidth(void) const{
	return _w;
}

int 	SfmlHandler::getHeight(void) const{
	return _h;
}

std::map<int, eKeys>	SfmlHandler::getKeyMap(void){
	return this->_keyMap;
}

void SfmlHandler::createWindow(void)
{
    _window = new sf::RenderWindow(sf::VideoMode(_w * BLOCK_SIZE, _h * BLOCK_SIZE), "Gomoku");
}

eKeys SfmlHandler::getKeyPressed(void)
{
	sf::Event event;

	// While there is events to handle
	while (_window->pollEvent(event))
	{
	    // Check the type of event
	    if (event.type == sf::Event::Closed){
	    	// Window Closed Event
	    	return eKeys::ESC;

	    }
	    else if (event.type == sf::Event::KeyPressed){
	    	// Key Pressed
	    	if (_keyMap.find(event.key.code) != _keyMap.end()){
	    		return _keyMap[event.key.code];
	    	}
	    	return eKeys::UNKNOWN;
	    }
	}
	return eKeys::UNKNOWN;
}

sf::Color SfmlHandler::_getColor(eColor color){
	if (_colorMap.find(color) != _colorMap.end()){
		return (_colorMap[color]);
	}
	return sf::Color(55, 55, 55);
}

void SfmlHandler::show(){
	_window->display();
}

void SfmlHandler::clearWindow(void){
	_window->clear(sf::Color::Black);
	_window->draw(_backgroundSprite);
}

void SfmlHandler::drawBlock(int x, int y, eColor color){

	if (color == eColor::DARK_BLUE)
	return ;

	// Create a Rectangle
	sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE ,BLOCK_SIZE));

	block.setPosition(x * BLOCK_SIZE, y  * BLOCK_SIZE);

	block.setFillColor(_getColor(color));

	_window->draw(block);
}

void SfmlHandler::close(void){
	if (_window->isOpen()){
		_window->close();
	}
}

void SfmlHandler::drawBonus(int score){

	sf::Text text;

	text.setFont(_font);
	text.setString("Score : " + std::to_string(score));
	text.setCharacterSize(24);
	text.setColor(sf::Color(255, 255, 255));
	text.setPosition(5, 5);
	// text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	_window->draw(text);
}

extern "C" IGraphicHandler *create(int w, int h)
{
	return new SfmlHandler(w, h);
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}