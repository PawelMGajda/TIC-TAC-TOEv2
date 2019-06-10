#pragma once
#include <iostream>
#include <assert.h>


class T_Board
{
private:
    int BoardSize{ 0 }; // Board size in square n x n
    int SignNumberInRow{ 0 }; // How many the same signs in a row to win
    int MaxMovesNumber{ 0 }; // Max number of moves on the board
    int CurrentMovesNumber{ 0 }; // Current, real number of done moves

    int LastInsertLine{ 0 };
    int LastInsertColumn{ 0 };
    char LastMovePlayer{'X'};

    char** BoardArray;

public:
    T_Board(int t_boardSize, int t_signNumberInRow);
    ~T_Board();

    void ClearBoardArray();

    void InsertSign(int t_ln, int t_col, char value);

    int getSize() const;
    char getValue(int line, int column) const;

    char IsWin() const;
    char IsDraw() const;
    char IsGameOver() const;

    void ShowBoard() const;
    void ShowBoardStats() const;
};

