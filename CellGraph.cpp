//
// Created by thdtj on 2018-12-10.
//

#include "CellGraph.h"

Cell::~Cell() {
    candidate.clear();
    std::set<int>().swap(candidate);
}

int Cell::getData() const {
    return data;
}

void Cell::setData(int data) {
    Cell::data = data;
}

const Point &Cell::getPos() const {
    return pos;
}

Cell &Cell::operator=(const Cell &c) {
    data = c.data;
    pos = c.pos;
    candidate.clear();
    candidate = c.candidate;
    return *this;
}


CellGraph::CellGraph(const Puzzle &puzzle) {
    width = puzzle.getWidth();
    height = puzzle.getHeight();

    //  Allocate map
    map = new Cell **[height + 2];
    for (int i = 0; i < height + 2; ++i) {
        map[i] = new Cell *[width + 2];
        for (int j = 0; j < width + 2; ++j) {
            map[i][j] = nullptr;
        }
    }

    //  Initialize remainders
    for (int n = 1; n < puzzle.getNumCells() + 1; ++n) {
        remainders.insert(n);
    }

    //  Create Cells
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (puzzle[i][j] < 0) {
                (*this)[i][j] = &*cells.emplace(cells.end(), puzzle[i][j], j, i);
            } else if (puzzle[i][j] > 0) {
                remainders.erase(puzzle[i][j]);
            }
        }
    }
}

CellGraph::CellGraph(const CellGraph &cg) : width(cg.width), height(cg.height), cells(cg.cells),
                                            remainders(cg.remainders) {

    //  Allocate map
    map = new Cell **[height + 2];
    for (int i = 0; i < height + 2; ++i) {
        map[i] = new Cell *[width + 2];
        for (int j = 0; j < width + 2; ++j) {
            map[i][j] = nullptr;
        }
    }

    //  Mapping map
    for (auto &cell : cells) {
        (*this)[cell.getPos()] = &cell;
    }
}

CellGraph::~CellGraph() {
    cells.clear();
    std::vector<Cell>().swap(cells);
    remainders.clear();
    std::set<int>().swap(remainders);

    if (map != nullptr) {
        for (int i = 0; i < height + 2; ++i) {
            delete[] map[i];
        }
        delete[] map;
    }
}

Cell **CellGraph::operator[](int i) const {
    return map[i + 1];
}

Cell **CellGraph::operator[](int i) {
    return map[i + 1];
}

Cell *CellGraph::operator[](const Point &p) const {
    return map[p.y + 1][p.x + 1];
}

Cell *&CellGraph::operator[](const Point &p) {
    return map[p.y + 1][p.x + 1];
}

CellGraph &CellGraph::operator=(const CellGraph &cg) {
    cells.clear();
    remainders.clear();

    if (map != nullptr) {
        for (int i = 0; i < height + 2; ++i) {
            delete[] map[i];
        }
        delete[] map;
    }

    width = cg.width;
    height = cg.height;
    cells = cg.cells;
    remainders = cg.remainders;


    //  Allocate map
    map = new Cell **[height + 2];
    for (int i = 0; i < height + 2; ++i) {
        map[i] = new Cell *[width + 2];
        for (int j = 0; j < width + 2; ++j) {
            map[i][j] = nullptr;
        }
    }

    //  Mapping map
    for (auto &cell : cells) {
        (*this)[cell.getPos()] = &cell;
    }


    return *this;
}
