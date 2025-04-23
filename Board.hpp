#include <SFML/Graphics.hpp>
#include "CheckerPiece.hpp"

class Board : public sf::Drawable {
public:
    Board();
    ~Board();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    CheckerPiece* getPieceAt(int row, int col) {
        return pieceArray[row][col];
    }
    void setFutureMoves() {
        if (curPiece == nullptr) {
            return;
        }
        else {
            vector<tuple<int, int>> nextMoves = curPiece->getMove();
            for (tuple<int, int> temp : nextMoves) {
                if (pieceArray[get<0>(temp)][get<1>(temp)] != nullptr) {
                    if (pieceArray[get<0>(temp)][get<1>(temp)]->getisRed() != curPiece->getisRed()) {
                        tuple
                    }
                }
                else {
                    futureMoves.
                }
            }
        }
    }
    void setCurPiece(CheckerPiece* piece) {
        curPiece = piece;
    }
    CheckerPiece* getCurPiece() {
        return curPiece;
    }
    bool capturePiece(CheckerPiece* piece, int row, int col) {
        if (pieceArray[row][col] != nullptr) {
            delete pieceArray[row][col];
            pieceArray[row][col] = nullptr;
            return true;
        }
        return false;
    }
    void movePiece(CheckerPiece* piece, int row, int col) {
        tuple<int, int> temp = piece->getPos();
        pieceArray[row][col] = piece;
        pieceArray[get<0>(temp)][get<1>(temp)] = nullptr;
        piece->changePos(make_tuple(row, col));
    }
    bool eligibleMove(int row, int col);
    bool eligibleCapture(int row, int col);
    void changeTurn() {
        curTurn = !curTurn;
    }
    bool getCurTurn() {
        return curTurn;
    }
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