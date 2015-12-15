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
		{ sf::Keyboard::Num3, eKeys::THREE },
		{ sf::Keyboard::Return, eKeys::RETURN },
		{ sf::Keyboard::Space, eKeys::SPACE },
		{ sf::Keyboard::R, eKeys::R },
		{ sf::Keyboard::D, eKeys::D }
	};

	this->_colorMap = {
		{ eColor::BLACK, sf::Color(0, 0, 0) },
		{ eColor::DARK_BLUE, sf::Color(52, 73, 94) },
		{ eColor::BLUE, sf::Color(22, 160, 133) },
		{ eColor::RED, sf::Color(207, 0, 15) },
		{ eColor::GREEN, sf::Color(46, 204, 113) },
		{ eColor::VIOLET, sf::Color(224, 130, 131) },
		{ eColor::ORANGE, sf::Color(242, 121, 53) },
		{ eColor::PLAYER_2_COLOR, sf::Color(255, 255, 255) },
		{ eColor::PLAYER_2_COLOR_TRANS, sf::Color(255, 255, 255, 128) },
		{ eColor::PLAYER_1_COLOR, sf::Color(55, 55, 55) },
		{ eColor::PLAYER_1_COLOR_TRANS, sf::Color(55, 55, 55, 128) },
		{ eColor::PLAYER_FORBIDDEN, sf::Color(207, 0, 15, 128) }
	};

	// Load font
	if (!_font.loadFromFile("fonts/MadSquire-Regular.otf")){ exit(EXIT_FAILURE); }

	// Load background texture
	if (!_backgroundTexture.loadFromFile("imgs/colored.png")){ std::cout << "Failed to load background texture" << std::endl; exit(EXIT_FAILURE); }

	// Load pawn texture
	if (!_pawnTexture.loadFromFile("imgs/pawn-texture.png")){ std::cout << "Failed to load pawn texture" << std::endl; exit(EXIT_FAILURE); }

	// Load logo texture
	if (!_logoTexture.loadFromFile("imgs/gomoku.png")){ std::cout << "Failed to load logo texture" << std::endl; exit(EXIT_FAILURE); }

	// Instanciate the window
	createWindow();

	// Init sprites & textures
	_backgroundTexture.setSmooth(true);
	_pawnTexture.setSmooth(true);
	_logoTexture.setSmooth(true);

	_backgroundSprite.setTexture(_backgroundTexture);
	_backgroundSprite.setOrigin(sf::Vector2f(_w / 2, _h / 2));
	_backgroundSprite.setPosition(_w / 2, _h / 2);

	// Mouse pawn
	_pawn.setTexture(_pawnTexture);
	sf::FloatRect rect = _pawn.getGlobalBounds();
	_pawn.setOrigin(rect.width / 2, rect.height / 2);
	_pawn.setScale(sf::Vector2f(0.17f, 0.17f));
	_pawn.setColor(_colorMap[eColor::PLAYER_1_COLOR_TRANS]);

	_logoSprite.setTexture(_logoTexture);
	_logoSprite.setPosition(sf::Vector2f(10, 10));

	sf::Vector2u size = _logoTexture.getSize();

	_logoSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	_logoSprite.setOrigin(size.x / 2 , size.y / 2);
	_logoSprite.setPosition(_w / 2, _h / 2);

	_setGridCoordinate();

	// Init Audio
	if (!_music.openFromFile("audio/japan.ogg")){ std::cout << "Fail to load audio" << std::endl; exit(EXIT_FAILURE); }
	// _music.play();
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
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			return eKeys::MOUSE_LEFT;
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
}

void SfmlHandler::_drawBackground(void){
	// draw the background
	_window->draw(_backgroundSprite);
}

void SfmlHandler::drawPawn(int i, int j, eColor color){

	int x = _grid[j][i].first;
	int y = _grid[j][i].second;

	sf::Sprite pawn;

	pawn.setTexture(_pawnTexture);
	sf::FloatRect rect = pawn.getGlobalBounds();
	pawn.setOrigin(rect.width / 2, rect.height / 2);
	pawn.setScale(sf::Vector2f(0.17f, 0.17f));
	pawn.setColor(_colorMap[color]);

	pawn.setPosition(x, y);

	_window->draw(pawn);
}

void SfmlHandler::close(void){
	if (_window->isOpen()){
		_window->close();
	}
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

std::pair<int, int> SfmlHandler::mouseMove()
{
	int indexI = 0, indexJ = 0;

	// Mouse position
	sf::Vector2i pos = sf::Mouse::getPosition(*_window);

	// we need to find the closest grid coordinate from the mouse position
	// Searching for the closest x
	int x 		= _grid[0][0].first;
	int diff 	= std::abs(pos.x - x);
	std::pair<int, int> tmp_x = std::make_pair(x, diff);
	for (int i = 0; i < GRID_SIZE; i++){
		x 		= _grid[0][i].first;
		diff 	= std::abs(pos.x - x);

		// Compare the current diff with current
		if (diff < tmp_x.second){
			tmp_x 	= std::make_pair(x, diff);
			indexI = i;
		}
	}

	// Searching for the closest y
	int y 			= _grid[0][0].second;
	diff			= std::abs(pos.y - y);
	std::pair<int, int> tmp_y	= std::make_pair(y, diff);
	for (int j = 0; j < GRID_SIZE; j++){
		y		= _grid[j][0].second;
		diff	= std::abs(pos.y - y);
		if (diff < tmp_y.second){
			tmp_y = std::make_pair(y, diff);
			indexJ = j;
		}
	}

	//
	_pawn.setPosition(tmp_x.first, tmp_y.first);
	_pawnIndex = std::make_pair(indexI, indexJ);
	return std::make_pair(tmp_x.first, tmp_y.first);
}

std::pair<int, int> SfmlHandler::play(eTurn turn){
	(void)turn;
	return _pawnIndex ;
}

void SfmlHandler::animationLogo(void)
{
	int y = _h;
	int opacity = 0;

	while (y > _h / 3)
	{
		clearWindow();
		_drawBackground();
		_window->draw(_logoSprite);
		show();
		_logoSprite.setPosition(_w / 2, y);
		if (opacity < 255){
			_logoSprite.setColor(sf::Color(255, 255, 255, opacity));
			opacity++;
		}
		y--;
		usleep(5000);
	}
}

void SfmlHandler::_drawSelectedChoice(sf::Text & choice)
{
	sf::FloatRect backgroundRect = choice.getLocalBounds();

	sf::RectangleShape background(sf::Vector2f(backgroundRect.width, 2));
	background.setFillColor(_colorMap[eColor::RED]);

	sf::Vector2f pos = background.getPosition();

	background.setPosition(pos.x, pos.y + 74);

	_window->draw(background, choice.getTransform());
}

/*
** Handle the startup menu
*/

eChoice SfmlHandler::drawMenu(void)
{
	_isMenu 			= true;
	eChoice choice 		= eChoice::QUIT;
	eChoice newChoice 	= eChoice::HUMAN;

	// Loop until a choice is made
	while (_isMenu)
	{
		// Get the pressed Key obviously
		eKeys key = getKeyPressed();

		// Handle the key
		if (key == eKeys::ESC)
			return eChoice::QUIT;
		else if (key == eKeys::DOWN || key == eKeys::UP)
			newChoice = (newChoice == eChoice::HUMAN ? eChoice::IA : eChoice::HUMAN);
		else if (key == eKeys::RETURN){
			return choice;
		}

		// If choice has changed, we cacn draw
		if (choice != newChoice){

			// Draw the background
			clearWindow();
			_drawBackground();
			_window->draw(_logoSprite);

			// Configure first choice
			sf::Text choice_1;
			choice_1.setFont(_font);
			choice_1.setString("1 - Human vs Human");
			choice_1.setCharacterSize(54);
			choice_1.setColor(sf::Color(255, 255, 255));
			choice_1.setPosition(_w / 3, _h / 2);

			// Configure second choice
			sf::Text choice_2;
			choice_2.setFont(_font);
			choice_2.setString("2 - Human vs AI");
			choice_2.setCharacterSize(54);
			choice_2.setColor(sf::Color(255, 255, 255));
			choice_2.setPosition(_w / 3, (_h / 2) + SPACING_RATIO);

			// Draw choices
			_window->draw(choice_1);
			_window->draw(choice_2);

			// Draw the line pointing on the selected choice
			if (newChoice == eChoice::HUMAN)
				_drawSelectedChoice(choice_1);
			else
				_drawSelectedChoice(choice_2);

			// Display our beautiful drawings
			show();

			// Update choice value to the actual value
			choice = newChoice;
		}
	}
	return eChoice::QUIT;
}


/*
**	Display some basics infos
*/

void SfmlHandler::drawInfos(eTurn turn, int p1Captures, int p2Captures){

	sf::Text title;
	title.setFont(_font);
	title.setString("Turn :");
	title.setCharacterSize(CHAR_SIZE_INFO);
	title.setColor(sf::Color(255, 255, 255));
	title.setPosition(_w / SPACING_RATIO, _h / SPACING_RATIO);

	std::string str = (turn == eTurn::TURN_PLAYER_1 ? "Player 1" : "Player 2");

	sf::FloatRect rect = title.getGlobalBounds();
	sf::Text info;
	info.setFont(_font);
	info.setString(str);
	info.setCharacterSize(CHAR_SIZE_INFO);
	info.setColor(_colorMap[eColor::RED]);
	info.setPosition((_w / SPACING_RATIO) + rect.width + 25, _h / SPACING_RATIO);

	sf::Text p1Score;
	p1Score.setFont(_font);
	p1Score.setString("Player 1 captured : " + std::to_string(p1Captures));
	p1Score.setCharacterSize(CHAR_SIZE_INFO);
	p1Score.setColor(sf::Color(255, 255, 255));
	p1Score.setPosition(_w / SPACING_RATIO, _h / SPACING_RATIO + CHAR_SIZE_INFO + MARGIN_SIZE_INFO);

	sf::Text p2Score;
	p2Score.setFont(_font);
	p2Score.setString("Player 2 captured : " + std::to_string(p2Captures));
	p2Score.setCharacterSize(CHAR_SIZE_INFO);
	p2Score.setColor(sf::Color(255, 255, 255));
	p2Score.setPosition(_w / SPACING_RATIO, _h / SPACING_RATIO + CHAR_SIZE_INFO * 2 + MARGIN_SIZE_INFO);

	_window->draw(title);
	_window->draw(p1Score);
	_window->draw(p2Score);
	_window->draw(info);
}

void SfmlHandler::draw(void){

	_drawBackground();

	// draw the grid obviously
	drawGrid();

	// Draw mouse pawn
	_window->draw(_pawn);
}

void	SfmlHandler::setTurn(eTurn turn){
	if (turn == eTurn::TURN_PLAYER_1){
		_pawn.setColor(_colorMap[eColor::PLAYER_1_COLOR_TRANS]);
	}
	else if (turn == eTurn::TURN_PLAYER_2){
		_pawn.setColor(_colorMap[eColor::PLAYER_2_COLOR_TRANS]);
	}

}

eKeys	SfmlHandler::modalShow(std::string msg){

	// Black transparent overlay
	sf::RectangleShape background(sf::Vector2f(_w, _h));
	background.setFillColor(sf::Color(0, 0, 0, 180));

	// Box containing the msg
	sf::RectangleShape box(sf::Vector2f(_w / 4, _h / 4));
	box.setFillColor(sf::Color(255, 255, 255));
	box.setOrigin((_w / 4) / 2, (_h / 4) / 2);
	box.setPosition(_w / 2, _h / 2 + 22);

	// Message
	sf::Text txt;
	txt.setFont(_font);
	txt.setString(msg);
	txt.setCharacterSize(44);
	txt.setColor(sf::Color(55, 55, 55));
	sf::FloatRect bounds = txt.getGlobalBounds();
	txt.setOrigin(bounds.width / 2, bounds.height / 2);
	txt.setPosition(_w / 2, _h / 2);

	// Available Commands
	sf::Text commands;
	commands.setFont(_font);
	commands.setString("ESC, SPACE or RETURN : close, R : re-run the game");
	commands.setCharacterSize(34);
	commands.setColor(sf::Color(255, 255, 255));
	bounds = commands.getGlobalBounds();
	commands.setOrigin(bounds.width / 2, bounds.height / 2);
	commands.setPosition(_w / 2, _h - (_h / 4));

	// Draw items
	_window->draw(background);
	_window->draw(box);
	_window->draw(txt);
	_window->draw(commands);

	// Display the modal
	show();

	while (42)
	{
		eKeys key = getKeyPressed();

		if (key == eKeys::ESC || key == eKeys::SPACE || key == eKeys::RETURN || key == eKeys::R)
			return key;
	}
}

void	SfmlHandler::drawAiStats(float elapsedTime){

	sf::Text stat;
	stat.setFont(_font);
	stat.setString("AI time : " + std::to_string(elapsedTime)  + " s");
	stat.setCharacterSize(CHAR_SIZE_INFO);
	stat.setColor(sf::Color(255, 255, 255));
	stat.setPosition(_w / SPACING_RATIO, _h / SPACING_RATIO + CHAR_SIZE_INFO * 3 + MARGIN_SIZE_INFO);

	_window->draw(stat);
}



extern "C" IGraphicHandler *create()
{
	return new SfmlHandler();
}

extern "C" void destroy(IGraphicHandler *handler)
{
	delete handler;
}