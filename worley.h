#ifndef WORLEY_H
#define WORLEY_H

#include <vector>
#include "consts.h"
#include "utils.h"

using namespace std;

class Worley {
    public:
        Worley();
        Worley(int N);
        double noise(double x, double y, double z);
    private:
        int N;
        vector<vec3> points;
        double distToPoint(int X, int Y, int Z, double x, double y, double z);
};

#endif