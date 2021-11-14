#include <cstdlib>
#include "vector3d.hpp"
#include "ray.hpp"
#include "writer.hpp"
#include "shapes/sphere.hpp"

Color output(const Ray& r) {
  // gradient from UIUC orange to blue
  Sphere s = Sphere(Vector3D(0, 0, -1), 0.5);
  if(s.Hit(r)) {
    return Color(0, 255, 0);
  }
  Vector3D unit = r.GetDirection().UnitVector();
  double t = 0.5 * (unit.GetY() + 1);
  return (1 - t) * Color(232, 74, 39) + t * Color(19, 41, 75);
}

int main(int argc, char *argv[]) {
  //NOTE: this sample will overwrite the file or test.png without warning!
  const char* filename = argc > 1 ? argv[1] : "test.png";

  std::vector<std::vector<Color>> image;
  size_t height = 225;
  size_t width = 400;
  double aspectRatio = width / (double) height;

  // Camera definitions
  auto viewHeight = 2.0;
  auto viewWidth = aspectRatio * viewHeight;
  auto focalLength = 1.0;

  auto origin = Vector3D(0, 0, 0);
  auto horizontal = Vector3D(viewWidth, 0, 0);
  auto vertical = Vector3D(0, viewHeight, 0);
  auto lower_left = origin - horizontal/2 - vertical/2 - Vector3D(0, 0, focalLength);

  for(size_t i = 0; i < height; i++) {
    std::vector<Color> row;
    for(size_t j = 0; j < width; j++) {
      auto u = (double)j/width;
      auto v = (double)i/height;
      Ray r(origin, lower_left + u*horizontal + v*vertical - origin);
      row.push_back(output(r));

    }
    image.push_back(row);
  }

  writeFile(image, filename);
}