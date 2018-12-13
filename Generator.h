//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_GENERATOR_H
#define HIDATO_GENERATOR_H


#include "Puzzle.h"
#include "CellGraph.h"

class Generator {
public:
    Generator() : width(0), height(0), numCells(0) {}
    Puzzle &Generate(Puzzle &puzzle);

private:
    int width;
    int height;
    int numCells;

    int start_x,start_y;
    int direction[8][2] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };

    //초기화 함수 필요 generater에?puzzle에?

    void Init_start(Puzzle &puzzle);

    void Recursive(Puzzle &puzzle,int x,int y,int count);

    void Invert(Puzzle &puzzle);

    Puzzle *Fill(Puzzle puzzle, CellGraph graph, const Cell cell);

    bool Update(Puzzle &puzzle, CellGraph &graph, const Cell cell);
};


#endif //HIDATO_GENERATOR_H
