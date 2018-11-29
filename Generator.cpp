//
// Created by thdtj on 2018-11-21.
//

#include "Generator.h"

Puzzle &Generator::Generate(Puzzle &puzzle) {

    int *p = InitPoint(puzzle); //find first location[0]

    std::cout << p[0]<<p[1]<<std::endl;

    int count = 1;
    Recursive(puzzle,p[0],p[1],count);


    return puzzle;
}

int *Generator::InitPoint(Puzzle &puzzle){

    srandom((unsigned int)time(nullptr));
    int *pa = new int[2];
    while(1) {
        pa[0] = (int) random() % puzzle.getWidth();  //rand() : 난수표 사용해서 항상 일정한 패턴으로 결과값 생성됨
        pa[1] = (int) random() % puzzle.getHeight();

        if(puzzle[pa[0]][pa[1]]!= 0){    // 벽이 아닌 blank 에서만 initpoint 함수 만족
            break;
        }
    }

    return pa;
}
Puzzle &Generator::Recursive(Puzzle &puzzle,int x,int y,int count) {
    puzzle[x][y] = count;
    count++;
    //std::cout << puzzle;
    if(count == puzzle.getSize())
        return puzzle;
    if(puzzle[x][y+1] == -1) return Recursive(puzzle, x, y + 1, count);          // ↑
    else if(puzzle[x+1][y+1] == -1) return Recursive(puzzle, x + 1, y + 1, count);  // ↗
    else if(puzzle[x+1][y] == -1) return Recursive(puzzle, x + 1, y, count);    // →
    else if(puzzle[x+1][y-1] == -1) return Recursive(puzzle, x + 1, y - 1, count);  // ↘
    else if(puzzle[x][y-1] == -1) return Recursive(puzzle, x, y - 1, count);    // ↓
    else if(puzzle[x-1][y-1] == -1) return Recursive(puzzle, x - 1, y - 1, count);  // ↙
    else if(puzzle[x-1][y] == -1) return Recursive(puzzle, x - 1, y, count);    // ←
    else if(puzzle[x-1][y+1] == -1) return Recursive(puzzle, x - 1, y + 1, count);    // ↖



    /*else if (puzzle[x][y] == -1) {
        puzzle[x][y] = count;
        count++;

        Recursive(puzzle, x, y + 1, count);    // ↑
        Recursive(puzzle, x + 1, y + 1, count);  // ↗
        Recursive(puzzle, x + 1, y, count);    // →
        Recursive(puzzle, x + 1, y - 1, count);  // ↘
        Recursive(puzzle, x, y - 1, count);    // ↓
        Recursive(puzzle, x - 1, y - 1, count);  // ↙
        Recursive(puzzle, x - 1, y, count);    // ←
        Recursive(puzzle, x - 1, y + 1, count);    // ↖
    }*/

}