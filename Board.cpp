#include "Board.hpp"
#include "BlackPiece.hpp"
#include "RedPiece.hpp" 

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

            if (boardArray[row][col] == 'b') {
                pieceArray[row][col] = new BlackPiece(col * 100 + 4, row * 100 + 4);
            } else if (boardArray[row][col] == 'r') {
                pieceArray[row][col] = new RedPiece(col * 100 + 4, row * 100 + 4);
            } else {
                pieceArray[row][col] = nullptr; // Empty square
            }
        }
    }
}

Board::~Board() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete pieceArray[row][col];
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            target.draw(squares[row][col], states);
        }
    }
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (pieceArray[row][col] != nullptr) {
                target.draw(*pieceArray[row][col], states);
            }
        }
    }
}

