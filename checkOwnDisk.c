#include "initialize.h"
#include "checkOwnDisk.h"

// le function prototypes.
void checkOwnNorthWest(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);
void checkOwnNorth(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);
void checkOwnNorthEast(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);
void checkOwnWest(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);
void checkOwnEast(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);
void checkOwnSouthWest(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);
void checkOwnSouth(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);
void checkOwnSouthEast(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col);

void checkOwnDisk(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
	// from previous function, row, col. (start location of own disk)
	// outer loop, i, j. (for perimeter of starting own disk)
	
	// check for adversary disks in the perimeter.
	for (int i = row-1; i <= row+1; i++)
		for (int j = col-1; j <= col+1; j++)
			if (board[i][j].type == pWitness->type)
			{
				// check further towards that direction for adversary disks.
				if (i == row-1)
				{
					if (j == col-1) // north-west direction.
						checkOwnNorthWest(board, pMove, pWitness, row, col);
					else if (j == col) // north.
						checkOwnNorth(board, pMove, pWitness, row, col);
					else if (j == col+1) // north-east.
						checkOwnNorthEast(board, pMove, pWitness, row, col);
				}
				else if (i == row)
				{
					if (j == col-1) // west.
						checkOwnWest(board, pMove, pWitness, row, col);
					else if (j == col+1) // east.
						checkOwnEast(board, pMove, pWitness, row, col);
				}
				else if (i == row+1)
				{
					if (j == col-1) // south-west.
						checkOwnSouthWest(board, pMove, pWitness, row, col);
					else if (j == col) // south.
						checkOwnSouth(board, pMove, pWitness, row, col);
					else if (j == col+1) // south-east.
						checkOwnSouthEast(board, pMove, pWitness, row, col);
				}
			}
}

void checkOwnNorthWest(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
	// outer loop, r, c. (for direction heading towards a direction)
	// inner loop, x, y. (for direction heading back towards start location of own disk)
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
}

void checkOwnNorth(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
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
}

void checkOwnNorthEast(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
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

void checkOwnWest(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
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
}

void checkOwnEast(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
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

void checkOwnSouthWest(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
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
}

void checkOwnSouth(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
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
}

void checkOwnSouthEast(Disk board[][BOARD_SIZE], Player *pMove, Player *pWitness, int row, int col)
{
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













