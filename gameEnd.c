#include <stdio.h>

#include "playerInfo.h"
#include "gameEnd.h"

// Le Function Definitions.

/* Function that determines win/draw/lose conditions and updates player info accordingly; it takes in,
 * - Player p1: player 1 info.
 * - Player p2: player 2 info.
 */
void manageEnding(Player p1, Player p2)
{
	if (p1.disks > p2.disks) // p1 win.
		printf("\n%s wins!\n", p1.name);
	else if (p2.disks > p1.disks) // p2 win.
		printf("\n%s wins!\n", p2.name);
	else // draw.
		printf("\nDraw! Good game %s and %s!\n", p1.name, p2.name);
}


// A.3 Printing the final result

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


/* Function outputs the board that represents the current turn and takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - turns: number of turns played
 * - Player p1: player 1 info
 * - Player p2: player 2 info
 * This function is only called once at the end of game.
 */
void outputResult(Disk board[][BOARD_SIZE], int turns, Player p1, Player p2)
{
	FILE *resultPtr;
	
	if ((resultPtr = fopen("reversi_result.txt", "w+")) == NULL)
		printf("Error: Could not output final result to reversi_result.txt\n\n");
	
	else 
	{
		fprintf(resultPtr, "COMP10050 Assignment 3: Othello/Reversi Game\n"
                "\tPlayer 1: Sng Hong Yao 17205050 \n"		
                "\tPlayer 2: Liew Xuan 17200573 \n\n");
		
		fprintf(resultPtr, "Game files compiled at %s %s.\n\n" "Result: \n", __DATE__, __TIME__);
		
		// column header at the top.
		fprintf(resultPtr, "\n    "); // 4 spaces.
		for (int c = 1; c <= BOARD_SIZE; c++)
			fprintf(resultPtr, "%c   ", c-1+'a');
			
		// rows header + data.
		for (int r = 0; r < BOARD_SIZE; r++)
		{
			// left row header.
			fprintf(resultPtr, "\n%d |", r+1);
			
			// row data.
			for (int c = 0; c < BOARD_SIZE; c++)
			{
				if (board[r][c].type == BLACK)
					fprintf(resultPtr, " 1 |");
				else if (board[r][c].type == WHITE)
					fprintf(resultPtr, " 0 |");
				else if (board[r][c].type != BLACK && board[r][c].type != WHITE)
					fprintf(resultPtr, "   |");
			}
			
			// right row header.
			fprintf(resultPtr, " %d", r+1);
		}
		
		// column footer.
		fprintf(resultPtr, "\n    "); // 4 spaces.
		for (int c = 1; c <= BOARD_SIZE; c++)
			fprintf(resultPtr, "%c   ", c-1+'a');
		
		fprintf(resultPtr, "\n\nTotal number of turns: %d\n", turns);
		fprintf(resultPtr, "Player 1 \"%s\" has %d points.\n", p1.name, p1.disks);
		fprintf(resultPtr, "Player 2 \"%s\" has %d points.\n\n", p2.name, p2.disks);
		
		if (p1.disks > p2.disks)
			fprintf(resultPtr, "%s WINS! \n\n", p1.name);
		else if (p1.disks < p2.disks)
			fprintf(resultPtr, "%s WINS! \n\n", p2.name);
		else
			fprintf(resultPtr, "%s and %s DRAWED! \n\n", p1.name, p2.name);
		
		fprintf(resultPtr, "Good game!\n\n");	
		
		printf("\nGood game! Final result is stored in reversi_result.txt\n\n");
	}
}