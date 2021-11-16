#pragma once

#include "hittable.hpp"
#include <vector>

class Hittables: public Hittable {
public:
    Hittables() = default;
    void Add(Hittable* hittable);
    bool Hit(const Ray& r, double min, double max, HitRecord& out) const override;
private:
    std::vector<Hittable*> hittable_vector_;
};