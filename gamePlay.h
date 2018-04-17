#define BOARD_SIZE 8 // Board is 8*8.

// Le function prototypes.

// A.2 Managing turns.
int manageTurns(Disk board[][BOARD_SIZE], Player *p1, Player *p2); // deals with each turn.

void manageMoves(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent); // manages each move.

void findPossibleMoves(Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE]); // calculates possible moves each player can make by checking adversary's disks.

void showAndChooseMoves (int coords[][BOARD_SIZE], Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent); // Display possible moves current player can make, prompts their choice, then places their disks appropriately.

int printCoords (int coords[][BOARD_SIZE], Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent); // Display possible moves current player can make.

int promptUserCoord (int coords[][BOARD_SIZE], Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int max); // Prompts their choice.

void placeDiskAtCoord (int coords[][BOARD_SIZE], Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int choice); // Places user disks appropriately.

void updateBoardAndScore(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col); // replaces adversary's disks after each move by checking current player's disk.
