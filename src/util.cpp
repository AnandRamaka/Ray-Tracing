#include <random>
#include "util.hpp"

double random_range(double lower, double upper) {
  return lower + (upper - lower) * random_double();
}

double random_double() { return rand() / (RAND_MAX + 1.0); }

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