#ifndef UTILS_H
#define UTILS_H

struct vec3 {
    double x;
    double y;
    double z;
};

double remap(double value, double oldLow, double oldHigh, double newLow, double newHigh);
vec3 normalize(vec3 vector);
vec3 cross(vec3 vector1, vec3 vector2);


#endif