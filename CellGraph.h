//
// Created by thdtj on 2018-12-10.
//

#ifndef HIDATO_CELLGRAPH_H
#define HIDATO_CELLGRAPH_H

#include <vector>
#include <set>
#include <map>

#include "Puzzle.h"
#include "Cell.h"

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

    Cell *getRandCell(int n) const;

    Cell *getNextRandCell() const;

    int getRemaindersSetSize();

    void eraseRemainder(int n, Cell *pCell);

    void eraseRemainders(int n);

    void eraseCell(Cell *pCell);

    void checkNeighbor(const Cell &c);

    bool checkMapping();

    bool is_candidatesEmpty();

    bool is_remaindersEmpty();

    bool is_finished();

    Cell *find_onlyCandidate();

    Cell *find_onlyRemainder();

private:
    int width;
    int height;

    Cell ***map;
    std::vector<Cell *> cells;
    std::map<int, std::set<Cell *>> remaindersSet;
};


#endif //HIDATO_CELLGRAPH_H
