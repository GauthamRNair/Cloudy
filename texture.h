#ifndef TEXTURE_H
#define TEXTURE_H

#include "perlin-worley.h"
#include "perlin.h"
#include "worley.h"

using namespace std;

class Texture {
    public:
        Texture();
        Texture(int N);

        double sample(double x, double y, double z, double coverage);

    private:
        // Based on the 2015 Horizon talk I'm going to sort the textures like them
        // 3dTexture1 will be textureA1, textureA2, textureA3, textureA4 (1 Perlin-Worley and 3 Layered Worley textures)
        // 3dTexture2 will be textureB1, textureB2, textureB3 (3 Worley textures)
        // 2dTexture is 3 curl textures? idk if ill implement it
        PerlinWorley textureA1;
        LayeredWorley textureA2, textureA3, textureA4;

        Worley textureB1, textureB2, textureB3;

        int N;
};

#endif