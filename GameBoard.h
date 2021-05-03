class Board{
    private:
    int gameBoard[];
    int numPockets;
    bool turnTracker;

    public:
    //numPockets: number of pockets on each side, numPieces: number of pieces in each pocket
    Board(int numPockets, int numPieces);
    //returns the game board array
    int[] getGameBoard();
    //returns the number of pockets on each side
    int getNumPockets();
    //returns true if the player has the current turn, false if the computer goes
    bool getCurrentTurn();
    //returns true if the game is over
    bool gameOver();
    //returns the current score
    int getCurrentScore();
    //checks if the spot at that index is playable
    bool spotPlayable(int pocket);
    //makes a move starting in the index provided
    void makeMove(int pocket);
};