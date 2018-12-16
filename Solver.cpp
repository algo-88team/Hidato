//
// Created by thdtj on 2018-11-21.
//

#include "Solver.h"
#include <time.h>

Stack::Stack() {
	top = -1;
	for (int i = 0; i < 1000; i++)
		this->s[i] = 0;
}

int Stack::pop() {
	if (empty()) {
		return 0;
	}
	else {
		return s[top--];
	}
}

void Stack::push(int x, int y, int dir) {
	s[++top] = x;
	s[++top] = y;
	s[++top] = dir;
}

bool Stack::empty() {
	return (top == -1);
}

int Solver::hidato_solve(int num, const int goal, int position_x, int position_y, Puzzle& p) {
	//***************************** Recursive *********************************************
	if (num == goal)
		return 1;

	for (int i = 0; i < 8; i++) {
		int next_x = position_x + this->direction[i][0];
		int next_y = position_y + this->direction[i][1];
		if (next_x >= 0 && next_x < p.getWidth() && next_y >= 0 && next_y < p.getHeight() && p[next_y][next_x] == num + 1) {
			if (hidato_solve(num + 1, goal, next_x, next_y, p))
				return 1;
		}
	}

	for (int i = 0; i < 8; i++) {
		int next_x = position_x + this->direction[i][0];
		int next_y = position_y + this->direction[i][1];

		if (next_x >= 0 && next_x < p.getWidth() && next_y >= 0 && next_y < p.getHeight() && p[next_y][next_x] == -1) {

			p[next_y][next_x] = num + 1;

			if (hidato_solve(num + 1, goal, next_x, next_y, p))
				return 1;

			p[next_y][next_x] = -1;
		}
	}
	return 0;
	
	/********************************** Stack **********************************************
	Puzzle temp(p);
	Stack s;
	s.push(position_x, position_y, 0);
	int found = 0;
	while (!s.empty() && !found) {
		int dir = s.pop();
		int y = s.pop();
		int x = s.pop();

		while (dir < 8 && !found) {
			int next_x = x + this->direction[dir][0];
			int next_y = y + this->direction[dir][1];

			if (num == goal)
				found = 1;

			else if (next_x >= 0 && next_x < p.getWidth() &&
				next_y >= 0 && next_y < p.getHeight() &&
				(p[next_y][next_x] == num + 1 || p[next_y][next_x] == -1)) {
				if (p[next_y][next_x] == num + 1) { // if the next number exists
					s.push(x, y, ++dir);
					x = next_x; y = next_y; dir = 0;
					++num;
				}
				else {   // if blank
					p[next_y][next_x] = ++num;
					s.push(x, y, ++dir);
					x = next_x; y = next_y; dir = 0;
				}
			}
			else
				dir++;
		}
		p[y][x] = temp[y][x];
		num--;

	}

	return 0;
	*/
}

Puzzle &Solver::Solve(Puzzle &p) {
	// TODO
	int goal = -1;
	int position_x = 0, position_y = 0;

	// find goal, find start_point
	for (int i = 0; i < p.getHeight(); i++) {
		for (int j = 0; j < p.getWidth(); j++) {
			int temp = p[i][j];
			if (temp != 0) {
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

	clock_t begin = clock();
	hidato_solve(1, goal, position_x, position_y, p);
	clock_t end = clock();
	long msec1 = end - begin;
	std::cout << msec1 * 0.001 << " ÃÊ" << "\n";


	return p;
}