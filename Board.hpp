#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include "CheckerPiece.hpp"

using std::abs;


class Board : public sf::Drawable {
public:
    Board();
    ~Board();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    CheckerPiece* getPieceAt(int row, int col) {
        return pieceArray[row][col];
    }
    void setFutureMoves(bool clear = false);
    void setCurPiece(CheckerPiece* piece) {
        curPiece = piece;
    }
    CheckerPiece* getCurPiece() {
        return curPiece;
    }
    bool capturePiece(int row, int col);
    void movePiece(int row, int col);
    bool eligibleMove(int row, int col);
    bool eligibleCapture(int row, int col);
    void changeTurn() {
        curTurn = !curTurn;
    }
    bool getCurTurn() {
        return curTurn;
    }
    bool checkInBounds(tuple<int, int> pos);
private:
    bool curTurn = true; // true for red, false for black
    vector<tuple<int, int>> futureMoves;
    CheckerPiece* curPiece = nullptr;
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
    CheckerPiece* pieceArray [8][8] = {nullptr};
};