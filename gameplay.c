#include <stdio.h>

#include "playerInfo.h"
#include "gamePlay.h"
#include "scanBoard.h"
#include "gameEnd.h"

// Le Function Definitions.


// A.2 Managing turns.

/* Function that manages each turn by keeping track of number of turns and spaces left on board and takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *p1: player 1
 * - Player *p2: player 2
 */
int manageTurns(Disk board[][BOARD_SIZE], Player *p1, Player *p2)
{
	int turns = 1; // number of turns in current game.
	int boardSpaceLeft = BOARD_SIZE*BOARD_SIZE - (p1->disks + p2->disks); // number of spaces currently left on board.
	
	while (boardSpaceLeft) // while there is still space left on the board.
	{
		if (turns % 2 != 0) // odd = p1's turns.
		{
			printf("\n\nTurn %d - %s's move - %d Points vs %d\n", turns, p1->name, p1->disks, p2->disks);
			manageMoves(board, p1, p2);
			
			printBoard(board); 
			
			turns++; // increments turn number.
		}
		if (turns % 2 == 0) // even = p2's turns.
		{
			printf("\n\nTurn %d - %s's move - %d Points vs %d\n", turns, p2->name, p2->disks, p1->disks);
			manageMoves(board, p2, p1);
			
			printBoard(board); 
			
			turns++; // increments turn number.
		}
		
		// assuming no number errors in p1 and p2's disks.
		boardSpaceLeft = BOARD_SIZE*BOARD_SIZE - (p1->disks + p2->disks);
	}
	
	return turns-1;
}


/* Function that manages each move by calculating possible moves then prompting user to chose one; it takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: current player
 * - Player *pOpponent: opponent player
 */
void manageMoves(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent)
{
	// stores coords of moves that can be made.
	int coords[BOARD_SIZE][BOARD_SIZE] = {0};
	
	// get coords.
	// first, loop through current board to find current player's disk.
	// then check for opponent disks in its perimeter.
	for (int r = 0; r < BOARD_SIZE; r++)
		for (int c = 0; c < BOARD_SIZE; c++) 
			if (board[r][c].type == pCurrent->type)
				findPossibleMoves(board, *pOpponent, r, c, coords);
	
	// Display possible moves current player can make, prompts their choice, then places their disks appropriately
	showAndChooseMoves(coords, board, pCurrent, pOpponent);
}


/* Function shows possible moves current player can make, prompts player's choice and places their disks appropriately; it takes in:
 * - coords[][]: 2D array representing possible moves that can be made (possible coords to place disk)
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: current player
 * - Player *pOpponent: opponent player
 */
void showAndChooseMoves (int coords[][BOARD_SIZE], Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent)
{
	// print possible coords.
	int max = printCoords(coords, board, pCurrent, pOpponent);	
	
	// ask for player's chosen coords.
	int choice = promptUserCoord(coords, board, pCurrent, pOpponent, max);
	
	// place player's disk at chosen coords (iff said coords hold no disks).	
	placeDiskAtCoord(coords, board, pCurrent, pOpponent, choice);
}

/* Function shows possible moves current player can make; it takes in:
 * - coords[][]: 2D array representing possible moves that can be made (possible coords to place disk)
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: current player
 * - Player *pOpponent: opponent player
 */
int printCoords (int coords[][BOARD_SIZE], Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent)
{
	int max;
	printf("    ");
	for (int r = 0, i = 1; r < BOARD_SIZE; r++) // i deals with index of possible coords
	{
		for (int c = 0; c < BOARD_SIZE; c++)
			if (coords[r][c])
			{
				// makes console output look neater.
				if (i < 10) // accounts for index of coords with single digits.
					printf("0%d. (%d, %c)  |  ", i, r+1, c+1-1+'a');
				else // all other 2 digit index.
					printf("%d. (%d, %c)  |  ", i, r+1, c+1-1+'a');
				
				i++;
				if ((i-4) % 3 == 0) // at 4, at 7, 10, 13. 4+3n.
					printf("\n    "); // prints whitespace above board in console
			}
		max = i;
	}	
	return max; // number of possible coords.
}

/* Function prompts player's choice of possible coords; it takes in:
 * - coords[][]: 2D array representing possible moves that can be made (possible coords to place disk)
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: current player
 * - Player *pOpponent: opponent player
 */
int promptUserCoord (int coords[][BOARD_SIZE], Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int max)
{
	int choice = 0;
	puts("");
	do{
		printf("%s, please select a coordinate to place your disk: ", pCurrent->name);
		scanf("%d", &choice);
	} while (!(choice > 0 && choice < max)); // while user enter something else but the given range.
	
	return choice;
}

/* Function places user disks according to their choice; it takes in:
 * - coords[][]: 2D array representing possible moves that can be made (possible coords to place disk)
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: current player
 * - Player *pOpponent: opponent player
 */
void placeDiskAtCoord (int coords[][BOARD_SIZE], Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int choice)
{
	// get player's chosen coords. // loops through board until i reaches index of player's chosen coords, then stores those coords in another variable.
	int row = 0, col = 0; // stores player's chosen coords.
	for (int r = 0, i = 0, exit = 0; r < BOARD_SIZE; r++) // i to find index of player's chosen coords, exit ensures loop is exited
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
	
	if (board[row][col].type == NONE) 
	{
		board[row][col].type = pCurrent->type;
		pCurrent->disks++;
		
		updateBoardAndScore(board, pCurrent, pOpponent, row, col); // replace all opponent's disk to be player's disk. 
	}
	else // check for error.
		printf("[Error] Something wrong, coordinate is not a NONE.");
}


/* Function that check own disks in order to replace opponent's disks after each turn and updates each player's number of disks; it takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player pCurrent: current player
 * - Player pOpponent: current opponent player
 * - row: current disk's y-coordinate
 * - col: current disk's x-coordinate
 * Note: this function is called once each turn.
 */
void updateBoardAndScore(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	// from previous function, row, col. (start location of own disk)
	// outer loop, i, j. (for perimeter of starting own disk)
	// inner loop, r, c. (for direction heading towards a direction)
	// inner inner loop, x, y. (for direction heading back towards start location of own disk)
	
	// check for opponent disks in the perimeter.
	for (int i = row-1; i <= row+1; i++)
		for (int j = col-1; j <= col+1; j++)
			if (board[i][j].type == pOpponent->type)
			{
				// check further towards that direction for opponent disks.
				if (i == row-1)
				{
					if (j == col-1) // north-west direction.
						updateBoardAndScoreNW(board, pCurrent, pOpponent, row, col);
					else if (j == col) // north.
						updateBoardAndScoreN (board, pCurrent, pOpponent, row, col);						
					else if (j == col+1) // north-east.
						updateBoardAndScoreNE(board, pCurrent, pOpponent, row, col);
				}
				else if (i == row)
				{
					if (j == col-1) // west.
						updateBoardAndScoreW (board, pCurrent, pOpponent, row, col);
					else if (j == col+1) // east.
						updateBoardAndScoreE (board, pCurrent, pOpponent, row, col);
				}
				else if (i == row+1)
				{
					if (j == col-1) // south-west.
						updateBoardAndScoreSW(board, pCurrent, pOpponent, row, col);
					else if (j == col) // south.
						updateBoardAndScoreS(board, pCurrent, pOpponent, row, col);
					else if (j == col+1) // south-east.
						updateBoardAndScoreSE(board, pCurrent, pOpponent, row, col);
				}
			}
}


/* Function checks for opponent disks to determine possible positions current player can move to and takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player pOpponent: current opponent player
 * - row: current disk's y-coordinate
 * - col: current disk's x-coordinate
 * - coords[][]: 2D array that stores the possible moves the current player can make
 * Note: this function is called to check each of current player's disks' perimeter for opponent's disks on board for every turn.
 */
void findPossibleMoves(Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
{
	// from function manageMoves, row, col. (start location of own disk)
	// outer loop, i, j. (for perimeter of starting own disk)
	// inner loop, r, c. (for direction heading towards a direction)
	
	// Checks perimeter for opponent disk, if opponent disk exists, goes further that direction.
	// In that direction, if more opponent disks exist, we continue until we get a NONE or player's own disk colour.
	// If we get a NONE, that means we can place our disk there.
	// If we get player's own disk colour, it means we simply ignore that path.
	
	// check for opponent disks in the perimeter.
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
			if (i == row && j == col) // ignores itself.
				continue;
				
			if (board[i][j].type == pOpponent.type)
			{
				// check further towards that direction for opponent disks.
				if (i == row-1)
				{
					if (j == col-1) // north-west.
						findPossibleMovesNW(board, pOpponent, row, col, coords);
					else if (j == col) // north.
						findPossibleMovesN (board, pOpponent, row, col, coords);
					else if (j == col+1) // north-east.
						findPossibleMovesNE(board, pOpponent, row, col, coords);
				}
				else if (i == row)
				{
					if (j == col-1) // west.
						findPossibleMovesW(board, pOpponent, row, col, coords);
					else if (j == col+1) // east.
						findPossibleMovesE(board, pOpponent, row, col, coords);
				}
				else if (i == row+1)
				{
					if (j == col-1) // south-west.
						findPossibleMovesSW(board, pOpponent, row, col, coords);
					else if (j == col) // south.
						findPossibleMovesS (board, pOpponent, row, col, coords);
					else if (j == col+1) // south-east.
						findPossibleMovesSE(board, pOpponent, row, col, coords);
				}
			}
		}
	}
}





























