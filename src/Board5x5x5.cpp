//
// Created by christopher on 17/07/19.
//

#include "Board5x5x5.h"

void Board5x5x5::showCube(Cube *cube) const {
    cube->clear();

    for (int x = 0; x < this->dimensions_.side_length; ++x)
        for (int y = 0; y < this->dimensions_.side_length; ++y)
            for (int z = 0; z < this->dimensions_.side_length; ++z) {
                auto color = getCellColor(this->board_[x][z][y]);
                cube->setLed(Vec3(x, y, z), color);
            }
}

bool Board5x5x5::validMove(Vec3 pos) const {
    if (pos.getX() < 0 || pos.getX() >= this->dimensions_.side_length)
        return false;
    if (pos.getY() < 0 || pos.getY() >= this->dimensions_.side_length)
        return false;
    if (pos.getZ() < 0 || pos.getZ() >= this->dimensions_.side_length)
        return false;
    return this->getPos(pos) == NONE;
}

bool Board5x5x5::checkVictory(Vec3 prev) {
    // Check for line in x
    if (this->checkLine({prev.withX(0), prev.withX(1), prev.withX(2), prev.withX(3), prev.withX(4)}))
        return true;
    // Check for line in y
    if (this->checkLine({prev.withY(0), prev.withY(1), prev.withY(2), prev.withY(3), prev.withY(4)}))
        return true;
    // Check for line in z
    if (this->checkLine({prev.withZ(0), prev.withZ(1), prev.withZ(2), prev.withZ(3), prev.withZ(4)}))
        return true;

    // Diagonals on x-y plane
    if (prev.getX() == prev.getY() && this->checkLine({Vec3(0, 0, prev.getZ()), Vec3(1, 1, prev.getZ()), Vec3(2, 2, prev.getZ()), Vec3(3, 3, prev.getZ()), Vec3(4, 4, prev.getZ())}))
        return true;
    if (prev.getX() + prev.getY() == 4 && this->checkLine({Vec3(4, 0, prev.getZ()), Vec3(3, 1, prev.getZ()), Vec3(2, 2, prev.getZ()), Vec3(1, 3, prev.getZ()), Vec3(0, 4, prev.getZ())}))
        return true;
    // Diagonals on x-z plane
    if (prev.getX() == prev.getZ() && this->checkLine({Vec3(0, prev.getY(), 0), Vec3(1, prev.getY(), 1), Vec3(2, prev.getY(), 2), Vec3(3, prev.getY(), 3), Vec3(4, prev.getY(), 4)}))
        return true;
    if (prev.getX() + prev.getZ() == 4 && this->checkLine({Vec3(4, prev.getY(), 0), Vec3(3, prev.getY(), 1), Vec3(2, prev.getY(), 2), Vec3(1, prev.getY(), 3), Vec3(0, prev.getY(), 4)}))
        return true;
    // Diagonals on y-z plane
    if (prev.getY() == prev.getZ() && this->checkLine({Vec3(prev.getX(), 0, 0), Vec3(prev.getX(), 1, 1), Vec3(prev.getX(), 2, 2), Vec3(prev.getX(), 3, 3), Vec3(prev.getX(), 4, 4)}))
        return true;
    if (prev.getY() + prev.getZ() == 4 && this->checkLine({Vec3(prev.getX(), 4, 0), Vec3(prev.getX(), 3, 1), Vec3(prev.getX(), 2, 2), Vec3(prev.getX(), 1, 3), Vec3(prev.getX(), 0, 4)}))
        return true;

    // Diagonals on x-y-z
    if (this->checkLine({Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(2, 2, 2), Vec3(3, 3, 3), Vec3(4, 4, 4)}))
        return true;
    if (this->checkLine({Vec3(4, 0, 0), Vec3(3, 1, 1), Vec3(2, 2, 2), Vec3(1, 3, 3), Vec3(0, 4, 4)}))
        return true;
    if (this->checkLine({Vec3(0, 4, 0), Vec3(1, 3, 1), Vec3(2, 2, 2), Vec3(3, 1, 3), Vec3(4, 0, 4)}))
        return true;
    if (this->checkLine({Vec3(0, 0, 4), Vec3(1, 1, 3), Vec3(2, 2, 2), Vec3(3, 3, 1), Vec3(4, 4, 0)}))
        return true;

    // Check for draw
    for (int x = 0; x < this->dimensions_.side_length; ++x)
        for (int y = 0; y < this->dimensions_.side_length; ++y)
            for (int z = 0; z < this->dimensions_.side_length; ++z)
                if (this->getPos(Vec3(x, y, z)) == NONE)
                    return false;
    this->setDraw();
    return true;
}
