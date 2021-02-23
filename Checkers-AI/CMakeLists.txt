cmake_minimum_required(VERSION 3.10)

# set the project name
project(Checkers-ai)

# add the executable
add_executable(Checkers-ai
    Board.cpp
    Board.test.cpp
    Checkers-AI.cpp
    Engine.cpp
)