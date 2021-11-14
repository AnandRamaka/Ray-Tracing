#include "vector3d.hpp"
#include "shapes/hittable.hpp"

class Sphere : Hittable {
public:
    Sphere(const Vector3D loc, double radius) : _loc(loc), _r(radius) {};
    bool Hit(const Ray& r) const;

private:
    Vector3D _loc;
    double _r;
};