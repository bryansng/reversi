/*
	COMP10050 Assignment 3: Othello/Reversi Game
	
	Player 1: Sng Hong Yao 17205050
	Player 2: Liew Xuan 17200573
*/
#include <stdio.h>
#include <stdlib.h>

#include "initialize.h"

void printBoard(Disk board[][BOARD_SIZE]);

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
}

void printMoves()
{
	
}


/* Function prints the board that represents the game and takes in,
* - d_p1: Struct of player 1.
* - d_p2: Struct of player 2.
*/
void printBoard(Disk board[][BOARD_SIZE])
{
	// Column headers.
	printf("    "); // 4 spaces.
	for (int c = 1; c <= BOARD_SIZE; c++)
		printf("%d   ", c);
		
	// Rows Header + Data.
	for (int r = 0; r < BOARD_SIZE; r++)
	{
		// Row Header.
		printf("\n%d |", r+1);
		
		// Row Data.
		for (int c = 0; c < BOARD_SIZE; c++)
		{
			if (board[r][c].type == BLACK)
				printf(" 1 |");
			else if (board[r][c].type == WHITE)
				printf(" 0 |");
			else if (board[r][c].type != BLACK && board[r][c].type != WHITE)
				printf(" x |");
		}
	}
	puts("\n");
}
