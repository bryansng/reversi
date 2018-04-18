#include <stdio.h>
#include <stdlib.h>	// for fgets.
#include <string.h>	// for removing newline characters with strlen.

#include "initialize.h"

// Le Function Prototypes.
void removeNewline(char a[]);


// Le Function Definitions.

/* Function asks user for input and inputs players' name into the struct variable and takes in,
* - *p1: Pointer to the struct player 1, to modify name in-place.
* - *p2: Pointer to the struct player 2, to modify name in-place.
*/
void initializePlayers(Player *p1, Player *p2)
{
	// name for player 1.
	printf("Please enter player 1's name (representing black disk): ");
	fgets(p1->name, STR_SIZE, stdin);
	p1->type = BLACK;
	p1->disks = 2;
	
	// name for player 2.
	printf("Please enter player 2's name (representing white disk): ");
	fgets(p2->name, STR_SIZE, stdin);
	p2->type = WHITE;
	p2->disks = 2;
	
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
							board[r][c].type = BLACK;
							break;
						case 4:
							board[r][c].type = WHITE;
							break;
						default: // rest of the columns in row 3.
							board[r][c].type = NONE;
					}
					break;
				case 4:
					switch (c)
					{
						case 3:
							board[r][c].type = WHITE;
							break;
						case 4:
							board[r][c].type = BLACK;
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


/* Function prints the board that represents the game and takes in,
* - d_p1: Struct of player 1.
* - d_p2: Struct of player 2.
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
		// row header on the left.
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
		
		// row header on the right.
		printf(" %d", r+1);
	}
	
	// column header at the bottom.
	printf("\n    "); // 4 spaces.
	for (int c = 1; c <= BOARD_SIZE; c++)
		printf("%c   ", c-1+'a');
}




























