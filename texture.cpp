#include "texture.h"
#include "consts.h"

Texture::Texture() : Texture(8) {
    // N = 8;

    // textureA1 = PerlinWorley(N);
    // textureA2 = LayeredWorley(N);
    // textureA3 = LayeredWorley(N*2);
    // textureA4 = LayeredWorley(N*4);

    // textureB1 = Worley(N);
    // textureB2 = Worley(N*2);
    // textureB3 = Worley(N*4);
}

Texture::Texture(int N) : 
    N(N), 
    textureA1(N), textureA2(N), textureA3(N*2), textureA4(N*4), 
    textureB1(N), textureB2(N*2), textureB3(N*4)
    {
    // textureA1 = PerlinWorley(N);
    // textureA2 = LayeredWorley(N);
    // textureA3 = LayeredWorley(N*2);
    // textureA4 = LayeredWorley(N*4);

    // textureB1 = Worley(N);
    // textureB2 = Worley(N*2);
    // textureB3 = Worley(N*4);

    // this->N = N;
}

// Samples the cloud density at x, y, z
double Texture::sample(double x, double y, double z, double coverage) {
    if(coverage <= 0.0) return 0; // Edge case to avoid any divide by zeroes js in case 
    if((z < LAYER_BOTTOM) || (z > LAYER_TOP)) return 0; // No clouds outside the cloud layer's range

    // Combine all the layered worley into one
    double newFBm = (0.625 * textureA2.noise(x, y, z)) + (0.25 * textureA3.noise(x, y, z)) + (0.125 * textureA4.noise(x, y, z));
    
    double baseValue = textureA1.noise(x, y, z) + (1 - newFBm); // Add the fBm in a weird way
    baseValue /= (2 - newFBm); // Scale it back down to 0-1

    baseValue = (baseValue - (1 - coverage)) / (1 - (1 - coverage)); // Everything from (1 - coverage) to 1 will be mapped to 0 to 1 (higher coverage means more clouds)
    if (baseValue < 0) baseValue = 0; // clamp the negatives
    baseValue *= coverage; // For the leftover stuff, scale it to match the density of the coverage

    // Get a scaled up pos to pull from the noise (remember that it tiles infinitly)
    // So basically from the perspective to these positions the noise is act rly smal
    double detailX = x * DETAIL_SCALE;
    double detailY = y * DETAIL_SCALE;
    double detailZ = z * DETAIL_SCALE;

    // Pull and combine the detailed noise 
    double detailFBm = (0.625 * textureB1.noise(detailX*N, detailY*N, detailZ*N)) + 
                        (0.25 * textureB2.noise(detailX*(2*N), detailY*(2*N), detailZ*(2*N))) + 
                        (0.125 * textureB3.noise(detailX*(4*N), detailY*(4*N), detailZ*(4*N)));

    // I'll map the z to 0-1 from between LAYER_BOTTOM and LAYER_TOP
    double h = (z - LAYER_BOTTOM) / (LAYER_TOP - LAYER_BOTTOM);

    double t = h*10; // Scale for the lerp math later on
    if(t > 1.0) t = 1.0; // clamp

    double detailValue = detailFBm + ((1 - detailFBm) - detailFBm) * t; // Some math idk for the detail to depend on the height

    double finalDensity = (baseValue - detailValue*EROSION_STRENGTH) / (1 - detailValue*EROSION_STRENGTH); // Maps baseValue to detailValue*erosion_strngth to 1
    if(finalDensity < 0) finalDensity = 0; // clamp
    if(finalDensity > 1) finalDensity = 1;

    return finalDensity;
}
