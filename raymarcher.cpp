#include "raymarcher.h"
#include "consts.h"
#include "utils.h"

#include <cstdlib>

RayMarcher::RayMarcher() : RayMarcher(vec3{0, 0, 0}) {

}

RayMarcher::RayMarcher(vec3 origin) : origin(origin) {

}

double RayMarcher::march(vec3 forward, Texture& density) {
    double opticalDepth = 0;
    vec3 currentPos = origin;

    if(forward.z <= 0) return 0.0;

    // Start the ray marching from right below the cloud layer
    double verticalDist = LAYER_BOTTOM - currentPos.z - STEP_SIZE;
    double scale = verticalDist / forward.z;
    currentPos.x += forward.x * scale;
    currentPos.y += forward.y * scale;
    currentPos.z += forward.z * scale;

    // Normalize to scale to the correct step size
    vec3 step = normalize(forward);
    step.x *= STEP_SIZE;
    step.y *= STEP_SIZE;
    step.z *= STEP_SIZE;

    for(int i = 0; i < MAX_STEPS; i++) {
        double j = rand() / ((double)RAND_MAX * 10) + 0.95; // add noise to avoid banding from the step size
        currentPos.x += step.x * j;
        currentPos.y += step.y * j;
        currentPos.z += step.z * j;

        if(currentPos.z > LAYER_TOP) return opticalDepth;
        if(SIGMA * opticalDepth > 5.0) return opticalDepth; // everything behind is so marginal

        opticalDepth += density.sample(currentPos.x, currentPos.y, currentPos.z, COVERAGE) * STEP_SIZE; // density x distance = volume idk
    }

    return opticalDepth;
}