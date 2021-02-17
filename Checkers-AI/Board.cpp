#include "Board.h"

#include <vector>


Board::Board(Coord dimensions)
: d_grid(dimensions.y)
{
	for (auto& line: d_grid) {
		line.assign(dimensions.x, Color::NONE);
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

Color Board::grid(Coord position) const
{
	return d_grid[position.y][position.x];
}

Coord directionToCoord(Board::Direction direction) {
	if (direction == Board::Direction::TRight) return {  1 ,  1 };
	if (direction == Board::Direction::TLeft)  return { -1 ,  1 };
	if (direction == Board::Direction::BRight) return {  1 , -1 };
	if (direction == Board::Direction::BLeft)  return { -1 , -1 };

	_ASSERT(false);
}

std::vector<Coord> generatePath(Board::Move move) {
	// Does not include neither the start nor the end
	std::vector<Coord> path;

	Coord coeff = directionToCoord(move.direction);

	for (int i = 1; i < move.value; ++i) {
		path.emplace_back(move.pieceCoord + i * coeff);
	}

	return path;
}

Coord findDestination(Board::Move move) {
	Coord toAdd = directionToCoord(move.direction);

	return move.pieceCoord + (toAdd * move.value);
}

bool inBound(const Board& board, Coord destination) {
	return 0 <= destination.x && destination.x < board.dimensions().x &&
	       0 <= destination.y && destination.y < board.dimensions().y;
}

bool Board::isMoveValid(Move candidate) const {
	Color candidateColor = grid(candidate.pieceCoord);
	Coord destination    = findDestination(candidate);

	if (!inBound(*this, destination) || grid(destination) != Color::NONE) {
		return false;
	}

	bool isValid = true;

	if (candidateColor == Color::BLACK) {
		isValid &= candidate.direction == Direction::BLeft ||
			       candidate.direction == Direction::BRight;
	}

	if (candidateColor == Color::WHITE) {
		isValid &= candidate.direction == Direction::TLeft ||
			       candidate.direction == Direction::TRight;
	}

	for (auto& p : generatePath(candidate)) {
		isValid &= areOppositeColor(candidateColor, grid(p));
	}

	return isValid;
}

void AddIfValid(const Board& board, Board::Move&& move, Board::BoardMoves *container) {
	if (board.isMoveValid(move)) {
		container->push_back(move);
	}
}

void Board::validMoves(Coord coord, BoardMoves *boardMoves) const
{
	// Whites are at the bottom -> they go to the top
	// Blacks are at the top    -> they go to the bottom

	switch (grid(coord)) {
	case Color::NONE:
		return;
	case Color::BLACK:
		AddIfValid(*this, {coord, Direction::BLeft,  1 }, boardMoves);
		AddIfValid(*this, {coord, Direction::BLeft,  2 }, boardMoves);
		AddIfValid(*this, {coord, Direction::BRight, 1 }, boardMoves);
		AddIfValid(*this, {coord, Direction::BRight, 2 }, boardMoves);
		break;
	case Color::WHITE:
		AddIfValid(*this, {coord, Direction::TLeft,  1 }, boardMoves);
		AddIfValid(*this, {coord, Direction::TLeft,  2 }, boardMoves);
		AddIfValid(*this, {coord, Direction::TRight, 1 }, boardMoves);
		AddIfValid(*this, {coord, Direction::TRight, 2 }, boardMoves);
		break;
	case Color::BLACK_QUEEN:
		break;
	case Color::WHITE_QUEEN:
		break;
	default:
		break;
	}
}

void Board::placePiece(Board::Piece piece) {
	Coord c = piece.coord;
	d_grid[c.y][c.x] = piece.color;
}

bool Board::movePiece(Move candidate) {
	if (!isMoveValid(candidate)) {
		return false;
	}

	Color candidateColor = grid(candidate.pieceCoord);
	Coord destination    = findDestination(candidate);
	
	placePiece({ candidate.pieceCoord, Color::NONE });

	for (auto& p : generatePath(candidate)) {
		placePiece({ p, Color::NONE });
	}

	placePiece({ destination, candidateColor });

	return true;
}

