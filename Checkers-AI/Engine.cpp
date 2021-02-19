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
{
}

void displayTurn(Color color) {
    std::cout << "This is " << (color == Color::WHITE ? "White" : "Black") << "'s turn.\n";
}

void displayMoves(const Board::BoardMoves& moves) {
    for (size_t i = 0; i < moves.size(); ++i) {
        std::cout << "Move " << moves[i].pieceCoord << " to " << moves[i].direction 
            << " [" << i << "]"
            << "\n";
    }
}

int Engine::play()
{
    // while there are moves to be played
    // display player name, display moves, let user choose

    Board::BoardMoves possibleMoves = d_board->validMoves(d_turn);

    
    std::cout << *d_board;

    while (possibleMoves.size() > 0) {
        displayTurn(d_turn);
        displayMoves(possibleMoves);

        int choice = -1;
        while (choice < 0 || int(possibleMoves.size()) <= choice) {
			std::cout << "Enter your choice (numbers only or -1 to quit): ";
			std::cin >> choice;

            if (choice == -1) return 0;
        }

        d_board->movePiece(possibleMoves[choice]);

        d_turn = oppositeColor(d_turn);
		possibleMoves = d_board->validMoves(d_turn);
		std::cout << *d_board;
    }

    std::cout << "The end!" << std::endl;
    return 0;
}
