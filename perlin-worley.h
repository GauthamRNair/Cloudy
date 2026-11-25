#ifndef PERLIN_WORLEY_H
#define PERLIN_WORLEY_H

#include <vector>
#include "consts.h"
#include "perlin.h"
#include "worley.h"

using namespace std;

class PerlinWorley {
    public:
        PerlinWorley();
        PerlinWorley(int N);
        double noise(double x, double y, double z);
    private:
        int N;
        LayeredWorley lw;
        Perlin p1, p2, p3, p4, p5, p6, p7;
};

#endif