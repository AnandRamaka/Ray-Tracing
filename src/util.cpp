#include <random>
#include "util.hpp"

double random_range(double lower, double upper) {
    static std::uniform_real_distribution<double> dist(lower, upper);
    static std::mt19937 gen;
    return dist(gen);
}

double random_double() { return random_range(0.0, 1.0); }

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