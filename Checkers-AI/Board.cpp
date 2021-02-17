#include "Board.h"


Board::Board(Coord dimensions)
: d_grid(dimensions.y)
{
	for (auto& line: d_grid) {
		line.assign(dimensions.x, 0);
	}
}

Coord Board::dimensions() const {
	return {
		int(d_grid[0].size()),
		int(d_grid.size()),
	};
}

const Board::Grid& Board::grid() const {
	return d_grid;
}

bool Board::MovePiece(BoardMove candidate) {
	// TO BE IMPLEMENTED
	return false;
}

bool Board::isMoveValid(BoardMove candidate) {
	// TO BE IMPLEMENTED
	return false;
}
