#include <iostream>
#include "Board.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Checkers Board");

    Board board;

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(board);
        window.display();
    }

    return 0;
}