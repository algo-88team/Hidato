//
// Created by thdtj on 2018-11-21.
//

#include "Generator.h"
#include "Cell.h"

#include <random>
#include <algorithm>

Puzzle &Generator::Generate(Puzzle &puzzle) {
    width = puzzle.getWidth();
    height = puzzle.getHeight();
    numCells = puzzle.getNumCells();

    //  Change empty cells from 1 to -1
    Invert(puzzle);
    /*
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
    */
    Init_start(puzzle);

    int num = 1;
    std::cout << start_x << "  "<< start_y << std::endl;
    int x,y;
    x = start_x;
    y = start_y;
    //puzzle[start_x][start_y] = num;
    Recursive(puzzle, {x,y},1);
    return puzzle;
}

//void Generator::Recursive(Puzzle &puzzle,int x,int y,int count){
//    std::cout << "step : "  <<count << std::endl;
//
//    //isback?
//    int isback = 0;
//    for(int i = 0; i < 8; i++){
//        if (puzzle[x+direction[i].x][y+direction[i].y] == -1)
//            isback = 1;
//    }
//
//
//    if(puzzle[x][y] == -1 && isback == 1) {
//        puzzle[x][y] = count;
//        for(int i = 0; i < 8; i ++){
//            //std::cout << direction[i][0]<< " "<<direction[i][1] << std::endl;
//            Recursive(puzzle,x+direction[i][0],y+direction[i][1],count+1);
//        }
//    }
//
//    else if (count == puzzle.getNumCells()){ // 퍼즐 완성
//        puzzle[x][y] = count;
//        return;
//    }
//
//}

bool Generator::Recursive(Puzzle &puzzle, Point pos, int n) {
    if (puzzle[pos] != -1) {
        return false;
    }
    puzzle[pos] = n;
    for (int i = 0; i < 8; ++i) {
        std::vector<Point> dir(direction);
        std::random_shuffle(dir.begin(), dir.end());
        if (Recursive(puzzle, pos+dir[i], n+1)) {
            return true;
        }
    }
    puzzle[pos] = -1;
    return false;
}

void Generator::Invert(Puzzle &puzzle) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            puzzle[i][j] *= -1;
        }
    }
    puzzle.setNumEmptyCells(puzzle.getNumCells());
}

void Generator::Init_start(Puzzle &puzzle) {
    int x,y = 0;
    x = std::rand()%width;  //rand() : 난수표 사용해서 항상 일정한 패턴으로 결과값 생성됨
    y = std::rand()%height;


    if(puzzle[x][y] == -1){
        std::cout << x << "  "<< y << std::endl;
        std::cout << "random start point" << std::endl;
        start_x = x;
        start_y = y;
    }
    else {
        std::cout << x << "  "<< y << std::endl;
        std::cout << "start point assign again" << std::endl;
        Init_start(puzzle);
    } // 생성된 시작점이 0(벽) 일시 다시 실행
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

