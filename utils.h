#ifndef UTILS_H
#define UTILS_H

struct vec3 {
    double x;
    double y;
    double z;
};

double remap(double value, double oldLow, double oldHigh, double newLow, double newHigh);

#endif