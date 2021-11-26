#pragma once
#include "vector3d.hpp"
#include <cstdlib>

double random_range(double lower, double upper);

double random_double();

// Returns a random vector that is inside of the unit sphere
Vector3D randomInUnitSphere();

// Returns a random vector that is on the unit sphere, mimics lambertian reflection
Vector3D randomUnitSphere();