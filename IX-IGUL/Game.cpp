#include "Engine.h"

//------Display Functions------//
// prints the board normal
void PrintBoard(char board[][board_size])
{
	for (int k = 0; k < board_size; k++)
		printf("+---");
	printf("+\n");
	for (int i = 0; i < board_size; i++)
	{
		for (int k = 0; k < board_size; k++)
		{
			printf("| %c ", board[i][k]);
		}
		printf("|\n");
		for (int k = 0; k < board_size; k++)
			printf("+---");
		printf("+\n");
	}
}
// requests from the user to select a square to place his piece in
VectorPos RequestInput(char board[][board_size], int MatWidth)
{
	char input;
	int converted;
	VectorPos loc;

	while (1)
	{
		printf("Enter number between 1-9: ");
		scanf(" %c", &input);
		if (input < '1' || input > '9')
			printf("Invalid board Location.\n\n");
		else
		{
			converted = input - '0';
			pos_to_xy(converted, MatWidth, &loc.col, &loc.row);
			if (board[loc.row][loc.col] != ' ')
				printf("This square is already taken.\n");
			else
				break;
		}
	}
	return loc;
}

//------Play Function------//
// combines the play between the player and the computer into the main game loop
// play function returns the winner of the round so you can easily track the score
const char *Play()
{
	boolean GameOver = False;
	char turn = 'X';
	int depth;

	Board board;
	for (int i = 0; i < 3; i++)
		for (int k = 0; k < 3; k++)
			board[i][k] = ' ';
	
	char player, AI;
	system("cls");
	// get input.
	while (1)
	{
		printf("Is player X or O?\nInput: ");
		scanf(" %c", &player);
		if (player == 'X' || player == 'O')
		{
			while (1)
			{
				printf("How hard is the game?\n[1(easy) - 9(impossible)]: ");
				scanf(" %d", &depth);
				if (depth <= 9 && depth >= 1)
					break;
				else
					printf("Invalid input. Only between 1 - 9.\n");
			}
			break;
		}
		else
		{
			system("cls");
			printf("Invalid input. Only write X or O.\n");
		}
	}
	AI = toggle_players(player);
	// end of input

	// main game loop:
	int i;
	VectorPos move;
	move.col = move.row = -1;
	for (i = 0; i < 9; i++)
	{
		system("cls");
		printf("Player:   %c\nComputer: %c\n", player, AI);
		switch (turn)
		{
		case 'X':
			if (player == 'X')
			{
				PrintBoard(board);
				move = RequestInput(board, 3);
				board[move.row][move.col] = 'X';
				GameOver = IsGameOver(board);
				if (GameOver)
				{
					system("cls");
					printf("Player:   %c\nComputer: %c\n", player, AI);
					PrintBoard(board);
					printf("Game Over!\nWinner is player as X\n");
					return "Player";
				}
			}
			else
			{
				// computer move
				move = ComputerMove(board, depth, AI);
				board[move.row][move.col] = 'X';

				PrintBoard(board);
				printf("AI's move was { %d, %d }. press any key to continue.\n", move.row, move.col);
				// check if game is over
				GameOver = IsGameOver(board);
				if (GameOver)
				{
					system("cls");
					printf("Player:   %c\nComputer: %c\n", player, AI);
					PrintBoard(board);
					printf("Game Over!\nWinner is computer as X\nLoL get rekt noob B)\n");
					return "AI";
				}
				printf("Press [Enter] key to continue.\n");
				while (getchar() != '\n');
				getchar();
			}
			break;
		case 'O':
			if (player == 'O')
			{
				PrintBoard(board);
				move = RequestInput(board, 3);
				board[move.row][move.col] = 'O';
				GameOver = IsGameOver(board);
				if (GameOver)
				{
					system("cls");
					printf("Player:   %c\nComputer: %c\n", player, AI);
					PrintBoard(board);
					printf("Game Over!\nWinner is player as O\n");
					return "Player";
				}
			}
			else
			{
				// computer move
				move = ComputerMove(board, depth, AI);
				board[move.row][move.col] = 'O';

				PrintBoard(board);
				printf("AI's move was { %d, %d }.\n", move.row, move.col);
				GameOver = IsGameOver(board);
				if (GameOver)
				{
					system("cls");
					printf("Player:   %c\nComputer: %c\n", player, AI);
					PrintBoard(board);
					printf("Game Over!\nWinner is computer as X\nLoL get rekt noob B)\n");
					return "AI";
				}
				printf("Press [Enter] key to continue.\n");
				while (getchar() != '\n');
				getchar();
			}
			break;
		}
		turn = (turn == 'X') ? 'O' : 'X';
	}
	system("cls");
	printf("Player:   %c\nComputer: %c\n", player, AI);
	PrintBoard(board);
	printf("Draw!\n");
	return "Draw";
}