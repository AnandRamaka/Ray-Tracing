#include "vector3d.hpp"
#include "ray.hpp"
#include <cmath>
#include "util.hpp"

class Camera {
public:
    Camera(Vector3D point_to_look_from, Vector3D point_to_look_at, double vertical_fov, double aspect_ratio, double distance_to_focus, double aperture);

    // Gets the ray starting from the origin and in the direction of a position on the projection plane
    Ray GetRayAt(double u, double v);

private:

    Vector3D origin_; // In camera coords, center is at 0
    Vector3D horizontal_; // Vector pointing in the direction of the x-axis
    Vector3D vertical_; // Vector pointing in the direction of the y-axis
    Vector3D lower_left_; // Lower left corner, focalLength away
    double thin_lens_radius; // The lens for our camera
    Vector3D u_; // orthonormal vector that describes the camera's orientation
    Vector3D v_; // orthonormal vector that describes the camera's orientation

    double DegreesToRadians(double degrees);
};