#ifndef SFML_HANDLER_HPP
# define SFML_HANDLER_HPP

# include <map>
# include <IGraphicHandler.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

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
        sf::Color _getColor(eColor);

        std::map<int, eKeys> _keyMap;
        std::map<eColor, sf::Color> _colorMap;
        sf::RenderWindow *_window;
        int _w;
        int _h;
        sf::Font _font;
        sf::Texture _backgroundTexture;
        sf::Texture _pawnTexture;

        sf::Sprite  _pawnSprite;
        sf::Sprite  _backgroundSprite;

        sf::CircleShape _pawn;
};

#endif //SFML_HANDLER_HPP
