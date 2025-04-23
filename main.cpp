#include <iostream>
#include "Board.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Checkers Board");

    Board board;

    int gameState = 0;

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (gameState == 0 && event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                    gameState = 1;
                }
            }
            else if (gameState == 1 && event->is<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int row = mousePos.y / 100;
                int col = mousePos.x / 100;
                if (board.getPieceAt(row, col) != nullptr && board.getCurPiece()) {
                    if (board.getPieceAt(row, col)->getisRed() == board.getCurTurn()) {
                        board.setCurPiece(board.getPieceAt(row, col));
                        board.setFutureMoves(board.getCurPiece()->getMove());
                    }
                }
                else if (board.getPieceAt(row, col) == nullptr) {
                    if (board.eligibleMove(row, col)) {
                        board.movePiece(board.getCurPiece(), row, col);
                        board.setCurPiece(nullptr);
                        board.changeTurn();
                    }
                    if (board.eligibleCapture(row, col)) {
                        board.capturePiece(board.getCurPiece(), row, col);
                        board.setCurPiece(nullptr);
                        board.changeTurn();
                    }
                }

            }
            else {

            }
        }
        window.clear();
        if (gameState == 0) {
            
        }
        else if (gameState == 1) {
            window.draw(board);
        }
        else {

        }
        window.display();
    }
    return 0;
}