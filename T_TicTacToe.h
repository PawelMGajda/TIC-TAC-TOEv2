#pragma once
#include "T_AI.h"

class T_TicTacToe
{
private:
    char CurrentPlayer = 'X'; // At the start X is always first
    char CurrentPVEPlayer = 'N'; // H or A

public:
    T_TicTacToe();
    ~T_TicTacToe();

    void AiMove(T_Board& board, char player, T_AI t_ai);
    void PlayerMove(T_Board& board, char player);

    void StartGame();
    void SwitchPlayer();
    void SwitchPVEPlayer();

    int GameStartMenu() const;
    char getPlayerType() const;

    void SetCurrentPVEPlayer(char t_humanPlayer);
    char getCurrentPVEPlayer();

    void showTheEndResult(char t_endResult) const;
};

