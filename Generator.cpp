//
// Created by thdtj on 2018-11-21.
//

#include "Generator.h"

Puzzle &Generator::Generate(Puzzle &puzzle) {


    //find first location[0] 1
    int x,y = 0;
    x = std::rand()%puzzle.getWidth();  //rand() : 난수표 사용해서 항상 일정한 패턴으로 결과값 생성됨
    y = std::rand()%puzzle.getHeight();
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    x=2;
    y=2; //

    //if(puzzle[x+1][y] == 1){
    //    puzzle[x+1][y] = count;
    //}
    std::cout << "pullsize: " << puzzle.getSize() << std::endl;
    int count = 1;
    Recursive(puzzle,x,y,count);


    return puzzle;
}

Puzzle &Generator::Recursive(Puzzle &puzzle,int x,int y,int count) {
    //std::cout << x << " "<< y <<" "<< count << std::endl;
    if (count == puzzle.getSize())  {// 모든 칸이 채워지면 퍼즐 출력
        std::cout << "complete create puzzle" << std::endl;
        return puzzle;
    }
    else if (puzzle[x][y] == -1) {
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
    }

}