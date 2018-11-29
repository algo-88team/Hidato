//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_GENERATOR_H
#define HIDATO_GENERATOR_H


#include "Puzzle.h"
#include <cstdlib> // for srand
#include <ctime>   // for srand

class Generator {
public:
    Puzzle &Generate(Puzzle &puzzle);
    Puzzle &Recursive(Puzzle &puzzle,int x,int y,int count);
};


#endif //HIDATO_GENERATOR_H
