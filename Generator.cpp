//
// Created by thdtj on 2018-11-21.
//

#include "Generator.h"
#include "Cell.h"

Puzzle &Generator::Generate(Puzzle &puzzle) {
    width = puzzle.getWidth();
    height = puzzle.getHeight();
    numCells = puzzle.getNumCells();

    //  Change empty cells from 1 to -1
    Invert(puzzle);

    //  Create CellGraph
    CellGraph graph(puzzle);


    //  Fill puzzle
    Puzzle *result;
    do {
        Cell *randCell = graph.getRandCell(1);
        if (randCell == nullptr) {
            std::cout << "There are no way" << std::endl;
            return puzzle;
        }
        randCell->setData(1);

        result = Fill(puzzle, graph, *randCell);

        if (result == nullptr) {
            randCell->eraseCandidate(1);
            graph.eraseRemainder(1, randCell);
            randCell->setData(-1);
        }
    } while (result == nullptr);

    puzzle = *result;

    //  Check puzzle
    int checker = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            checker ^= puzzle[i][j];
        }
    }
    for (int n = 1; n < numCells + 1; ++n) {
        checker ^= n;
    }
    if (checker) {
        std::cout << "Fill failed." << std::endl;
        return puzzle;
    }


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

Puzzle *Generator::Fill(Puzzle puzzle, CellGraph graph, const Cell cell) {
    if (!Update(puzzle, graph, cell)) {
        return nullptr;
    }

    if (graph.is_finished()) {
        return new Puzzle(puzzle);
    }

    Puzzle *result;
    do {
        Cell *randCell = graph.getNextRandCell();

        if (randCell == nullptr) {
//            std::cout << "There are no way " << graph.getRemaindersSetSize() << std::endl;
            return nullptr;
        }

        int n = randCell->getData();

        result = Fill(puzzle, graph, *randCell);

        if (result == nullptr) {
            randCell->eraseCandidate(n);
            graph.eraseRemainder(n, randCell);
            randCell->setData(-1);
        }
    } while (result == nullptr);

    return result;
}

bool Generator::Update(Puzzle &puzzle, CellGraph &graph, const Cell cell) {
    puzzle[cell.getPos()] = cell.getData();
    graph.eraseCell(graph[cell.getPos()]);
    graph.checkNeighbor(cell);

    if (graph.is_finished()) {
        return true;
    }

    if (!graph.checkMapping() || !graph.is_candidatesEmpty() || !graph.is_remaindersEmpty()) {
        return false;
    }

    Cell *pCell = graph.find_onlyCandidate();
    if (pCell == nullptr) {
        pCell = graph.find_onlyRemainder();
        if (pCell == nullptr) {
            return true;
        }
    }

    return Update(puzzle, graph, *pCell);
}

