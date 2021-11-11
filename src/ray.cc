#include "ray.hpp"

Vector3D Ray::GetSource() const {
    return source_;
}

Vector3D Ray::GetDirection() const {
    return direction_;
}

Vector3D Ray::GetAt(double t) {
    return source_ + t * direction_;
}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    os << "Source: " << ray.GetSource() << std::endl;
    os << "Direction: " << ray.GetDirection();
    return os;
}