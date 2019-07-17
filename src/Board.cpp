//
// Created by christopher on 4/07/19.
//

#include "Board.h"

Board::Board(BoardDimensions dimensions) {
    initBoard(dimensions);
}

Board::~Board() {
    deleteBoard();
}

void Board::initBoard(BoardDimensions dimensions) {
    this->board_ = new CellState**[dimensions.side_length];
    for (int i = 0; i < dimensions.side_length; ++i) {
        this->board_[i] = new CellState*[dimensions.side_length];
        for (int j = 0; j < dimensions.side_length; ++j) {
            this->board_[i][j] = new CellState[dimensions.side_length];
            for (int k = 0; k < dimensions.side_length; ++k)
                this->board_[i][j][k] = NONE;
        }
    }
    this->dimensions_ = dimensions;
    this->state_ = NAUGHTS_MOVE;
}

void Board::deleteBoard() {
    for (int i = 0; i < this->dimensions_.side_length; ++i) {
        for (int j = 0; j < this->dimensions_.side_length; ++j) {
            delete [] this->board_[i][j];
        }
        delete [] this->board_[i];
    }
    delete [] this->board_;
}

void Board::reset() {
    deleteBoard();
    initBoard(this->dimensions_);
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

bool Board::makeMove(Vec3 pos) {
    if (!this->validMove(pos))
        return false;
    this->setPos(pos, this->getNextMove());
    this->endMove(pos);
    Serial.println(this->toString().c_str());
    return true;
}

String Board::toString() const {
    String result;
    for (int y = 0; y < this->dimensions_.side_length; ++y) {
        for (int z = 0; z < this->dimensions_.side_length; ++z) {
            for (int x = 0; x < this->dimensions_.side_length; ++x)
                result += Board::getCellSymbol(this->board_[x][y][z]);
            result += " | ";
        }
        result += '\n';
    }
    char stateStr[8];
    sprintf(stateStr, "State: %d\n", (int) this->state_);
    result += stateStr;
    return result;
}

bool Board::checkLine(std::vector<Vec3> line) {
    if (this->getPos(line[0]) == NONE)
        return false;
    for (int i = 0; i < line.size() - 1; ++i)
        if (this->getPos(line[i]) != this->getPos(line[i + 1]))
            return false;
    setWinner(line);
    return true;
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

void Board::endMove(Vec3 move) {
    // Don't update the move if somebody wins
    if (this->checkVictory(move))
        return;

    if (this->state_ == NAUGHTS_MOVE)
        this->state_ = CROSSES_MOVE;
    else if (this->state_ == CROSSES_MOVE)
        this->state_ = NAUGHTS_MOVE;
}

CellState Board::getPos(Vec3 pos) const {
    return this->board_[pos.getX()][pos.getY()][pos.getZ()];
}

void Board::setPos(Vec3 pos, CellState value) {
    this->board_[pos.getX()][pos.getY()][pos.getZ()] = value;
}

void Board::setWinner(std::vector<Vec3> winning_line) {
    // Change the board state
    auto winner = this->getPos(winning_line[0]);
    if (winner == NAUGHT)
        this->state_ = NAUGHTS_WIN;
    else if (winner == CROSS)
        this->state_ = CROSSES_WIN;

    // Change state of the cells that caused the win
    for (int i = 0; i < this->dimensions_.side_length; ++i)
        this->setPos(winning_line[i], WINNING_LINE);
}

void Board::setDraw() {
    this->state_ = DRAW;
}
