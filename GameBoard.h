class GameBoard{
    private:
    int* gameBoard;
    int numPockets;
    bool turnTracker;
    bool gameOngoing;

    public:
    /*numPockets: number of pockets on each side (if >6, will be set to 6)
    *numPieces: number of pieces in each pocket
    *turnStart: If true, player starts turn. If false, computer does.
    */
    GameBoard(int numPockets, int numPieces, bool turnStart);

    //returns the game board array
    int * getGameBoard();

    //returns the number of pockets on each side
    int getNumPockets();

    //returns true if the player has the current turn, false if the computer goes
    bool getCurrentTurn();

    //returns true if the game is over
    bool gameOver();

    /*checks if game is still ongoing. If it is not, handles game over phase and sets gameOngoing to false.
    *returns true if game is over, false if game is not over
    */
    bool handleEndgame();

    //returns the difference of scores (player-computer)
    int getCurrentScore();

    //checks if the spot at that index is playable by the current player
    bool spotPlayable(int pocket);

    //makes a move starting in the index provided
    void makeMove(int pocket);
};