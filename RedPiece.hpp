#pragma once

#include "CheckerPiece.hpp"

class RedPiece : public CheckerPiece {
public:
    RedPiece(int row, int col) : CheckerPiece(row, col) {
        circle.setFillColor(sf::Color::Red);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::White);
        circle.setPosition(sf::Vector2f(4, 4));
    };

    vector<tuple<int, int>> getMove() {
        if (isKingPiece()) {
            return CheckerPiece::getMove();
        }
        return vector<tuple<int, int>>{
                        {get<0>(getPos()) + 1, get<1>(getPos()) + 1},
                        {get<0>(getPos()) + 1, get<1>(getPos()) - 1}
        };
    }
    vector<tuple<int, int>> getCapture() {
        if (isKingPiece()) {
            return CheckerPiece::getCapture();
        }
        return vector<tuple<int, int>>{
                        {get<0>(getPos()) + 2, get<1>(getPos()) + 2},
                        {get<0>(getPos()) + 2, get<1>(getPos()) - 2}
        };
    }
};