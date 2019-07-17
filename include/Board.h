//
// Created by christopher on 4/07/19.
//

#pragma once

#include <Vec3.h>
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
    virtual ~Board();

    void reset();

    CellState ***getBoard() const;
    BoardDimensions getDimensions() const;
    BoardState getState() const;

    bool makeMove(Vec3 pos);

    virtual void showCube(Cube *cube) const = 0;
    String toString() const;

protected:
    virtual bool validMove(Vec3 pos) const = 0;
    virtual bool checkVictory(Vec3 prev_move) = 0;

    CellState getPos(Vec3 pos) const;
    void setPos(Vec3 pos, CellState value);

    void setDraw();
    void setWinner(const Vec3 winning_line[]);

    CellState ***board_;
    BoardDimensions dimensions_{};

    static CRGB getCellColor(CellState cellState);

private:
    void initBoard(BoardDimensions dimensions);
    void deleteBoard();

    static char getCellSymbol(CellState cellState);

    CellState getNextMove() const;
    void endMove(Vec3 move);

    BoardState state_;
};

