#include "Board.h"

#include <algorithm>
#include <vector>

namespace {

Coord directionToCoord(Board::Direction direction) {
	if (direction == Board::Direction::TRight) return {  1 ,  1 };
	if (direction == Board::Direction::TLeft)  return { -1 ,  1 };
	if (direction == Board::Direction::BRight) return {  1 , -1 };
	if (direction == Board::Direction::BLeft)  return { -1 , -1 };

	return { 0, 0 };
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

void AddIfValid(const Board& board, Board::Move&& move, Board::BoardMoves *container) {
	if (board.isMoveValid(move)) {
		container->push_back(move);
	}
}

} // End of Anonymous namespace

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

void Board::validMoves(Coord coord, BoardMoves *boardMoves) const
{
	// Whites are at the bottom -> they go to the top
	// Blacks are at the top    -> they go to the bottom
	std::vector<Board::Direction> validDirections;

	switch (grid(coord)) {
	case Color::NONE:
		return;
	case Color::BLACK:
		validDirections.emplace_back(Direction::BLeft);
		validDirections.emplace_back(Direction::BRight);
		break;
	case Color::WHITE:
		validDirections.emplace_back(Direction::TLeft);
		validDirections.emplace_back(Direction::TRight);
		break;
	case Color::BLACK_QUEEN:
		break;
	case Color::WHITE_QUEEN:
		break;
	default:
		break;
	}

	for (auto& d : validDirections) AddIfValid(*this, {coord, d, 2 }, boardMoves);
	for (auto& d : validDirections) AddIfValid(*this, {coord, d, 1 }, boardMoves);

	// Eating is mandatory so if there are any eat move, we remove the normal moves.
	if (std::any_of(boardMoves->begin(), boardMoves->end(), [](const Move& m) { return m.value > 1; })) {
		boardMoves->erase(
			std::remove_if(boardMoves->begin(),
						   boardMoves->end(),
				           [](const Move& m) { return m.value < 2; }
			),
			boardMoves->end()
		);
	}
}

Board::BoardMoves Board::validMoves(Coord coord) const
{
	BoardMoves moves;

	validMoves(coord, &moves);

	return std::move(moves);
}

Board::BoardMoves Board::validMoves(Color color) const
{
	BoardMoves moves;

	for (int x = 0; x < dimensions().x; ++x) {
		for (int y = 0; y < dimensions().y; ++y) {
			Coord c{ x, y };
			if (grid(c) == color) validMoves(c, &moves);
		}
	}

	return std::move(moves);
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

