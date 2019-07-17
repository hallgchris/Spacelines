//
// Created by christopher on 17/07/19.
//

#pragma once

#include "Board.h"

class Board5x5x5 : public Board {
public:
    Board5x5x5() : Board(BoardDimensions {5, 3}) { };

    void showCube(Cube *cube) const override;

protected:
    bool validMove(Vec3 pos) const override;
    bool checkVictory(Vec3 prev_move) override;
};
