//
// Created by thdtj on 2018-12-10.
//

#include "CellGraph.h"
#include <random>
#include <time.h>

Cell::~Cell() {
    candidates.clear();
    std::set<int>().swap(candidates);
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
    candidates.clear();
    candidates = c.candidates;
    return *this;
}

void Cell::insertCandidate(int n) {
    candidates.insert(n);
}

void Cell::eraseCandidate(int n) {
    candidates.erase(n);
}

bool Cell::is_Neighbor(int x, int y) {
    return abs(pos.x - x) + abs(pos.y - y) <= 1;
}

bool Cell::is_Neighbor(const Point &p) {
    return abs(pos.x - p.x) + abs(pos.y - p.y) <= 1;
}

bool Cell::is_Neighbor(const Cell &c) {
    return abs(pos.x - c.pos.x) + abs(pos.y - c.pos.y) <= 1;
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
        remainders.insert(std::pair<int, std::set<Cell *>>(n, std::set<Cell *>()));
    }

    //  Create Cells
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value = puzzle[i][j];
            auto &p = (*this)[i][j];
            if (value < 0) {
                p = new Cell(value, j, i);
                cells.emplace_back(p);

                for (auto &remainder : remainders) {
                    remainder.second.insert(p);
                    p->insertCandidate(remainder.first);
                }
            } else if (value > 0) {
                auto &remainder = remainders.find(value)->second;
                remainder.clear();
                std::set<Cell *>().swap(remainder);
                remainders.erase(value);

                int prevValue = value - 1;
                int nextValue = value + 1;

                auto &prevCells = remainders.find(prevValue)->second;
                for (auto &prevCell : prevCells) {
                    if (!prevCell->is_Neighbor(j, i)) {
                        prevCell->eraseCandidate(prevValue);
                    }
                }

                auto &nextCells = remainders.find(nextValue)->second;
                for (auto &nextCell : nextCells) {
                    if (!nextCell->is_Neighbor(j, i)) {
                        nextCell->eraseCandidate(nextValue);
                    }
                }

            }
        }
    }
}

CellGraph::CellGraph(const CellGraph &cg) : width(cg.width), height(cg.height), cells(cg.cells) {

    //  Allocate map
    map = new Cell **[height + 2];
    for (int i = 0; i < height + 2; ++i) {
        map[i] = new Cell *[width + 2];
        for (int j = 0; j < width + 2; ++j) {
            map[i][j] = cg.map[i][j] == nullptr ? nullptr : new Cell(*cg.map[i][j]);
        }
    }

    //  Mapping cells
    for (auto &cell : cells) {
        cell = (*this)[cell->getPos()];
    }

    //  Mapping remainders
    for (auto &cgRemainder : cg.remainders) {
        std::pair<std::map<int, std::set<Cell *>>::iterator, bool> remainder = remainders.insert(std::pair<int, std::set<Cell *>>(cgRemainder.first, std::set<Cell *>()));
        for (auto &iter : cgRemainder.second) {
            remainder.first->second.insert((*this)[iter->getPos()]);
        }
    }
}

CellGraph::~CellGraph() {
    cells.clear();
    std::vector<Cell *>().swap(cells);

    for (auto &remainder : remainders) {
        remainder.second.clear();
        std::set<Cell *>().swap(remainder.second);
    }
    remainders.clear();
    std::map<int, std::set<Cell *>>().swap(remainders);

    if (map != nullptr) {
        for (int i = 0; i < height + 2; ++i) {
            for (int j = 0; j < width + 2; ++j) {
                if (map[i][j] != nullptr) {
                    delete map[i][j];
                }
            }
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

    for (auto &remainder : remainders) {
        remainder.second.clear();
        std::set<Cell *>().swap(remainder.second);
    }
    remainders.clear();

    if (map != nullptr) {
        for (int i = 0; i < height + 2; ++i) {
            for (int j = 0; j < width + 2; ++j) {
                if (map[i][j] != nullptr) {
                    delete map[i][j];
                }
            }
            delete[] map[i];
        }
        delete[] map;
    }

    width = cg.width;
    height = cg.height;
    cells = cg.cells;


    //  Allocate map
    map = new Cell **[height + 2];
    for (int i = 0; i < height + 2; ++i) {
        map[i] = new Cell *[width + 2];
        for (int j = 0; j < width + 2; ++j) {
            map[i][j] = cg.map[i][j] == nullptr ? nullptr : new Cell(*cg.map[i][j]);
        }
    }

    //  Mapping cells
    for (auto &cell : cells) {
        cell = (*this)[cell->getPos()];
    }

    //  Mapping remainders
    for (auto &cgRemainder : cg.remainders) {
        std::pair<std::map<int, std::set<Cell *>>::iterator, bool> remainder = remainders.insert(std::pair<int, std::set<Cell *>>(cgRemainder.first, std::set<Cell *>()));
        for (auto &iter : cgRemainder.second) {
            remainder.first->second.insert((*this)[iter->getPos()]);
        }
    }

    return *this;
}

Cell *CellGraph::RandCell(int n) const {
    srand(static_cast<unsigned int>(time(nullptr)));
    auto &nRemainders = remainders.find(n)->second;
    if (nRemainders.empty()) {
        return nullptr;
    }
    unsigned long idx = rand() % nRemainders.size();
    auto iter = nRemainders.begin();
    for (int i = 0; i < idx; ++i) {
        ++iter;
    }
    return *iter;
}

void CellGraph::eraseRemainder(int n, Cell *pC) {
    remainders.find(n)->second.erase(pC);
}


}
