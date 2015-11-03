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
        int                     getWidth() const;
        int                     getHeight() const;

        void                    createWindow(void);
        eKeys                   getKeyPressed(void);
        void                    clearWindow(void);

        void                    show(void);
        void                    close(void);
        void                    animationLogo(void);
        eChoice                 drawMenu(void);

        void                    drawPawn(int i, int j, eColor);
        void                    drawGrid(void);
        void                    draw(void);
        std::pair<int, int>     play(eTurn);
        std::pair<int, int>     mouseMove();
        void                    drawInfos(eTurn);
        void                    setTurn(eTurn);
        eKeys                   modalShow(std::string);


        std::map<int, eKeys>    getKeyMap();

    private:
        // Methods
        sf::Color                                       _getColor(eColor);
        void                                            _setGridCoordinate();
        void                                            _drawSelectedChoice(sf::Text & choice);
        void                                            _drawBackground(void);

        // Attr
        std::map<int, eKeys>                            _keyMap;
        std::map<eColor, sf::Color>                     _colorMap;
        sf::RenderWindow                                *_window;
        int                                             _w;
        int                                             _h;
        bool                                            _isMenu;

        sf::Font                                        _font;

        sf::Music                                       _music;

        sf::Texture                                     _backgroundTexture;
        sf::Texture                                     _logoTexture;
        sf::Texture                                     _pawnTexture;

        sf::Sprite                                      _pawn;
        sf::Sprite                                      _backgroundSprite;
        sf::Sprite                                      _logoSprite;

        // sf::CircleShape                                 _pawn;
        std::pair<int, int>                             _pawnIndex;
        int                                             _block_size;
        std::vector<std::vector<std::pair<int, int>>>   _grid;
};

#endif //SFML_HANDLER_HPP
