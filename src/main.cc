#include <cstdlib>
#include "vector3d.hpp"
#include "ray.hpp"
#include "writer.hpp"
#include "shapes/hittables.hpp"
#include "shapes/sphere.hpp"
#include "camera.hpp"

Color output(const Ray& r, const Hittables& hittable) {
  // gradient from UIUC orange to blue
  HitRecord hit;
  if(hittable.Hit(r, hit)) {
    // This doesn't actually "do" anything, it just allows us to make sure that the normal looks reasonable
    // should be a gradient circle
    // return 255*Color(hit.normal.GetX(), hit.normal.GetY(), hit.normal.GetZ()); // This one looks funky
    return 0.5*255*Color(hit.normal.GetX() + 1, hit.normal.GetY() + 1, hit.normal.GetZ() + 1);
  }
  Vector3D unit = r.GetDirection().UnitVector();
  double t = 0.5 * (unit.GetY() + 1);
  return (1 - t) * Color(232, 74, 39) + t * Color(19, 41, 75);
}

int main(int argc, char *argv[]) {
  //NOTE: this sample will overwrite the file or test.png without warning!
  const char* filename = argc > 1 ? argv[1] : "test.png";

  std::vector<std::vector<Color>> image;
  size_t height = 1080;
  size_t width = 1920;
  double aspectRatio = width / (double) height;

  // Define hittable objects
  Hittables hittable_list;
  Sphere s1 = Sphere(Vector3D(-1, 0, -3), 0.5);
  Sphere s2 = Sphere(Vector3D(1, 0, -3), 0.5);

  hittable_list.Add(&s1);
  hittable_list.Add(&s2);

  // Camera definitions
  double viewHeight = 2.0;
  double viewWidth = aspectRatio * viewHeight;
  double focalLength = 4.0;
  Vector3D origin = Vector3D(0, 0, 0); // In camera coords, center is at 0

  Camera camera = Camera(viewHeight, viewWidth, focalLength, origin);

  for(size_t i = 0; i < height; i++) {
    std::vector<Color> row;
    for(size_t j = 0; j < width; j++) {
      auto u = (double)j/width;
      // We want to flip the v coordinate since raytracing starts at the upper left, otherwise it would start at lower left
      auto v = (double)(height - i)/height;
      Ray r = camera.GetRayAt(u, v);
      row.push_back(output(r, hittable_list));
    }
    image.push_back(row);
  }

  writeFile(image, filename);
}