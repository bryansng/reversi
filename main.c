/*
	COMP10050 Assignment 3: Othello/Reversi Game
	
	Player 1: Sng Hong Yao 17205050
	Player 2: Liew Xuan 17200573
*/
#include <stdio.h>
#include <stdlib.h>

#include "initialize.h"

void manageMoves(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness);
void printBoard(Disk board[][BOARD_SIZE]);
void checkAdversaryDisk(Disk board[][BOARD_SIZE], Player pMove, Player pWitness, int row, int col, int coords[][BOARD_SIZE]);
void checkOwnDisk(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);
void manageTurns(Disk board[][BOARD_SIZE], Player *p1, Player *p2);
void manageEnding(Player p1, Player p2);

int main(void)
{
	// initialize players.
	Player p1 = {"player 1", NONE, 0};
	Player p2 = {"player 2", NONE, 0};
			
	// initialize disk.
	Disk board[BOARD_SIZE][BOARD_SIZE];
	
	initializePlayers(&p1, &p2);
	
	initializeBoard(board);
	
	printBoard(board);

    //invoke a method that implements the game logic
    manageTurns(board, &p1, &p2);

    //invoke a method that prints the final result
	// when game ends i.e. no board space left.
	manageEnding(p1, p2);
}

void manageTurns(Disk board[][BOARD_SIZE], Player *p1, Player *p2)
{
	int turns = 1;
	int boardSpaceLeft = BOARD_SIZE*BOARD_SIZE - (p1->disks + p2->disks);
	
	while (boardSpaceLeft) // while there is still space left on the board.
	{
		if (turns % 2 != 0) // odd = p1's turns.
		{
			printf("\n\nTurn %d - %s's move - %d Points vs %d\n", turns, p1->name, p1->disks, p2->disks);
			manageMoves(board, p1, p2);
			
			printBoard(board);
			
			turns++;
		}
		if (turns % 2 == 0) // even = p2's turns.
		{
			printf("\n\nTurn %d - %s's move - %d Points vs %d\n", turns, p2->name, p2->disks, p1->disks);
			manageMoves(board, p2, p1);
			
			printBoard(board);
			
			turns++;
		}
		
		// assuming no number errors in p1 and p2's disks.
		boardSpaceLeft = BOARD_SIZE*BOARD_SIZE - (p1->disks + p2->disks);
	}
}

void manageEnding(Player p1, Player p2)
{
	if (p1.disks > p2.disks) // p1 win.
		printf("\n%s wins!\n", p1.name);
	else if (p2.disks > p1.disks) // p2 win.
		printf("\n%s wins!\n", p2.name);
	else // draw.
		printf("\nDraw! Good game %s and %s!\n", p1.name, p2.name);
}

void manageMoves(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness)
{
	// stores the moves that can be made.
	int coords[BOARD_SIZE][BOARD_SIZE] = {0};
	
	/* get coords. */
	// first, find own disk,
	for (int r = 0; r < BOARD_SIZE; r++)
		for (int c = 0; c < BOARD_SIZE; c++)
			if (board[r][c].type == pMove->type)
				// then check for adversary disks in the perimeter.
				checkAdversaryDisk(board, *pMove, *pWitness, r, c, coords);
	
	/* print board with coords. */
	// NOT DONE.. (nice to have)
	
	/* print coords. */
	int max;
	printf("    ");
	for (int r = 0, i = 1, printed = 0; r < BOARD_SIZE; r++)
	{
		for (int c = 0; c < BOARD_SIZE; c++)
			if (coords[r][c])
			{
				// makes console printing look neater.
				if (i < 10) // accounts for coords less than 10.
					printf("0%d. (%d, %c)  |  ", i, r+1, c+1-1+'a');
				else // all other 2 digit numbers.
					printf("%d. (%d, %c)  |  ", i, r+1, c+1-1+'a');
				
				i++;
				if ((i-4) % 3 == 0) // at 4, at 7, 10, 13. 4+3n.
					printf("\n    ");
			}
		max = i-1;
	}
	
	/* ask player for coord. */
	int choice = 0;
	puts("");
	do{
		printf("%s, please select a coordinate to place your disk: ", pMove->name);
		scanf("%d", &choice);
	} while (!(choice > 0 && choice <= max)); // while user enter something else but the range.
	
	/* get player chosen coord. */
	int row = 0, col = 0;
	for (int r = 0, i = 0, exit = 0; r < BOARD_SIZE; r++)
	{
		if (exit)
			break;
			
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (coords[r][c])
				++i;
			if (i == choice)
			{
				row = r;
				col = c;
				
				exit = 1;
				break;
			}
		}
	}
	/* place player's disk there. */
	// disk checking before placement.
	if (board[row][col].type == NONE)
	{
		board[row][col].type = pMove->type;
		pMove->disks++;
		
		/* replace all opponent's disk to be player's disk. */
		checkOwnDisk(board, pMove, pWitness, row, col);
	}
	else
		printf("[Error] Something wong, coordinate is not a NONE.");
}

void checkOwnDisk(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
	// from previous function, row, col. (start location of own disk)
	// outer loop, i, j. (for perimeter of starting own disk)
	// inner loop, r, c. (for direction heading towards a direction)
	// inner inner loop, x, y. (for direction heading back towards start location of own disk)
	
	// check for adversary disks in the perimeter.
	for (int i = row-1; i <= row+1; i++)
		for (int j = col-1; j <= col+1; j++)
			if (board[i][j].type == pWitness->type)
			{
				// check further towards that direction for adversary disks.
				if (i == row-1)
				{
					if (j == col-1) // north-west direction.
						for (int r = row-2, c = col-2; r >= 0 && c >= 0; )
						{
							if (board[r][c].type == pWitness->type)
							{
								r--;
								c--;
							}
							else if (board[r][c].type == pMove->type)
							{
								// we replace all disks from the start of our own disk,
								// till before this disk, with our own disks.
								for (int x = r+1, y = c+1; x < row && y < col; )
									// checks if it is adversary disk, replace only if so.
									if (board[x][y].type == pWitness->type)
									{
										board[x][y].type = pMove->type;
										x++;
										y++;
										pMove->disks++;
										pWitness->disks--;
									}
									
								break;
							}
							else // else = NONE, we ignore
								break;
						}
					else if (j == col) // north.
						for (int r = row-2, c = col; r >= 0; )
						{
							if (board[r][c].type == pWitness->type)
								r--;
							else if (board[r][c].type == pMove->type)
							{
								for (int x = r+1, y = c; x < row; )
									if (board[x][y].type == pWitness->type)
									{
										board[x][y].type = pMove->type;
										x++;
										pMove->disks++;
										pWitness->disks--;
									}
								
								break;
							}
							else
								break;
						}
					else if (j == col+1) // north-east.
						for (int r = row-2, c = col+2; r >= 0 && c < BOARD_SIZE; )
						{
							if (board[r][c].type == pWitness->type)
							{
								r--;
								c++;
							}
							else if (board[r][c].type == pMove->type)
							{
								for (int x = r+1, y = c-1; x < row && y > col; )
									if (board[x][y].type == pWitness->type)
									{
										board[x][y].type = pMove->type;
										x++;
										y--;
										pMove->disks++;
										pWitness->disks--;
									}
								
								break;
							}
							else
								break;
						}
				}
				else if (i == row)
				{
					if (j == col-1) // west.
						for (int c = col-2, r = row; c >= 0; )
						{
							if (board[r][c].type == pWitness->type)
								c--;
							else if (board[r][c].type == pMove->type)
							{
								for (int y = c+1, x = r; y < col; )
									if (board[x][y].type == pWitness->type)
									{
										board[x][y].type = pMove->type;
										y++;
										pMove->disks++;
										pWitness->disks--;
									}
								
								break;
							}
							else
								break;
						}
					else if (j == col+1) // east.
						for (int c = col+2, r = row; c < BOARD_SIZE; )
						{
							if (board[r][c].type == pWitness->type)
								c++;
							else if (board[r][c].type == pMove->type)
							{
								for (int y = c-1, x = r; y > col; )
									if (board[x][y].type == pWitness->type)
									{
										board[x][y].type = pMove->type;
										y--;
										pMove->disks++;
										pWitness->disks--;
									}
								
								break;
							}
							else
								break;
						}
				}
				else if (i == row+1)
				{
					if (j == col-1) // south-west.
						for (int r = row+2, c = col-2; r < BOARD_SIZE && c >= 0; )
						{
							if (board[r][c].type == pWitness->type)
							{
								r++;
								c--;
							}
							else if (board[r][c].type == pMove->type)
							{
								for (int x = r-1, y = c+1; x > row && y < col; )
									if (board[x][y].type == pWitness->type)
									{
										board[x][y].type = pMove->type;
										x--;
										y++;
										pMove->disks++;
										pWitness->disks--;
									}
								
								break;
							}
							else
								break;
						}
					else if (j == col) // south.
						for (int r = row+2, c = col; r < BOARD_SIZE; )
						{
							if (board[r][c].type == pWitness->type)
								r++;
							else if (board[r][c].type == pMove->type)
							{
								for (int x = r-1, y = c; x > row; )
									if (board[x][y].type == pWitness->type)
									{
										board[x][y].type = pMove->type;
										x--;
										pMove->disks++;
										pWitness->disks--;
									}
									
								break;
							}
							else
								break;
						}
					else if (j == col+1) // south-east.
						for (int r = row+2, c = col+2; r < BOARD_SIZE && c < BOARD_SIZE; )
						{
							if (board[r][c].type == pWitness->type)
							{
								r++;
								c++;
							}
							else if (board[r][c].type == pMove->type)
							{
								for (int x = r-1, y = c-1; x > row && y > col; )
									if (board[x][y].type == pWitness->type)
									{
										board[x][y].type = pMove->type;
										x--;
										y--;
										pMove->disks++;
										pWitness->disks--;
									}
								
								break;
							}
							else
								break;
						}
				}
			}
}

void checkAdversaryDisk(Disk board[][BOARD_SIZE], Player pMove, Player pWitness, int row, int col, int coords[][BOARD_SIZE])
{
	// from previous function, row, col. (start location of own disk)
	// outer loop, i, j. (for perimeter of starting own disk)
	// inner loop, r, c. (for direction heading towards a direction)
	
	// Checks perimeter for adversary disk, if adversary disk exists, goes further that direction.
	// In that direction, if more adversary disks exist, we continue until we get a NONE or player's own disk colour.
	// If we get a NONE, that means we can place our disk there.
	// If we get player's own disk colour, it means we simply ignore that path.
	
	// check for adversary disks in the perimeter.
	for (int i = row-1; i <= row+1; i++)
	{
		// ignore coords outside board.
		if (!(i >= 0 && i < BOARD_SIZE))
			continue;
			
		for (int j = col-1; j <= col+1; j++)
		{
			// ignore coords outside board.
			if (!(j >= 0 && j < BOARD_SIZE))
				continue;
			if (i == row && j == col) // deal with itself.
				continue;
				
			if (board[i][j].type == pWitness.type)
			{
				// check further towards that direction for adversary disks.
				if (i == row-1)
				{
					if (j == col-1) // north-west.
						for (int r = row-2, c = col-2; r >= 0 && c >= 0; )
						{
							if (board[r][c].type == pWitness.type)
							{
								r--;
								c--;
							}
							else if (board[r][c].type == NONE)
							{
								coords[r][c] = 1;
								break;
							}
							else // else = own colour, we ignore.
								break;
						}
					else if (j == col) // north.
						for (int r = row-2, c = col; r >= 0; )
						{
							if (board[r][c].type == pWitness.type)
								r--;
							else if (board[r][c].type == NONE)
							{
								coords[r][c] = 1;
								break;
							}
							else
								break;
						}
					else if (j == col+1) // north-east.
						for (int r = row-2, c = col+2; r >= 0 && c < BOARD_SIZE; )
						{
							if (board[r][c].type == pWitness.type)
							{
								r--;
								c++;
							}
							else if (board[r][c].type == NONE)
							{
								coords[r][c] = 1;
								break;
							}
							else
								break;
						}
				}
				else if (i == row)
				{
					if (j == col-1) // west.
						for (int c = col-2, r = row; c >= 0; )
						{
							if (board[r][c].type == pWitness.type)
								c--;
							else if (board[r][c].type == NONE)
							{
								coords[r][c] = 1;
								break;
							}
							else
								break;
						}
					else if (j == col+1) // east.
						for (int c = col+2, r = row; c < BOARD_SIZE; )
						{
							if (board[r][c].type == pWitness.type)
								c++;
							else if (board[r][c].type == NONE)
							{
								coords[r][c] = 1;
								break;
							}
							else
								break;
						}
				}
				else if (i == row+1)
				{
					if (j == col-1) // south-west.
						for (int r = row+2, c =col-2; r < BOARD_SIZE&& c >= 0; )
						{
							if (board[r][c].type == pWitness.type)
							{
								r++;
								c--;
							}
							else if (board[r][c].type == NONE)
							{
								coords[r][c] = 1;
								break;
							}
							else
								break;
						}
					else if (j == col) // south.
						for (int r = row+2, c = col; r < BOARD_SIZE; )
						{
							if (board[r][c].type == pWitness.type)
								r++;
							else if (board[r][c].type == NONE)
							{
								coords[r][c] = 1;
								break;
							}
							else
								break;
						}
					else if (j == col+1) // south-east.
						for (int r = row+2, c = col+2; r < BOARD_SIZE && c < BOARD_SIZE; )
						{
							if (board[r][c].type == pWitness.type)
							{
								r++;
								c++;
							}
							else if (board[r][c].type == NONE)
							{
								coords[r][c] = 1;
								break;
							}
							else
								break;
						}
				}
			}
		}
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
