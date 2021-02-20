#include "Engine.h"

#include <iostream>

namespace {
    Color oppositeColor(Color color) {
        switch (color)
        {
        case Color::BLACK:
        case Color::BLACK_QUEEN:
            return Color::WHITE;
        case Color::WHITE:
        case Color::WHITE_QUEEN:
            return Color::BLACK;
        }
        return Color::NONE;
    }
}

Engine::Engine(Board* board)
    : d_board(board)
    , d_turn(Color::WHITE)
    , d_gridToDraw(board->dimensions().y)
{
    for (auto& line : d_gridToDraw) {
        line = std::string(board->dimensions().x, ' ');
    }
}

void displayTurn(Color color) {
    std::cout << "This is " << (color == Color::WHITE ? "White" : "Black") << "'s turn.\n";
}

void displayVictory(Score scores) {
    Color color = scores.white > scores.black ? Color::WHITE : Color::BLACK;

    std::cout << "Scores are:\n"
        << "\tWhite: " << scores.white << "\n"
        << "\tBlack: " << scores.black << "\n"
        << (color == Color::WHITE ? "White" : "Black") << " won!\n";
}

void displayMoves(const Board::BoardMoves& moves, const std::vector<std::string>& gridToDraw) {
    for (size_t i = 0; i < moves.size(); ++i) {
        int x = moves[i].pieceCoord.x;
        int y = moves[i].pieceCoord.y;
        std::cout << "Move " << gridToDraw[y][x] << " to " << moves[i].direction 
            << " [" << i << "]"
            << "\n";
    }
}

Score getScores(const Board& board) {
    int white = 0;
    int black = 0;

    for (auto& line : board.grid()) {
        for (Color color : line) {
            switch (color)
            {
            case Color::NONE:
                break;
            case Color::WHITE:
            case Color::WHITE_QUEEN:
                white++;
                break;
            case Color::BLACK:
            case Color::BLACK_QUEEN:
                black++;
                break;
            default:
                break;
            }
        }
    }
    return Score{ white, black };
}

int Engine::play()
{
    // while there are moves to be played
    // display player name, display moves, let user choose

    Board::BoardMoves possibleMoves = d_board->validMoves(d_turn);

    while (possibleMoves.size() > 0) {
        updateGridToDraw(possibleMoves);

        displayTurn(d_turn);
        displayMoves(possibleMoves, d_gridToDraw);
        draw(std::cout);

        int choice = -1;
        while (choice < 0 || int(possibleMoves.size()) <= choice) {
			std::cout << "Enter your choice (numbers only or -1 to quit): ";
			std::cin >> choice;

            if (choice == -1) return 0;
        }

        d_board->movePiece(possibleMoves[choice]);

        d_turn = oppositeColor(d_turn);
		possibleMoves = d_board->validMoves(d_turn);
    }

	updateGridToDraw(possibleMoves);
	draw(std::cout);

    displayVictory(getScores(*d_board));
    std::cout << "The end!" << std::endl;
    return 0;
}

void Engine::updateGridToDraw(const Board::BoardMoves& possibleMoves) {
    const auto& grid = d_board->grid();

    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[0].size(); ++x) {
            Color value = grid[y][x];
            char  sprite;

            switch (value)
            {
            case Color::NONE:
                sprite = ' ';
                break;
            case Color::WHITE:
            case Color::WHITE_QUEEN:
                sprite = '+';
                break;
            case Color::BLACK:
            case Color::BLACK_QUEEN:
                sprite = '-';
                break;
            default:
                sprite = '0';
                break;
            }

            d_gridToDraw[y][x] = sprite;
        }
    }

    // Sometimes, there can be multiple moves from the same coordonates
    for (int i = possibleMoves.size() - 1; i >= 0; --i) {
        auto& move = possibleMoves[i];
        int x = move.pieceCoord.x;
        int y = move.pieceCoord.y;
        d_gridToDraw[y][x] = '0' + i;
    }
}

std::ostream& Engine::draw(std::ostream& os)
{
	for (auto lineIte = d_gridToDraw.rbegin(); lineIte != d_gridToDraw.rend(); ++lineIte) {
		os << "\n|";

		for (auto ite = lineIte->begin(); ite != lineIte->end(); ++ite) {
			os << *ite << "|";
		}

		os << " - " << d_board->dimensions().y - 1 - int(lineIte - d_gridToDraw.rbegin());
	}

	os << "\n";
	for (int i = 0; i < d_board->dimensions().x; ++i) {
		os << " " << i;
	}

	return os << "\n\n";
}
