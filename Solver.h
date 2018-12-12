//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_SOLVER_H
#define HIDATO_SOLVER_H

#include "Puzzle.h"
#include <stack>
#include <utility>

class Solver {
public:
    Puzzle &Solve(Puzzle &p);
	int hidato_solve(int num, const int goal, int position_x, int position_y, Puzzle &p);
	int direction[8][2] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
};


#endif //HIDATO_SOLVER_H
