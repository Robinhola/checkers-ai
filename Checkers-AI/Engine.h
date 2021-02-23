#pragma once

#include "Board.h"

#include <string>
#include <vector>

struct Score {
    int white;
    int black;
};

class Engine
{
    Board* d_board;
    Color  d_turn;
    
    std::vector<std::string> d_gridToDraw;

    void updateGridToDraw(const Board::BoardMoves& possibleMoves);

public:
    Engine(Board* board);

    int play();

    std::ostream& draw(std::ostream& os);
};
