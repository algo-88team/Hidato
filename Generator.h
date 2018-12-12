//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_GENERATOR_H
#define HIDATO_GENERATOR_H


#include "Puzzle.h"
#include "CellGraph.h"

class Generator {
public:
    Puzzle &Generate(Puzzle &puzzle);

private:
    int width;
    int height;
    int numCells;

    void Invert(Puzzle &puzzle);
    Puzzle *Fill(Puzzle puzzle, CellGraph graph, Cell cell);
};


#endif //HIDATO_GENERATOR_H
