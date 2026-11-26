#include "utils.h"
#include <cmath>

double remap(double value, double oldLow, double oldHigh, double newLow, double newHigh) {
    return (((value - oldLow) / (oldHigh - oldLow)) * (newHigh - newLow)) + newLow;
}

vec3 normalize(vec3 vector) {
    double magnitude = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));

    vec3 normalizedVector = vector;
    normalizedVector.x /= magnitude;
    normalizedVector.y /= magnitude;
    normalizedVector.z /= magnitude;

    return normalizedVector;
}

vec3 cross(vec3 vector1, vec3 vector2) {
    vec3 crossedVector;

    crossedVector.x = (vector1.y * vector2.z) - (vector2.y * vector2.z);
    crossedVector.y = -((vector1.x - vector2.z) - (vector2.x - vector1.z));
    crossedVector.z = (vector1.x * vector2.y) - (vector2.x * vector1.y);

    return crossedVector;
}
