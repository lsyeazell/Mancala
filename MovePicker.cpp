#include <iostream>
#include "MovePicker.h"
#include "GameBoard.h"
#include "heaps/MaxHeap.h"
#include "heaps/MinHeap.h"
#include <limits>
using namespace std;

MovePicker::MovePicker(GameBoard * newGame){
    myGame = newGame;
}


int MovePicker::miniMax(int alpha, int beta){
    //base case
    if (myGame->gameOver()){
        // returns score difference, player-computer
        return myGame->getCurrentScore();
    }

    // recursive case
    if(myGame->getCurrentTurn()){
        // player (maximizer's) turn

        //create max heap for finding max val later
        MaxHeap * possibleMoves = new MaxHeap();

        //loop through possible moves
        for(int i=0;i<myGame->getNumPockets();i++){
            if(myGame->spotPlayable(i)){

                //makes moves and backtracks to find optimum move
                myGame->makeMove(i);
                int score = miniMax(alpha, beta);
                myGame->undoMove();
                possibleMoves->insert(score);

                //alpha beta pruning
                if(score>alpha){
                    alpha = score;
                }
                if(score>=beta){
                    return possibleMoves->max();
                }
            }
        }
        //returns best move for player
        return possibleMoves->max();
    }else{
        // computer (minimizer's) turn

        //create min heap for finding min val later
        MinHeap * possibleMoves = new MinHeap();

        //loop through possible moves
        for(int i=0;i<myGame->getNumPockets();i++){
            if(myGame->spotPlayable(i)){

                //makes moves and backtracks to find optimum move
                myGame->makeMove(i);
                int score = miniMax(alpha, beta);
                myGame->undoMove();
                possibleMoves->insert(score);

                //alpha beta pruning
                if(score<beta){
                    beta= score;
                }
                if(score<=alpha){
                    return possibleMoves->min();
                }
            }
        }
        //returns best move for computer
        return possibleMoves->min();
    }
}

//chooses move for computer
int MovePicker::chooseMove(){
    //likely outcome tracks what predicted score will be
    likelyOutcome = numeric_limits<int>::max();

    //tests each move using miniMax
    for(int i=0; i<myGame->getNumPockets(); i++){
        if(myGame->spotPlayable(i)){
            int alpha = numeric_limits<int>::min();
            int beta = numeric_limits<int>::max();
            myGame->makeMove(i);
            int score = miniMax(alpha, beta);
            myGame->undoMove();

            //set likelyOutcome and bestSpot to optimal move for computer
            if (score<likelyOutcome){
                likelyOutcome = score;
                bestSpot = i;
            }
        }
    }
    //returns computer's move
    return bestSpot;
}

//returns what the predicted outcome is based on the miniMax
int MovePicker::getLikelyOutcome(){
    return likelyOutcome;
}