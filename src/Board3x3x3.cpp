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

bool Board3x3x3::checkVictory(Vec3 prev) {
    // Check for line in x
    if (this->checkLine({prev.withX(0), prev.withX(1), prev.withX(2)}))
        return true;
    // Check for line in y
    if (this->checkLine({prev.withY(0), prev.withY(1), prev.withY(2)}))
        return true;
    // Check for line in z
    if (this->checkLine({prev.withZ(0), prev.withZ(1), prev.withZ(2)}))
        return true;

    // Diagonals on x-y plane
    if (prev.getX() == prev.getY() && this->checkLine({Vec3(0, 0, prev.getZ()), Vec3(1, 1, prev.getZ()), Vec3(2, 2, prev.getZ())}))
        return true;
    if (prev.getX() + prev.getY() == 2 && this->checkLine({Vec3(2, 0, prev.getZ()), Vec3(1, 1, prev.getZ()), Vec3(0, 2, prev.getZ())}))
        return true;
    // Diagonals on x-z plane
    if (prev.getX() == prev.getZ() && this->checkLine({Vec3(0, prev.getY(), 0), Vec3(1, prev.getY(), 1), Vec3(2, prev.getY(), 2)}))
        return true;
    if (prev.getX() + prev.getZ() == 2 && this->checkLine({Vec3(2, prev.getY(), 0), Vec3(1, prev.getY(), 1), Vec3(0, prev.getY(), 2)}))
        return true;
    // Diagonals on y-z plane
    if (prev.getY() == prev.getZ() && this->checkLine({Vec3(prev.getX(), 0, 0), Vec3(prev.getX(), 1, 1), Vec3(prev.getX(), 2, 2)}))
        return true;
    if (prev.getY() + prev.getZ() == 2 && this->checkLine({Vec3(prev.getX(), 2, 0), Vec3(prev.getX(), 1, 1), Vec3(prev.getX(), 0, 2)}))
        return true;

    // Diagonals on x-y-z
    if (this->checkLine({Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(2, 2, 2)}))
        return true;
    if (this->checkLine({Vec3(2, 0, 0), Vec3(1, 1, 1), Vec3(0, 2, 2)}))
        return true;
    if (this->checkLine({Vec3(0, 2, 0), Vec3(1, 1, 1), Vec3(2, 0, 2)}))
        return true;
    if (this->checkLine({Vec3(0, 0, 2), Vec3(1, 1, 1), Vec3(2, 2, 0)}))
        return true;

    // Check for draw (Technically impossible on 3x3x3 apparently...)
    for (int x = 0; x < this->dimensions_.side_length; ++x)
        for (int y = 0; y < this->dimensions_.side_length; ++y)
            for (int z = 0; z < this->dimensions_.side_length; ++z)
                if (this->getPos(Vec3(x, y, z)) == NONE)
                    return false;
    this->setDraw();
    return true;
}
