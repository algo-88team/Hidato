//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_GENERATOR_H
#define HIDATO_GENERATOR_H


#include "Puzzle.h"
#include "CellGraph.h"

class Generator {
public:
	Generator() : width(0), height(0), numCells(0) {}
	Puzzle &Generate(Puzzle &puzzle, Puzzle& answer);
	Puzzle &GenerateWithCellGraph(Puzzle &puzzle);

	virtual ~Generator();

private:
	int width;
	int height;
	int width2;
	int height2;
	int numCells;

	int *map;

	std::vector<Point> startLoader;
	std::vector<Point> cellLoader;
	std::vector<Point> **direction;

	void init_direction(const Puzzle &puzzle);

	void init_map(const Puzzle &puzzle);

	void Init_startLoader();

	void init_cellLoader();


    bool Recursive(Point pos, int n);

	Puzzle &copy_map(Puzzle &puzzle, bool stay = false);

	void Invert(Puzzle &puzzle);

	int is_UniquePath(int num, const int goal, Point pos);

	Puzzle *Fill(Puzzle puzzle, CellGraph graph, const Cell cell);

	bool Update(Puzzle &puzzle, CellGraph &graph, const Cell cell);
};


#endif //HIDATO_GENERATOR_H
