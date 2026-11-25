#include "worley.h"
#include "utils.h"
#include <cmath>

using namespace std;

Worley::Worley() {
    N = 8; // Arbitrary base N

    points.resize(N * N * N);

    for(int x = 0; x < N; x++) {
        for(int y = 0; y < N; y++) {
            for(int z = 0; z < N; z++) {
                double randomValX = static_cast<double>(rand()) / RAND_MAX; // 0.0 to 1.0
                double randomValY = static_cast<double>(rand()) / RAND_MAX;
                double randomValZ = static_cast<double>(rand()) / RAND_MAX;

                points.at(((x * N * N) + (y * N) + z)) = vec3{randomValX, randomValY, randomValZ};
            }
        }
    }
}

Worley::Worley(int N) {
    points.resize(N * N * N);
    this->N = N;

    for(int x = 0; x < N; x++) {
        for(int y = 0; y < N; y++) {
            for(int z = 0; z < N; z++) {
                double randomValX = static_cast<double>(rand()) / RAND_MAX; // 0.0 to 1.0
                double randomValY = static_cast<double>(rand()) / RAND_MAX;
                double randomValZ = static_cast<double>(rand()) / RAND_MAX;

                points.at(((x * N * N) + (y * N) + z)) = vec3{randomValX, randomValY, randomValZ};
            }
        }
    }
}

double Worley::noise(double x, double y, double z) {
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

    double smallestDist = INFINITY;

    // Loop thru the 27 cells in and around the sample
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            for(int k = -1; k <= 1; k++) {
                // i is X, j is Y, k is Z
                double dist = distToPoint(X + i, Y + j, Z + k, x - i, y - j, z - k);
                if(dist < smallestDist) smallestDist = dist;
            }
        }
    }

    if (smallestDist > 1) smallestDist = 1.0;
    if (smallestDist < 0) smallestDist = 0.0; // idk if this can even go below 0 but i feel safer

    return smallestDist;
}

double Worley::distToPoint(int X, int Y, int Z, double x, double y, double z) {
    // Just in case the +1 goes over so it loops over to the other side
    X = ((X % N) + N) % N;
    Y = ((Y % N) + N) % N;
    Z = ((Z % N) + N) % N;

    vec3 p = points.at(((X * N * N) + (Y * N) + Z)); // Relative point at the indices

    double dx = p.x - x;
    double dy = p.y - y;
    double dz = p.z - z;
    
    return sqrt(dx*dx + dy*dy + dz*dz); // Dist between the point and x,y,z (assuming they were adjusted to account for diff cells)
}

LayeredWorley::LayeredWorley() : LayeredWorley(8) {
    // N = 8; // Arbitrary base N

    // // Initialize all 4 worleys
    // w1 = Worley(N);
    // w2 = Worley(N*2);
    // w3 = Worley(N*4);
}

LayeredWorley::LayeredWorley(int N) :
    N(N),
    w1(N), w2(N*2), w3(N*4)
    {
    // // Initialize all 4 worleys
    // w1 = Worley(N);
    // w2 = Worley(N*2);
    // w3 = Worley(N*4);

    // this->N = N;
}

double LayeredWorley::noise(double x, double y, double z) {
    // ik how bad this looks but i js want it to work
    double worleyFBmValue = 0.625*w1.noise(N * x, N * y, N * z) + 
                            0.25*w2.noise((N*2) * x, (N*2) * y, (N*2) * z) +
                            0.125*w3.noise((N*4) * x, (N*4) * y, (N*4) * z);

    return (1 - worleyFBmValue); // Just cus the clouds expect bright spots at centers(puffs)
}

