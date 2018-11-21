//
// Created by thdtj on 2018-11-21.
//

#include "Puzzle.h"
#include <string.h>

Puzzle::Puzzle() = default;

Puzzle::Puzzle(int width, int height) : mWidth(width), mHeight(height) {
    mMap = new int *[height + 2];

    for (int i = 0; i < height + 2; ++i) {
        mMap[i] = new int[width + 2];
    }

    memset(mMap[0], 0, (width + 2) * sizeof(int));
    memset(mMap[height + 2 - 1], 0, (width + 2) * sizeof(int));

    for (int i = 1; i < height + 1; ++i) {
        mMap[i][0] = 0;
        mMap[i][width + 1] = 0;
    }
}


Puzzle::~Puzzle() {
    if (mMap != nullptr) {
        for (int i = 0; i < mHeight + 2; ++i) {
            delete [] mMap[i];
        }
        delete [] mMap;
    }
}

int *Puzzle::operator[](int i) const {
    return mMap[i + 1] + 1;
}

int *Puzzle::operator[](int i) {
    return mMap[i + 1] + 1;
}

Puzzle &Puzzle::operator=(const Puzzle &p) {
    if (mMap != nullptr) {
        for (int i = 0; i < mHeight + 2; ++i) {
            delete [] mMap[i];
        }
        delete [] mMap;
    }

    int width, height;

    width = p.mWidth;
    height = p.mHeight;

    mWidth = width;
    mHeight = height;

    mMap = new int *[height + 2];

    for (int i = 0; i < height + 2; ++i) {
        mMap[i] = new int[width + 2];
        memcpy(mMap[i], p.mMap[i], (width + 2) * sizeof(int));
    }

    return *this;
}

std::ostream &operator<<(std::ostream &o, const Puzzle p) {
    for (int i = 0; i < p.mHeight; ++i) {
        for (int j = 0; j < p.mWidth; ++j) {
            o << p[i][j] << " ";
        }
        o << std::endl;
    }
    return o;
}

std::ifstream &operator>>(std::ifstream &in, Puzzle p) {
    int width, height;
    in >> width >> height;

    p.mWidth = width;
    p.mHeight = height;

    p = Puzzle(width, height);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            in >> p[i][j];
        }
    }

    return in;
}
