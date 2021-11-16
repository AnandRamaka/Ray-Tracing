#include <cmath>
#include "shapes/sphere.hpp"

bool Sphere::Hit(const Ray& ray, HitRecord& out) const {
    // The equation for a hit is (P - C) . (P - C) = r^2, where P is any given point
    // Our ray is of the form P = A + tb, so we want to solve (A + tb - C) . (A + tb - C) = r^2
    // Expanding out, this is a quadratic in t of the form t^2 * (b . b) + t * (2b . (A - C)) + (A - C) . (A - C) - r^2
    Vector3D A_minus_C = ray.GetSource() - _loc;
    double a = ray.GetDirection().Dot(ray.GetDirection()); // (b . b)
    double b = (2.0*ray.GetDirection()).Dot(A_minus_C); // (2b . (A - C))
    double c = A_minus_C.Dot(A_minus_C) - _r*_r;

    double discriminant = b*b - 4*a*c;
    if(discriminant < 0) {
        return false;
    } else {
        auto t = (-b - std::sqrt(discriminant))/(2.0 * a); // use closest t for now, -b - discriminant instead of +discriminant
        out.t = t; // t
        out.point = ray.GetAt(t); // point of intersection


        out.normal = (out.point - _loc) / _r;
        if( ray.GetDirection().Dot(out.normal) > 0.0 ){
            out.frontFacing = false;
        } else {
            out.frontFacing = true;
        }
        if( !out.frontFacing ){
           out.normal = -out.normal;
        }

         // normalize the normal vector
        return true;

    }
}