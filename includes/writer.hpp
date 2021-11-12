#pragma once

#include <vector>
#include "lodepng.h"
#include "vector3d.hpp"

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void writeFile(std::vector<std::vector<Color>> image, std::string filename) {
    auto height = image.size();
    auto width = image[0].size();

    std::vector<unsigned char> imagePixels(width * height * 4);
    for(unsigned y = 0; y < height; y++)
    for(unsigned x = 0; x < width; x++) {
        imagePixels[4 * width * y + 4 * x + 0] = image[y][x].GetX();
        imagePixels[4 * width * y + 4 * x + 1] = image[y][x].GetY();
        imagePixels[4 * width * y + 4 * x + 2] = image[y][x].GetZ();
        imagePixels[4 * width * y + 4 * x + 3] = 255;
    }

      encodeOneStep(filename.c_str(), imagePixels, width, height);


}