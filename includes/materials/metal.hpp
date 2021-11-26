#include "vector3d.hpp"
#include "materials/material.hpp"
#include "shapes/hittable.hpp"

class Metal : public Material {
public:
    Metal(const Color& color) : albedo_(color) {}

    // Instead of scattering rays, metals reflect
    bool Scatter(const Ray& r, const HitRecord& hit, Color& attenuation, Ray& scattered) const override;

    // Calculates the vector reflecting off a surface describied by a normal vector
    Vector3D Reflect(Vector3D in, Vector3D normal) const;
private:
    Color albedo_;
};