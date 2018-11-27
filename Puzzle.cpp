//
// Created by thdtj on 2018-11-21.
//

#include "Generator.h"
#include "Puzzle.h"
#include <string.h>

Puzzle::Puzzle() : mWidth(0), mHeight(0), mMap(nullptr) {};

Puzzle::Puzzle(int width, int height) : mWidth(width), mHeight(height), mMap(nullptr) {
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
            delete[] mMap[i];
        }
        delete[] mMap;
    }
}

int *Puzzle::operator[](int i) const {
    return mMap[i + 1] + 1;
}

int *Puzzle::operator[](int i) {
    return mMap[i + 1] + 1;
}

Puzzle &Puzzle::operator=(const Puzzle &p) {
    if (&p == this) {
        return *this;
    }
    if (mMap != nullptr) {
        for (int i = 0; i < mHeight + 2; ++i) {
            delete[] mMap[i];
        }
        delete[] mMap;
    }

    int width, height;

    width = p.mWidth;
    height = p.mHeight;

    mWidth = width;
    mHeight = height;

    if (width == 0 || height == 0 || p.mMap == nullptr) {
        mMap = nullptr;
        return *this;
    }

    mMap = new int *[height + 2];

    for (int i = 0; i < height + 2; ++i) {
        mMap[i] = new int[width + 2];
        memcpy(mMap[i], p.mMap[i], (width + 2) * sizeof(int));
    }

    return *this;
}

std::ostream &operator<<(std::ostream &o, const Puzzle &p) {
#ifdef PRINT_EDGE
    for (int i = -1; i < p.mHeight+1; ++i) {
        for (int j = -1; j < p.mWidth+1; ++j) {
            o << p[i][j] << " ";
        }
        o << std::endl;
    }
#else
    for (int i = 0; i < p.mHeight; ++i) {
        for (int j = 0; j < p.mWidth; ++j) {
            o << p[i][j] << " ";
        }
        o << std::endl;
    }
#endif
    return o;
}

std::istream &operator>>(std::istream &in, Puzzle &p) {
    int width, height;
    in >> width >> height;

    p = Puzzle(width, height);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            in >> p[i][j];
        }
    }

    return in;
}

Puzzle &Puzzle::LoadFormFile(const char *name) {
    if (mMap != nullptr) {
        for (int i = 0; i < mHeight + 2; ++i) {
            delete[] mMap[i];
        }
        delete[] mMap;
    }

    std::ifstream in;

    in.open(name);
    if (in.fail()) {
        std::cerr << "file open error : " << name << std::endl;
        return *this;
    }

    in >> *this;

    return *this;
}