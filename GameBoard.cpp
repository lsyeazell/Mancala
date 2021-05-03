#include "GameBoard.h"

GameBoard::GameBoard(int numPockets, int numPieces, bool turnStart)
{
    GameBoard::gameBoard = new int[numPockets*2 + 2];
    GameBoard::numPockets = numPockets;
    GameBoard::turnTracker = turnStart;
    GameBoard::gameOngoing = true;
    //initializes the number of pieces in each pocket besides the ends to be numPieces
    for(int i=1;i<numPockets*2+2;i++)
    {
        GameBoard::gameBoard[i] = numPieces;
        if(i == numPockets+1)
        {
            i++;
        }
    }
}

int* GameBoard::getGameBoard()
{
    return GameBoard::gameBoard;
}

int GameBoard::getNumPockets()
{
    return GameBoard::numPockets;
}

bool GameBoard::getCurrentTurn()
{
    return GameBoard::turnTracker;
}

bool GameBoard::gameOver()
{
    return GameBoard::gameOngoing;
}

int GameBoard::getCurrentScore()
{
    return GameBoard::gameBoard[0] - GameBoard::gameBoard[numPockets + 1];
}

bool GameBoard::spotPlayable(int pocket)
{
    if(pocket == 0 || pocket==numPockets+1 || GameBoard::gameBoard[pocket]==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}