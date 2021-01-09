#include "Engine.h"

// function that converts board positions 1 - board_size to board coordinates.
void pos_to_xy(int pos, int board_width, int *col, int *row)
{
	pos -= 1;  // Bring range 1.. to 0..
	*row = pos / board_width;
	*col = pos % board_width;
}

//------Game End Functions------//
// checks if the column won
boolean CheckColumn(Board board, int col_number)
{
	if (board[0][col_number] == ' ')
		return False;
	if (board[0][col_number] == board[1][col_number] && board[1][col_number] == board[2][col_number])
		return True;
	return False;
}
// checks if the row won
boolean CheckRow(Board board, int row_number)
{
	if(board[row_number][0] == ' ')
		return False;
	if (board[row_number][0] == board[row_number][1] && board[row_number][1] == board[row_number][2])
		return True;
	return False;
}
// checks if the one of the diagonals won
boolean CheckDiag(Board board)
{
	if (board[1][1] == ' ')
		return False;
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
		return True;
	else if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
		return True;
	return False;
}
// checks if a player has won
boolean IsGameOver(Board board)
{
	if (CheckDiag(board))
		return True;
	for (int i = 0; i < 3; i++)
	{
		if (CheckColumn(board, i))
			return True;
		if (CheckRow(board, i))
			return True;
	}

	return False;
}
// checks if the board is full
boolean IsBoardFull(Board board)
{
	VectorPos pos;
	for (int i = 1; i <= 9; i++)
	{
		pos_to_xy(i, board_size, &pos.col, &pos.row);
		if (board[pos.row][pos.col] == ' ')
			return False;
	}
	return True;
}
// checks if the game ended in a draw
boolean IsDraw(Board board)
{
	if (!IsGameOver(board) && IsBoardFull(board))
		return True;
	return False;
}

//------Static Evaluation Functions------//
// evaluates how valuable is this row to this player
int EvaluateRow(Board board, char computer_player, int row)
{
	int rating = 0;
	for (int i = 0; i < board_size; i++)
	{
		// check row
		if (board[row][i] == computer_player)
			rating++;
		else if(board[row][i] == toggle_players(computer_player))
		{
			rating = 0;
			break;
		}
	}
	return rating;
}
// evaluates how valuable is this column to this player
int EvaluateCol(Board board, char computer_player, int col)
{
	int rating = 0;
	for (int i = 0; i < board_size; i++)
	{
		// check col
		if (board[i][col] == computer_player)
			rating++;
		else if (board[i][col] == toggle_players(computer_player))
		{
			rating = 0;
			break;
		}
	}
	return rating;
}
// evaluates how valuable are the diagonals to this player
int EvaluateDiag(Board board, char computer_player, boolean diag)
{
	int rating = 0;
	for (int i = 0; i < board_size; i++)
	{
		// check diag
		if (diag = True)
		{
			if (board[i][i] == computer_player)
				rating++;
			else if (board[i][i] == toggle_players(computer_player))
			{
				rating = 0;
				break;
			}
		}
		else
		{
			if (board[i][board_size - i - 1] == computer_player)
				rating++;
			else if (board[i][board_size - i - 1] == toggle_players(computer_player))
			{
				rating = 0;
				break;
			}
		}
	}
	return rating;
}
// total evaluation of the players position
int EvaluatePlayer(Board board, char player)
{
	int rows, cols, diag, diagr;
	rows = cols = diag = diagr = 0;
	boolean is_clean_row, is_clean_col;
	for (int i = 0; i < board_size; i++)
	{
		rows += EvaluateRow(board, player, i);
		cols += EvaluateCol(board, player, i);
	}
	diag += EvaluateDiag(board, player, True);
	diagr += EvaluateDiag(board, player, False);
	return diag + diagr + rows + cols;
}
// evaluation of the board position
int StaticEval(Board board, char last_player, char computer_player, boolean is_win, boolean is_draw)
{
	if (is_win)
	{
		if (last_player == computer_player)
			return infinity;
		else
			return -infinity;
	}

	if (is_draw)
		return 0;
	int AI_rating = EvaluatePlayer(board, computer_player);
	int opponent_rating = EvaluatePlayer(board, toggle_players(computer_player));

	return AI_rating - opponent_rating;
}

//------MiniMax AI Function------//
int miniMax(Board board, int depth, int alpha, int beta, char player_turn, char computer_player)
{
	boolean is_gg = False, is_draw = False;
	if ((is_gg = IsGameOver(board)) || depth == 0 || (is_draw = IsDraw(board)))
		// static evaluation
		return StaticEval(board, toggle_players(player_turn), computer_player, is_gg, is_draw);
	int min_eval, max_eval, eval;
	min_eval = infinity;
	max_eval = -infinity;
	for (int i = 1; i <= 9; i++)
	{
		VectorPos pos;
		pos_to_xy(i, board_size, &pos.col, &pos.row);
		if (board[pos.row][pos.col] == ' ')
		{
			if (player_turn == computer_player)
			{
				// if maximizing
				board[pos.row][pos.col] = player_turn;
				eval = miniMax(board, depth - 1, alpha, beta, toggle_players(player_turn), computer_player);
				board[pos.row][pos.col] = ' ';
				
				max_eval = max(eval, max_eval);
				//alpha = max(alpha, eval);
				//if(beta <= alpha)
				//	return
			}
			else
			{
				// if minimizing
				board[pos.row][pos.col] = player_turn;
				eval = miniMax(board, depth - 1, alpha, beta, toggle_players(player_turn), computer_player);
				board[pos.row][pos.col] = ' ';

				min_eval = min(eval, min_eval);
			}
		}
	}
	if (computer_player == player_turn)
		return max_eval;
	else 
		return min_eval;
}

//------Computer Best Move Function------//
VectorPos ComputerMove(Board board, int depth, char computer_player)
{	
	int rating, best_rating = -infinity;
	VectorPos move, best_move;
	for (int i = 1; i <= 9; i++)
	{
		pos_to_xy(i, board_size, &move.col, &move.row);
		if (board[move.row][move.col] == ' ')
		{
			board[move.row][move.col] = computer_player;
			rating = miniMax(board, depth, -infinity, infinity, toggle_players(computer_player), computer_player);
			board[move.row][move.col] = ' ';
			best_rating = max(best_rating, rating);
			if (rating == best_rating)
				best_move = move;
		}
	}
	return best_move;
}