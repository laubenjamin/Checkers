#include "Board.hpp"

Board::Board() {
    const float squareSize = 100.0f; // Size of each square
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            squares[row][col].setSize(sf::Vector2f(squareSize, squareSize));
            squares[row][col].setPosition({static_cast<float>(col) * squareSize, static_cast<float>(row) * squareSize});

            // Alternate colors: red and black
            if ((row + col) % 2 == 0) {
                squares[row][col].setFillColor(sf::Color::Red);
            } else {
                squares[row][col].setFillColor(sf::Color::Black);
            }
        }
    }
}

Board::~Board() {}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            target.draw(squares[row][col], states);
        }
    }
}