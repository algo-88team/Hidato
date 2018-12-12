//
// Created by thdtj on 2018-12-13.
//

#ifndef HIDATO_CELL_H
#define HIDATO_CELL_H

#include <set>

#include "Puzzle.h"

class Cell {
public:
    Cell() : data(0), pos(0, 0) {}

    Cell(int data, const Point &p) : data(data), pos(p) {}

    Cell(int data, int x, int y) : data(data), pos(x, y) {}

    Cell(const Cell &c) = default;

    virtual ~Cell();

    int getData() const;

    void setData(int data);

    const Point &getPos() const;

    Cell &operator=(const Cell &c);

    void insertCandidate(int n);

    void eraseCandidate(int n);

    bool is_Neighbor(int x, int y);

    bool is_Neighbor(const Point &p);

    bool is_Neighbor(const Cell &c);

private:
    int data;
    Point pos;
    std::set<int> candidates;
};


#endif //HIDATO_CELL_H
