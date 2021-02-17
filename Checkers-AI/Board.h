#include <ostream>
#include <vector>


struct Coord {
	int x;
	int y;
};

inline bool operator==(const Coord& a, const Coord& b) {
	return a.x == b.x && a.y == b.y;
}


class Board
{
	using Line = std::vector<int>;
	using Grid = std::vector<Line>;

	Grid d_grid;
	
public:
	enum Direction {
		TLeft  = 0,
		TRight = 1,
		BLeft  = 2,
		BRight = 3,
	};

	struct BoardMove {
		// A move on the board is entirely characterised by the following data: 
		Coord     pieceCoord;
		Direction direction;
		int       value;
	};

	Board(Coord dimensions);

	Coord dimensions() const;

	const Grid& grid() const;

	bool MovePiece(BoardMove candidate);

	bool isMoveValid(BoardMove candidate);
};


inline std::ostream& operator<<(std::ostream& os, const Board& board) {
	const auto& grid = board.grid();

	for (auto lineIte = grid.begin(); lineIte != grid.end(); ++lineIte) {
		os << "\n|";

		for (auto ite = lineIte->begin(); ite != lineIte->end(); ++ite) {
			os << *ite << "|";
		}
	}

	return os << "\n";
}
