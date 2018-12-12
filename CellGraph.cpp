//
// Created by thdtj on 2018-12-10.
//

#include "CellGraph.h"
#include <random>


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

    //  Initialize remaindersSet
    for (int n = 1; n < puzzle.getNumCells() + 1; ++n) {
        remaindersSet.insert(std::pair<int, std::set<Cell *>>(n, std::set<Cell *>()));
    }

    //  Create Cells
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int value = puzzle[i][j];
            auto &p = (*this)[i][j];
            if (value < 0) {
                p = new Cell(value, j, i);
                cells.emplace_back(p);

                for (auto &remainders : remaindersSet) {
                    remainders.second.insert(p);
                    p->insertCandidate(remainders.first);
                }
            } else if (value > 0) {
                auto &remainders = remaindersSet.find(value)->second;
                remainders.clear();
                std::set<Cell *>().swap(remainders);
                remaindersSet.erase(value);

                int prevValue = value - 1;
                int nextValue = value + 1;

                auto iter = remaindersSet.find(prevValue);
                if (iter != remaindersSet.end()) {
                    auto &prevRemainders = iter->second;
                    for (auto prevRemainder = prevRemainders.begin(); prevRemainder != prevRemainders.end();) {
                        if (!prevRemainder.operator*()->is_Neighbor(j, i)) {
                            prevRemainder.operator*()->eraseCandidate(prevValue);
                            prevRemainder = prevRemainders.erase(prevRemainder);
                        } else {
                            ++prevRemainder;
                        }
                    }

                }

                iter = remaindersSet.find(nextValue);
                if (iter != remaindersSet.end()) {
                    auto &nextRemainders = iter->second;
                    for (auto nextRemainder = nextRemainders.begin(); nextRemainder != nextRemainders.end();) {
                        if (!nextRemainder.operator*()->is_Neighbor(j, i)) {
                            nextRemainder.operator*()->eraseCandidate(nextValue);
                            nextRemainder = nextRemainders.erase(nextRemainder);
                        } else {
                            ++nextRemainder;
                        }
                    }
                }

            }
        }
    }
}

CellGraph::CellGraph(const CellGraph &cg) : width(cg.width), height(cg.height) {

    //  Allocate map
    map = new Cell **[height + 2];
    for (int i = 0; i < height + 2; ++i) {
        map[i] = new Cell *[width + 2];
        for (int j = 0; j < width + 2; ++j) {
            map[i][j] = cg.map[i][j] == nullptr ? nullptr : new Cell(*cg.map[i][j]);
        }
    }

    //  Mapping cells
    for (auto &cgCell : cg.cells) {
        cells.emplace_back((*this)[cgCell->getPos()]);
    }

    //  Mapping remaindersSet
    for (auto &cgRemainders : cg.remaindersSet) {
        std::pair<std::map<int, std::set<Cell *>>::iterator, bool> remainders = remaindersSet.insert(
                std::pair<int, std::set<Cell *>>(cgRemainders.first, std::set<Cell *>()));
        for (auto &cgRemainder : cgRemainders.second) {
            remainders.first->second.insert((*this)[cgRemainder->getPos()]);
        }
    }
}

CellGraph::~CellGraph() {
    cells.clear();
    std::vector<Cell *>().swap(cells);

    for (auto &remainders : remaindersSet) {
        remainders.second.clear();
        std::set<Cell *>().swap(remainders.second);
    }
    remaindersSet.clear();
    std::map<int, std::set<Cell *>>().swap(remaindersSet);

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
    return map[i + 1] + 1;
}

Cell **CellGraph::operator[](int i) {
    return map[i + 1] + 1;
}

Cell *CellGraph::operator[](const Point &p) const {
    return map[p.y + 1][p.x + 1];
}

Cell *&CellGraph::operator[](const Point &p) {
    return map[p.y + 1][p.x + 1];
}

CellGraph &CellGraph::operator=(const CellGraph &cg) {
    cells.clear();

    for (auto &remainders : remaindersSet) {
        remainders.second.clear();
        std::set<Cell *>().swap(remainders.second);
    }
    remaindersSet.clear();

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

    //  Mapping remaindersSet
    for (auto &cgRemainders : cg.remaindersSet) {
        std::pair<std::map<int, std::set<Cell *>>::iterator, bool> remainders = remaindersSet.insert(
                std::pair<int, std::set<Cell *>>(cgRemainders.first, std::set<Cell *>()));
        for (auto &cgRemainder : cgRemainders.second) {
            remainders.first->second.insert((*this)[cgRemainder->getPos()]);
        }
    }

    return *this;
}

Cell *CellGraph::RandCell(int n) const {
    auto &remainders = remaindersSet.find(n)->second;
    if (remainders.empty()) {
        return nullptr;
    }
    unsigned long idx = rand() % remainders.size();
    auto remainder = remainders.begin();
    for (int i = 0; i < idx; ++i) {
        ++remainder;
    }
    return *remainder;
}

void CellGraph::eraseRemainder(int n, Cell *pCell) {
    remaindersSet.find(n)->second.erase(pCell);
    pCell->eraseCandidate(n);
}

void CellGraph::eraseRemainders(int n) {
    auto iter = remaindersSet.find(n);
    if (iter == remaindersSet.end()) {
        return;
    }
    auto &remainders = iter->second;
    for (auto &remainder : remainders) {
        remainder->eraseCandidate(n);
    }
    remainders.clear();
    std::set<Cell *>().swap(remainders);
    remaindersSet.erase(iter);
}

void CellGraph::eraseCell(Cell *pCell) {
    eraseRemainders(pCell->getData());

    for (auto &remainders : remaindersSet) {
        remainders.second.erase(pCell);
    }

    for (auto iter = cells.begin(); iter != cells.end(); ++iter) {
        if (*iter == pCell) {
            cells.erase(iter);
            break;
        }
    }

    (*this)[pCell->getPos()] = nullptr;
    delete pCell;
}

void CellGraph::checkNeighbor(const Cell &c) {
    int value = c.getData();
    int prevValue = value - 1;
    int nextValue = value + 1;

    auto iter = remaindersSet.find(prevValue);
    if (iter != remaindersSet.end()) {
        auto &prevRemainders = iter->second;
        for (auto prevRemainder = prevRemainders.begin(); prevRemainder != prevRemainders.end();) {
            if (!prevRemainder.operator*()->is_Neighbor(c)) {
                prevRemainder.operator*()->eraseCandidate(prevValue);
                prevRemainder = prevRemainders.erase(prevRemainder);
            } else {
                ++prevRemainder;
            }
        }

    }

    iter = remaindersSet.find(nextValue);
    if (iter != remaindersSet.end()) {
        auto &nextRemainders = iter->second;
        for (auto nextRemainder = nextRemainders.begin(); nextRemainder != nextRemainders.end();) {
            if (!nextRemainder.operator*()->is_Neighbor(c)) {
                nextRemainder.operator*()->eraseCandidate(nextValue);
                nextRemainder = nextRemainders.erase(nextRemainder);
            } else {
                ++nextRemainder;
            }
        }
    }
}

bool CellGraph::checkMapping() {
    for (auto &cell : cells) {
        if (cell != (*this)[cell->getPos()]) {
            std::cerr << "Error : cells mapping was broken. " << cell->getPos() << std::endl;
            return false;
        }
    }

    for (auto &remainders : remaindersSet) {
        for (auto &remainder : remainders.second) {
            if (remainder != (*this)[remainder->getPos()]) {
                std::cerr << "Error : remaindersSet mapping was broken. " << remainder->getPos() << std::endl;
                return false;
            }
        }
    }

    return true;
}
