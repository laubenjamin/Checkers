#include <SFML/Graphics.hpp>

sf::Font arial("arial.ttf");

class MainMenu : public sf::Drawable {
    public:
        MainMenu() {
            sf::Text title(arial);
            title.setString("Checkers");
            title.setCharacterSize(50);
            title.setFillColor(sf::Color::Red);
            title.setPosition({400, 50});
            title.setStyle(sf::Text::Bold);
            title.setOutlineColor(sf::Color::Black);
            title.setOutlineThickness(2);
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(title, states);
        }
    private:
        sf::Text title;
};

class GameOver : public sf::Drawable {
    public:
    GameOver() {
        sf::Text gameOverText(arial);
        gameOverText.setString("Game Over\nTo Play Again Press 'R'");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color(255, 215, 0));
        gameOverText.setPosition({400, 50});
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setOutlineColor(sf::Color::Black);
        gameOverText.setOutlineThickness(2);
    }
    ~GameOver();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(gameOverText, states);
    }
};