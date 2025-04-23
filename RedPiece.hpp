#pragma once

#include "CheckerPiece.hpp"

class RedPiece : public CheckerPiece {
public:
    RedPiece(int row, int col) : CheckerPiece(row, col) {
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(sf::Vector2f(row, col));
        isRed = true;
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
    tuple<int, int> getCapture(bool left, bool up) {
        if (isKingPiece()) {
            return CheckerPiece::getCapture(left, up);
        }
        int row = get<1>(getPos()) - 2;
        int col;
        if (left) {
            col = get<0>(getPos()) + 2;
        }
        else {
            col = get<0>(getPos()) - 2;
        }
        return make_tuple(col, row);
    }
};