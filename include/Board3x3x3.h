//
// Created by christopher on 15/07/19.
//

#pragma once

#include "Board.h"

class Board3x3x3 : public Board {
public:
    Board3x3x3() : Board(BoardDimensions {3, 3}) { };

    void showCube(Cube *cube) const override;

protected:
    bool validMove(Vec3 pos) const override;
    bool checkVictory(Vec3 prev_move) override;
};
