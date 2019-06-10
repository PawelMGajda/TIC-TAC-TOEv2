#include "T_AI.h"
#include <vector>


// CONSTRUCTOR
T_AI::T_AI()
{

}

//--------------------------------------------------------------------------------------
// DESTRUCTOR
T_AI::~T_AI()
{

}

////////////////////////////////////////////////////////////////////////////////////////
// Initialize players, pick the aiPlayer
void T_AI::initPlayers()
{
	int option;

	std::cout << "Pick your player: " << std::endl
		<< "1. X " << std::endl
		<< "2. O " << std::endl;

	std::cin >> option;

	if (option == 1)
	{
		humanPlayer = 'X';
		aiPlayer = 'O';
	}
	else
	{
		humanPlayer = 'O';
		aiPlayer = 'X';
	}
}

//--------------------------------------------------------------------------------------
char T_AI::getAIPlayer() const
{
	return aiPlayer;
}

//--------------------------------------------------------------------------------------
char T_AI::getHumanPlayer() const
{
	return humanPlayer;
}

////////////////////////////////////////////////////////////////////////////////////////
void T_AI::setDepth(int t_depth)
{
	depth = t_depth;
}

////////////////////////////////////////////////////////////////////////////////////////
// Get the best possible move for this player
AIMove T_AI::getBestMove(T_Board& board, char player, int t_depth) //MINIMAX
{
	// std::cout << __func__ << std::endl;

	// Recursion depth

	// std::cout << "Depth = " << t_depth << std::endl;
	if (t_depth == 0)
	{
		return AIMove(0);
	}

	// Base case
	char rv = board.IsGameOver(); // X/Y - x/y wins, D - draw, N - No draw/no win

	if (rv == aiPlayer)
	{
		return AIMove(10); // AIMove(score)
	}
	else if(rv == humanPlayer)
	{
		return AIMove(-10);
	}
	else if(rv == 'D')
	{
		return AIMove(0);
}

	// Recursive case
	std::vector<AIMove> moves;

	for (int iLn = 0; iLn < board.getSize(); iLn++)
	{
		for (int jCol = 0; jCol < board.getSize(); jCol++)
		{
			if (board.getValue(iLn, jCol) == '-')
			{
				AIMove move;

				move.line = iLn;
				move.column = jCol;

				board.InsertSign(iLn, jCol, player);


				if (player == aiPlayer) // If AI -> human //REKURENCJA
				{
					move.score = getBestMove(board, humanPlayer, t_depth - 1).score;
				}
				else // if human -> AI
				{
					move.score = getBestMove(board, aiPlayer, t_depth - 1).score;
				}


				moves.push_back(move);
				board.InsertSign(iLn, jCol, '-');
			}
		}
	}

	int bestMove = 0;
	if (player == aiPlayer)
	{
		int bestScore = -100000000;
		for (int i = 0; i < moves.size(); i++)
		{
			if (moves[i].score > bestScore)
			{
				bestMove = i;
				bestScore = moves[i].score;

			}
		}
	}
	else
	{
		int bestScore = 100000000;
		for (int i = 0; i < moves.size(); i++)
		{
			if (moves[i].score < bestScore)
			{
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	return moves[bestMove];
}

////////////////////////////////////////////////////////////////////////////////////////
// Make this move
void T_AI::performMove(T_Board& t_board, char player)
{
	// std::cout << __func__ << std::endl;

	AIMove bestMove = getBestMove(t_board, aiPlayer, depth);

	t_board.InsertSign(bestMove.line, bestMove.column, aiPlayer);
}



/*
AIMove T_AI::getBestMove(T_Board& board,int alpha,int beta, char player,int depth){

    int bestScore;
    int iterator=0;

    char result=board.IsGameOver();
    AIMove move;
    std::vector<AIMove> moves;

    if(result=='D')
        return AIMove(0);
    else if (result == aiPlayer)
    {
        return AIMove(10); // AIMove(score)
    }
    else if(result == humanPlayer)
    {
        return AIMove(-10);
    }

    else if(player==aiPlayer)
    {
        bestScore=alpha;

        for(int i=0;i<board.getSize();i++)
        {
            for(int j=0;j<board.getSize();j++)
            {
                if(board.getValue(i,j)==humanPlayer)
                {
                    board.InsertSign(i,j,player);

                    move.score = getBestMove(board,bestScore,beta,humanPlayer,depth-1).score;
                    move.line=i;
                    move.column=j;
                    moves.push_back(move);
                    board.InsertSign(i,j,humanPlayer);

                    if(move.score>bestScore) bestScore=move.score;
                    if(beta<=bestScore) i=j=board.getSize();
                }
            }
        }

        bestScore=-10000;

        for(int i=0;i<(int)moves.size();i++)
        {
            if(moves[i].score>bestScore)
            {
                iterator=i;
                bestScore=moves[i].score;
            }
        }
    }

    else{

        bestScore=beta;

        for(int i=0;i<board.getSize();i++)
        {
            for(int j=0;j<board.getSize();j++)
            {
                if(board.getValue(i,j)==aiPlayer)
                {
                    board.InsertSign(i,j,player);
                    move.score = getBestMove(board,alpha,bestScore,aiPlayer,depth-1).score;
                    move.line=i;
                    move.column=j;
                    moves.push_back(move);
                    board.InsertSign(i,j,aiPlayer);

                    if(move.score<bestScore) bestScore=move.score;

                    if(alpha>=bestScore) i=j=board.getSize();
                }
            }
        }

        bestScore=10000;

        for(int i=0;i<(int)moves.size();i++)
        {
            if(moves[i].score<bestScore)
            {
                iterator=i;
                bestScore=moves[i].score;
            }
        }
    }
    return moves[iterator];
}



void T_AI::performMove(T_Board &board, char player) {

    AIMove Bestmove;
    Bestmove = getBestMove(board, -10000, 10000, aiPlayer, depth);

    board.InsertSign(Bestmove.line, Bestmove.column, aiPlayer);
}
*/
