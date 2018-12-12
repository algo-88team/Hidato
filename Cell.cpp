//
// Created by thdtj on 2018-12-13.
//

#include "Cell.h"

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

void Cell::setDataCandidate() {
    data = *candidates.begin();
}

int Cell::getCandidate() {
    return *candidates.begin();
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
    return abs(pos.x - x) <= 1 && abs(pos.y - y) <= 1;
}

bool Cell::is_Neighbor(const Point &p) {
    return abs(pos.x - p.x) <= 1 && abs(pos.y - p.y) <= 1;
}

bool Cell::is_Neighbor(const Cell &c) {
    return abs(pos.x - c.pos.x) <= 1 && abs(pos.y - c.pos.y) <= 1;
}

int Cell::getCandidatesSize() {
    return static_cast<int>(candidates.size());
}

bool Cell::isCandidatesEmpty() {
    return candidates.empty();
}

bool Cell::is_candidate(int n) {
    return candidates.find(n) != candidates.end();
}
