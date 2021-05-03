#include "GameBoard.h"

class MovePicker{
    private:
        GameBoard * myGame;
        int bestSpot;
        int likelyOutcome;
    public:
        MovePicker(GameBoard * newGame);
        int miniMax(int alpha, int beta);
        int chooseMove();
        int getLikelyOutcome();

};