//
// Created by christopher on 4/07/19.
//

#pragma once

#include "Cube.h"

enum CellState {
    NONE,
    NAUGHT,
    CROSS,
    WINNING_LINE,
};

enum BoardState {
    NAUGHTS_MOVE,
    CROSSES_MOVE,
    NAUGHTS_WIN,
    CROSSES_WIN,
    DRAW,
};

struct BoardDimensions {
    int side_length;
    int dimensions;
};

class Board {
public:
    explicit Board(BoardDimensions dimensions);
    ~Board();

    CellState ***getBoard() const;
    BoardDimensions getDimensions() const;
    BoardState getState() const;

    bool makeMove(int x, int y, int z);

    virtual void showCube(Cube *cube) const = 0;
    std::string toString() const;

protected:
    virtual bool validMove(int x, int y, int z) const = 0;
    virtual bool checkVictory() = 0;

    void setDraw();
    void setWinner(const int xrange[], const int yrange[], const int zrange[]);

    CellState ***board_;
    BoardDimensions dimensions_{};

    static CRGB getCellColor(CellState cellState);

private:
    static char getCellSymbol(CellState cellState);

    CellState getNextMove() const;
    void endMove();

    BoardState state_;
};

