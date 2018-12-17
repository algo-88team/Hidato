//
// Created by thdtj on 2018-11-21.
//

#include <iostream>

#include "Puzzle.h"
#include "Generator.h"
#include "Solver.h"
#include <string>

#define RANDOM_SEED (time(nullptr))

int main() {



	Generator generator;
	Solver solver;

	srand(static_cast<unsigned int>(RANDOM_SEED));

	for (int i = 0; i < 5; i++) {
		Puzzle puzzle, answer;

		std::string s = "input" + std::to_string(i) + ".txt";
		const char* c = s.c_str();
		std::cout << "--------------------- testcase " << i + 1 << " ---------------------" << std::endl;

		puzzle.LoadFormFile(c);

		std::cout << "Input puzzle" << std::endl;
		std::cout << puzzle << std::endl;

		std::cout << "Generated puzzle" << std::endl;
		std::cout << generator.Generate(puzzle, answer) << std::endl;

		std::cout << "Solved puzzle" << std::endl;
		std::cout << solver.Solve(puzzle, answer) << std::endl;

	}
	std::getchar();

	return 0;
}