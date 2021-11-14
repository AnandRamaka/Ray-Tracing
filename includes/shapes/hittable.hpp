#pragma once

#include "ray.hpp"

class Hittable {
public:
    virtual bool Hit(const Ray& r) const = 0;
};