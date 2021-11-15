
#include "shapes/hittables.hpp"

void Hittables::Add(Hittable* hittable) {
    hittable_vector_.push_back(hittable);
}

bool Hittables::Hit(const Ray& r, HitRecord& out) const {

    bool did_hit = false;
    HitRecord temp_record;
    double smallest_t = -1;

    for (size_t i = 0; i < hittable_vector_.size(); i++) {
        if (hittable_vector_.at(i)->Hit(r, temp_record)) {
            did_hit = true;
            if (smallest_t == -1 || smallest_t > temp_record.t) {
                smallest_t = temp_record.t;
                out = temp_record;
            }
        }
    }
    return did_hit;
}


