#ifndef CONSTS_H
#define CONSTS_H

#include "utils.h"

const int IMAGE_WIDTH = 1920;
const int IMAGE_HEIGHT = 1080;

const double SHAPE_SCALE = 0.05; // Scale factor between the cloud texture and the real 3d world

const int MAX_PERLIN_N = 32;

const double DETAIL_SCALE = 2.0;
const double EROSION_STRENGTH = 0.35;
const double COVERAGE = 0.3;
const double LAYER_BOTTOM = 4;
const double LAYER_TOP = 7;

const vec3 CAM_POS = vec3{0, 0, 0};
const vec3 CAM_FORWARD = vec3{2, 2, 1};
const int MAX_STEPS = 30;
const double STEP_SIZE = 0.1;

const double SIGMA = 10.0;

#endif