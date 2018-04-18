#define STR_SIZE 20  // maximum length for player names.
#define BOARD_SIZE 8 // board is 8*8.

enum colour {BLACK, WHITE, NONE};

// create a new type struct to represent player, i.e. a type of class, for Players.
typedef struct Player
{
	char name[STR_SIZE]; // holds the name of the player.
	enum colour type;
	int disks; // current number of disk the player has on the board.
} Player;

typedef struct Position
{
	int row;
	int col;
} Position;

// create a new type struct to represent disks, i.e. a type of class, for Players.
typedef struct Disk
{
	enum colour type;
	Position pos;
} Disk;

void initializePlayers(Player *p1, Player *p2);

void initializeBoard(Disk board[][BOARD_SIZE]);

void printBoard(Disk board[][BOARD_SIZE]);

struct ListNode
{
	int row;
	int col;
	struct ListNode *nextPtr;
};

typedef struct ListNode listNode;
typedef listNode *listNodePtr;

