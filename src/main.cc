#include <cstdlib>
#include "vector3d.hpp"
#include "writer.hpp"

int main(int argc, char *argv[]) {
  //NOTE: this sample will overwrite the file or test.png without warning!
  const char* filename = argc > 1 ? argv[1] : "test.png";

  std::vector<std::vector<Color>> image;
  size_t height = 400;
  size_t width = 600;
  for(size_t i = 0; i < height; i++) {
    std::vector<Color> row;
    for(size_t j = 0; j < width; j++) {
      row.push_back(Vector3D(rand() % 255, rand() % 255, rand() % 255));
    }
    image.push_back(row);
  }

  writeFile(image, filename);
}