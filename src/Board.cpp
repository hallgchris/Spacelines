//
// Created by christopher on 4/07/19.
//

#include "Board.h"
#include "Board3x3.h"

#include <string>

Board::Board(BoardDimensions dimensions) {
    this->board_ = new CellState**[dimensions.side_length];
    for (int i = 0; i < dimensions.side_length; ++i) {
        this->board_[i] = new CellState*[dimensions.side_length];
        for (int j = 0; j < dimensions.side_length; ++j) {
            this->board_[i][j] = new CellState[dimensions.side_length];
        }
    }
    this->dimensions_ = dimensions;
    this->state_ = NAUGHTS_MOVE;
}
Board::~Board() {
    for (int i = 0; i < this->dimensions_.side_length; ++i) {
        for (int j = 0; j < this->dimensions_.side_length; ++j) {
            delete [] this->board_[i][j];
        }
        delete [] this->board_[i];
    }
    delete [] this->board_;
}

BoardDimensions Board::getDimensions() const {
    return this->dimensions_;
}

CellState ***Board::getBoard() const {
    return this->board_;
}

BoardState Board::getState() const {
    return this->state_;
}

bool Board::makeMove(int x, int y, int z) {
    if (!this->validMove(x, y, z))
        return false;
    this->board_[x][y][z] = this->getNextMove();
    this->endMove();
    Serial.println(this->toString().c_str());
    return true;
}

std::string Board::toString() const {
    std::string result;
    for (int z = 0; z < this->dimensions_.side_length; ++z) {
        for (int y = 0; y < this->dimensions_.side_length; ++y) {
            for (int x = 0; x < this->dimensions_.side_length; ++x)
                result += Board::getCellSymbol(this->board_[x][y][z]);
            result += '\n';
        }
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

void Board::setWinner(const int xrange[], const int yrange[], const int zrange[]) {
    // Change the board state
    auto winner = this->board_[xrange[0]][yrange[0]][zrange[0]];
    if (winner == NAUGHT)
        this->state_ = NAUGHTS_MOVE;
    else if (winner == CROSS)
        this->state_ = CROSSES_WIN;

    // Change state of the cells that caused the win
    for (int i = 0; i < this->dimensions_.side_length; ++i) {
        this->board_[xrange[i]][yrange[i]][zrange[i]] = WINNING_LINE;
    }
}

void Board::setDraw() {
    this->state_ = DRAW;
}
