#pragma once
#include "Includes.h"

//------Important Functions From Engine------//

void pos_to_xy(int pos, int board_width, int *x, int *y);

boolean IsGameOver(Board board);

boolean IsDraw(Board board);

VectorPos ComputerMove(Board board, int depth, char computer_player);