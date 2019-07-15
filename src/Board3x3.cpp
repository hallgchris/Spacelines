//
// Created by christopher on 14/07/19.
//

#include <string>
#include "Vec2.h"
#include "Board.h"
#include "Board3x3.h"

void Board3x3::showCube(Cube *cube) const {
    cube->clear();

    Vec3 base = Vec3(1, 4, 1);

    for (int x = 0; x < this->dimensions_.side_length; ++x)
        for (int y = 0; y < this->dimensions_.side_length; ++y) {
            auto color = getCellColor(this->getPos(Vec2(x, y)));
            cube->setLed(base + Vec3(x, 0, y), color);
        }
}

bool Board3x3::validMove(Vec3 pos) const {
    if (pos.getX() < 0 || pos.getX() >= this->dimensions_.side_length)
        return false;
    if (pos.getY() < 0 || pos.getY() >= this->dimensions_.side_length)
        return false;
    if (pos.getZ() != 0)
        return false;
    return this->getPos(pos) == NONE;
}

bool Board3x3::checkVictory(Vec3 prev) {
    // Check row
    if (this->getPos(prev.withX(0)) != NONE && this->getPos(prev.withX(0)) == this->getPos(prev.withX(1)) && this->getPos(prev.withX(1)) == this->getPos(prev.withX(2))) {
        this->setWinner(new Vec3[3] { prev.withX(0), prev.withX(1), prev.withX(2) });
        return true;
    }
    // Check column
    if (this->getPos(prev.withY(0)) != NONE && this->getPos(prev.withY(0)) == this->getPos(prev.withY(1)) && this->getPos(prev.withY(1)) == this->getPos(prev.withY(2))) {
        this->setWinner(new Vec3[3] { prev.withY(0), prev.withY(1), prev.withY(2) });
        return true;
    }
    // Check diagonals
    if (this->getPos(Vec2(1, 1)) != NONE) {
        if (this->getPos(Vec2(0, 0)) == this->getPos(Vec2(1, 1)) && this->getPos(Vec2(1, 1)) == this->getPos(Vec2(2, 2))) {
            this->setWinner(new Vec3[3] { Vec2(0, 0), Vec2(1, 1), Vec2(2, 2)});
            return true;
        }
        if (this->getPos(Vec2(2, 0)) == this->getPos(Vec2(1, 1)) && this->getPos(Vec2(1, 1)) == this->getPos(Vec2(0, 2))) {
            this->setWinner(new Vec3[3] { Vec2(2, 0), Vec2(1, 1), Vec2(0, 2)});
            return true;
        }
    }

    // Check for draw
    int count = 0;
    for (int x = 0; x < this->dimensions_.side_length; ++x)
        for (int y = 0; y < this->dimensions_.side_length; ++y)
            if (this->getPos(Vec2(x, y)) != NONE)
                count++;
    if (count == 9) {
        this->setDraw();
        return true;
    }
    return false;
}
