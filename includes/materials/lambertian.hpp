#include "materials/material.hpp"
#include "util.hpp"

// Diffuse, Lambertian material
class Lambertian : public Material {
public:

    Lambertian(const Color& col) : albedo(col) {}

    // we will need the ray for other types of materials, but not for this one
    virtual bool scatter([[maybe_unused]] const Ray& _, const HitRecord& hit, Color& attenuation, Ray& scattered) const override {
        auto scatter_direction = hit.normal + randomUnitSphere();
        if(scatter_direction.NearZero()) {
            scatter_direction = hit.normal;
        }
        scattered = Ray(hit.point, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};