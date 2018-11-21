//
// Created by thdtj on 2018-11-21.
//

#include <iostream>

#include "Puzzle.h"
#include "Generator.h"
#include "Solver.h"

int main() {
    Puzzle puzzle;
    Generator generator;
    Solver solver;

    puzzle.LoadFormFile("input.txt");

    std::cout << "Input puzzle" << std::endl;
    std::cout << puzzle << std::endl;

    std::cout << "Generated puzzle" << std::endl;
    std::cout << generator.Generate(puzzle) << std::endl;

    std::cout << "Solved puzzle" << std::endl;
    std::cout << solver.Solve(puzzle) << std::endl;

    return 0;
}