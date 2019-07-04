//
// Created by christopher on 4/07/19.
//

#pragma once

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

class Board {
public:
    explicit Board(int size);
    ~Board();

    CellState **getBoard() const;
    int getSize() const;
    BoardState getState() const;

    bool makeMove(int x, int y);

private:
    bool validMove(int x, int y) const;
    CellState getNextMove() const;
    void endMove();
    bool checkVictory();
    void setWinner(const int xrange[], const int yrange[]);
    void setDraw();

    int size_;
    CellState **board_;
    BoardState state_;
};

