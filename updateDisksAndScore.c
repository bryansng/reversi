#include "initialize.h"
#include "updateDisksAndScore.h"

// Le function prototypes.

// Aid replaceOpponentDisks to look in certain cardinal directions.
void updateAtNorthWest(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
void updateAtNorth(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
void updateAtNorthEast(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
void updateAtWest(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
void updateAtEast(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
void updateAtSouthWest(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
void updateAtSouth(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);
void updateAtSouthEast(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col);


/* Function updates both player's disks based on current user's choice of move;
 * it takes in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: Pointer to current player's struct.
 * - Player *pOpponent: Pointer to current opponent player's struct.
 * - row: User chosen x-coordinate.
 * - col: User chosen y-coordinate.
 * NOTE: this function is called once each turn.
 */
void updateDisksAndScore(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	// from previous function, row, col. (start location of current player's disk)
	// outer loop, i, j. (for perimeter of that disk)
	
	// check for adversary disks in the perimeter.
	for (int i = row-1; i <= row+1; i++)
		for (int j = col-1; j <= col+1; j++)
			if (board[i][j].type == pOpponent->type)
			{
				// check further towards that direction for opponent disks.
				if (i == row-1)
				{
					if (j == col-1) // north-west direction.
						updateAtNorthWest(board, pCurrent, pOpponent, row, col);
					else if (j == col) // north.
						updateAtNorth(board, pCurrent, pOpponent, row, col);						
					else if (j == col+1) // north-east.
						updateAtNorthEast(board, pCurrent, pOpponent, row, col);
				}
				else if (i == row)
				{
					if (j == col-1) // west.
						updateAtWest(board, pCurrent, pOpponent, row, col);
					else if (j == col+1) // east.
						updateAtEast(board, pCurrent, pOpponent, row, col);
				}
				else if (i == row+1)
				{
					if (j == col-1) // south-west.
						updateAtSouthWest(board, pCurrent, pOpponent, row, col);
					else if (j == col) // south.
						updateAtSouth(board, pCurrent, pOpponent, row, col);
					else if (j == col+1) // south-east.
						updateAtSouthEast(board, pCurrent, pOpponent, row, col);
				}
			}
}

/* Functions below aid updateDisksAndScore to look at their respective cardinal directions;
 * They each take in,
 * - Disk board[][]: 2D array representing row and col of board
 * - Player *pCurrent: Pointer to current player's struct.
 * - Player *pOpponent: Pointer to current opponent player's struct.
 * - row: User chosen x-coordinate.
 * - col: User chosen y-coordinate.
 * NOTE: For each direction, disk and score changes are only registered if it is true that player disk can be found around opponent disk. If that position holds an opponent disk or no disk, it is ignored.
 */
void updateAtNorthWest(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
{
	// outer loop, r, c. (for direction heading towards a direction)
	// inner loop, x, y. (for direction heading back towards start location of own disk)
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
				// checks if it is adversary disk, replace only if so.
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

void updateAtNorth(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
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

void updateAtNorthEast(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
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

void updateAtWest(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
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

void updateAtEast(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
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

void updateAtSouthWest(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
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
 
void updateAtSouth(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
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

void updateAtSouthEast(Disk board[][BOARD_SIZE], Player *pCurrent, Player *pOpponent, int row, int col)
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
