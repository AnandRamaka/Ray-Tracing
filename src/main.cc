#include <cstdlib>
#include <limits>
#include <utility>

#include "util.hpp"
#include "vector3d.hpp"
#include "ray.hpp"
#include "writer.hpp"
#include "shapes/hittables.hpp"
#include "shapes/sphere.hpp"
#include "shapes/triangle.hpp"
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
        return attenuation * output(scattered, hittable, depth-1);
    return Color(0, 0, 0);
  }
  Vector3D unit = r.GetDirection().UnitVector();
  double t = 0.5 * (unit.GetY() + 1);
  return (1 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1.0);
}

std::pair<Hittables*, Camera*> LargeScene(double aspectRatio) {
  Hittables* hittable_list = new Hittables();

  for (int i = -12; i < 12; ++i) {
    for (int j = -12; j < 12; ++j) {
      double choose_mat = random_double();
      Vector3D center(i + 0.9 * random_double(), 0.2, j + 0.9 * random_double());

      if ((center - Vector3D(4, 0.2, 0)).Magnitude() > 0.9) {

          if (choose_mat < 0.65) {
              // diffuse
              Vector3D albedo = Vector3D::random() * Vector3D::random();
              Lambertian* sphere_material = new Lambertian(albedo);
              Sphere* s = new Sphere(center, 0.2, sphere_material);
              hittable_list->Add(s);
          } else {
              // metal
              Vector3D albedo = Vector3D::random(0.5, 1);
              Metal* sphere_material = new Metal(albedo);
              Sphere* s = new Sphere(center, 0.2, sphere_material);
              hittable_list->Add(s);
          }
      }
    }
  }

  Lambertian* ground = new Lambertian(Color(0.5, 0.5, 0.5));
  Sphere* ground_sphere = new Sphere(Vector3D(0, -1000, 0), 1000, ground);

  hittable_list->Add(ground_sphere);

  Metal* center_material = new Metal(Vector3D(0.7, 0.6, 0.5));
  Sphere* center_sphere = new Sphere(Vector3D(0, 1, 0), 1.0, center_material);
  hittable_list->Add(center_sphere);

  // Camera definitions
  double vertical_fov = 40;
  Vector3D look_from = Vector3D(12, 2, 3);
  Vector3D look_at = Vector3D(0, 0, 0);
  double distance_to_focus = 12.0;
  double aperture = 0.1;

  Camera* camera = new Camera(look_from, look_at, vertical_fov, aspectRatio, distance_to_focus, aperture);
  return std::make_pair(hittable_list, camera);
}

std::pair<Hittables*, Camera*> SimpleScene(double aspectRatio, Vector3D look_from, double vertical_fov) {
  Hittables* hittable_list = new Hittables();

  Lambertian* ground = new Lambertian(Color(0.8, 0.8, 0));
  Lambertian* center = new Lambertian(Color(0.1, 0.2, 0.5));
  Metal* left = new Metal(Color(0.1, 0.3, 0.5));
  Metal* right = new Metal(Color(0.8, 0.6, 0.2));

  Sphere* s1 = new Sphere(Vector3D(0.0, -100.5, -1.0), 100.0, ground);
  Sphere* s2 = new Sphere(Vector3D(-1.0, 0.0, 1.0), 0.5, center);
  Sphere* s3 = new Sphere(Vector3D(0.0, 0.0, 1.0), 0.5, left);
  Sphere* s4 = new Sphere(Vector3D(1.0, 0.0, 1.0), 0.5, right);

  hittable_list->Add(s1);
  hittable_list->Add(s2);
  hittable_list->Add(s3);
  hittable_list->Add(s4);  

  // Camera definitions
  Vector3D look_at = Vector3D(0, 0, 1);

  Camera* camera = new Camera(look_from, look_at, vertical_fov, aspectRatio); 

  return std::make_pair(hittable_list, camera);
}

std::pair<Hittables*, Camera*> TriangleScene(double aspectRatio) {
  // Define hittable objects
  Hittables* hittable_list = new Hittables();

  Lambertian* t_red = new Lambertian(Color(0.8, 0, 0));
  Lambertian* t_blue = new Lambertian(Color(0, 0, 0.8));
  Lambertian* t_green = new Lambertian(Color(0, 0.8, 0));

  Triangle* t = new Triangle(Vector3D(-0.5, 0.5, -1), Vector3D(0, 1.5, -1), Vector3D(0.5, 0.5, -1), t_red);
  Triangle* t2 = new Triangle(Vector3D(-0.5, 0.5, -2), Vector3D(0, 1.5, -1), Vector3D(0.5, 0.5, -1), t_blue);
  Triangle* t3 = new Triangle(Vector3D(-0.5, 0.5, -2), Vector3D(0, 1.5, -1), Vector3D(-0.5, 0.5, -1), t_green);

  Lambertian* ground = new Lambertian(Color(0.8, 0.8, 0));
  Metal* right = new Metal(Color(0.8, 0.6, 0.2));

  Sphere* s1 = new Sphere(Vector3D(0.0, -100.5, -1.0), 100.0, ground);
  Sphere* s2 = new Sphere(Vector3D(0.9, 0.0, -0.5), 0.5, right);

  hittable_list->Add(s1);
  hittable_list->Add(s2);   
  hittable_list->Add(t);
  hittable_list->Add(t2);
  hittable_list->Add(t3);


  // Camera definitions
  double vertical_fov = 120;
  Vector3D look_from = Vector3D(0, 0, 1);
  Vector3D look_at = Vector3D(0, 0, -1);

  Camera* camera = new Camera(look_from, look_at, vertical_fov, aspectRatio);

  return std::make_pair(hittable_list, camera);
}


int main(int argc, char *argv[]) {
  // //NOTE: this sample will overwrite the file or test.png without warning!

  const char* filename = argc > 1 ? argv[1] : "scene.png";
  size_t height = argc > 2 ? atoi(argv[2]) : 225;
  size_t width = argc > 3 ? atoi(argv[3]) : 440;
  size_t chosen_scene = argc > 4 ? atoi(argv[4]) : 1;

  std::vector<std::vector<Color>> image;
  double aspectRatio = width / (double) height;
  
  /* Specify which scene you want to generate.
     You can also provide your own creating a Hittable object.
   */

  std::pair<Hittables*, Camera*> settings;

  if (chosen_scene == 2) {
    settings = SimpleScene(aspectRatio, Vector3D(4, 2, -3), 40);
  } else if (chosen_scene == 3) {
    settings = TriangleScene(aspectRatio);
  } else if (chosen_scene == 4) {
    settings = LargeScene(aspectRatio);
  } else {
    settings = SimpleScene(aspectRatio, Vector3D(0, 0, -1), 120);
  }

  /* Produces ray traced image */

  Hittables* world = settings.first;
  Camera* camera = settings.second;

  int depth = 50;

  for(size_t i = 0; i < height; i++) {
    std::vector<Color> row;
    for(size_t j = 0; j < width; j++) {
      Color pixel_color(0, 0, 0);
      for (int s = 0; s < 10; s++) {
        auto u = (j + random_double()) / (width);
        auto v = (height - i + random_double()) / (height);
        Ray r = camera->GetRayAt(u, v);
        pixel_color += output(r, *world, depth) / 10;
      }
      row.push_back(pixel_color * 255);

      // progress counter
      std::cout << int((float)(i)/height * 100.0) << " %\r";
      std::cout.flush();
    }
    image.push_back(row);
  }

  writeFile(image, filename);
}