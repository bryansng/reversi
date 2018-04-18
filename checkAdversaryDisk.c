#include <stdio.h> // printf
#include <stdlib.h> // sizeof and malloc.
#include "initialize.h"
#include "checkAdversaryDisk.h"

// le function prototypes.
int isInList(listNodePtr currentPtr, int r, int c);
void insert(listNodePtr *sPtr, int r, int c);
void checkAdvNorthWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col);
void checkAdvNorth(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col);
void checkAdvNorthEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col);
void checkAdvWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col);
void checkAdvEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col);
void checkAdvSouthWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col);
void checkAdvSouth(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col);
void checkAdvSouthEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col);

void checkAdversaryDisk(Disk board[][BOARD_SIZE], Player pWitness, int row, int col, listNodePtr *sPtr)
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
						checkAdvNorthWest(board, sPtr, pWitness, row, col);
					else if (j == col) // north.
						checkAdvNorth(board, sPtr, pWitness, row, col);
					else if (j == col+1) // north-east.
						checkAdvNorthEast(board, sPtr, pWitness, row, col);
				}
				else if (i == row)
				{
					if (j == col-1) // west.
						checkAdvWest(board, sPtr, pWitness, row, col);
					else if (j == col+1) // east.
						checkAdvEast(board, sPtr, pWitness, row, col);
				}
				else if (i == row+1)
				{
					if (j == col-1) // south-west.
						checkAdvSouthWest(board, sPtr, pWitness, row, col);
					else if (j == col) // south.
						checkAdvSouth(board, sPtr, pWitness, row, col);
					else if (j == col+1) // south-east.
						checkAdvSouthEast(board, sPtr, pWitness, row, col);
				}
			}
		}
	}
}

void checkAdvNorthWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col)
{
	for (int r = row-2, c = col-2; r >= 0 && c >= 0; )
	{
		if (board[r][c].type == pWitness.type)
		{
			r--;
			c--;
		}
		else if (board[r][c].type == NONE)
		{
			insert(sPtr, r, c);
			break;
		}
		else // else = own colour, we ignore.
			break;
	}
}

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

// loops through the list to check if the coordinates already exists.
int isInList(listNodePtr currentPtr, int r, int c)
{
	while (currentPtr != NULL)
	{
		if (currentPtr->row == r && currentPtr->col == c)
			return 1;
		
		currentPtr = currentPtr->nextPtr;
	}
	
	return 0;
}

void checkAdvNorth(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col)
{
	for (int r = row-2, c = col; r >= 0; )
	{
		if (board[r][c].type == pWitness.type)
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

void checkAdvNorthEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col)
{
	for (int r = row-2, c = col+2; r >= 0 && c < BOARD_SIZE; )
	{
		if (board[r][c].type == pWitness.type)
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

void checkAdvWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col)
{
	for (int c = col-2, r = row; c >= 0; )
	{
		if (board[r][c].type == pWitness.type)
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

void checkAdvEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col)
{
	for (int c = col+2, r = row; c < BOARD_SIZE; )
	{
		if (board[r][c].type == pWitness.type)
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

void checkAdvSouthWest(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col)
{
	for (int r = row+2, c =col-2; r < BOARD_SIZE&& c >= 0; )
	{
		if (board[r][c].type == pWitness.type)
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

void checkAdvSouth(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col)
{
	for (int r = row+2, c = col; r < BOARD_SIZE; )
	{
		if (board[r][c].type == pWitness.type)
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

void checkAdvSouthEast(Disk board[][BOARD_SIZE], listNodePtr *sPtr, Player pWitness, int row, int col)
{
	for (int r = row+2, c = col+2; r < BOARD_SIZE && c < BOARD_SIZE; )
	{
		if (board[r][c].type == pWitness.type)
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


















