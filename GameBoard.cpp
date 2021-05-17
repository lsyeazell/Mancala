#include <iostream>
#include "GameBoard.h"

GameBoard::GameBoard(int numPockets, int numPieces, bool turnStart)
{
    GameBoard::boardSize = numPockets*2 + 2;
    GameBoard::player2Bank = numPockets+1;
    GameBoard::gameBoard = new int[numPockets*2 + 2];
    GameBoard::numPockets = numPockets;
    GameBoard::turnTracker = turnStart;
    GameBoard::gameOngoing = true;
    //initializes the number of pieces in each pocket besides the ends to be numPieces
    for(int i=1;i<GameBoard::boardSize;i++)
    {
        if(i == player2Bank)
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

Node * GameBoard::getTopNode()
{
    return GameBoard::topNode;
}

bool GameBoard::gameOver()
{
    return GameBoard::gameOngoing;
}

int GameBoard::getCurrentScore()
{
    return GameBoard::gameBoard[0] - GameBoard::gameBoard[player2Bank];
}

bool GameBoard::spotPlayable(int pocket)
{
    if((GameBoard::turnTracker && pocket > 0 && pocket < GameBoard::player2Bank) || (!(GameBoard::turnTracker) && pocket > (GameBoard::player2Bank) && pocket < (GameBoard::boardSize)))
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
    GameBoard::holderGameBoard = new int[numPockets*2 + 2];
    for(int i = 0; i < GameBoard::boardSize; i++)
    {
        holderGameBoard[i] = gameBoard[i];
    }
    int side1;
    int side2;
    //checks if sides are empty
    for(int i = 1; i<GameBoard::player2Bank; i++)
    {
        side1 += GameBoard::gameBoard[i];
    }
    for(int i = (GameBoard::player2Bank + 1); i<GameBoard::boardSize; i++)
    {
        side2 += GameBoard::gameBoard[i];
    }
    //if a side is empty, adds all contents on other side to other's bank side, sets game to over
    if(side1 == 0)
    {
        for(int i = (GameBoard::player2Bank + 1); i<GameBoard::boardSize; i++)
        {
            GameBoard::gameBoard[i]=0;
        }
        GameBoard::gameBoard[GameBoard::player2Bank] += side2;
        GameBoard::gameOngoing = false;
    }
    else if(side2 == 0)
    {
        for(int i = 1; i<GameBoard::player2Bank; i++)
        {
            GameBoard::gameBoard[i]=0;
        }
        GameBoard::gameBoard[0] += side1;
        GameBoard::gameOngoing = false;
    }
    return GameBoard::gameOngoing;
}

void GameBoard::makeMove(int pocket)
{
    if(!(GameBoard::spotPlayable(pocket)))
    {
        throw "Move Invalid";
    }
    else
    {
        Node * currentMove = new Node();
        currentMove->prevNode = topNode;
        currentMove->moveIndex = pocket;
        int pieces = GameBoard::gameBoard[pocket];
        GameBoard::gameBoard[pocket] = 0;
        int ending = (pocket-pieces)%(GameBoard::boardSize);
        //Adding pieces in the circle
        for(int i=1;i<=pieces;i++)
        {
            int changedIndex = (pocket-i)%(GameBoard::boardSize);
            if((changedIndex == 0 && !GameBoard::turnTracker) || (changedIndex == (GameBoard::player2Bank) && GameBoard::turnTracker))
            {
                ending = (ending-1)%(GameBoard::boardSize);
                GameBoard::gameBoard[ending]++;
            }
            else
            {
                GameBoard::gameBoard[changedIndex]++;
            }
        }
        currentMove->endingIndex = ending;
        currentMove->piecesCaptured = 0;
        //Implements capturing
        if(GameBoard::gameBoard[ending] == 1 && GameBoard::gameBoard[GameBoard::boardSize-ending] != 0 && GameBoard::spotPlayable(ending))
        {
            int captured = GameBoard::gameBoard[GameBoard::boardSize-ending];
            currentMove->piecesCaptured = captured;
            GameBoard::gameBoard[GameBoard::boardSize-ending] = 0;
            GameBoard::gameBoard[ending] = 0;
            if(GameBoard::turnTracker)
            {
                GameBoard::gameBoard[0] += captured + 1;
            }
            else
            {
                GameBoard::gameBoard[GameBoard::player2Bank] += captured + 1;
            }
        }
        topNode = currentMove;
        GameBoard::handleEndgame();
        //swaps whose turn it is as long as it does not end in a scoring pocket
        if(ending != 0 && ending != GameBoard::player2Bank)
        {
            GameBoard::turnTracker = !(GameBoard::turnTracker);
        }
    }
}

void GameBoard::undoMove()
{
    if(topNode->endingIndex != 0 && topNode->endingIndex != GameBoard::player2Bank)
    {
        GameBoard::turnTracker = !(GameBoard::turnTracker);
    }
    if(!GameBoard::gameOngoing)
    {
        GameBoard::gameBoard = GameBoard::holderGameBoard;
    }
    if(topNode->piecesCaptured > 0)
    {
        if(GameBoard::turnTracker)
        {
            GameBoard::gameBoard[0] -= (topNode->piecesCaptured + 1);
        }
       else
        {
            GameBoard::gameBoard[GameBoard::player2Bank] -= (topNode->piecesCaptured + 1);
        }
        GameBoard::gameBoard[topNode->endingIndex]++;
        GameBoard::gameBoard[GameBoard::boardSize - topNode->endingIndex] += topNode->piecesCaptured;
    }
    int ending = (topNode->moveIndex - topNode->numPiecesMoved)%(GameBoard::boardSize);
    for(int i = 1; i<=topNode->numPiecesMoved;i++)
    {
        int changedIndex = (topNode->moveIndex-i)%(GameBoard::boardSize);
        if((changedIndex == 0 && !GameBoard::turnTracker) || (changedIndex == (GameBoard::player2Bank) && GameBoard::turnTracker))
        {
            ending = (ending-1)%(GameBoard::boardSize);
            GameBoard::gameBoard[ending]--;
        }
        else
        {
            GameBoard::gameBoard[changedIndex]--;
        }
    }
    GameBoard::gameBoard[topNode->moveIndex] += topNode -> numPiecesMoved;
    Node * copy = topNode;
    topNode = topNode->prevNode;
    delete copy;
}

void GameBoard::printMoves(Node * currentNode)
{
    if(currentNode->prevNode != nullptr)
    {
        GameBoard::printMoves(currentNode->prevNode);
    }
    int playerNumber;
    if(currentNode->moveIndex < GameBoard::player2Bank)
    {
        playerNumber = 1;
    }
    else
    {
        playerNumber = 2;
    }
    std::cout << "Player: " << playerNumber << " Space: " << currentNode->moveIndex << '\n';
}

void GameBoard::printCurrentBoard()
{
    for(int i = GameBoard::player2Bank + 1; i<GameBoard::boardSize; i++)
    {
        std::cout << GameBoard::gameBoard[i] << '\t';
    }
    std::cout << '\n' << GameBoard::gameBoard[player2Bank];
    for(int i = GameBoard::player2Bank + 1; i<GameBoard::boardSize; i++)
    {
        std::cout << " \t";
    }
    std::cout << '\n';
    for(int i = 0; i<GameBoard::player2Bank;i++)
    {
        std::cout << GameBoard::gameBoard[i] << '\t';
    }
}