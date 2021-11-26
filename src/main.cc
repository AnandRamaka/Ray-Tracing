#include <cstdlib>
#include <limits>

#include "util.hpp"
#include "vector3d.hpp"
#include "ray.hpp"
#include "writer.hpp"
#include "shapes/hittables.hpp"
#include "shapes/sphere.hpp"
#include "camera.hpp"
#include "materials/lambertian.hpp"
#include "materials/metal.hpp"

Color output(const Ray& r, const Hittables& hittable, int depth) {
  // prevents from recursing for too long
  if (depth <= 0)
    return Color(0, 0, 0);
  HitRecord hit;
  // 0.001 to remove shadow acne
  if(hittable.Hit(r, 0.001, std::numeric_limits<double>::infinity(), hit)) {
    Ray scattered;
    Color attenuation;
    if (hit.mat->Scatter(r, hit, attenuation, scattered))
        return (attenuation / 255) * output(scattered, hittable, depth-1);
    return Color(0, 0, 0);
  }
  Vector3D unit = r.GetDirection().UnitVector();
  double t = 0.5 * (unit.GetY() + 1);
  return (1 - t) * Color(255, 255, 255) + t * Color(128, 180, 255);
}

int main(int argc, char *argv[]) {
  //NOTE: this sample will overwrite the file or test.png without warning!
  const char* filename = argc > 1 ? argv[1] : "test.png";
  size_t height = argc > 2 ? atoi(argv[2]) : 225;
  size_t width = argc > 3 ? atoi(argv[3]) : 400;

  std::vector<std::vector<Color>> image;
  double aspectRatio = width / (double) height;

  // Define hittable objects
  Hittables hittable_list;

  Metal blue(Color(0, 0, 200));
  Lambertian orange(Color(233, 74, 39));
  Lambertian red(Color(200, 0, 0));
  Metal green(Color(0, 200, 0));

  Sphere s1 = Sphere(Vector3D(-1.5, 0, 1), 0.5, &blue);
  Sphere s2 = Sphere(Vector3D(0, -100.5, 1), 100, &orange);
  Sphere s3 = Sphere(Vector3D(1.5, 0, 1), 0.5, &red);
  Sphere s4 = Sphere(Vector3D(0, 0, 1), 0.5, &green);

  hittable_list.Add(&s1);
  hittable_list.Add(&s2);
  hittable_list.Add(&s3);
  hittable_list.Add(&s4);

  // Camera definitions
  double vertical_fov = 120;
  Vector3D look_from = Vector3D(0, 0, -1);
  Vector3D look_at = Vector3D(0, 0, 1);

  Camera camera = Camera(look_from, look_at, vertical_fov, aspectRatio);

  int depth = 50;

  for(size_t i = 0; i < height; i++) {
    std::vector<Color> row;
    for(size_t j = 0; j < width; j++) {
      Color pixel_color(0, 0, 0);
      for (int s = 0; s < 10; s++) {
        auto u = (j + random_double()) / (width);
        auto v = (height - i + random_double()) / (height);
        Ray r = camera.GetRayAt(u, v);
        pixel_color += output(r, hittable_list, depth) / 10;
      }
      row.push_back(pixel_color);

      // progress counter
      std::cout << int((float)(i)/height * 100.0) << " %\r";
      std::cout.flush();
    }
    image.push_back(row);
  }

  writeFile(image, filename);
}