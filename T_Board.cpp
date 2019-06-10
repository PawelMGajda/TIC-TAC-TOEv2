#include "T_Board.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
T_Board::T_Board(int t_boardSize, int t_signNumberInRow)
{
    std::cout << "T_Board CONSTRUCTOR " << std::endl;

    BoardSize = t_boardSize;
    SignNumberInRow = t_signNumberInRow;
    MaxMovesNumber = BoardSize * BoardSize;

    BoardArray = new char* [BoardSize];

    for (int i = 0; i < BoardSize; i++)
    {
        BoardArray[i] = new char[BoardSize];
    }
}

//---------------------------------------------------------------------------------------------------
// DESTRUCTOR
T_Board::~T_Board()
{
    std::cout << "T_Board DESTRUCTOR " << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Fill the board with '-'
void T_Board::ClearBoardArray()
{
    // std::cout << __func__ << std::endl;

    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            BoardArray[i][j] = '-';
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Show current game board:
void T_Board::ShowBoard() const
{
    // std::cout << __func__ << std::endl;

    for (int i = 0; i < BoardSize; i++)
    {
        std::cout<<"|";
        for (int j = 0; j < BoardSize; j++)
        {
            std::cout << BoardArray[i][j] << "|";
        }
        std::cout << std::endl;
    }
}

//---------------------------------------------------------------------------------------------------
// Show board stats, size, how many signs in row to win etc.
void T_Board::ShowBoardStats() const
{
    // std::cout << __func__ << std::endl;

    std::cout << std::endl <<  "========== BOARD STATS ==========" << std::endl
              << "Board size: " << BoardSize << " x " << BoardSize << std::endl
              << "Number of signs in a row to win: " << SignNumberInRow << std::endl;
}

//---------------------------------------------------------------------------------------
// Is a win after last move, if X won, return X, if O return O, if no win return 'N'
char T_Board::IsWin() const
{
    // std::cout << __func__ << std::endl;

    int t_lastIndexCol = LastInsertColumn;
    int t_lastIndexLn = LastInsertLine;
    char t_player = LastMovePlayer;

    // std::cout << "last line: " << t_lastIndexLn << std::endl
    //	<< "last column: " << t_lastIndexCol << std::endl
    //	<< "Last player: " << t_player << std::endl;

    // COUNTERS:
    int horizontalCounter{ 1 };
    int verticalCounter{ 1 };
    int lrDiagonalCounter{ 1 };
    int rlDiagonalCounter{ 1 };

    // HORIZONTAL:
    // To right
    for (int i = t_lastIndexCol + 1; i < BoardSize && BoardArray[t_lastIndexLn][i] == t_player; i++)
        horizontalCounter++;

    // To left
    for (int i = t_lastIndexCol - 1; i >= 0 && BoardArray[t_lastIndexLn][i] == t_player; i--)
        horizontalCounter++;

    // VERTICAL:
    // To up
    for (int i = t_lastIndexLn - 1; i >= 0 && BoardArray[i][t_lastIndexCol] == t_player; i--)
        verticalCounter++;

    // To down
    for (int i = t_lastIndexLn + 1; i < BoardSize && BoardArray[i][t_lastIndexCol] == t_player; i++)
        verticalCounter++;

    // LEFT TO RIGHT DIAGONAL
    // To up
    for (int l = t_lastIndexLn - 1, c = t_lastIndexCol + 1; l >= 0 && c < BoardSize
                                                            && BoardArray[l][c] == t_player; l--, c++)
    {
        lrDiagonalCounter++;
    }

    // To down
    for (int l = t_lastIndexLn + 1, c = t_lastIndexCol - 1; l < BoardSize && c >= 0
                                                            && BoardArray[l][c] == t_player; l++, c--)
    {
        lrDiagonalCounter++;
    }

    // RIGHT TO LEFT DIAGONAL
    // To up
    for (int l = t_lastIndexLn - 1, c = t_lastIndexCol - 1; l >= 0 && c >= 0
                                                            && BoardArray[l][c] == t_player; l--, c--)
    {
        rlDiagonalCounter++;
    }

    // To down
    for (int l = t_lastIndexLn + 1, c = t_lastIndexCol + 1; l < BoardSize && c < BoardSize
                                                            && BoardArray[l][c] == t_player; l++, c++)
    {
        rlDiagonalCounter++;
    }


    if (horizontalCounter >= SignNumberInRow || verticalCounter >= SignNumberInRow
        || lrDiagonalCounter >= SignNumberInRow || rlDiagonalCounter >= SignNumberInRow)
    {
        // std::cout << t_player << "win! " << std::endl;
        return t_player; // It's win of player O or X
    }
    else
    {
        // std::cout << t_player << "No win! " << std::endl;
        return 'N'; // It's no win
    }
}

//---------------------------------------------------------------------------------------------------
// Check is the array full and no win -> draw
char T_Board::IsDraw() const
{
    if (CurrentMovesNumber >= MaxMovesNumber) // If it's draw
        return 'D'; // It's draw
    else
        return 'N'; // It's No draw
}

//--------------------------------------------------------------------------------------
// Using IsDraw and IsWin functions
char T_Board::IsGameOver() const
{
    // It's win of X or O:
    char win = IsWin();
    char draw = IsDraw();

    // std::cout << "IsWin returns: " << win << std::endl;
    // std::cout << "IsDraw returns: " << draw << std::endl;

    if (win == 'X' || win == 'O') // One of players wins
    {
        // std::cout << "***** Player " << win << " wins ***** " << std::endl;
        return win;
    }
    else if (draw == 'D') // If draw
    {
        // std::cout << "***** Draw ***** " << std::endl;
        return draw;
    }
    else // No win and no draw win = draw
    {
        return 'N'; // Always 'N', draw is also 'N'
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Insert the sign in of the free fields in Game array. If the field is
// free, insert symbol and return 1 if not return 0 if it's win return 2
// FOR TESTS
void T_Board::InsertSign(int t_ln, int t_col, char t_player)
{
    // std::cout << __func__ << std::endl;

    // std::cout << "Insert line: " << t_ln << std::endl;
    // std::cout << "Insert column: " << t_col << std::endl;

    assert(t_ln >= 0 && t_col >= 0 && t_ln < BoardSize && t_col < BoardSize);
    assert(t_player == 'X' || t_player == 'O' || t_player == '-');

    BoardArray[t_ln][t_col] = t_player;

    if (t_player == 'X' || t_player == 'O')
    {
        CurrentMovesNumber++;

        LastInsertLine = t_ln;
        LastInsertColumn = t_col;
        LastMovePlayer = t_player;
    }
    else
    {
        CurrentMovesNumber--;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
// Get board size:
int T_Board::getSize() const
{
    return BoardSize;
}

//---------------------------------------------------------------------------------------
// Get value of this field
char T_Board::getValue(int line, int column) const
{
    return BoardArray[line][column];
}

//---------------------------------------------------------------------------------------



