#pragma once
#include "T_Board.h"


struct AIMove
{
    AIMove() {};
    AIMove(int t_score) : score(t_score) {};
    AIMove(int t_line, int t_column) : line(t_line), column(t_column) {};

    int line{-2};
    int column{-2};
    int score{0};
};


class T_AI
{
private:

    char humanPlayer;
    char aiPlayer;
    int depth{ 2 };

    AIMove getBestMove(T_Board& board, char player, int t_depth);
    //AIMove getBestMove (T_Board& board,int alpha,int beta, char player,int glebokosc);
public:
    T_AI();
    ~T_AI();

    char getAIPlayer() const;
    char getHumanPlayer() const;

    void setDepth(int t_depth);

    void initPlayers();
    void performMove(T_Board& board, char player);
};

