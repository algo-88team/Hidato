//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_PUZZLE_H
#define HIDATO_PUZZLE_H

#include <iostream>
#include <fstream>

class Point {
public:
    Point() = default;

    explicit Point(int x, int y) : x(x), y(y) {};

    Point(const Point &p) = default;;

    virtual ~Point() = default;

    Point operator+(Point p) {
        return Point(x + p.x, y + p.y);
    }

    bool operator==(const Point &rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool operator!=(const Point &rhs) const {
        return !(rhs == *this);
    }

    int x;
    int y;
};

class Puzzle {
public:
    Puzzle();

    Puzzle(int width, int height);

    virtual ~Puzzle();

    int *operator[](int i) const;

    int *operator[](int i);

    int operator[](const Point &p) const;

    int &operator[](const Point &p);

    Puzzle &operator=(const Puzzle &p);

    friend std::ostream &operator<<(std::ostream &o, const Puzzle &p);

    friend std::istream &operator>>(std::istream &o, Puzzle &p);

    Puzzle &LoadFormFile(const char *name);

    int getWidth() const;

    int getHeight() const;

    int getNumCells() const;

    int getNumEmptyCells() const;

    void setNumCells(int numCells);

    void setNumEmptyCells(int numEmptyCells);

private:
    int width;
    int height;
    int **map;
    int numCells;
    int numEmptyCells;
};

#endif //HIDATO_PUZZLE_H
