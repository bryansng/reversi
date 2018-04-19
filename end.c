#include <stdio.h>

#include "initialize.h"
#include "end.h"

// Le Function Definitions.

/* Function determines win/draw/lose conditions and prints out end game results; it takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player p1: Player 1's struct.
 * - Player p2: Player 2's struct.
 */
void manageEnding(Disk board[][BOARD_SIZE], Player p1, Player p2)
{
	// print points.
	printf("\n\nPlayer 1 %s, points: %d.\n", p1.name, p1.disks);
	printf("Player 2 %s, points: %d.", p2.name, p2.disks);
	
	if (p1.disks > p2.disks) // p1 win.
		printf("\nThe winner is %s\n", p1.name);
	else if (p2.disks > p1.disks) // p2 win.
		printf("\nThe winner is %s\n", p2.name);
	else // draw.
		printf("\nDraw! Good game %s and %s!\n", p1.name, p2.name);
		
	saveToFile(board, p1, p2);
}



// A.3 Printing the final result.

/* Function outputs end game result to a txt file and takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player p1: Player 1's struct.
 * - Player p2: Player 2's struct.
 * NOTE: This function is only called once at the end of the game.
 */
void saveToFile(Disk board[][BOARD_SIZE], Player p1, Player p2)
{
	FILE *fp;
	
	if ((fp = fopen("game_results.txt", "w")) == NULL)
		printf("\n[Error] Cannot open game_results.txt.\n");
	else
	{
		printBoardToFile(board, fp);
		
		fprintf(fp, "\n\nPlayer 1 %s, points: %d.\n", p1.name, p1.disks);
		fprintf(fp, "Player 2 %s, points: %d.", p2.name, p2.disks);
		
		if (p1.disks > p2.disks) // p1 win.
			fprintf(fp, "\nThe winner is %s\n", p1.name);
		else if (p2.disks > p1.disks) // p2 win.
			fprintf(fp, "\nThe winner is %s\n", p2.name);
		else // draw.
			fprintf(fp, "\nDraw! Good game %s and %s!\n", p1.name, p2.name);
		
		fclose(fp);
	}
}



/* Function is a modified version of the printBoard function that is used to
 * print data to files. and takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - *fp: Pointer to the txt file.
 * NOTE: This function is used in each turn, including the final turn.
 */
void printBoardToFile(Disk board[][BOARD_SIZE], FILE *fp)
{
	// column header at the top.
	fprintf(fp, "    "); // 4 spaces.
	for (int c = 1; c <= BOARD_SIZE; c++)
		fprintf(fp, "%c   ", c-1+'a');
		
	// rows header + data.
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		// row header on the left.
		fprintf(fp, "\n%d |", r+1);
		
		// row data.
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (board[r][c].type == BLACK)
				fprintf(fp, " 1 |");
			else if (board[r][c].type == WHITE)
				fprintf(fp, " 0 |");
			else if (board[r][c].type != BLACK && board[r][c].type != WHITE)
				fprintf(fp, "   |");
		}
		
		// row header on the right.
		fprintf(fp, " %d", r+1);
	}
	
	// column header at the bottom.
	fprintf(fp, "\n    "); // 4 spaces.
	for (int c = 1; c <= BOARD_SIZE; c++)
		fprintf(fp, "%c   ", c-1+'a');
}
