// Checkers-AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Board.test.h"

int main()
{
    std::cout << "Hello World!\n";

    std::cout << "Running tests\n";
    std::cout << "Test board: " << (testBoard() ? "SUCCESS" : "FAILURE") << std::endl;
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
