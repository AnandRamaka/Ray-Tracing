#include "camera.hpp"

Camera::Camera(double view_height, double view_width, double focal_length, Vector3D origin) : origin_(origin), focal_length_(focal_length) {
    horizontal_ = Vector3D(view_width, 0, 0);
    vertical_ = Vector3D(0, view_height, 0);
    lower_left_ = origin - horizontal_/2 - vertical_/2 - Vector3D(0, 0, focal_length_);
}

Ray Camera::GetRayAt(double u, double v) {
    Ray r(origin_, lower_left_ + u*horizontal_ + v*vertical_ - origin_);
    return r;
}