#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using std::tuple;
using std::vector;
using std::get;
using std::make_tuple;

class CheckerPiece : public sf::Drawable{
public:
    CheckerPiece(int row, int col) :isKing(false) {
        pos = make_tuple(row, col);
        circle.setRadius(46);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::White);
    }

    void changePos(tuple<int, int> posChange) {
        pos = posChange;
        circle.setPosition({static_cast<float>(get<1>(pos)*100 + 4), static_cast<float>(get<0>(pos)*100+4)});
    }

    tuple<int, int> getPos() const {
        return pos;
    }

    bool getisRed() const {
        return isRed;
    }

    bool isKingPiece() const {
        return isKing;
    }

    void promoteToKing() {
        isKing = true;
    }

    virtual vector<tuple<int, int>> getMove() const {
        if (isKing) {
            return vector<tuple<int, int>>{
                            {get<0>(pos) - 1, get<1>(pos) - 1},
                            {get<0>(pos) - 1, get<1>(pos) + 1},
                            {get<0>(pos) + 1, get<1>(pos) - 1},
                            {get<0>(pos) + 1, get<1>(pos) + 1}
            };
        }
        return {};
    }

    virtual tuple<int, int> getCapture(bool left, bool up) const {
        if (isKing) {
            int row;
            int col;
            if (left) {
                col = get<1>(pos) - 2;
            }
            else {
                col = get<1>(pos) + 2;
            }
            if (up) {
                row = get<0>(pos) - 2;
            }
            else {
                row = get<0>(pos) + 2;
            }
            return make_tuple(col, row);
        }
        return {};
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(circle, states);
    }

protected:
    sf::CircleShape circle;
    bool isRed;
    bool isKing;
    tuple<int, int> pos;
};