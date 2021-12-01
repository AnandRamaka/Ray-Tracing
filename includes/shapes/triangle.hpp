#include "vector3d.hpp"
#include "shapes/hittable.hpp"
#include <vector>

class Triangle: public Hittable {
public:
    Triangle(const Vector3D p1, const Vector3D p2, const Vector3D p3, Material * m ) : _p1(p1), _p2(p2), _p3(p3), _mat(m){
        _e1 = _p2 - _p1;
        _e2 = _p3 - _p1;
        _normal = _e1.Cross(_e2);
    };
    bool Hit(const Ray& r, [[maybe_unused]] double min, [[maybe_unused]] double max, HitRecord& out) const override;
    std::vector<Vector3D> GetPoints() const{ return {_p1, _p2, _p3}; }

    void SetEpsilon(double e){
        EPSILON = e;
    }

private:
    Vector3D _p1, _p2, _p3;
    Vector3D _e1, _e2;
    Vector3D _normal;
    double EPSILON = .00001;
    Material * _mat;
};