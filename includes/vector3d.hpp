#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#include <iostream>
#include <cmath>

class Vector3D {
    public:
        Vector3D() = default;
        Vector3D(double x, double y, double z);

        static Vector3D random(double lower, double upper);
        static Vector3D random();


        Vector3D operator-() const;
        Vector3D& operator+=(const Vector3D &vector);
        Vector3D& operator-=(const Vector3D &vector);
        Vector3D& operator*=(const double scalar);
        Vector3D& operator/=(const double scalar);

        double GetX() const {return coordinates_[0];}
        double GetY() const {return coordinates_[1];}
        double GetZ() const {return coordinates_[2];}
        bool NearZero() const { return (std::fabs(coordinates_[0]) < 1e-8) && (std::fabs(coordinates_[1]) < 1e-8) && (std::fabs(coordinates_[2]) < 1e-8); }

        double Magnitude() const;
        Vector3D UnitVector() const;

        double Dot(const Vector3D& other) const;
        Vector3D Cross(const Vector3D& other) const;

        friend Vector3D operator+(const Vector3D& v, const Vector3D& other);
        friend Vector3D operator-(const Vector3D& v, const Vector3D& other);
        friend Vector3D operator*(const Vector3D& v, const Vector3D& other);
        friend Vector3D operator*(const Vector3D& v, double t);
        friend Vector3D operator*(double t, const Vector3D& v);
        friend Vector3D operator/(const Vector3D& v, const Vector3D& other);
        friend Vector3D operator/(const Vector3D& v, double t);
        friend Vector3D operator/(double t, const Vector3D& v);
        friend bool operator==(const Vector3D& v, const Vector3D& other);

    private:
        double coordinates_[3];
};

std::ostream& operator<<(std::ostream& os, const Vector3D& vector);

typedef Vector3D Color;

#endif