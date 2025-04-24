#include <iostream>
#include "Board.hpp"
#include "Screen.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Checkers Board");

    Board board;

    MainMenu mainMenu;
    GameOver gameOver;

    int gameState = 1;

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
                if (board.getPieceAt(row, col) != nullptr && (board.getPieceAt(row, col)->getisRed() == board.getCurTurn())) {
                    board.setFutureMoves(true);
                    board.setCurPiece(board.getPieceAt(row, col));
                    board.setFutureMoves();
                }
                else if (board.getPieceAt(row, col) == nullptr) {
                    if (board.eligibleMove(row, col)) {
                        board.movePiece(row, col);
                        board.setCurPiece(nullptr);
                        board.setFutureMoves(true);
                        board.changeTurn();
                    }
                    if (board.eligibleCapture(row, col)) {
                        board.capturePiece(row, col);
                        board.setCurPiece(nullptr);
                        board.setFutureMoves(true);
                        board.changeTurn();
                    }
                }

            }
            else if (gameState == 3 && event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
                    gameState = 0;
                }
            }
        }
        window.clear();
        if (gameState == 0) {
            window.draw(mainMenu);
        }
        else if (gameState == 1) {
            window.draw(board);
        }
        else {
            window.draw(gameOver);
        }
        window.display();
    }
    return 0;
}