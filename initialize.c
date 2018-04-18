#include <stdio.h> // For printf.
#include <stdlib.h>	// For fgets.
#include <string.h>	// For removing newline characters with strlen.

#include "initialize.h"

// Le Function Definitions.
void removeNewline(char a[]);

// A.1 Start conditions.

/* Function asks user for input and inputs players' name into the struct variable and takes in,
 * - *p1: Pointer to the struct player 1, to modify name in-place.
 * - *p2: Pointer to the struct player 2, to modify name in-place.
 */
void initializePlayers(Player *p1, Player *p2)
{
	// player 1.
	printf("Please enter player 1's name (representing black disk): ");
	fgets(p1->name, STR_SIZE, stdin); // prompts for name.
	p1->type = BLACK; // player 1 plays with black disks.
	p1->disks = 2; // each player starts with 2 disks on board.
	
	// player 2.
	printf("Please enter player 2's name (representing white disk): ");
	fgets(p2->name, STR_SIZE, stdin); // prompts for name.
	p2->type = WHITE; // player 2 plays with black disks.
	p2->disks = 2; // each player starts with 2 disks on board.
	
	// removes newline characters for player names due to fgets.
	removeNewline(p1->name);
	removeNewline(p2->name);
}


/* Function removes newline at the end of a string in a 1D character array and takes in,
 * - a[]: a 1D character array.
 */
void removeNewline(char a[])
{
	int len = strlen(a)-1;	// gets the string length-1.
	
	// if the 2nd last character is a newline, replace it with the null character.
	if (a[len] == '\n')
		a[len] = '\0';
}


/* Function initializes disks positions on board to start conditions and takes in,
 * - Disk board[][]: 2D array representing row and col of board.
 */
void initializeBoard(Disk board[][BOARD_SIZE])
{
	for (unsigned int r = 0; r < BOARD_SIZE; r++)
		for (unsigned int c = 0; c < BOARD_SIZE; c++)
		{
			switch (r)
			{
				case 3:
					switch (c)
					{
						case 3:
							board[r][c].type = WHITE;
							break;
						case 4:
							board[r][c].type = BLACK;
							break;
						default: // rest of the columns in row 3.
							board[r][c].type = NONE;
					}
					break;
				case 4:
					switch (c)
					{
						case 3:
							board[r][c].type = BLACK;
							break;
						case 4:
							board[r][c].type = WHITE;
							break;
						default: // rest of the columns in row 4.
							board[r][c].type = NONE;
					}
					break;
				default: // all other rows and their columns.
					board[r][c].type = NONE;
			}
			board[r][c].pos.row = r;
			board[r][c].pos.col = c;
		}
}


/* Function outputs the board that represents the current turn and takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * Note: This function is used in each turn, including the final turn.
 */
void printBoard(Disk board[][BOARD_SIZE])
{
	// gives a cleaner and spacious look in the console.
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	
	// column header at the top.
	printf("\n    "); // 4 spaces.
	for (int c = 1; c <= BOARD_SIZE; c++)
		printf("%c   ", c-1+'a');
		
	// rows header + data.
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		// left row header.
		printf("\n%d |", r+1);
		
		// row data.
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (board[r][c].type == BLACK)
				printf(" 1 |");
			else if (board[r][c].type == WHITE)
				printf(" 0 |");
			else if (board[r][c].type != BLACK && board[r][c].type != WHITE)
				printf("   |");
		}
		
		// right row header.
		printf(" %d", r+1);
	}
	
	// column footer.
	printf("\n    "); // 4 spaces.
	for (int c = 1; c <= BOARD_SIZE; c++)
		printf("%c   ", c-1+'a');
}
