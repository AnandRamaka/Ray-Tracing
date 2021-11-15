#include "vector3d.hpp"
#include "ray.hpp"

class Camera {
public:
    Camera(double viewHeight, double viewWidth, double focal_length, Vector3D origin);
    Ray GetRayAt(double u, double v);

private:

    Vector3D origin_; // In camera coords, center is at 0
    Vector3D horizontal_; // vector pointing in the direction of the x-axis
    Vector3D vertical_; // vector pointing in the direction of the y-axis
    Vector3D lower_left_; // lower left corner, focalLength away

    double focal_length_; // this controls the "FOV". Things will get distorted if they move around unless we change this. Distance to camera
};