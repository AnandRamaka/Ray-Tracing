#pragma once

#include "ray.hpp"

class HitRecord {
public:
    Vector3D point;
    Vector3D normal;
    double t;
    bool frontFacing;
};

class Hittable {
public:
    virtual bool Hit(const Ray& r, HitRecord& out) const = 0;
};