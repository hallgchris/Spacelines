//
// Created by christopher on 14/07/19.
//

#include <Board.h>
#include "Cube.h"

class Board3x3 : public Board {
public:
    Board3x3() : Board(BoardDimensions {3, 2}) { };

    void showCube(Cube *cube) const override;

private:
    bool validMove(int x, int y, int z) const override;
    bool checkVictory() override;
};



