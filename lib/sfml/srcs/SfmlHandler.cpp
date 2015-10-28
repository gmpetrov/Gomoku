#include "SfmlHandler.hpp"

SfmlHandler::SfmlHandler(){

	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	_w = mode.width;
	_h = mode.height;

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

	// Load font
	if (!_font.loadFromFile("fonts/Orbitron-Regular.ttf")){ exit(EXIT_FAILURE); }

	// Load background texture
	if (!_backgroundTexture.loadFromFile("imgs/wood_dark.jpg")){ std::cout << "Failt to load background texture" << std::endl; exit(EXIT_FAILURE); }

	// Load pawn texture
	if (!_pawnTexture.loadFromFile("imgs/pawn.jpg")){ std::cout << "Failt to load pawn texture" << std::endl; exit(EXIT_FAILURE); }

	// Instanciate the window
	createWindow();

	_backgroundTexture.setSmooth(true);
	_pawnTexture.setSmooth(true);

	_backgroundSprite.setTexture(_backgroundTexture);
	_backgroundSprite.setColor(sf::Color(104, 195, 163));

	_pawnSprite.setTexture(_pawnTexture);
	_pawnSprite.setPosition(sf::Vector2f(10, 10));

	_pawn = sf::CircleShape(BLOCK_SIZE / 3);
	_pawn.setTexture(&_pawnTexture);
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
    _window = new sf::RenderWindow(sf::VideoMode(_w, _h), "Gomoku", sf::Style::Fullscreen);
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

	// clear the window
	_window->clear(sf::Color::Black);

	// draw the background
	_window->draw(_backgroundSprite);

	// draw the grid obviously
	drawGrid();

	// draw the background
	_window->draw(_pawn);
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

void SfmlHandler::drawGrid(void)
{
	int grid_size = 19 * BLOCK_SIZE;
	int offsetX = (_w / 2) - (grid_size / 2);
	int offsetY = (_h / 2) - (grid_size / 2);

	sf::Vector2i localPosition = sf::Mouse::getPosition(*_window);
	_pawn.setPosition(localPosition.x, localPosition.y);
	std::cout << "x : "  << localPosition.x << ", y : " << localPosition.y << std::endl;

	for (int j = 0; j < 19; j++){
		for (int i = 0; i < 19; i++){
			sf::Vertex hLine[] =
			{
			    sf::Vertex(sf::Vector2f(i * BLOCK_SIZE + offsetX, j * BLOCK_SIZE + offsetY)),
			    sf::Vertex(sf::Vector2f(i * BLOCK_SIZE + offsetX + BLOCK_SIZE, j * BLOCK_SIZE + offsetY))
			};
			sf::Vertex vLine[] =
			{
			    sf::Vertex(sf::Vector2f(i * BLOCK_SIZE + offsetX, j * BLOCK_SIZE + offsetY)),
			    sf::Vertex(sf::Vector2f(i * BLOCK_SIZE + offsetX, j * BLOCK_SIZE + offsetY + BLOCK_SIZE))
			};
			_window->draw(hLine, 2, sf::Lines);
			_window->draw(vLine, 2, sf::Lines);
		}
	}
}

extern "C" IGraphicHandler *create()
{
	return new SfmlHandler();
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}