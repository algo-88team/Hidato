//
// Created by thdtj on 2018-11-21.
//

#include "Solver.h"
#include <time.h>
int Solver::hidato_solve(int num, const int goal, int position_x, int position_y, Puzzle& p) {
	/***************************** Recursive *********************************************/
	if (num == goal)
		return 1;

	for (int i = 0; i < 8; i++) {
		int next_x = position_x + this->direction[i][0];
		int next_y = position_y + this->direction[i][1];
		if (next_x >= 0 && next_x < p.getWidth() && next_y >= 0 && next_y < p.getHeight() && p[next_y][next_x] == num + 1) {
			if (p[next_y][next_x] == num + 1) {
				if (hidato_solve(num + 1, goal, next_x, next_y, p))
					return 1;
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		int next_x = position_x + this->direction[i][0];
		int next_y = position_y + this->direction[i][1];

		if (next_x >= 0 && next_x < p.getWidth() && next_y >= 0 && next_y < p.getHeight() && p[next_y][next_x] == 0) {
			
			p[next_y][next_x] = num + 1;

			if (hidato_solve(num + 1, goal, next_x, next_y, p))
				return 1;

			p[next_y][next_x] = 0;	
		}
	}
	
	/********************************** Stack **********************************************
	Puzzle temp(p);
	std::stack<int> s;
	s.push(position_x); s.push(position_y); s.push(0);
	int found = 0;
	while (!s.empty() && !found) {
		int dir = s.top(); s.pop();
		int y = s.top(); s.pop();
		int x = s.top(); s.pop();

		while (dir < 8 && !found) {
			int next_x = x + this->direction[dir][0];
			int next_y = y + this->direction[dir][1];

			if (num == goal)
				found = 1;

			else if (next_x >= 0 && next_x < p.getWidth() && 
					 next_y >= 0 && next_y < p.getHeight() && 
					 (p[next_y][next_x] == num + 1 || p[next_y][next_x] == 0)) {
				if (p[next_y][next_x] == num + 1) {
					s.push(x); s.push(y); s.push(++dir);
					x = next_x; y = next_y; dir = 0;
					++num;
				}
				else {
					p[next_y][next_x] = ++num;
					s.push(x); s.push(y); s.push(++dir);
					x = next_x; y = next_y; dir = 0;
				}
			}
			else
				dir++;
		}
		p[y][x] = temp[y][x];
		num--;

	}
	*/
	return 0;
}

Puzzle &Solver::Solve(Puzzle &p) {
    // TODO
	int goal = 0;
	int position_x = 0, position_y = 0;
	
	// find goal, find start_point
	for (int i = 0; i < p.getHeight(); i++) {
		for (int j = 0; j < p.getWidth(); j++) {
			int temp = p[i][j];
			if (temp != -1) {
				if (temp > goal)
					goal = temp;
				if (temp == 1) {
					position_x = j;
					position_y = i;
				}
			}
		}
	}

	//std::cout << goal << std::endl << position_x << " " << position_y << std::endl;
	// solve_program
	hidato_solve(1, goal, position_x, position_y, p);
	
    return p;
}
