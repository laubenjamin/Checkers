#include <SFML/Graphics.hpp>


class MainMenu : public sf::Drawable {
    public:
        MainMenu(sf::Font arial) : title(arial), instructions(arial) {
            title.setString("Checkers");
            title.setCharacterSize(100);
            title.setFillColor(sf::Color::Red);
            title.setPosition({400, 50});
            title.setStyle(sf::Text::Bold);
            instructions.setString("To Start Press 'Enter'");
            instructions.setCharacterSize(50);
            instructions.setFillColor(sf::Color::White);
            instructions.setPosition({400, 200});
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(title, states);
            target.draw(instructions, states);
        }
    private:
        sf::Text title;
        sf::Text instructions;
};

class GameOver : public sf::Drawable {
    public:
    GameOver(sf::Font arial) : gameOverText(arial) {}
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(gameOverText, states);
    }
    void setWinner(bool redWinner) {
        if (redWinner) {
            gameOverText.setString("Red Wins!\nPress 'Esc' to Quit");
        } else {
            gameOverText.setString("Black Wins!\nPress 'Esc' to Quit");
        }
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color(255, 215, 0));
        gameOverText.setPosition({400, 50});
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setOutlineColor(sf::Color::Black);
        gameOverText.setOutlineThickness(2);
    }
    private:
        sf::Text gameOverText;
};