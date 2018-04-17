#define STR_SIZE 20  // Maximum length for player names.


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