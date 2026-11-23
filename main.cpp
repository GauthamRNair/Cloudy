#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "consts.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<char> img(IMAGE_WIDTH * IMAGE_HEIGHT * 3); // 3 chars for each pixel cus 1 char = 1 byte = 1 color channel

    for(int y = 0; y < IMAGE_HEIGHT; y++) {
        for(int x = 0; x < IMAGE_WIDTH; x++) {
            int index = ((y * IMAGE_WIDTH) + x) * 3;
            img.at(index + 0) = (255 * x) / IMAGE_WIDTH; // red
            img.at(index + 1) = (255 * y) / IMAGE_HEIGHT; // green
            img.at(index + 2) = (255 * x) / IMAGE_WIDTH; // blue

        }
    }

    stbi_write_png("test.png", IMAGE_WIDTH, IMAGE_HEIGHT, 3, img.data(), IMAGE_WIDTH * 3);

    return 0;
}