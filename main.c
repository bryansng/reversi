/*
	COMP10050 Assignment 3: Othello/Reversi Game
	
	Player 1: Sng Hong Yao 17205050
	Player 2: Liew Xuan 17200573
*/
#include <stdio.h>
#include <stdlib.h>

#include "initialize.h"
#include "turns.h"
#include "end.h"

int main (void)
{
	// A.1 Start Condition.
	// initialize players.
	Player p1 = {"player 1", NONE, 0};
	Player p2 = {"player 2", NONE, 0};
			
	// initialize disk.
	Disk board[BOARD_SIZE][BOARD_SIZE];
	
	initializePlayers(&p1, &p2);
	initializeBoard(board);
	
	printBoard(board);
	
	// A.2 Manage turn.
    // invoke a method that implements the game logic.
    manageTurns(board, &p1, &p2);

	// A.3 Printing the final result.
    // invoke a method that prints the final result.
	// when game ends i.e. no board space left.
	manageEnding(board, p1, p2);
}
