#define BOARD_SIZE 8 // Board is 8*8.

// Aid findPossibleMoves to look in certain cardinal directions.

void findPossibleMovesNW (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]);

void findPossibleMovesN (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]);

void findPossibleMovesNE (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]);

void findPossibleMovesW (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]);

void findPossibleMovesE (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]);

void findPossibleMovesSW (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]);

void findPossibleMovesS (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]);

void findPossibleMovesSE (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]);

// Aid replaceOpponentDisks to look in certain cardinal directions.

void updateBoardAndScoreNW (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
 
void updateBoardAndScoreN (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
 
void updateBoardAndScoreNE (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
 
void updateBoardAndScoreW (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
 
void updateBoardAndScoreE (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
 
void updateBoardAndScoreSW (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
 
void updateBoardAndScoreS (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
 
void updateBoardAndScoreSE (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);

