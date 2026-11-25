#ifndef PERLIN_H
#define PERLIN_H

#include <vector>
#include "consts.h"
#include "utils.h"

using namespace std;

// https://mrl.cs.nyu.edu/~perlin/noise/
class Perlin {
    public:
        Perlin();
        Perlin(int N);
        double noise(double x, double y, double z);
        double fade(double t);
        double lerp(double t, double a, double b);
    private:
        int N; // True size of the grid (NxNxN)
        // Ignore: int gradientSize; // True size of each dimension of gradients (cus I wanna cap it since it will use a lot of memory, also it tiles anyway)
        vector<vec3> gradients;
        double dotGradient(int X, int Y, int Z, double x, double y, double z);
};

#endif