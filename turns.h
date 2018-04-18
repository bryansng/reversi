void manageTurns(Disk board[][BOARD_SIZE], Player *p1, Player *p2);

void manageMoves(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent);

void getCoords(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, listNodePtr *sPtr);

void printCoords(listNodePtr currentPtr, int *max);

void askChooseCoord(Player pCurrent, int max, int *choice);

void getChosenCoord(listNodePtr *sPtr, int choice, int *row, int *col);

void placeDisks(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
