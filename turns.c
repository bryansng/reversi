#include <stdio.h>
#include <stdlib.h>

#include "initialize.h"
#include "turns.h"
#include "findPossibleMoves.h"
#include "updateDisksAndScore.h"

// Le Function Definitions.
int isEmpty(listNodePtr sPtr);
void dequeue(listNodePtr *sPtr);

// A.2 Managing turns.

/* Function that manages each turn by keeping track of number of turns and spaces left on board and takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *p1: Pointer to player 1's struct.
 * - Player *p2: Pointer to player 2's struct.
 */
void manageTurns(Disk board[][BOARD_SIZE], Player *p1, Player *p2)
{
	int turns = 1; // number of turns in current game.
	int boardSpaceLeft = BOARD_SIZE*BOARD_SIZE - (p1->disks + p2->disks); // number of spaces currently left on board.
	
	while (boardSpaceLeft) // while there is still space left on the board.
	{
		if (turns % 2 != 0) // odd = p1's turns.
		{
			printf("\n\nTurn %d - %s's move - %d Points against %d\n", turns, p1->name, p1->disks, p2->disks);
			manageMoves(board, p1, p2);
			
			printBoard(board); 
			
			turns++; // increments turn number.
		}
		if (turns % 2 == 0) // even = p2's turns.
		{
			printf("\n\nTurn %d - %s's move - %d Points against %d\n", turns, p2->name, p2->disks, p1->disks);
			manageMoves(board, p2, p1);
			
			printBoard(board); 
			
			turns++; // increments turn number.
		}
		
		// assuming no number errors in p1 and p2's disks.
		boardSpaceLeft = BOARD_SIZE*BOARD_SIZE - (p1->disks + p2->disks);
	}
}


/* Function that manages each move by calculating possible moves then prompting user to chose one; it takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: current player
 * - Player *pOpponent: opponent player
 */
void manageMoves(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent)
{
	// Initially, there are no nodes at start.
	listNodePtr startPtr = NULL;
	
	getCoords(board, pCurrent, pOpponent, &startPtr);
	
	int max;
	printCoords(startPtr, &max);
	
	int choice = 0;
	askChooseCoord(*pCurrent, max, &choice);
	
	int row = 0, col = 0;
	getChosenCoord(&startPtr, choice, &row, &col);
	
	placeDisks(board, pCurrent, pOpponent, row, col);
}


/* Function gets coordinates by finding the possible moves; it takes in:
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: current player
 * - Player *pOpponent: opponent player
 * - listNodePtr *sPtr: Pointer that points to the start of the linked list, used to store the number of possible moves per turn.
 */
void getCoords(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, listNodePtr *sPtr)
{
	// first, find own disk,
	for (int r = 0; r < BOARD_SIZE; r++)
		for (int c = 0; c < BOARD_SIZE; c++)
			if (board[r][c].type == pCurrent->type)
				// then check for adversary disks in the perimeter.
				findPossibleMoves(board, sPtr, *pOpponent, r, c);
}


/* Function prints the possible moves/coordinates to the console; it takes in:
 * - listNodePtr currentPtr: Pointer that points to the start of the linked list, used to store the number of possible moves per turn.
 * - int *max: Pointer used to store the number of maximum coordinates.
 */
void printCoords(listNodePtr currentPtr, int *max)
{
	printf("    ");
	
	// i deals with index of possible coords.
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


/* Function prompts the user to choose a move to make; it takes in:
 * - Player pCurrent: current player
 * - int max: Number of maximum coordinates.
 * - int *choice: Pointer used to store the move the player wishes to make.
 */
void askChooseCoord(Player pCurrent, int max, int *choice)
{
	do{
		printf("\n%s, please select a coordinate to place your disk: ", pCurrent.name);
		scanf("%d", choice);
	} while (!(*choice > 0 && *choice <= max)); // while user enter something else but the range.
}

/* Function that check own disks in order to replace opponent's disks after each turn and updates each player's number of disks; it takes in,
 * - listNodePtr *sPtr: Pointer that points to the start of the linked list, used to store the number of possible moves per turn.
 * - *row: Pointer to the current player's disk's y-coordinate
 * - *col: Pointer to the current plaer's disk's x-coordinate
 * NOTE: this function is called once each turn.
*/
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


/* Function checks if the linked list is empty, i.e. first node leads to nothing,
 * i.e. first node is NULL; it takes in,
 * - listNodePtr sPtr: Points to the start of the linked list i.e., first struct, used to store the number of possible moves per turn.
*/
int isEmpty(listNodePtr sPtr)
{
	return sPtr == NULL;
}

/* Function removes the node from the linked list as well as free the memory
 * allocated to it; it takes in,
 * - listNodePtr *sPtr: Pointer that points to the start of the linked list, used to store the number of possible moves per turn.
*/
void dequeue(listNodePtr *sPtr)
{
	listNodePtr tempPtr = *sPtr;
	*sPtr = (*sPtr)->nextPtr;
	free(tempPtr);
}

/* Function places user disks according to their choice and make changes to opponent's disks; it takes in:
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: current player
 * - Player *pOpponent: opponent player
 * - row: x coordinate to place current player's disk at.
 * - col: y coordinate to place current player's disk at.
 */
void placeDisks(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	// disk checking before placement.
	if (board[row][col].type == NONE)
	{
		board[row][col].type = pCurrent->type;
		pCurrent->disks++;
		
		// replace all opponent's disk to be player's disk.
		updateDisksAndScore(board, pCurrent, pOpponent, row, col);
	}
	else
		printf("[Error] Something wrong, coordinate is not a NONE.");
}
















