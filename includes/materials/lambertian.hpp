#include "materials/material.hpp"
#include "util.hpp"

// Diffuse, Lambertian material
class Lambertian : public Material {
public:

    Lambertian(const Color& color) : albedo_(color) {}

    // we will need the ray for other types of materials, but not for this one
    virtual bool Scatter([[maybe_unused]] const Ray& _, const HitRecord& hit, Color& attenuation, Ray& scattered) const override {
        Vector3D randomDirection = randomUnitSphere();
        auto scatter_direction = hit.normal + randomDirection;
        if(scatter_direction.NearZero()) {
            scatter_direction = hit.normal;
        }
        scattered = Ray(hit.point, scatter_direction);
        attenuation = albedo_;
        return true;
    }

private:
    Color albedo_;
};