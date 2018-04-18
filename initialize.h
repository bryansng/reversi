#define STR_SIZE 20  // Maximum length for player names.
#define BOARD_SIZE 8 // board is 8*8.

// A.1 Start Condition.

enum colour {BLACK, WHITE, NONE}; // Disk colours.

// Player info.
typedef struct Player
{
	char name[STR_SIZE];    // player name.
	enum colour type;       // player's disk colour.
	int disks;              // player's current number of disks on board.
} Player;

// Disk position (mainly used in struct Disk).
typedef struct Position
{
	int row;
	int col;
} Position;

// Disk info.
typedef struct Disk
{
	enum colour type; // disk colour.
	Position pos;     // disk position.
} Disk;

// Linked List that is used to store the number of moves per turn.
struct ListNode
{
	int row;
	int col;
	struct ListNode *nextPtr; // points to next node.
};

typedef struct ListNode listNode; // listNode is a synonym for struct ListNode.
typedef listNode *listNodePtr; // listNodePtr is a synonym for pointer to a listNode.

void initializePlayers(Player *p1, Player *p2);
void initializeBoard(Disk board[][BOARD_SIZE]);
void printBoard(Disk board[][BOARD_SIZE]);
