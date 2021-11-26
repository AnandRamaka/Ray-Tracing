#include "materials/metal.hpp"

bool Metal::Scatter(const Ray& r, const HitRecord& hit, Color& attenuation, Ray& scattered) const {
    Vector3D reflected_vector = Reflect(r.GetDirection().UnitVector(), hit.normal);
    scattered = Ray(hit.point, reflected_vector);
    attenuation = albedo_;

    // Returns true only if the scattered ray is pointing away from the surface
    return (scattered.GetDirection().Dot(hit.normal) > 0);
}

Vector3D Metal::Reflect(Vector3D in_vector, Vector3D normal) const {
    Vector3D vec_along = in_vector.Dot(normal) * normal;
    return in_vector - 2 * vec_along; 
}
