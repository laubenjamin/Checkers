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
        if (get<0>(pos) == 0 && isRed) {
            isKing = true;
        }
        else if (get<0>(pos) == 7 && !isRed) {
            isKing = true;
        }
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
            return make_tuple(row, col);
        }
        return {};
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(circle, states);
        if (isKing) {
            sf::ConvexShape base;
            base.setPointCount(4);
            base.setPoint(0, sf::Vector2f(0, 40));  
            base.setPoint(1, sf::Vector2f(60, 40)); 
            base.setPoint(2, sf::Vector2f(60, 50)); 
            base.setPoint(3, sf::Vector2f(0, 50));
            base.setFillColor(sf::Color::Yellow);
            base.setOutlineThickness(2);
            base.setOutlineColor(sf::Color::Black);
            base.setPosition({static_cast<float>(get<1>(pos) * 100 + 20), static_cast<float>(get<0>(pos) * 100 + 15)});
    
            sf::ConvexShape leftSpike;
            leftSpike.setPointCount(3);
            leftSpike.setPoint(0, sf::Vector2f(0, 40)); 
            leftSpike.setPoint(1, sf::Vector2f(0, 20)); 
            leftSpike.setPoint(2, sf::Vector2f(15, 40)); 
            leftSpike.setFillColor(sf::Color::Yellow);
            leftSpike.setOutlineThickness(2);
            leftSpike.setOutlineColor(sf::Color::Black);
            leftSpike.setPosition({static_cast<float>(get<1>(pos) * 100 + 20), static_cast<float>(get<0>(pos) * 100 + 15)});
    
            sf::ConvexShape middleSpike;
            middleSpike.setPointCount(3);
            middleSpike.setPoint(0, sf::Vector2f(15, 40)); 
            middleSpike.setPoint(1, sf::Vector2f(30, 20)); 
            middleSpike.setPoint(2, sf::Vector2f(45, 40));
            middleSpike.setFillColor(sf::Color::Yellow);
            middleSpike.setOutlineThickness(2);
            middleSpike.setOutlineColor(sf::Color::Black);
            middleSpike.setPosition({static_cast<float>(get<1>(pos) * 100 + 20), static_cast<float>(get<0>(pos) * 100 + 15)});
    
            sf::ConvexShape rightSpike;
            rightSpike.setPointCount(3);
            rightSpike.setPoint(0, sf::Vector2f(45, 40));
            rightSpike.setPoint(1, sf::Vector2f(60, 20));
            rightSpike.setPoint(2, sf::Vector2f(60, 40));
            rightSpike.setFillColor(sf::Color::Yellow);
            rightSpike.setOutlineThickness(2);
            rightSpike.setOutlineColor(sf::Color::Black);
            rightSpike.setPosition({static_cast<float>(get<1>(pos) * 100 + 20), static_cast<float>(get<0>(pos) * 100 + 15)});
    
            target.draw(base, states);
            target.draw(leftSpike, states);
            target.draw(middleSpike, states);
            target.draw(rightSpike, states);
        }
    }

protected:
    sf::CircleShape circle;
    bool isRed;
    bool isKing;
    tuple<int, int> pos;
};