#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <ostream>
#include <string>
#include <vector>


struct Coord {
	int x;
	int y;
};

inline bool operator==(const Coord& a, const Coord& b) {
	return a.x == b.x && a.y == b.y;
}

inline Coord operator+(const Coord& a, const Coord& b) {
	return {a.x + b.x , a.y + b.y};
}

inline Coord operator*(const Coord& a, int v) {
	return {a.x * v , a.y * v};
}

inline Coord operator*(int v, const Coord& a) {
	return {a.x * v , a.y * v};
}

inline std::ostream& operator<<(std::ostream& os, const Coord& coord) {
	return os << "(" << coord.x << ", " << coord.y << ")";
}

enum class Color {
	NONE  = 0,
	WHITE = 1,
	BLACK = 2,
	WHITE_QUEEN = 8,
	BLACK_QUEEN = 9,
};

inline bool areOppositeColor(Color a, Color b) {
	switch (a)
	{
	case Color::NONE:
		return false;

	case Color::BLACK:
	case Color::BLACK_QUEEN:
		return b == Color::WHITE || b == Color::WHITE_QUEEN;

	case Color::WHITE:
	case Color::WHITE_QUEEN:
		return b == Color::BLACK || b == Color::BLACK_QUEEN;
	}

	_ASSERT(false);
	return false;
}

class Board
{
	using Line = std::vector<Color>;
	using Grid = std::vector<Line>;

	Grid d_grid;
	
public:
	enum class Direction {
		TLeft  = 0,
		TRight = 1,
		BLeft  = 2,
		BRight = 3,
	};

	struct Move {
		// A move on the board is entirely characterised by the following data: 
		Coord     pieceCoord;
		Direction direction;
		int       value;
	};

	using BoardMoves = std::vector<Move>;

	struct Piece {
		// Likewise, a piece is entirely characterised by:
		Coord coord;
		Color color;
	};

	Board(Coord dimensions);

	Coord dimensions() const;

	const Grid& grid() const;
	Color grid(Coord position) const;

	bool isMoveValid(Move candidate) const;

	void validMoves(Coord coord, BoardMoves *boardMoves) const;
	BoardMoves validMoves(Coord coord) const;
	BoardMoves validMoves(Color color) const;

	void placePiece(Piece);

	bool movePiece(Move candidate);
};

inline std::ostream& operator<<(std::ostream& os, const Board::Direction& direction) {
	switch (direction)
	{
	case Board::Direction::TLeft:
		return os << "NW";
	case Board::Direction::TRight:
		return os << "NE";
	case Board::Direction::BLeft:
		return os << "SW";
	case Board::Direction::BRight:
		return os << "SE";
	}
	return os;
}

inline bool operator==(const Board::Move& a, const Board::Move& b) {
	return a.pieceCoord == b.pieceCoord &&
		   a.direction  == b.direction &&
		   a.value      == b.value;
}


inline std::ostream& operator<<(std::ostream& os, const Board& board) {
	const auto& grid = board.grid();

	for (auto lineIte = grid.rbegin(); lineIte != grid.rend(); ++lineIte) {
		os << "\n|";

		for (auto ite = lineIte->begin(); ite != lineIte->end(); ++ite) {
			if (*ite == Color::NONE) {
				os << " ";
			}
			else {
				os << int(*ite);
			}

			os << "|";
		}

		os << " - " << board.dimensions().y - 1 - int(lineIte - grid.rbegin());
	}

	os << "\n";
	for (int i = 0; i < board.dimensions().x; ++i) {
		os << " " << i;
	}

	return os << "\n\n";
}

#endif
