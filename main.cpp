#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "consts.h"
#include "texture.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

char floatToByte(double color);

int main() {
    srand(0);

    vector<char> img(IMAGE_WIDTH * IMAGE_HEIGHT); // Outdated: 3 chars for each pixel cus 1 char = 1 byte = 1 color channel
    Texture t(8);
    LayeredWorley lw(8);

    for(int y = 0; y < IMAGE_HEIGHT; y++) {
        for(int x = 0; x < IMAGE_WIDTH; x++) {
            int index = ((y * IMAGE_WIDTH) + x);
            // img.at(index + 0) = (255 * x) / IMAGE_WIDTH; // red
            // img.at(index + 1) = (255 * y) / IMAGE_HEIGHT; // green
            // img.at(index + 2) = (255 * x) / IMAGE_WIDTH; // blue
            double u = 2 * (double)x / IMAGE_WIDTH;
            double v = 2 * (double)y / IMAGE_HEIGHT;

            double finalFBmValue = t.sample(u, v, 0, COVERAGE);

            img.at(index + 0) = (char)((255 * finalFBmValue));
        }
        if ((y+1) % 10 == 0) cout << "Row #" << y+1 << " completed!\n";
    }

    stbi_write_png("out7.png", IMAGE_WIDTH, IMAGE_HEIGHT, 1, img.data(), IMAGE_WIDTH);

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