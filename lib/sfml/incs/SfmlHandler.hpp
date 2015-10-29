#ifndef SFML_HANDLER_HPP
# define SFML_HANDLER_HPP

# include <map>
# include <IGraphicHandler.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include <SFML/Audio.hpp>

class SfmlHandler : public IGraphicHandler{
    public:
        SfmlHandler();
        SfmlHandler(const SfmlHandler & src);
        SfmlHandler &   operator=(SfmlHandler const & rhs);
        ~SfmlHandler(void);
        int getWidth() const;
        int getHeight() const;

        void createWindow(void);
        eKeys getKeyPressed(void);
        void clearWindow(void);
        void drawBlock(int x, int y, eColor color);
        void show(void);
        void close(void);
        void drawBonus(int);
        void drawGrid(void);

        std::map<int, eKeys> getKeyMap();

    private:
        // Methods
        sf::Color                                       _getColor(eColor);
        void                                            _setGridCoordinate();
        void                                            _handleMousePosition();

        // Attr
        std::map<int, eKeys>                            _keyMap;
        std::map<eColor, sf::Color>                     _colorMap;
        sf::RenderWindow                                *_window;
        int                                             _w;
        int                                             _h;

        sf::Font                                        _font;

        sf::Music                                       _music;

        sf::Texture                                     _backgroundTexture;
        sf::Texture                                     _pawnTexture;

        sf::Sprite                                      _pawnSprite;
        sf::Sprite                                      _backgroundSprite;

        sf::CircleShape                                 _pawn;
        int                                             _block_size;
        std::vector<std::vector<std::pair<int, int>>>   _grid;
};

#endif //SFML_HANDLER_HPP
