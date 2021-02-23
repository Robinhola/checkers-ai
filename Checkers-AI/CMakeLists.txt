cmake_minimum_required(VERSION 3.10)

set(SOURCES
    Board.cpp
    Board.test.cpp
    Engine.cpp
)

project(Checkers-ai)
add_executable(Checkers-ai Checkers-AI.cpp ${SOURCES})

set(TESTSOURCES
    Board.test.cpp
)

project(tests)
add_executable(tests Checkers-AI.test.cpp ${SOURCES} ${TESTSOURCES})