//
//  Running Water
//  Copyright (c) 2015 John Ward. All rights reserved.
//

#ifndef __Running_Water__Helper_Functions__
#define __Running_Water__Helper_Functions__

#include <stdio.h>
#include <math.h>

class Vector {
public:
    Vector();
    Vector(float x, float y, float z);
    float length();
    void normalize();
    float x;
    float y;
    float z;
};

class Matrix {
public:
    Matrix();
    union {
        float m[4][4];
        float ml[16];
    };
    void identity();
    Matrix inverse();
    Matrix operator* (const Matrix &m2);
    Vector operator* (const Vector &v2);
};

float lerp(float v0, float v1, float t);

#endif /* defined(__Running_Water__Helper_Functions__) */
