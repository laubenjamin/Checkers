#include <SFML/Graphics.hpp>

class Board : public sf::Drawable {
public:
    Board();
    ~Board();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape squares[8][8]; // 8x8 grid of squares
    char boardArray [8][8] = {
        {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
        {'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
        {' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'r', ' ', 'r', ' ', 'r', ' ', 'r', ' '},
        {' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r'},
        {'r', ' ', 'r', ' ', 'r', ' ', 'r', ' '}
    };
};