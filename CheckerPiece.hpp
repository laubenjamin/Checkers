#pragma once

#include <iostream>

using std::tuple;

class CheckerPiece {
    public:
    private:
        bool isKing = false;
        tuple<int, int> pos;
};