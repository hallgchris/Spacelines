//
// Created by christopher on 4/07/19.
//

#include "Board.h"

#include <string>

Board::Board(int size) {
    this->board_ = new CellState*[size];
    for (int i = 0; i < size; ++i) {
        this->board_[i] = new CellState[size];
    }
    this->size_ = size;
    this->state_ = NAUGHTS_MOVE;
}
Board::~Board() {
    for (int i = 0; i < this->size_; ++i) {
        delete [] this->board_[i];
    }
    delete [] this->board_;
}

int Board::getSize() const {
    return size_;
}

CellState **Board::getBoard() const {
    return this->board_;
}

BoardState Board::getState() const {
    return this->state_;
}

bool Board::makeMove(int x, int y) {
    if (!this->validMove(x, y))
        return false;
    this->board_[x][y] = this->getNextMove();
    this->endMove();
    Serial.println(this->toString().c_str());
    return true;
}

void Board::showCube(Cube *cube) const {
    cube->clear();

    int baseX = 1;
    int baseY = 4;
    int baseZ = 1;

    for (int x = 0; x < this->size_; ++x)
        for (int y = 0; y < this->size_; ++y) {
            auto color = Board::getCellColor(this->board_[x][y]);
            cube->setLed(color, baseX + x, baseY, baseZ + y);
        }
}

std::string Board::toString() const {
    std::string result;
    for (int y = 0; y < this->size_; ++y) {
        for (int x = 0; x < this->size_; ++x)
            result += Board::getCellSymbol(this->board_[x][y]);
        result += '\n';
    }
    char stateStr[8];
    sprintf(stateStr, "State: %d\n", (int) this->state_);
    result += stateStr;
    return result;
}

CRGB Board::getCellColor(CellState cellState) {
    switch (cellState) {
        case NONE:
            return CRGB::Black;
        case NAUGHT:
            return CRGB::Red;
        case CROSS:
            return CRGB::Blue;
        case WINNING_LINE:
            return CRGB::White;
    }
}

char Board::getCellSymbol(CellState cellState) {
    switch (cellState) {
        case NONE:
            return ' ';
        case NAUGHT:
            return 'O';
        case CROSS:
            return 'X';
        case WINNING_LINE:
            return '#';
    }
}

bool Board::validMove(int x, int y) const {
    if (x < 0 || x >= this->size_)
        return false;
    if (y < 0 || y >= this->size_)
        return false;
    return this->board_[x][y] == NONE;
}

CellState Board::getNextMove() const {
    switch (this->state_) {
        case NAUGHTS_MOVE:
            return NAUGHT;
        case CROSSES_MOVE:
            return CROSS;
        default:
            return NONE;
    }
}

void Board::endMove() {
    // Don't update the move if somebody wins
    if (this->checkVictory())
        return;

    if (this->state_ == NAUGHTS_MOVE)
        this->state_ = CROSSES_MOVE;
    else if (this->state_ == CROSSES_MOVE)
        this->state_ = NAUGHTS_MOVE;
}

bool Board::checkVictory() {
    // Check each row:
    static int onetwothree[3] = {0, 1, 2};
    static int threetwoone[3] = {2, 1, 0};

    for (int y = 0; y < this->size_; ++y)
        if (this->board_[0][y] != NONE && this->board_[0][y] == this->board_[1][y] && this->board_[1][y] == this->board_[2][y]) {
            const int yrange[3] = {y, y, y};
            this->setWinner(onetwothree, yrange);
            return true;
        }
    // Check each column
    for (int x = 0; x < this->size_; ++x)
        if (this->board_[x][0] != NONE && this->board_[x][0] == this->board_[x][1] && this->board_[x][1] == this->board_[x][2]) {
            const int xrange[3] = {x, x, x};
            this->setWinner(xrange, onetwothree);
            return true;
        }
    // Check diagonals
    if (this->board_[1][1] != NONE) {
        if (this->board_[0][0] == this->board_[1][1] && this->board_[1][1] == this->board_[2][2]) {
            this->setWinner(onetwothree, onetwothree);
            return true;
        }
        if (this->board_[0][2] == this->board_[1][1] && this->board_[1][1] == this->board_[2][0]) {
            this->setWinner(onetwothree, threetwoone);
            return true;
        }
    }
    // Check for draw
    int count = 0;
    for (int x = 0; x < this->size_; ++x)
        for (int y = 0; y < this->size_; ++y)
            if (this->board_[x][y] != NONE)
                count++;
    if (count == 9) {
        this->setDraw();
        return true;
    }
    return false;
}

void Board::setWinner(const int xrange[], const int yrange[]) {
    // Change the board state
    auto winner = this->board_[xrange[0]][yrange[0]];
    if (winner == NAUGHT)
        this->state_ = NAUGHTS_MOVE;
    else if (winner == CROSS)
        this->state_ = CROSSES_WIN;

    // Change state of the cells that caused the win
    for (int i = 0; i < this->size_; ++i) {
        this->board_[xrange[i]][yrange[i]] = WINNING_LINE;
    }
}

void Board::setDraw() {
    this->state_ = DRAW;
}
