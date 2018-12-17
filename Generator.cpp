#include <random>

//
// Created by thdtj on 2018-11-21.
//

#include "Generator.h"
#include "Cell.h"

#include <random>
#include <algorithm>

#define GET(map, p) (map[p.y * width2 + p.x])

Generator::~Generator() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			direction[i][j].clear();
			std::vector<Point>().swap(direction[i][j]);
		}
		delete[] direction[i];
	}
	delete[] direction;

	startLoader.clear();
	std::vector<Point>().swap(startLoader);

	delete[] map;
}

Puzzle &Generator::Generate(Puzzle &puzzle, Puzzle& answer) {
	width = puzzle.getWidth();
	height = puzzle.getHeight();
	width2 = width + 2;
	height2 = height + 2;
	numCells = puzzle.getNumCells();

	//  Change empty cells from 1 to -1
	Invert(puzzle);

	//  Init map
	init_map(puzzle);

	//  Init random direction
	init_direction(puzzle);

	//  Init start
	Init_startLoader();

	bool result;
	do {
		if (startLoader.empty()) {
			std::cout << "There is no way." << std::endl;
		}

		result = Recursive(*startLoader.begin(), 1);
		startLoader.erase(startLoader.begin());
	} while (!result);

	copy_map(puzzle, true);

	std::cout << "Filled Puzzle" << std::endl << puzzle << std::endl;
	answer = puzzle;
	init_cellLoader();

	while (!cellLoader.empty()) {
		Point pos = *cellLoader.begin();
		cellLoader.erase(cellLoader.begin());
		int value = GET(map, pos);
		GET(map, pos) = -1;

		int lower = 0;
		int upper = numCells + 1;
		Point lowerPoint;
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				Point p(j, i);
				int v = GET(map, p);
				if (v < value) {
					if (v > lower) {
						lower = v;
						lowerPoint = p;
					}
				}
				else if (v < upper) {
					upper = v;
				}
			}
		}
		if (is_UniquePath(lower, upper, lowerPoint) != 1) {
			GET(map, pos) = value;
		}
	}

	copy_map(puzzle);
	return puzzle;
}

bool Generator::Recursive(Puzzle &puzzle, Point pos, int n) {
	if (n > puzzle.getNumEmptyCells()) {
		return true;
	}
	if (puzzle[pos] != -1) {
		return false;
	}
	puzzle[pos] = n;
	std::vector<Point> &dir = direction[pos.y][pos.x];
	for (int i = 0; i < 8; ++i) {
		if (Recursive(puzzle, pos + dir[i], n + 1)) {
			return true;
		}
	}
	puzzle[pos] = -1;
	return false;
}

bool Generator::Recursive(Point pos, int n) {
	if (n > numCells) {
		return true;
	}
	if (GET(map, pos) != -1) {
		return false;
	}
	GET(map, pos) = n;
	std::vector<Point> &dir = direction[pos.y][pos.x];
	for (int i = 0; i < 8; ++i) {
		if (Recursive(pos + dir[i], n + 1)) {
			return true;
		}
	}
	GET(map, pos) = -1;
	return false;
}

void Generator::Invert(Puzzle &puzzle) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			puzzle[i][j] *= -1;
		}
	}
	puzzle.setNumEmptyCells(puzzle.getNumCells());
}

void Generator::init_direction(const Puzzle &puzzle) {
	std::vector<Point> dir = { { 0,  -1 },
	{ 1,  -1 },
	{ 1,  0 },
	{ 1,  1 },
	{ 0,  1 },
	{ -1, 1 },
	{ -1, 0 },
	{ -1, -1 } };

	direction = new std::vector<Point> *[height];

	for (int i = 0; i < height; ++i) {
		direction[i] = new std::vector<Point>[width];
		for (int j = 0; j < width; ++j) {
			Point p = { j, i };
			if (puzzle[p] == -1) {
				std::vector<Point> shuffled(dir);
				std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937(std::random_device()()));
				direction[i][j].swap(shuffled);
			}
		}
	}
}

void Generator::init_map(const Puzzle &puzzle) {
	map = new int[(height2) * (width2)];
	for (int i = 0; i < height2; ++i) {
		for (int j = 0; j < width2; ++j) {
			map[i * (width2)+j] = puzzle[i - 1][j - 1];
		}
	}
	map = map + width2 + 1;
}

void Generator::Init_startLoader() {
	std::vector<Point> EmptyCells;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Point p(j, i);
			if (GET(map, p) == -1) {
				EmptyCells.emplace_back(p);
			}
		}
	}
	std::shuffle(EmptyCells.begin(), EmptyCells.end(), std::mt19937(std::random_device()()));
	startLoader.swap(EmptyCells);
}

void Generator::init_cellLoader() {
	std::vector<Point> FilledCells;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			Point p(j, i);
			if (1 < GET(map, p) && GET(map, p) < numCells) {
				FilledCells.emplace_back(p);
			}
		}
	}
	std::shuffle(FilledCells.begin(), FilledCells.end(), std::mt19937(std::random_device()()));
	cellLoader.swap(FilledCells);
}

Puzzle &Generator::copy_map(Puzzle &puzzle, bool stay) {
	map = map - width2 - 1;
	for (int i = 0; i < height2; ++i) {
		for (int j = 0; j < width2; ++j) {
			puzzle[i - 1][j - 1] = map[i * (width2)+j];
		}
	}
	if (stay) {
		map = map + width2 + 1;
	}
	return puzzle;
}

int Generator::is_UniquePath(int num, const int goal, Point pos) {
	std::vector<Point> &dir = direction[pos.y][pos.x];

	for (int i = 0; i < 8; i++) {
		Point next = pos + dir[i];
		if (GET(map, next) == num + 1) {
			if (num + 1 == goal) {
				return 1;
			}
			return is_UniquePath(num + 1, goal, next);
		}
	}

	if (num == goal - 1) {
		return 0;
	}

	int count = 0;

	for (int i = 0; i < 8; i++) {
		if (count > 1) {
			return count;
		}
		Point next = pos + dir[i];

		if (GET(map, next) == -1) {
			GET(map, next) = num + 1;
			count += is_UniquePath(num + 1, goal, next);
			GET(map, next) = -1;
		}
	}

	return count;
}

Puzzle &Generator::GenerateWithCellGraph(Puzzle &puzzle) {
	width = puzzle.getWidth();
	height = puzzle.getHeight();
	width2 = width + 2;
	height2 = height + 2;
	numCells = puzzle.getNumCells();

	//  Change empty cells from 1 to -1
	Invert(puzzle);

	//  Init map
	init_map(puzzle);

	//  Create CellGraph
	CellGraph graph(puzzle);

	//  Fill puzzle
	Puzzle *result;
	do {
		Cell *randCell = graph.getRandCell(1);
		if (randCell == nullptr) {
			std::cout << "There are no way" << std::endl;
			return puzzle;
		}
		randCell->setData(1);

		result = Fill(puzzle, graph, *randCell);

		if (result == nullptr) {
			randCell->eraseCandidate(1);
			graph.eraseRemainder(1, randCell);
			randCell->setData(-1);
		}
	} while (result == nullptr);

	puzzle = *result;

	//  Check puzzle
	int checker = 0;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			checker ^= puzzle[i][j];
		}
	}
	for (int n = 1; n < numCells + 1; ++n) {
		checker ^= n;
	}
	if (checker) {
		std::cout << "Fill failed." << std::endl;
		return puzzle;
	}
}

Puzzle *Generator::Fill(Puzzle puzzle, CellGraph graph, const Cell cell) {
	if (!Update(puzzle, graph, cell)) {
		return nullptr;
	}

	if (graph.is_finished()) {
		return new Puzzle(puzzle);
	}

	Puzzle *result;
	do {
		Cell *randCell = graph.getNextRandCell();

		if (randCell == nullptr) {
			//            std::cout << "There are no way " << graph.getRemaindersSetSize() << std::endl;
			return nullptr;
		}

		int n = randCell->getData();

		result = Fill(puzzle, graph, *randCell);

		if (result == nullptr) {
			randCell->eraseCandidate(n);
			graph.eraseRemainder(n, randCell);
			randCell->setData(-1);
		}
	} while (result == nullptr);

	return result;
}

bool Generator::Update(Puzzle &puzzle, CellGraph &graph, const Cell cell) {
	puzzle[cell.getPos()] = cell.getData();
	graph.eraseCell(graph[cell.getPos()]);
	graph.checkNeighbor(cell);

	if (graph.is_finished()) {
		return true;
	}

	if (!graph.checkMapping() || !graph.is_candidatesEmpty() || !graph.is_remaindersEmpty()) {
		return false;
	}

	Cell *pCell = graph.find_onlyCandidate();
	if (pCell == nullptr) {
		pCell = graph.find_onlyRemainder();
		if (pCell == nullptr) {
			return true;
		}
	}

	return Update(puzzle, graph, *pCell);
}
