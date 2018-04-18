#include <stdio.h> // printf
#include <stdlib.h> // sizeof, malloc and free.

#include "initialize.h"
#include "findPossibleMoves.h"

// Le function prototypes.
int isInList(listNodePtr currentPtr, int r, int c);
void insert(listNodePtr *sPtr, int r, int c);

// Aid findMovesAt to look in certain cardinal directions.
void findMovesAtNorthWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col);
void findMovesAtNorth(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col);
void findMovesAtNorthEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col);
void findMovesAtWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col);
void findMovesAtEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col);
void findMovesAtSouthWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col);
void findMovesAtSouth(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col);
void findMovesAtSouthEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col);


/* Function checks for opponent disks to determine possible positions current player can move to and takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - listNodePtr *sPtr: Pointer that points to the start of the linked list, used to store the number of possible moves per turn.
 * - Player pOpponent: current opponent player
 * - row: Current player's disk's y-coordinate
 * - col: Current player's disk's x-coordinate
 * NOTE: this function is called to check each of current player's disks' perimeter for opponent's disks on board for every turn.
 */
void findPossibleMoves(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
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
						findMovesAtNorthWest(board, sPtr, pOpponent, row, col);
					else if (j == col) // north.
						findMovesAtNorth (board, sPtr, pOpponent, row, col);
					else if (j == col+1) // north-east.
						findMovesAtNorthEast(board, sPtr, pOpponent, row, col);
				}
				else if (i == row)
				{
					if (j == col-1) // west.
						findMovesAtWest(board, sPtr, pOpponent, row, col);
					else if (j == col+1) // east.
						findMovesAtEast(board, sPtr, pOpponent, row, col);
				}
				else if (i == row+1)
				{
					if (j == col-1) // south-west.
						findMovesAtSouthWest(board, sPtr, pOpponent, row, col);
					else if (j == col) // south.
						findMovesAtSouth (board, sPtr, pOpponent, row, col);
					else if (j == col+1) // south-east.
						findMovesAtSouthEast(board, sPtr, pOpponent, row, col);
				}
			}
		}
	}
}



/* Function inserts the data i.e., row and column, into the linked list; It takes in,
 * - listNodePtr *sPtr: Pointer that points to the start of the linked list, used to store the number of possible moves per turn.
 * - int r: Row / x-coordinate to insert.
 * - int c: Col / y-coordinate to insert.
*/
void insert(listNodePtr *sPtr, int r, int c)
{
	// check if coordinates is already in the linked list.
	if (!(isInList(*sPtr, r, c)))
	{
		listNodePtr newPtr = malloc(sizeof(listNode)); // create new node.
				
		// check if sufficient memory, else, malloc returns NULL.
		if (newPtr != NULL)
		{
			newPtr->row = r;
			newPtr->col = c;
			newPtr->nextPtr = NULL;
			
			listNodePtr previousPtr = NULL;
			listNodePtr currentPtr = *sPtr;
			
			// loop to find the correct location in the list.
			while (currentPtr != NULL && ( (r > currentPtr->row) || (r == currentPtr->row && c > currentPtr->col) ))
			{
				previousPtr = currentPtr;
				currentPtr = currentPtr->nextPtr;
			}
			
			// insert at the beginning of linked list, if no nodes in linked list.
			if (previousPtr == NULL)
			{
				newPtr->nextPtr = *sPtr;
				*sPtr = newPtr;
			}
			else // insert new node between previousPtr and currentPtr.
			{
				previousPtr->nextPtr = newPtr;
				newPtr->nextPtr = currentPtr;
			}
		}
		else
			printf("[Error] Memory insufficient.\n");
	}
}

/* Function loops through the linked list to check if the coordinates already
 * exists within the linked list; It takes in,
 * - listNodePtr currentPtr: Pointer that points to the start of the linked list, used to store the number of possible moves per turn.
 * - int r: Row / x-coordinate to check.
 * - int c: Col / y-coordinate to check.
*/
int isInList(listNodePtr currentPtr, int r, int c)
{
	while (currentPtr != NULL)
	{
		// if exist, we return 1.
		if (currentPtr->row == r && currentPtr->col == c)
			return 1;
		
		// else, we continue searching until we reach the end of the linked-list.
		currentPtr = currentPtr->nextPtr;
	}
	
	// if not in list, we return 0.
	return 0;
}



/* Functions below aid findPossibleMoves to look for possible moves in their respective cardinal directions; They each take in,
 * - Disk board[][]: 2D array representing row and col of board
 * - listNodePtr *sPtr: Pointer that points to the start of the linked list, used to store the number of possible moves per turn.
 * - Player pOpponent: Player struct of current opponent.
 * - row: Current player's disk's y-coordinate.
 * - col: Current player's disk's x-coordinate.
 * NOTE: For each direction, the possible move is only registered if there are no disks there. If there is an opponent disk or player disk, it is ignored.
*/

void findMovesAtNorthWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
{
	for (int r = row-2, c = col-2; r >= 0 && c >= 0; )
	{
		if (board[r][c].type == pOpponent.type) // continue checking until the conditions below are met.
		{
			r--;
			c--;
		}
		else if (board[r][c].type == NONE) // current player may place disk here.
		{
			insert(sPtr, r, c);
			break;
		}
		else // ignore current player's disk color.
			break;
	}
}

void findMovesAtNorth(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
{
	for (int r = row-2, c = col; r >= 0; )
	{
		if (board[r][c].type == pOpponent.type)
			r--;
		else if (board[r][c].type == NONE)
		{
			insert(sPtr, r, c);
			break;
		}
		else
			break;
	}
}

void findMovesAtNorthEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
{
	for (int r = row-2, c = col+2; r >= 0 && c < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent.type)
		{
			r--;
			c++;
		}
		else if (board[r][c].type == NONE)
		{
			insert(sPtr, r, c);
			break;
		}
		else
			break;
	}
}

void findMovesAtWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
{
	for (int c = col-2, r = row; c >= 0; )
	{
		if (board[r][c].type == pOpponent.type)
			c--;
		else if (board[r][c].type == NONE)
		{
			insert(sPtr, r, c);
			break;
		}
		else
			break;
	}
}

void findMovesAtEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
{
	for (int c = col+2, r = row; c < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent.type)
			c++;
		else if (board[r][c].type == NONE)
		{
			insert(sPtr, r, c);
			break;
		}
		else
			break;
	}
}

void findMovesAtSouthWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
{
	for (int r = row+2, c =col-2; r < BOARD_SIZE&& c >= 0; )
	{
		if (board[r][c].type == pOpponent.type)
		{
			r++;
			c--;
		}
		else if (board[r][c].type == NONE)
		{
			insert(sPtr, r, c);
			break;
		}
		else
			break;
	}
}

void findMovesAtSouth(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
{
	for (int r = row+2, c = col; r < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent.type)
			r++;
		else if (board[r][c].type == NONE)
		{
			insert(sPtr, r, c);
			break;
		}
		else
			break;
	}
}

void findMovesAtSouthEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pOpponent, int row, int col)
{
	for (int r = row+2, c = col+2; r < BOARD_SIZE && c < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent.type)
		{
			r++;
			c++;
		}
		else if (board[r][c].type == NONE)
		{
			insert(sPtr, r, c);
			break;
		}
		else
			break;
	}
}
