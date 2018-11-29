//
// Created by thdtj on 2018-11-21.
//

#ifndef HIDATO_PUZZLE_H
#define HIDATO_PUZZLE_H

#include <iostream>
#include <fstream>

class Puzzle {
public:
    Puzzle();

    Puzzle(int width, int height);

    virtual ~Puzzle();

    int *operator[](int i) const;

    int *operator[](int i);

    Puzzle &operator=(const Puzzle &p);

    friend std::ostream &operator<<(std::ostream &o, const Puzzle &p);

    friend std::istream &operator>>(std::istream &o, Puzzle &p);

    Puzzle &LoadFormFile(const char *name);

    int getWidth() const;

    int getHeight() const;

    int getSize() const;

private:
    int width;
    int height;
    int size = 0;
    int **map;
};

#endif //HIDATO_PUZZLE_H
