#include <stdio.h>
#include <stdlib.h>

#include "initialize.h"
#include "turns.h"
#include "checkAdversaryDisk.h"
#include "checkOwnDisk.h"

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

void manageMoves(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness)
{
	// Initially, there are no nodes at start.
	listNodePtr startPtr = NULL;
	
	getCoords(board, pMove, pWitness, &startPtr);
	
	int max;
	printCoords(startPtr, &max);
	
	int choice = 0;
	askChooseCoord(*pMove, max, &choice);
	
	int row = 0, col = 0;
	getChosenCoord(&startPtr, choice, &row, &col);
	
	placeDisks(board, pMove, pWitness, row, col);
}

/* get coords. */
void getCoords(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, listNodePtr *sPtr)
{
	// first, find own disk,
	for (int r = 0; r < BOARD_SIZE; r++)
		for (int c = 0; c < BOARD_SIZE; c++)
			if (board[r][c].type == pMove->type)
				// then check for adversary disks in the perimeter.
				checkAdversaryDisk(board, *pWitness, r, c, sPtr);
}

/* print coords. */
void printCoords(listNodePtr currentPtr, int *max)
{
	printf("    ");
	
	int i = 1, r, c;
	while (currentPtr != NULL)
	{
		r = currentPtr->row;
		c = currentPtr->col;
		
		// makes console printing look neater.
		if (i < 10) // accounts for coords less than 10.
			printf("0%d. (%d, %c)  |  ", i, r+1, c+1-1+'a');
		else // all other 2 digit numbers.
			printf("%d. (%d, %c)  |  ", i, r+1, c+1-1+'a');
		
		i++;
		if ((i-4) % 3 == 0) // at 4, at 7, 10, 13. 4+3n.
			printf("\n    ");
			
		*max = i-1;
		
		currentPtr = currentPtr->nextPtr; // finally, point to next node.
	}
}

/* ask player for coord. */
void askChooseCoord(Player pMove, int max, int *choice)
{
	do{
		printf("\n%s, please select a coordinate to place your disk: ", pMove.name);
		scanf("%d", choice);
	} while (!(*choice > 0 && *choice <= max)); // while user enter something else but the range.
}

/* get player chosen coord. */
void getChosenCoord(listNodePtr *sPtr, int choice, int *row, int *col)
{
	int i = 0;
	if (!(isEmpty(*sPtr)))
	{
		// points to the beginning of the list, i.e., first node.
		listNodePtr previousPtr = *sPtr;
		listNodePtr currentPtr = (*sPtr)->nextPtr;
		
		// increments i, until we get user chosen coordinates.
		while (previousPtr != NULL)
		{
			++i;
			if (i == choice)
			{
				*row = previousPtr->row;
				*col = previousPtr->col;
				
				break;
			}
			
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
	}
	else
		printf("[WARNING] List is empty.\n");
	
	// dequeues all the nodes once we are done with the linked list.
	while (!(isEmpty(*sPtr)))
		dequeue(sPtr);
}

// used to check if the linked list is empty, i.e. first node leads to nothing, i.e. first node is NULL.
int isEmpty(listNodePtr sPtr)
{
	return sPtr == NULL;
}

// removes the node from the linked list as well as free the memory allocated to it.
void dequeue(listNodePtr *sPtr)
{
	listNodePtr tempPtr = *sPtr;
	*sPtr = (*sPtr)->nextPtr;
	free(tempPtr);
}

/* place player's disk there. */
void placeDisks(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
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




