//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_SOLVER_H
#define HIDATO_SOLVER_H

#include "Puzzle.h"
#include <utility>

class Solver {
public:
	Puzzle & Solve(Puzzle &p, Puzzle &answer);
	int hidato_solve(int num, const int goal, int position_x, int position_y, Puzzle &p);
	int direction[8][2] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
	int Answer_checking(Puzzle& p, Puzzle &answer);
};

class Stack {
public:
	Stack();
	int pop();
	void push(int x, int y, int dir);
	bool empty();

private:
	int s[1000];
	int top;
};

#endif //HIDATO_SOLVER_H
