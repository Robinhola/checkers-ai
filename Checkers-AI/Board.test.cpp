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

bool testSimpleMovePieces() {
	Board X(Coord{ 8, 8 });

	X.placePiece({ { 0, 0 }, Color::BLACK });

	_ASSERT(X.grid({ 0, 0 }) == Color::BLACK);

	// FIRST MOVE
	Board::BoardMoves moves;
	X.validMoves({ 0, 0 }, &moves);

	Board::Move expectedFirstMove{ { 0, 0 }, Board::Direction::TRight, 1 };

	_ASSERT(moves.size() == 1);
	_ASSERT(moves[0] == expectedFirstMove);

	bool firstMoveResult = X.movePiece(expectedFirstMove);

	_ASSERT(firstMoveResult);
	_ASSERT(X.grid({ 0, 0 }) == Color::NONE);
	_ASSERT(X.grid({ 1, 1 }) == Color::BLACK);

	// SECOND MOVE
	moves.clear();
	X.validMoves({ 1, 1 }, &moves);

	Board::BoardMoves expectedSecondMoves{
		{ { 1, 1 }, Board::Direction::TLeft,  1 },
		{ { 1, 1 }, Board::Direction::TRight, 1 },
	};

	_ASSERT(moves.size() == 2);
	_ASSERT(moves == expectedSecondMoves);

	bool SecondMoveResult = X.movePiece(expectedSecondMoves[0]);

	_ASSERT(SecondMoveResult);
	_ASSERT(X.grid({ 0, 0 }) == Color::NONE);
	_ASSERT(X.grid({ 1, 1 }) == Color::NONE);
	_ASSERT(X.grid({ 0, 2 }) == Color::BLACK);

	return true;
}


bool testBoard() {
	bool success = true;

	success &= testConstructBoard();
	success &= testSimpleMovePieces();

	return success;
}