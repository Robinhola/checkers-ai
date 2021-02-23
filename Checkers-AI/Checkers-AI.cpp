// Checkers-AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Board.h"
#include "Engine.h"

int main()
{
    std::cout << "Hello World!\n";

    std::cout << "Let's play!" << std::endl;

    Board board({ 8, 8 });
    // _#_#_#_#
    // #_#_#_#_
    // _#_#_#_#
    // ________
    // ________
    // +_+_+_+_
    // _+_+_+_+
    // +_+_+_+_
    board.placePiece(Board::Piece{ Coord{0, 0}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{2, 0}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{4, 0}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{6, 0}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{1, 1}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{3, 1}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{5, 1}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{7, 1}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{0, 2}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{2, 2}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{4, 2}, Color::WHITE });
    board.placePiece(Board::Piece{ Coord{6, 2}, Color::WHITE });

    board.placePiece(Board::Piece{ Coord{1, 7}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{3, 7}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{5, 7}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{7, 7}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{0, 6}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{2, 6}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{4, 6}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{6, 6}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{1, 5}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{3, 5}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{5, 5}, Color::BLACK });
    board.placePiece(Board::Piece{ Coord{7, 5}, Color::BLACK });

    Engine engine(&board);
    engine.play();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// Checkers AI -
// Game engine - needs to let players play the game
// AI needs to read the game and take decision to play it
//
// Game engine -> display a board, display pieces, let you move pieces

// https://en.wikipedia.org/wiki/Draughts

// Grid
// 0 1 0 1 0 1
