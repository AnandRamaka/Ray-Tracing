#ifndef RAY_HPP
#define RAY_HPP

#include "vector3d.hpp"

class Ray {
public:
    Ray() = default;
    Ray(Vector3D source, Vector3D direction) : source_{source}, direction_{direction} {};

    Vector3D GetSource() const;
    Vector3D GetDirection() const;

    Vector3D GetAt(double t);
    
private:
    Vector3D source_;
    Vector3D direction_;
};

std::ostream& operator<<(std::ostream& os, const Ray& ray);


#endif