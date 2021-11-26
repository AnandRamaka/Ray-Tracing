#pragma once

#include "vector3d.hpp"
#include "ray.hpp"

class HitRecord;

class Material {
public:
    virtual bool Scatter(const Ray& r, const HitRecord& hit, Color& attenuation, Ray& scattered) const = 0;
};