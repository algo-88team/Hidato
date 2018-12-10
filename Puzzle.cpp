//
// Created by thdtj on 2018-11-21.
//

#include "Generator.h"
#include "Puzzle.h"
#include <string.h>

Puzzle::Puzzle() : width(0), height(0), map(nullptr), numCells(0), numEmptyCells(0) {};

Puzzle::Puzzle(int width, int height) : width(width), height(height), map(nullptr), numCells(0), numEmptyCells(0) {
    map = new int *[height + 2];

    for (int i = 0; i < height + 2; ++i) {
        map[i] = new int[width + 2];
    }

    memset(map[0], 0, (width + 2) * sizeof(int));
    memset(map[height + 2 - 1], 0, (width + 2) * sizeof(int));

    for (int i = 1; i < height + 1; ++i) {
        map[i][0] = 0;
        map[i][width + 1] = 0;
    }
}

Puzzle::Puzzle(const Puzzle &p) {
    width = p.width;
    height = p.height;
    numCells = p.numCells;
    numEmptyCells = p.numEmptyCells;

    if (width == 0 || height == 0 || p.map == nullptr) {
        map = nullptr;
        return;
    }

    map = new int *[height + 2];

    for (int i = 0; i < height + 2; ++i) {
        map[i] = new int[width + 2];
        memcpy(map[i], p.map[i], (width + 2) * sizeof(int));
    }
}


Puzzle::~Puzzle() {
    if (map != nullptr) {
        for (int i = 0; i < height + 2; ++i) {
            delete[] map[i];
        }
        delete[] map;
    }
}

int *Puzzle::operator[](int i) const {
    return map[i + 1] + 1;
}

int *Puzzle::operator[](int i) {
    return map[i + 1] + 1;
}

int Puzzle::operator[](const Point &p) const {
    return map[p.y+1][p.x+1];
}

int &Puzzle::operator[](const Point &p) {
    return map[p.y+1][p.x+1];
}

Puzzle &Puzzle::operator=(const Puzzle &p) {
    if (&p == this) {
        return *this;
    }

    if (map != nullptr) {
        for (int i = 0; i < height + 2; ++i) {
            delete[] map[i];
        }
        delete[] map;
    }

    width = p.width;
    height = p.height;
    numCells = p.numCells;
    numEmptyCells = p.numEmptyCells;

    if (width == 0 || height == 0 || p.map == nullptr) {
        map = nullptr;
        return *this;
    }

    map = new int *[height + 2];

    for (int i = 0; i < height + 2; ++i) {
        map[i] = new int[width + 2];
        memcpy(map[i], p.map[i], (width + 2) * sizeof(int));
    }

    return *this;
}

std::ostream &operator<<(std::ostream &o, const Puzzle &p) {
#ifdef PRINT_EDGE
    for (int i = -1; i < p.height+1; ++i) {
        for (int j = -1; j < p.width+1; ++j) {
            o << p[i][j] << " ";
        }
        o << std::endl;
    }
#else
    for (int i = 0; i < p.height; ++i) {
        for (int j = 0; j < p.width; ++j) {
            o << p[i][j] << " ";
        }
        o << std::endl;
    }
#endif
    return o;
}

std::istream &operator>>(std::istream &in, Puzzle &p) {
    int width, height;
    in >> width >> height;

    p = Puzzle(width, height);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            in >> p[i][j];
            if (p[i][j]) {
                ++p.numCells;
                if (p[i][j] < 0) {
                    ++p.numEmptyCells;
                }
            }
        }
    }

    return in;
}

Puzzle &Puzzle::LoadFormFile(const char *name) {
    if (map != nullptr) {
        for (int i = 0; i < height + 2; ++i) {
            delete[] map[i];
        }
        delete[] map;
    }

    std::ifstream in;

    in.open(name);
    if (in.fail()) {
        std::cerr << "file open error : " << name << std::endl;
        return *this;
    }

    in >> *this;

    return *this;
}

int Puzzle::getWidth() const {
    return width;
}

int Puzzle::getHeight() const {
    return height;
}

int Puzzle::getNumCells() const {
    return numCells;
}

int Puzzle::getNumEmptyCells() const {
    return numEmptyCells;
}

void Puzzle::setNumCells(int numCells) {
    Puzzle::numCells = numCells;
}

void Puzzle::setNumEmptyCells(int numEmptyCells) {
    Puzzle::numEmptyCells = numEmptyCells;
}

Point::Point(int x, int y) : x(x), y(y) {}
