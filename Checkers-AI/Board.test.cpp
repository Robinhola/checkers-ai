#include "Board.h"
#include "Board.test.h"


bool testConstructBoard() {

	for (auto& d : { Coord{1,1}, Coord{10, 10}, Coord{2, 2}, Coord{8,8} }) {
		Board X(d);

		_ASSERT(d == X.dimensions());
		_ASSERT(X.grid().size() == d.y);
		_ASSERT(X.grid()[0].size() == d.x);
	}

	return true;
}

bool testBoard() {
	return testConstructBoard();
}