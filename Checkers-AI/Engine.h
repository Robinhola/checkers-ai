#pragma once

#include "Board.h"

class Engine
{
	Board* d_board;
	Color  d_turn;
public:
	Engine(Board* board);

	int play();
};

