#include "T_TicTacToe.h"


////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
T_TicTacToe::T_TicTacToe()
{
    std::cout << "T_TicTacToe CONSTRUCTOR " << std::endl;
}

//----------------------------------------------------------------------
//DESTRUCTOR
T_TicTacToe::~T_TicTacToe()
{
    std::cout << "T_TicTacToe DESTRUCTOR " << std::endl;
}

//----------------------------------------------------------------------
// Game start menu: pvp, pve, exit
int T_TicTacToe::GameStartMenu() const
{
    int i{};

    std::cout << "TIC TAC TOE" << std::endl
              << "---------- MAIN MENU ----------" << std::endl
              << "1. PvP " << std::endl
              << "2. PvE " << std::endl
              << "3. Exit " << std::endl;

    std::cin >> i;

    return i;
}

////////////////////////////////////////////////////////////////////////
// Switching actual player to the other
void T_TicTacToe::SwitchPlayer()
{
    std::cout << __func__ << std::endl;

    assert(CurrentPlayer == 'X' || CurrentPlayer == 'O');

    if (CurrentPlayer == 'X')
        CurrentPlayer = 'O';
    else
        CurrentPlayer = 'X';
}

////////////////////////////////////////////////////////////////////////
// Switch pve player AI -> Human...
void T_TicTacToe::SwitchPVEPlayer()
{
    assert(CurrentPVEPlayer == 'A' || CurrentPVEPlayer == 'H');

    if (CurrentPVEPlayer == 'H')
        CurrentPVEPlayer = 'A';
    else
        CurrentPVEPlayer = 'H';
}

//----------------------------------------------------------------------
// If human is X it starts if not AI starts
void T_TicTacToe::SetCurrentPVEPlayer(char t_humanPlayer)
{

    if (t_humanPlayer == 'X')
        CurrentPVEPlayer = 'H';
    else
        CurrentPVEPlayer = 'A';
}

//----------------------------------------------------------------------
// Curent PVE player - human/AI
char T_TicTacToe::getCurrentPVEPlayer()
{
    return CurrentPVEPlayer;
}

////////////////////////////////////////////////////////////////////////
// Get current player
char T_TicTacToe::getPlayerType() const
{
    return CurrentPlayer;
}

////////////////////////////////////////////////////////////////////////
//
void T_TicTacToe::showTheEndResult(char t_endResult) const
{
    assert(t_endResult == 'X' || t_endResult == 'O' || t_endResult == 'D');

    if (t_endResult == 'X' || t_endResult == 'O')
        std::cout << "********** Player " << t_endResult << " wins! ********** " << std::endl;
    else if (t_endResult == 'D')
        std::cout << " Draw! " << std::endl;
}


////////////////////////////////////////////////////////////////////////
// Execute AI move
void T_TicTacToe::AiMove(T_Board& board, char player, T_AI t_ai)
{
    // std::cout << "It's AI move <------ " << std::endl;
    t_ai.performMove(board, player);
}

//----------------------------------------------------------------------
// Player move with cin's
void T_TicTacToe::PlayerMove(T_Board& board, char player)
{
    int line{-1};
    int column{-1};

    assert(player == 'X' || player == 'O');

    std::cout << "You're " << player << " player" << std::endl;

    bool goodField = false;
    while(goodField == false)
    {
        std::cout << "Line: ";
        std::cin >> line;
        std::cout << "Column: ";
        std::cin >> column;

        if (line >= 0 && line < board.getSize() && column >= 0 && column < board.getSize()
            && board.getValue(line, column) == '-')
        {
            goodField = true;
        }
        else
        {
            std::cout << "Wrong co-ordinates, try again: " << std::endl;
            goodField = false;
        }
    }

    board.InsertSign(line, column, player);
}

////////////////////////////////////////////////////////////////////////
// Start TicTacToe game
void T_TicTacToe::StartGame()
{
    int size=3;
    int win_condition=3;
    std::cout<<"SIZE:"<<std::endl;
    std::cin >> size;
    std::cout<<"WIN_CONDITION:"<<std::endl;
    std::cin >> win_condition;
    // std::cout << __func__ << std::endl;
    T_Board board(size, win_condition); // Create only space for board array(size of area, how many in a row)
    T_AI minimax;

    minimax.setDepth(size==3?10:4);

    board.ClearBoardArray();
    board.ShowBoardStats();

    char isEnd = 'N';

    switch (GameStartMenu())
    {
        case 1:
            std::cout << "Start PVP game " << std::endl;

            while (isEnd == 'N')
            {
                board.ShowBoard();

                PlayerMove(board, CurrentPlayer);
                board.ShowBoard();
                isEnd = board.IsGameOver();

                SwitchPlayer();

                if (isEnd == 'N')
                {
                    PlayerMove(board, CurrentPlayer);
                    board.ShowBoard();
                    isEnd = board.IsGameOver();

                    SwitchPlayer();
                }
            }

            break;
        case 2:
            std::cout << "Start PVE game " << std::endl;

            minimax.initPlayers();
            SetCurrentPVEPlayer(minimax.getHumanPlayer());

            board.ShowBoard();

            while (isEnd == 'N')
            {
                if (getCurrentPVEPlayer() == 'A')
                    AiMove(board, CurrentPlayer, minimax);
                else
                    PlayerMove(board, CurrentPlayer);

                board.ShowBoard();

                isEnd = board.IsGameOver();

                SwitchPVEPlayer();
                SwitchPlayer();
            }

            break;

        default:
            std::cout << "Exit game" << std::endl;

            break;
    }

    showTheEndResult(isEnd);

    system("PAUSE");
}
