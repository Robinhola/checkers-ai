#include "Board.h"
#include "Board.test.h"

namespace {
	bool assert(bool condition) {
		_ASSERT(condition);
		return condition;
	}
}

bool testConstructBoard() {
	bool success = true;

	for (auto& d : { Coord{1,1}, Coord{10, 10}, Coord{2, 2}, Coord{8,8} }) {
		Board X(d);

		success &= assert(d == X.dimensions());
		success &= assert(X.grid().size() == d.y);
		success &= assert(X.grid()[0].size() == d.x);
	}

	return success;
}

bool testIsMoveValid() {
	bool success = true;

	Board X{ {8, 8} };

	X.placePiece({ {1, 1}, Color::WHITE });

	// Valid
	success &= assert(X.isMoveValid(Board::Move{ {1, 1}, Board::Direction::TLeft,  1}));
	success &= assert(X.isMoveValid(Board::Move{ {1, 1}, Board::Direction::TRight, 1}));

	// Invalid
	success &= assert(!X.isMoveValid(Board::Move{ {1, 1}, Board::Direction::BLeft,  1}));
	success &= assert(!X.isMoveValid(Board::Move{ {1, 1}, Board::Direction::BRight, 1}));
	success &= assert(!X.isMoveValid(Board::Move{ {1, 1}, Board::Direction::TRight, 2}));
	success &= assert(!X.isMoveValid(Board::Move{ {1, 1}, Board::Direction::TRight, 3}));
	success &= assert(!X.isMoveValid(Board::Move{ {1, 1}, Board::Direction::TLeft,  2}));
	success &= assert(!X.isMoveValid(Board::Move{ {1, 1}, Board::Direction::TLeft,  3}));

	// We add a Black piece:
	X.placePiece({ {2, 2}, Color::BLACK });

	// Capturing is mandatory but this will only be reflected in the `validMoves` method
	Board::BoardMoves moves;
	Board::Move expected{ { 1, 1 }, Board::Direction::TRight, 2 };

	X.validMoves({ 1, 1 }, &moves);
	success &= assert(moves.size() == 1);
	success &= assert(moves[0] == expected);

	// We add a white piece instead:
	X.placePiece({ {2, 2}, Color::WHITE });

	// Now the piece can only move left
	moves.clear();
	expected = { { 1, 1 }, Board::Direction::TLeft, 1 };

	X.validMoves({ 1, 1 }, &moves);
	success &= assert(moves.size() == 1);
	success &= assert(moves[0] == expected);

	return success;
}

bool testSimpleMovePieces() {
	bool success = true;

	Board X(Coord{ 8, 8 });

	X.placePiece({ { 0, 0 }, Color::WHITE });

	success &= assert(X.grid({ 0, 0 }) == Color::WHITE);

	// FIRST MOVE
	Board::BoardMoves moves;
	X.validMoves({ 0, 0 }, &moves);

	Board::Move expectedFirstMove{ { 0, 0 }, Board::Direction::TRight, 1 };

	success &= assert(moves.size() == 1);
	success &= assert(moves[0] == expectedFirstMove);

	bool firstMoveResult = X.movePiece(expectedFirstMove);

	success &= assert(firstMoveResult);
	success &= assert(X.grid({ 0, 0 }) == Color::NONE);
	success &= assert(X.grid({ 1, 1 }) == Color::WHITE);

	// SECOND MOVE
	moves.clear();
	X.validMoves({ 1, 1 }, &moves);

	Board::BoardMoves expectedSecondMoves{
		{ { 1, 1 }, Board::Direction::TLeft,  1 },
		{ { 1, 1 }, Board::Direction::TRight, 1 },
	};

	success &= assert(moves.size() == 2);
	success &= assert(moves == expectedSecondMoves);

	bool SecondMoveResult = X.movePiece(expectedSecondMoves[0]);

	success &= assert(SecondMoveResult);
	success &= assert(X.grid({ 0, 0 }) == Color::NONE);
	success &= assert(X.grid({ 1, 1 }) == Color::NONE);
	success &= assert(X.grid({ 0, 2 }) == Color::WHITE);

	return success;
}

bool testBoard() {
	bool success = true;

	success &= testConstructBoard();
	success &= testIsMoveValid();
	success &= testSimpleMovePieces();

	return success;
}