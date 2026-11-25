#include "perlin-worley.h"
#include "perlin.h"
#include "worley.h"
#include "utils.h"

using namespace std;

PerlinWorley::PerlinWorley() : PerlinWorley(8) {
    // N = 8; // Arbitrary base N

    // // Initialize layered worley
    // lw = LayeredWorley(N);

    // // Initialize all 7 perlins
    // p1 = Perlin(N);
    // p2 = Perlin(N*2);
    // p3 = Perlin(N*4);
    // p4 = Perlin(N*8);
    // p5 = Perlin(N*16);
    // p6 = Perlin(N*32);
    // p7 = Perlin(N*64);
}

PerlinWorley::PerlinWorley(int N) :
    N(N), lw(N),
    p1(N), p2(N*2), p3(N*4), p4(N*8), p5(N*16), p6(N*32), p7(N*64)
    {
    // // Initialize layered worley
    // lw = LayeredWorley(N);

    // // Initialize all 7 perlins
    // p1 = Perlin(N);
    // p2 = Perlin(N*2);
    // p3 = Perlin(N*4);
    // p4 = Perlin(N*8);
    // p5 = Perlin(N*16);
    // p6 = Perlin(N*32);
    // p7 = Perlin(N*64);

    // this->N = N;
}

double PerlinWorley::noise(double x, double y, double z) {
    // ik how bad this looks but i js want it to work
    double worleyFBmValue = lw.noise(x, y, z);

    double perlinFBmValue = 0.5078125*p1.noise(N * x, N * y, N * z) +
                            0.25*p2.noise((N*2) * x, (N*2) * y, (N*2) * z) +
                            0.125*p3.noise((N*4) * x, (N*4) * y, (N*4) * z) +
                            0.0625*p4.noise((N*8) * x, (N*8) * y, (N*8) * z) +
                            0.03125*p5.noise((N*16) * x, (N*16) * y, (N*16) * z) +
                            0.015625*p6.noise((N*32) * x, (N*32) * y, (N*32) * z) +
                            0.0078125*p7.noise((N*64) * x, (N*64) * y, (N*64) * z);

    perlinFBmValue = (perlinFBmValue + 1.0) * 0.5;

    return remap(perlinFBmValue, 0, 1, worleyFBmValue, 1);
}
