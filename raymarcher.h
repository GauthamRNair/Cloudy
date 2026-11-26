#ifndef RAYMARCHER_H
#define RAYMARCHER_H

#include "utils.h"
#include "texture.h"

class RayMarcher {
    public:
        RayMarcher();
        RayMarcher(vec3 origin);

        double march(vec3 forward, Texture& density); // gets the total density(thru the cloud density) it passes through in a given direction
    private:
        vec3 origin;
};

#endif