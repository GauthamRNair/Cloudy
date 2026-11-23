#include "noise.h"
#include <cmath>

using namespace std;

Noise::Noise(int N) {
    gradients.resize(N * N * N);
    this->N = N;

    for(int x = 0; x < N; x++) {
        for(int y = 0; y < N; y++) {
            for(int z = 0; z < N; z++) {
                double randomValX = static_cast<double>(rand()) / RAND_MAX; // 0.0 to 1.0
                double randomValY = static_cast<double>(rand()) / RAND_MAX;
                double randomValZ = static_cast<double>(rand()) / RAND_MAX;

                randomValX = (randomValX * 2.0) - 1.0; // -1.0 to 1.0
                randomValY = (randomValY * 2.0) - 1.0;
                randomValZ = (randomValZ * 2.0) - 1.0;

                gradients.at(((x * N * N) + (y * N) + z)) = vec3{randomValX, randomValY, randomValZ};
            }
        }
    }
}

double Noise::noise(double x, double y, double z) {
    int X = floor(x);
    int Y = floor(y);
    int Z = floor(z);

    X = X % N;
    Y = Y % N;
    Z = Z % N;

    // X, Y, Z are now the indices for the correct unit cube

    // Convert x, y, and z to just the coords within the unit cube (relative x,y,z)
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    // Compute fade curves for x,y,z (idk why)
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    // Final interpolation of all gradients
    return lerp(w, lerp(v, lerp(u, dotGradient(X, Y, Z, x, y, z),
                                   dotGradient(X+1, Y, Z, x-1, y, z)),
                           lerp(u, dotGradient(X, Y+1, Z, x, y-1, z),
                                   dotGradient(X+1, Y+1, Z, x-1, y-1, z))),
                   lerp(v, lerp(u, dotGradient(X, Y, Z+1, x, y, z-1),
                                   dotGradient(X+1, Y, Z+1, x-1, y, z-1)),
                           lerp(u, dotGradient(X, Y+1, Z+1, x, y-1, z-1),
                                   dotGradient(X+1, Y+1, Z+1, x-1, y-1, z-1))));
}

double Noise::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10); // Borrowed from the official improved perlin implementation
}

double Noise::lerp(double t, double a, double b) {
    return a + t * (b - a); // linear interpolation FROM a TO b
}

double Noise::dotGradient(int X, int Y, int Z, double x, double y, double z) {
    // Just in case the +1 goes over so it loops over to the other side
    X = X % N;
    Y = Y % N;
    Z = Z % N;

    vec3 g = gradients.at(((X * N * N) + (Y * N) + Z)); // Gradient at the given indices
    return g.x * x + g.y * y + g.z * z; // Dot product between the random gradient and the relative pos
}