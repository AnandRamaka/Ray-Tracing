#pragma once

#include "ray.hpp"

// we need to do this because materials and hit record are circular
class Material;

class HitRecord {
public:
    Vector3D point;
    Vector3D normal;
    Material* mat;
    double t;
    bool frontFacing;
};

class Hittable {
public:
    virtual bool Hit(const Ray& r, double min, double max, HitRecord& out) const = 0;
};