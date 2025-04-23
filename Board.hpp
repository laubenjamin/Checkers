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
    void setFutureMoves(vector<tuple<int, int>> moves) {
        futureMoves = moves;
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

private:
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