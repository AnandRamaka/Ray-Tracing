#include "shapes/sphere.hpp"

bool Sphere::Hit(const Ray& ray) const {
    // The equation for a hit is (P - C) . (P - C) = r^2, where P is any given point
    // Our ray is of the form P = A + tb, so we want to solve (A + tb - C) . (A + tb - C) = r^2
    // Expanding out, this is a quadratic in t of the form t^2 * (b . b) + t * (2b . (A - C)) + (A - C) . (A - C) - r^2
    Vector3D A_minus_C = ray.GetSource() - _loc;
    double a = ray.GetDirection().Dot(ray.GetDirection()); // (b . b)
    double b = (2.0*ray.GetDirection()).Dot(A_minus_C); // (2b . (A - C))
    double c = A_minus_C.Dot(A_minus_C) - _r*_r;

    return b*b - 4 * a * c > 0; // determinant is positive means that there is a hit
}