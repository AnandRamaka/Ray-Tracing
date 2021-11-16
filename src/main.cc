#include <cstdlib>
#include <limits>

#include "util.hpp"
#include "vector3d.hpp"
#include "ray.hpp"
#include "writer.hpp"
#include "shapes/hittables.hpp"
#include "shapes/sphere.hpp"
#include "camera.hpp"

// Returns a random vector that is inside of the unit sphere
Vector3D randomInUnitSphere() {
  while (true) {
    Vector3D p = Vector3D::random(-1, 1);
    if(p.Magnitude() >= 1) continue;
    return p;
  }
}

// Returns a random vector that is on the unit sphere, mimics lambertian reflection
Vector3D randomUnitSphere() {
  return randomInUnitSphere().UnitVector();
}

Color output(const Ray& r, const Hittables& hittable, int depth) {
  // gradient from UIUC orange to blue
  if (depth <= 0)
    return Color(0, 0, 0);
  HitRecord hit;
  // 0.001 to remove shadow acne
  if(hittable.Hit(r, 0.001, std::numeric_limits<double>::infinity(), hit)) {
    // This doesn't actually "do" anything, it just allows us to make sure that the normal looks reasonable
    // should be a gradient circle
    // return 255*Color(hit.normal.GetX(), hit.normal.GetY(), hit.normal.GetZ()); // This one looks funky
    Vector3D target = hit.point + hit.normal + randomUnitSphere();
    return 0.5*output(Ray(hit.point, target - hit.point), hittable, depth - 1);
  }
  Vector3D unit = r.GetDirection().UnitVector();
  double t = 0.5 * (unit.GetY() + 1);
  return (1 - t) * Color(255, 255, 255) + t * Color(128, 180, 255);
}

int main(int argc, char *argv[]) {
  //NOTE: this sample will overwrite the file or test.png without warning!
  const char* filename = argc > 1 ? argv[1] : "test.png";

  std::vector<std::vector<Color>> image;
  size_t height = 225;
  size_t width = 400;
  double aspectRatio = width / (double) height;

  // Define hittable objects
  Hittables hittable_list;

  Sphere s1 = Sphere(Vector3D(0, 0, 1), 0.5);
  // Sphere s2 = Sphere(Vector3D(-2, 0, -1), 0.5);
  // Sphere s3 = Sphere(Vector3D(-1, 0, -1), 0.5);
  // Sphere s4 = Sphere(Vector3D(1, 0, -1), 0.5);
  Sphere s5 = Sphere(Vector3D(0, -100.5, 1), 100);

  hittable_list.Add(&s1);
  // hittable_list.Add(&s2);
  // hittable_list.Add(&s3);
  // hittable_list.Add(&s4);
  hittable_list.Add(&s5);

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
      for (int s = 0; s < 100; s++) {
        auto u = (j + random_double()) / (width);
        auto v = (height - i + random_double()) / (height);
        Ray r = camera.GetRayAt(u, v);
        pixel_color += output(r, hittable_list, depth) / 100;
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