#include "vector3d.hpp"
#include "shapes/hittable.hpp"

class Sphere : public Hittable {
public:
    Sphere(const Vector3D loc, double radius) : _loc(loc), _r(radius) {};
    bool Hit(const Ray& r, HitRecord& out) const override;

private:
    Vector3D _loc;
    double _r;
};