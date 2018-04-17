#define BOARD_SIZE 8 // Board is 8*8.

// A.1 Start Condition.

// Le function prototypes.

void removeNewline(char a[]);                    // removes newline char from player name due to fgets.
void initializePlayers(Player *p1, Player *p2);  // initializes player name, disk colour, and disk numbers on board.
void initializeBoard(Disk board[][BOARD_SIZE]);  // initializes board to game starting conditions.