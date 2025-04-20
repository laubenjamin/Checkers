#pragma once

#include <iostream>
#include <vector>

using std::tuple;
using std::vector;
using std::get;
using std::make_tuple;

class CheckerPiece {
    public:
        CheckerPiece(int row, int col) :isKing(false) {
            pos = make_tuple(row, col);
        }

        void changePos(tuple<int, int> posChange) {
            pos = make_tuple(get<0>(pos) + get<0>(posChange), get<1>(pos) + get<1>(posChange));
        }

        tuple<int, int> getPos() {
            return pos;
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
        virtual vector<tuple<int, int>> getCapture() const {
            if (isKing) {
                return vector<tuple<int, int>>{
                    {get<0>(pos) - 2, get<1>(pos) - 2},
                    {get<0>(pos) - 2, get<1>(pos) + 2},
                    {get<0>(pos) + 2, get<1>(pos) - 2},
                    {get<0>(pos) + 2, get<1>(pos) + 2}
                };
            }
            return {};
        }


    private:
        bool isKing;
        tuple<int, int> pos;
};