#include "vector3d.hpp"
#include "ray.hpp"

class Camera {
public:
    Camera(double viewHeight, double viewWidth, double focal_length, Vector3D origin);

    // Gets the ray starting from the origin and in the direction of a position on the projection plane
    Ray GetRayAt(double u, double v);

private:

    Vector3D origin_; // In camera coords, center is at 0
    Vector3D horizontal_; // Vector pointing in the direction of the x-axis
    Vector3D vertical_; // Vector pointing in the direction of the y-axis
    Vector3D lower_left_; // Lower left corner, focalLength away

    double focal_length_; // This controls the "FOV". Things will get distorted if they move around unless we change this. Distance to camera
};