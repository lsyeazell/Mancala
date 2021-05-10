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
        if(i == numPockets+1)
        {
            i++;
        }
        GameBoard::gameBoard[i] = numPieces;

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
    if((GameBoard::turnTracker && pocket > 0 && pocket <= GameBoard::numPockets) || (!(GameBoard::turnTracker) && pocket > (GameBoard::numPockets+1) && pocket <= (GameBoard::numPockets*2+1)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameBoard::handleEndgame()
{
    int side1;
    int side2;
    for(int i = 1; i<=GameBoard::numPockets; i++)
    {
        side1 += GameBoard::gameBoard[i];
    }
    for(int i = GameBoard::numPockets+2; i<=2*GameBoard::numPockets+1; i++)
    {
        side2 += GameBoard::gameBoard[i];
    }
    if(side1 == 0)
    {
        for(int i = GameBoard::numPockets+2; i<=2*GameBoard::numPockets+1; i++)
        {
            GameBoard::gameBoard[i]=0;
        }
        GameBoard::gameBoard[GameBoard::numPockets + 1] += side2;
        GameBoard::gameOngoing = false;
    }
    else if(side2 == 0)
    {
        for(int i = 1; i<=GameBoard::numPockets+1; i++)
        {
            GameBoard::gameBoard[i]=0;
        }
        GameBoard::gameBoard[0] += side1;
        GameBoard::gameOngoing = false;
    }
}

void GameBoard::makeMove(int pocket)
{
    if(!(GameBoard::spotPlayable(pocket)))
    {
        throw "Move Invalid";
    }
    else
    {
        int pieces = GameBoard::gameBoard[pocket];
        int ending = (pocket-pieces)%(2*GameBoard::numPockets+2);
        for(int i=i;i<=pieces;i++)
        {
            if(((pocket-i)%(2*GameBoard::numPockets+2) == 0 && !GameBoard::turnTracker) || ((pocket-i)%(2*GameBoard::numPockets+2) == (GameBoard::numPockets + 1) && GameBoard::turnTracker))
            {
                ending = (ending-1)%(2*GameBoard::numPockets+2);
                GameBoard::gameBoard[ending]++;
            }
            else
            {
                GameBoard::gameBoard[(pocket-i)%(2*GameBoard::numPockets+2)]++;
            }
            //still needing to be implemented: capturing, not placing anything in opponent's score pocket
        }
        if(GameBoard::gameBoard[ending] == 1 && GameBoard::gameBoard[2*GameBoard::numPockets + 2-ending] != 0)
        {
            int captured = GameBoard::gameBoard[2*GameBoard::numPockets + 2-ending];
            GameBoard::gameBoard[2*GameBoard::numPockets + 2-ending] = 0;
            if(GameBoard::turnTracker)
            {
                GameBoard::gameBoard[0] += captured;
            }
            else
            {
                GameBoard::gameBoard[2*GameBoard::numPockets + 1] += captured;
            }
        }
        GameBoard::handleEndgame();
        //swaps whose turn it is as long as it does not end in a scoring pocket
        if(ending != 0 && ending != GameBoard::numPockets + 1)
        {
            GameBoard::turnTracker = !(GameBoard::turnTracker);
        }
    }
}