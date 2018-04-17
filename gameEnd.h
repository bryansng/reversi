#define BOARD_SIZE 8 // Board is 8*8.

// Le function prototypes.

void manageEnding(Player p1, Player p2); // deals with win/draw/lose conditions.

// A.3 Printing the final result. 
void printBoard(Disk board[][BOARD_SIZE]); // prints the board after each turn
void outputResult(Disk board[][BOARD_SIZE], int turns, Player p1, Player p2); // outputs the final result to a text file