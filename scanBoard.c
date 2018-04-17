#include <stdio.h>

#define BOARD_SIZE 8 // Board is 8*8.

#include "playerInfo.h"
#include "scanBoard.h"

/* Functions below aid findPossibleMoves to look in certain cardinal directions; They each take in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player pOpponent: current opponent player
 * - row: current disk's y-coordinate
 * - col: current disk's x-coordinate
 * - coords[][]: 2D array that stores the possible moves the current player can make
 * Note: For each direction, the possible move is only registered if there are no disks there. If there is an opponent disk or player disk, it is ignored.
*/

void findPossibleMovesNW (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
{
	for (int r = row-2, c = col-2; r >= 0 && c >= 0; )
	{
		if (board[r][c].type == pOpponent.type) // continue checking until below conditions are met
		{
			r--;
			c--;
		}
		else if (board[r][c].type == NONE) // current player may place disk here
		{
			coords[r][c] = 1;
			break;
		}
		else // ignore current player's disk color.
			break;
	}
}

void findPossibleMovesN (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
{
	for (int r = row-2, c = col; r >= 0; )
	{
		if (board[r][c].type == pOpponent.type)
			r--;
		else if (board[r][c].type == NONE)
		{
			coords[r][c] = 1;
			break;
		}
		else
			break;
	}
}

void findPossibleMovesNE (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
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
			coords[r][c] = 1;
			break;
		}
		else
			break;
	}
}

void findPossibleMovesW (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
{
	for (int c = col-2, r = row; c >= 0; )
	{
		if (board[r][c].type == pOpponent.type)
			c--;
		else if (board[r][c].type == NONE)
		{
			coords[r][c] = 1;
			break;
		}
		else
			break;
	}
}

void findPossibleMovesE (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
{
	for (int c = col+2, r = row; c < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent.type)
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

void findPossibleMovesSW (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
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
			coords[r][c] = 1;
			break;
		}
		else
			break;
	}
}

void findPossibleMovesS (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
{
	for (int r = row+2, c = col; r < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent.type)
			r++;
		else if (board[r][c].type == NONE)
		{
			coords[r][c] = 1;
			break;
		}
		else
			break;
	}
}

void findPossibleMovesSE (Disk board[][BOARD_SIZE], Player pOpponent, int row, int col, int coords[][BOARD_SIZE])
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
			coords[r][c] = 1;
			break;
		}
		else
			break;
	}
}

/* Function below aid updateBoardAndScore to look in certain cardinal directions; They each take in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player pCurrent: current player
 * - Player pOpponent: current opponent player
 * - row: current disk's y-coordinate
 * - col: current disk's x-coordinate
 * Note: For each direction, disk and score changes are only registered if it is true that player disk can be found around opponent disk. If that position holds an opponent disk or no disk, it is ignored.
 */
 
void updateBoardAndScoreNW (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	 for (int r = row-2, c = col-2; r >= 0 && c >= 0; )
	{
		if (board[r][c].type == pOpponent->type)
		{
			r--;
			c--;
		}
		else if (board[r][c].type == pCurrent->type)
		{
			// we replace all disks from the start of our own disk,
			// till before this disk, with our own disks.
			for (int x = r+1, y = c+1; x < row && y < col; )
				// if it is opponent's disk, replace with own disk and update score.
				if (board[x][y].type == pOpponent->type)
				{	
					board[x][y].type = pCurrent->type;
					x++;
					y++;
					pCurrent->disks++;
					pOpponent->disks--;
				}
				
			break;
		}
		else // ignore type NONE.
			break;
	}
} 
 
void updateBoardAndScoreN (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	for (int r = row-2, c = col; r >= 0; )
	{
		if (board[r][c].type == pOpponent->type)
			r--;
		else if (board[r][c].type == pCurrent->type)
		{
			for (int x = r+1, y = c; x < row; )
				if (board[x][y].type == pOpponent->type)
				{
					board[x][y].type = pCurrent->type;
					x++;
					pCurrent->disks++;
					pOpponent->disks--;
				}
			
			break;
		}
		else
			break;
	}
} 
 
void updateBoardAndScoreNE (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	for (int r = row-2, c = col+2; r >= 0 && c < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent->type)
		{
			r--;
			c++;
		}
		else if (board[r][c].type == pCurrent->type)
		{
			for (int x = r+1, y = c-1; x < row && y > col; )
				if (board[x][y].type == pOpponent->type)
				{
					board[x][y].type = pCurrent->type;
					x++;
					y--;
					pCurrent->disks++;
					pOpponent->disks--;
				}
			
			break;
		}
		else
			break;
	}
} 
 
void updateBoardAndScoreW (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	for (int c = col-2, r = row; c >= 0; )
	{
		if (board[r][c].type == pOpponent->type)
			c--;
		else if (board[r][c].type == pCurrent->type)
		{
			for (int y = c+1, x = r; y < col; )
				if (board[x][y].type == pOpponent->type)
				{
					board[x][y].type = pCurrent->type;
					y++;
					pCurrent->disks++;
					pOpponent->disks--;
				}
			
			break;
		}
		else
			break;
	}
} 
 
void updateBoardAndScoreE (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	for (int c = col+2, r = row; c < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent->type)
			c++;
		else if (board[r][c].type == pCurrent->type)
		{
			for (int y = c-1, x = r; y > col; )
				if (board[x][y].type == pOpponent->type)
				{
					board[x][y].type = pCurrent->type;
					y--;
					pCurrent->disks++;
					pOpponent->disks--;
				}
			
			break;
		}
		else
			break;
	}
 }  
 
void updateBoardAndScoreSW (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	for (int r = row+2, c = col-2; r < BOARD_SIZE && c >= 0; )
	{
		if (board[r][c].type == pOpponent->type)
		{
			r++;
			c--;
		}
		else if (board[r][c].type == pCurrent->type)
		{
			for (int x = r-1, y = c+1; x > row && y < col; )
				if (board[x][y].type == pOpponent->type)
				{
					board[x][y].type = pCurrent->type;
					x--;
					y++;
					pCurrent->disks++;
					pOpponent->disks--;
				}
			
			break;
		}
		else
			break;
	}
}  
 
void updateBoardAndScoreS (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	for (int r = row+2, c = col; r < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent->type)
			r++;
		else if (board[r][c].type == pCurrent->type)
		{
			for (int x = r-1, y = c; x > row; )
				if (board[x][y].type == pOpponent->type)
				{
					board[x][y].type = pCurrent->type;
					x--;
					pCurrent->disks++;
					pOpponent->disks--;
				}
				
			break;
		}
		else
			break;
	}
}
 
void updateBoardAndScoreSE (Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	for (int r = row+2, c = col+2; r < BOARD_SIZE && c < BOARD_SIZE; )
	{
		if (board[r][c].type == pOpponent->type)
		{
			r++;
			c++;
		}
		else if (board[r][c].type == pCurrent->type)
		{
			for (int x = r-1, y = c-1; x > row && y > col; )
				if (board[x][y].type == pOpponent->type)
				{
					board[x][y].type = pCurrent->type;
					x--;
					y--;
					pCurrent->disks++;
					pOpponent->disks--;
				}
			
			break;
		}
		else
			break;
	}
}
 
 
 
 