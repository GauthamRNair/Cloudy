#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "consts.h"
#include "texture.h"
#include "raymarcher.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

char floatToByte(double color);

int main() {
    srand(0);

    vector<char> img(IMAGE_WIDTH * IMAGE_HEIGHT * 3); // Outdated: 3 chars for each pixel cus 1 char = 1 byte = 1 color channel
    Texture t(8);
    // LayeredWorley lw(8);
    RayMarcher rm(CAM_POS);

    int startTime = time(NULL);

    #pragma omp parallel for schedule(dynamic) // use cores parallelly
    for(int y = 0; y < IMAGE_HEIGHT; y++) {
        for(int x = 0; x < IMAGE_WIDTH; x++) {
            int index = 3 * ((y * IMAGE_WIDTH) + x);
            // img.at(index + 0) = (255 * x) / IMAGE_WIDTH; // red
            // img.at(index + 1) = (255 * y) / IMAGE_HEIGHT; // green
            // img.at(index + 2) = (255 * x) / IMAGE_WIDTH; // blue
            double u = 2 * ((double)x / IMAGE_WIDTH) - 1.0;
            double v = -2 * ((double)y / IMAGE_HEIGHT) + 1.0; // 1..-1 for top to bottom

            vec3 camRight = normalize(cross(CAM_FORWARD, vec3{0, 0, 1}));
            vec3 camUp = normalize(cross(camRight, CAM_FORWARD));

            vec3 pixelDir = CAM_FORWARD;
            pixelDir.x += camRight.x * u + camUp.x * v;
            pixelDir.y += camRight.y * u + camUp.y * v;
            pixelDir.z += camRight.z * u + camUp.z * v;

            // double finalFBmValue = t.sample(u, v, 0, COVERAGE);
            double opticalDepth = rm.march(pixelDir, t);
            double T = exp(-SIGMA * opticalDepth);

            vec3 sky = {0.35, 0.55, 0.90};
            vec3 cloud = {1.0, 1.0, 1.0};

            double r = sky.x * T + cloud.x * (1-T);
            double g = sky.y * T + cloud.y * (1-T);
            double b = sky.z * T + cloud.z * (1-T);

            img.at(index + 0) = floatToByte(r);
            img.at(index + 1) = floatToByte(g);
            img.at(index + 2) = floatToByte(b); 
        }
        if ((y+1) % 10 == 0) cout << "Row #" << y+1 << " completed at " << time(NULL) - startTime << "s!\n";
    }

    stbi_write_png("out8.png", IMAGE_WIDTH, IMAGE_HEIGHT, 3, img.data(), IMAGE_WIDTH * 3);

    return 0;
}

char floatToByte(double color) {
    double value = color;
    if(color > 1.0) value = 1.0;
    if(color < 0.0) value = 0.0;

    value = pow(value, 1.0/2.2); // Something abt gamma to convert diff brightnesses

    char byte = (char)(value * 255.0 + 0.5); // 254.6 -> +0.5 -> 255.1 -> truncated to -> 255

    return byte;
}