//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_GENERATOR_H
#define HIDATO_GENERATOR_H


#include "Puzzle.h"
#include <cstdlib> // for srand
#include <ctime>   // for srand

class Generator {
private:
public:
    int *InitPoint(Puzzle &puzzle);
    Puzzle &Generate(Puzzle &puzzle);
    Puzzle &Recursive(Puzzle &puzzle,int x,int y,int count);
};


#endif //HIDATO_GENERATOR_H
