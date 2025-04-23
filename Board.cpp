#include "Board.hpp"
#include "BlackPiece.hpp"
#include "RedPiece.hpp" 

Board::Board() {
    const float squareSize = 100.0f; // Size of each square
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            squares[row][col].setSize(sf::Vector2f(squareSize, squareSize));
            squares[row][col].setPosition({static_cast<float>(col) * squareSize, static_cast<float>(row) * squareSize});

            // Alternate colors: red and black
            if ((row + col) % 2 == 0) {
                squares[row][col].setFillColor(sf::Color::Red);
            } else {
                squares[row][col].setFillColor(sf::Color::Black);
            }

            if (boardArray[row][col] == 'b') {
                pieceArray[row][col] = new BlackPiece(col * 100 + 4, row * 100 + 4);
            } else if (boardArray[row][col] == 'r') {
                pieceArray[row][col] = new RedPiece(col * 100 + 4, row * 100 + 4);
            } else {
                pieceArray[row][col] = nullptr; // Empty square
            }
        }
    }
}

Board::~Board() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            delete pieceArray[row][col];
        }
    }
}

bool Board::eligibleMove(int row, int col) {
    if (curPiece == nullptr) {
        return false;
    }
    if (pieceArray[row][col] == nullptr) {
        for (tuple<int, int> move : futureMoves) {
            if (get<0>(move) == row && get<1>(move) == col) {
                return true;
            }
        }
    }
    return false;
}

bool Board::eligibleCapture(int row, int col) {
    if (curPiece == nullptr) {
        return false;
    }
    if (pieceArray[row - 1][col - 1] != nullptr) {
        for (tuple<int, int> move : futureMoves) {
            if (get<0>(move) == row && get<1>(move) == col) {
                return true;
            }
        }
    }
    return false;
}

bool Board::capturePiece(CheckerPiece* piece, int row, int col) {
    if (pieceArray[row][col] != nullptr) {
        delete pieceArray[row][col];
        pieceArray[row][col] = nullptr;
        return true;
    }
    return false;
}

void Board::movePiece(CheckerPiece* piece, int row, int col) {
    tuple<int, int> temp = piece->getPos();
    pieceArray[row][col] = piece;
    pieceArray[get<0>(temp)][get<1>(temp)] = nullptr;
    piece->changePos(make_tuple(row, col));
}

void Board::setFutureMoves() {
    if (curPiece == nullptr) {
        return;
    }
    else {
        vector<tuple<int, int>> nextMoves = curPiece->getMove();
        for (tuple<int, int> temp : nextMoves) {
            if (pieceArray[get<0>(temp)][get<1>(temp)] != nullptr) {
                if (pieceArray[get<0>(temp)][get<1>(temp)]->getisRed() != curPiece->getisRed()) {
                    bool left;
                    bool up;
                    if ((get<0>(temp) - get<0>(curPiece->getPos())) < 0) {
                        left = true;
                    }
                    if ((get<1>(temp) - get<1>(curPiece->getPos())) < 0) {
                        up = true;
                    }
                    futureMoves.push_back(curPiece->getCapture(left, up));
                }
            }
            else {
                futureMoves.push_back(temp);
            }
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            target.draw(squares[row][col], states);
        }
    }
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (pieceArray[row][col] != nullptr) {
                target.draw(*pieceArray[row][col], states);
            }
        }
    }
}

