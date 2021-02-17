#include <ostream>
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

enum class Color {
	NONE  = 0,
	BLACK = 1,
	WHITE = 2,
	BLACK_QUEEN = 8,
	WHITE_QUEEN = 9,
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

	void placePiece(Piece);

	bool movePiece(Move candidate);
};


inline bool operator==(const Board::Move& a, const Board::Move& b) {
	return a.pieceCoord == b.pieceCoord &&
		   a.direction  == b.direction &&
		   a.value      == b.value;
}


inline std::ostream& operator<<(std::ostream& os, const Board& board) {
	const auto& grid = board.grid();

	for (auto lineIte = grid.begin(); lineIte != grid.end(); ++lineIte) {
		os << "\n|";

		for (auto ite = lineIte->begin(); ite != lineIte->end(); ++ite) {
			os << int(*ite) << "|";
		}
	}

	return os << "\n";
}
