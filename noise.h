#ifndef NOISE_H
#define NOISE_H

#include <vector>

using namespace std;

struct vec3 {
    double x;
    double y;
    double z;
};

// https://mrl.cs.nyu.edu/~perlin/noise/
class Noise {
    public:
        Noise(int N);
        double noise(double x, double y, double z);
        double fade(double t);
        double lerp(double t, double a, double b);
    private:
        int N;
        vector<vec3> gradients;
        double dotGradient(int X, int Y, int Z, double x, double y, double z);
};

#endif