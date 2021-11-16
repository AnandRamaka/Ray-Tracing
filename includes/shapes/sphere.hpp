#include "vector3d.hpp"
#include "shapes/hittable.hpp"

class Sphere : public Hittable {
public:
    Sphere(const Vector3D loc, double radius) : _loc(loc), _r(std::abs(radius)) {};
    bool Hit(const Ray& r, double min, double max, HitRecord& out) const override;
    Vector3D GetLoc(){ return _loc; }
    double GetRadius(){ return _r; }

private:
    Vector3D _loc;
    double _r;
};