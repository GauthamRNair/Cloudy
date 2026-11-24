#include "utils.h"

double remap(double value, double oldLow, double oldHigh, double newLow, double newHigh) {
    return (((value - oldLow) / (oldHigh - oldLow)) * (newHigh - newLow)) + newLow;
}