//
// Created by thdtj on 2018-11-21.
//

#include "Generator.h"

Puzzle &Generator::Generate(Puzzle &puzzle) {
    width = puzzle.getWidth();
    height = puzzle.getHeight();
    numCells = puzzle.getNumCells();

    //  Change empty cells from 1 to -1
    Invert(puzzle);

    //  Create CellGraph
    CellGraph graph(puzzle);

    //  Fill puzzle
    Fill(puzzle, graph);
    return puzzle;
}

void Generator::Invert(Puzzle &puzzle) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            puzzle[i][j] *= -1;
        }
    }
    puzzle.setNumEmptyCells(puzzle.getNumCells());
}

Puzzle *Generator::Fill(Puzzle puzzle, CellGraph graph) {
    return nullptr;
}

