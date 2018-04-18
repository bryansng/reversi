void manageMoves(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness);

void getCoords(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, listNodePtr *sPtr);

void printCoords(listNodePtr currentPtr, int *max);

void askChooseCoord(Player pMove, int max, int *choice);

void getChosenCoord(listNodePtr *sPtr, int choice, int *row, int *col);

int isEmpty(listNodePtr sPtr);

void dequeue(listNodePtr *sPtr);

void placeDisks(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);

void manageTurns(Disk board[][BOARD_SIZE], Player *p1, Player *p2);
