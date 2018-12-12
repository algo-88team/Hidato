//
// Created by thdtj on 2018-12-10.
//

#ifndef HIDATO_CELLGRAPH_H
#define HIDATO_CELLGRAPH_H

#include <vector>
#include <set>
#include <map>

#include "Puzzle.h"

class Cell {
public:
    Cell() = default;

    Cell(int data, const Point &p) : data(data), pos(p) {}

    Cell(int data, int x, int y) : data(data), pos(x, y) {}

    Cell(const Cell &c) : data(c.data), pos(c.pos), candidate(c.candidate) {}

    virtual ~Cell();

    int getData() const;

    void setData(int data);

    const Point &getPos() const;

    Cell &operator=(const Cell &c);

    void insertCandidate(int n);

    void eraseCandidate(int n);

private:
    int data;
    Point pos;
    std::set<int> candidates;
};

class CellGraph {
public:
    CellGraph() : width(0), height(0), map(nullptr) {}

    CellGraph(const Puzzle &puzzle);

    CellGraph(const CellGraph &cg);

    virtual ~CellGraph();

    Cell **operator[](int i) const;

    Cell **operator[](int i);

    Cell *operator[](const Point &p) const;

    Cell *&operator[](const Point &p);

    CellGraph &operator=(const CellGraph &cg);

private:
    int width;
    int height;

    Cell ***map;
    std::vector<Cell> cells;
    std::map<int, std::set<Cell *>> remainders;
};


#endif //HIDATO_CELLGRAPH_H
