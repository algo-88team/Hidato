# cmake_minimum_required(VERSION <specify CMake version here>)
project(Hidato)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hidato main.cpp Puzzle.cpp Puzzle.h Generator.cpp Generator.h Solver.cpp Solver.h CellGraph.cpp CellGraph.h)