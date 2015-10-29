#include "SfmlHandler.hpp"

SfmlHandler::SfmlHandler() : _grid(GRID_SIZE, std::vector<std::pair<int, int>>(GRID_SIZE)){

	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	_w = mode.width;
	_h = mode.height;

	_block_size = _w / 40;

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
	if (!_backgroundTexture.loadFromFile("imgs/colored.png")){ std::cout << "Failt to load background texture" << std::endl; exit(EXIT_FAILURE); }

	// Load pawn texture
	if (!_pawnTexture.loadFromFile("imgs/pawn.jpg")){ std::cout << "Failt to load pawn texture" << std::endl; exit(EXIT_FAILURE); }

	// Instanciate the window
	createWindow();

	// Init sprites & textures
	_backgroundTexture.setSmooth(true);
	_pawnTexture.setSmooth(true);

	_backgroundSprite.setTexture(_backgroundTexture);
	_backgroundSprite.setColor(sf::Color(104, 195, 163));
	_backgroundSprite.setOrigin(sf::Vector2f(_w / 2, _h / 3));

	_pawnSprite.setTexture(_pawnTexture);
	_pawnSprite.setPosition(sf::Vector2f(10, 10));

	_pawn = sf::CircleShape(_block_size / 3);
	_pawn.setTexture(&_pawnTexture);
	_pawn.setOrigin(_pawn.getRadius(), _pawn.getRadius());

	_setGridCoordinate();

	if (!_music.openFromFile("audio/japan.ogg")){ std::cout << "Fail to load audio" << std::endl; exit(EXIT_FAILURE); }
	_music.play();
	_music.setPlayingOffset(sf::seconds(2));
	_music.setLoop(true);
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

	//Handle the mouse position
	_handleMousePosition();

	// draw the background
	_window->draw(_pawn);
}

void SfmlHandler::drawBlock(int x, int y, eColor color){

	if (color == eColor::DARK_BLUE)
	return ;

	// Create a Rectangle
	sf::RectangleShape block(sf::Vector2f(_block_size ,_block_size));

	block.setPosition(x * _block_size, y  * _block_size);

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

	// Draw horizontal lines
	for (int j = 0; j < GRID_SIZE; j++){

		int x1 = _grid[j][0].first;
		int y1 = _grid[j][0].second;

		int x2 = _grid[j][GRID_SIZE - 1].first;
		int y2 = _grid[j][GRID_SIZE - 1].second;
		sf::Vertex line[] =
		{
		    sf::Vertex(sf::Vector2f(x1, y1)),
		    sf::Vertex(sf::Vector2f(x2, y2))
		};
		_window->draw(line, 2, sf::Lines);
	}

	// Draw vertical lines
	for (int i = 0; i < GRID_SIZE; i++){
		int x1 = _grid[0][i].first;
		int y1 = _grid[0][i].second;

		int x2 = _grid[GRID_SIZE - 1][i].first;
		int y2 = _grid[GRID_SIZE - 1][i].second;
		sf::Vertex line[] =
		{
		    sf::Vertex(sf::Vector2f(x1, y1)),
		    sf::Vertex(sf::Vector2f(x2, y2))
		};
		_window->draw(line, 2, sf::Lines);
	}
}

void SfmlHandler::_setGridCoordinate(void)
{
	int grid_size = GRID_SIZE * _block_size;
	int offsetX = (_w / 2) - (grid_size / 2);
	int offsetY = (_h / 2) - (grid_size / 2);

	for (int j = 0; j < GRID_SIZE; j++){
		for (int i = 0; i < GRID_SIZE; i++){
			_grid[j][i] = std::make_pair(i * _block_size + offsetX, j * _block_size + offsetY);
		}
	}
}

void SfmlHandler::_handleMousePosition(void)
{
	// Mouse position
	sf::Vector2i pos = sf::Mouse::getPosition(*_window);

	// std::cout << "x : "  << pos.x << ", y : " << pos.y << std::endl;

	// Get min & max value
	int min_X = _grid[0][0].first;
	int max_X = _grid[0][GRID_SIZE - 1].first;
	int min_Y = _grid[0][0].second;
	int max_Y = _grid[0][GRID_SIZE - 1].second;

	// if not in the interval
	if ((pos.x < min_X || pos.x > max_X) || (pos.y < min_Y || pos.y > max_Y)){
		// _pawn.setPosition(pos.x, pos.y);
		// return ;
	}

	// Know we need to find the closest grid coordinate from the mouse position
	// Searching for the closest x
	int x 		= _grid[0][0].first;
	int diff 	= std::abs(pos.x - x);
	std::pair<int, int> tmp_x = std::make_pair(x, diff);
	for (int i = 0; i < GRID_SIZE; i++){
		x 		= _grid[0][i].first;
		diff 	= std::abs(pos.x - x);
		if (diff < tmp_x.second)
			tmp_x 	= std::make_pair(x, diff);
	}

	// Searching for the closest y
	int y 			= _grid[0][0].second;
	diff			= pos.y - y;
	std::pair<int, int> tmp_y	= std::make_pair(x, diff);
	for (int j = 0; j < GRID_SIZE; j++){
		y		= _grid[j][0].second;
		diff	= std::abs(pos.y - y);
		if (diff < tmp_y.second)
			tmp_y = std::make_pair(y, diff);
	}
	std::cout << "x : " << tmp_x.first << ", y : " << tmp_x.first << std::endl;
	_pawn.setPosition(tmp_x.first, tmp_y.first);
}

extern "C" IGraphicHandler *create()
{
	return new SfmlHandler();
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}