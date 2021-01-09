#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// minimus macro
#define min(a, b) (a) < (b) ? (a) : (b)
// maximum macro
#define max(a, b) (a) > (b) ? (a) : (b)
// switch between players macro
#define toggle_players(player) (player) == 'X' ? 'O' : 'X'

#define board_size 3
#define infinity 100000

// position on board
typedef struct VectorPos
{
	int row;
	int col;
};

// boolean variable definition in c
typedef	enum { False, True } boolean;

// board type varable
typedef char Board[board_size][board_size];