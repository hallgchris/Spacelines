//
// Created by christopher on 15/07/19.
//

#include "Board3x3x3.h"

void Board3x3x3::showCube(Cube *cube) const {
    cube->clear();

    for (int x = 0; x < this->dimensions_.side_length; ++x)
        for (int y = 0; y < this->dimensions_.side_length; ++y)
            for (int z = 0; z < this->dimensions_.side_length; ++z) {
                auto color = getCellColor(this->board_[x][z][y]);
                cube->setLed(Vec3(x, y, z) * 2, color);
            }
}

bool Board3x3x3::validMove(Vec3 pos) const {
    if (pos.getX() < 0 || pos.getX() >= this->dimensions_.side_length)
        return false;
    if (pos.getY() < 0 || pos.getY() >= this->dimensions_.side_length)
        return false;
    if (pos.getZ() < 0 || pos.getZ() >= this->dimensions_.side_length)
        return false;
    return this->getPos(pos) == NONE;
}

bool Board3x3x3::checkVictory(Vec3 prev_move) {
    return false;
}
