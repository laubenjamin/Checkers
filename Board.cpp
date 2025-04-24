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
                pieceArray[row][col] = new BlackPiece(row, col);
            } else if (boardArray[row][col] == 'r') {
                pieceArray[row][col] = new RedPiece(row, col);
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
    if (curPiece == nullptr || (abs(row - get<0>(curPiece->getPos())) != 1)) {
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
    if (curPiece == nullptr || (abs(row - get<0>(curPiece->getPos())) != 2)) {
        return false;
    }
    if (pieceArray[(row + get<0>(curPiece->getPos()))/2][(col + get<1>(curPiece->getPos()))/2] != nullptr) {
        for (tuple<int, int> move : futureMoves) {
            if (get<0>(move) == row && get<1>(move) == col) {
                return true;
            }
        }
    }
    return false;
}

bool Board::capturePiece(int row, int col) {
    int captureRow = (row + get<0>(curPiece->getPos())) / 2;
    int captureCol = (col + get<1>(curPiece->getPos())) / 2;
    if (pieceArray[captureRow][captureCol] != nullptr) {
        delete pieceArray[captureRow][captureCol];
        pieceArray[captureRow][captureCol] = nullptr;
        movePiece(row, col);
        if (curTurn) {
            numBlackPieces--;
        }
        else {
            numRedPieces--;
        }
        return true;
    }
    return false;
}

void Board::movePiece(int row, int col) {
    tuple<int, int> temp = curPiece->getPos();
    pieceArray[row][col] = curPiece;
    pieceArray[get<0>(temp)][get<1>(temp)] = nullptr;
    curPiece->changePos(make_tuple(row, col));
}

bool Board::checkInBounds(tuple<int, int> pos) {
    if (get<0>(pos) < 0 || get<0>(pos) > 7 || get<1>(pos) < 0 || get<1>(pos) > 7) {
        return false;
    }
    return true;
}

void Board::setFutureMoves(bool clear) {
    if (clear) {
        futureMoves.clear();
        return;
    }
    if (curPiece == nullptr) {
        return;
    }
    else {
        vector<tuple<int, int>> nextMoves = curPiece->getMove();
        for (tuple<int, int> temp : nextMoves) {
            if (!checkInBounds(temp)) {
                continue;
            }
            if (pieceArray[get<0>(temp)][get<1>(temp)] != nullptr) {
                if (pieceArray[get<0>(temp)][get<1>(temp)]->getisRed() != curPiece->getisRed()) {
                    bool left = false;
                    bool up = false;
                    if ((get<0>(temp) - get<0>(curPiece->getPos())) < 0) {
                        up = true;
                    }
                    if ((get<1>(temp) - get<1>(curPiece->getPos())) < 0) {
                        left = true;
                    }
                    tuple<int, int> tempCapture = curPiece->getCapture(left, up);
                    if (pieceArray[get<0>(tempCapture)][get<1>(tempCapture)] == nullptr && checkInBounds(tempCapture)) {
                        futureMoves.push_back(tempCapture);
                    }
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
    if (!futureMoves.empty()) {
        for (tuple<int, int> move : futureMoves) {
            sf::CircleShape circle(20);
            circle.setFillColor(sf::Color(255, 255, 0, 128));
            circle.setPosition({static_cast<float>(get<1>(move) * 100 + 30), static_cast<float>(get<0>(move) * 100 + 30)});
            target.draw(circle, states);
        }
    }
}

