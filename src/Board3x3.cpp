//
// Created by christopher on 14/07/19.
//

#include <string>
#include "Board.h"
#include "Board3x3.h"

void Board3x3::showCube(Cube *cube) const {
    cube->clear();

    int baseX = 1;
    int baseY = 4;
    int baseZ = 1;

    for (int x = 0; x < this->dimensions_.side_length; ++x)
        for (int y = 0; y < this->dimensions_.side_length; ++y) {
            auto color = getCellColor(this->board_[x][y][0]);
            cube->setLed(color, baseX + x, baseY, baseZ + y);
        }
}

bool Board3x3::validMove(int x, int y, int z) const {
    if (x < 0 || x >= this->dimensions_.side_length)
        return false;
    if (y < 0 || y >= this->dimensions_.side_length)
        return false;
    if (z != 0)
        return false;
    return this->board_[x][y][0] == NONE;
}

bool Board3x3::checkVictory() {
    // Check each row:
    static int onetwothree[3] = {0, 1, 2};
    static int threetwoone[3] = {2, 1, 0};
    static int zeros[3] = {0, 0, 0};

    for (int y = 0; y < this->dimensions_.side_length; ++y)
        if (this->board_[0][y][0] != NONE && this->board_[0][y][0] == this->board_[1][y][0] && this->board_[1][y][0] == this->board_[2][y][0]) {
            const int yrange[3] = {y, y, y};
            this->setWinner(onetwothree, yrange, zeros);
            return true;
        }
    // Check each column
    for (int x = 0; x < this->dimensions_.side_length; ++x)
        if (this->board_[x][0][0] != NONE && this->board_[x][0][0] == this->board_[x][1][0] && this->board_[x][1][0] == this->board_[x][2][0]) {
            const int xrange[3] = {x, x, x};
            this->setWinner(xrange, onetwothree, zeros);
            return true;
        }
    // Check diagonals
    if (this->board_[1][1][0] != NONE) {
        if (this->board_[0][0][0] == this->board_[1][1][0] && this->board_[1][1][0] == this->board_[2][2][0]) {
            this->setWinner(onetwothree, onetwothree, zeros);
            return true;
        }
        if (this->board_[0][2][0] == this->board_[1][1][0] && this->board_[1][1][0] == this->board_[2][0][0]) {
            this->setWinner(onetwothree, threetwoone, zeros);
            return true;
        }
    }
    // Check for draw
    int count = 0;
    for (int x = 0; x < this->dimensions_.side_length; ++x)
        for (int y = 0; y < this->dimensions_.side_length; ++y)
            if (this->board_[x][y][0] != NONE)
                count++;
    if (count == 9) {
        this->setDraw();
        return true;
    }
    return false;
}
