#include <cmath>

#include "vector3d.hpp"

/* -------- Constructors -------- */

Vector3D::Vector3D(double x, double y, double z) {
    coordinates_[0] = x;
    coordinates_[1] = y;
    coordinates_[2] = z;

};

Vector3D Vector3D::operator-() const {
    return Vector3D(-coordinates_[0], -coordinates_[1], -coordinates_[2]);
}

/* -------- Member Functions -------- */

Vector3D& Vector3D::operator+=(const Vector3D &vector) {
    coordinates_[0] += vector.GetX();
    coordinates_[1] += vector.GetY();
    coordinates_[2] += vector.GetZ();
    return *this;
}


Vector3D& Vector3D::operator-=(const Vector3D &vector) {
    return *this += -vector;
}

Vector3D& Vector3D::operator*=(const double t) {
    coordinates_[0] *= t;
    coordinates_[1] *= t;
    coordinates_[2] *= t;
    return *this;
}

Vector3D& Vector3D::operator/=(const double t) {
    return *this *= 1/t;
}

/* -------- Math Operation Functions -------- */

double Vector3D::Magnitude() const {
    return std::sqrt(coordinates_[0] * coordinates_[0] + coordinates_[1] * coordinates_[1] + coordinates_[2] * coordinates_[2]);
}

Vector3D Vector3D::UnitVector() const {
    return Vector3D{coordinates_[0]/Magnitude(), coordinates_[1]/Magnitude(), coordinates_[2]/Magnitude()};
}


double Vector3D::Dot(const Vector3D& other) const {
    return coordinates_[0] * other.GetX() + coordinates_[1] * other.GetY() + coordinates_[2] * other.GetZ();
}

Vector3D Vector3D::Cross(const Vector3D& other) const {
    double new_x = coordinates_[1] * other.GetZ() - coordinates_[2] * other.GetY();
    double new_y = -(coordinates_[0] * other.GetZ() - coordinates_[2] * other.GetX());
    double new_z = coordinates_[0] * other.GetY() - coordinates_[1] * other.GetX();

    return Vector3D{new_x, new_y, new_z};
}


/* -------- Friend Functions -------- */

Vector3D operator+(const Vector3D& v, const Vector3D& other) {
    return Vector3D(v.coordinates_[0] + other.coordinates_[0], v.coordinates_[1] + other.coordinates_[1], v.coordinates_[2] + other.coordinates_[2]);
}

Vector3D operator-(const Vector3D& v, const Vector3D& other) {
    return Vector3D(v.coordinates_[0] - other.coordinates_[0], v.coordinates_[1] - other.coordinates_[1], v.coordinates_[2] - other.coordinates_[2]);   
}

Vector3D operator*(const Vector3D& v, const Vector3D& other) {
    return Vector3D(v.coordinates_[0] * other.coordinates_[0], v.coordinates_[1] * other.coordinates_[1], v.coordinates_[2] * other.coordinates_[2]);
}

Vector3D operator*(const Vector3D& v, double t) {
    return Vector3D(v.coordinates_[0] * t, v.coordinates_[1] * t, v.coordinates_[2] * t);

}

Vector3D operator*(double t,const Vector3D& v) {
    return Vector3D(v.coordinates_[0] * t, v.coordinates_[1] * t, v.coordinates_[2] * t);
}

Vector3D operator/(const Vector3D& v, const Vector3D& other)
{
    return Vector3D(v.coordinates_[0]/ other.coordinates_[0], v.coordinates_[1]/other.coordinates_[1], v.coordinates_[2]/ other.coordinates_[2]);
}

Vector3D operator/(const Vector3D& v, double t) {
    return Vector3D(v.coordinates_[0] / t, v.coordinates_[1] / t, v.coordinates_[2] / t);

}

Vector3D operator/(double t, const Vector3D& v) {
    return Vector3D(t / v.coordinates_[0] , t / v.coordinates_[1], t / v.coordinates_[2]);
}

bool operator==(const Vector3D& v, const Vector3D& other) {
    return v.coordinates_[0] == other.coordinates_[0] && v.coordinates_[1] == other.coordinates_[1] && v.coordinates_[2] == other.coordinates_[2];
}

/* -------- Output to Stream -------- */

std::ostream& operator<<(std::ostream& os, const Vector3D& vector) {
    os << "(" << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << ")";
    return os;
}