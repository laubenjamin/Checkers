#pragma once
#include <iostream>
#include <cassert>
#include "Board.hpp"
#include "RedPiece.hpp"
#include "BlackPiece.hpp"

using std::cout;
using std::endl;

class TestCase {
    public:
        void printTestResult(const std::string& testName, bool result) {
            if (result) {
                cout << "[PASS] " << testName << endl;
            } else {
                cout << "[FAIL] " << testName << endl;
            }
        }
        
        void testCheckerPieceInitialization() {
            RedPiece redPiece(5, 2);
            BlackPiece blackPiece(2, 3);
            assert(redPiece.getPos() == make_tuple(5, 2));
            assert(blackPiece.getPos() == make_tuple(2, 3));
            assert(redPiece.getisRed());
            assert(!blackPiece.getisRed());
            printTestResult("CheckerPiece Initialization", true);
        }
        
        void testCheckerPieceKingPromotion() {
            RedPiece redPiece(0, 2);
            BlackPiece blackPiece(7, 3);
            assert(!redPiece.isKingPiece());
            assert(!blackPiece.isKingPiece());
            redPiece.changePos(make_tuple(0, 2));
            blackPiece.changePos(make_tuple(7, 3));
            assert(redPiece.isKingPiece());
            assert(blackPiece.isKingPiece());
            printTestResult("CheckerPiece King Promotion", true);
        }
        
        void testBoardInitialization(sf::Font arial) {
            Board board(arial);
            assert(board.getNumRedPieces() == 12);
            assert(board.getNumBlackPieces() == 12);
            assert(board.getPieceAt(0, 1) != nullptr);
            assert(board.getPieceAt(7, 0) != nullptr);
            assert(board.getPieceAt(3, 3) == nullptr);
            printTestResult("Board Initialization", true);
        }
        
        void testBoardMovePiece(sf::Font arial) {
            Board board(arial);
            CheckerPiece* piece = board.getPieceAt(5, 0);
            assert(piece != nullptr);
            board.setCurPiece(piece);
            board.movePiece(4, 1);
            assert(board.getPieceAt(5, 0) == nullptr);
            assert(board.getPieceAt(4, 1) == piece);
            printTestResult("Board Move Piece", true);
        }
        
        void testBoardChangeTurn(sf::Font arial) {
            Board board(arial);
            assert(board.getCurTurn());
            board.changeTurn();
            assert(!board.getCurTurn());
            board.changeTurn();
            assert(board.getCurTurn());
            printTestResult("Board Change Turn", true);
        }
        
};