#include "camera.hpp"

Camera::Camera(Vector3D point_to_look_from, Vector3D point_to_look_at, double vertical_fov, double aspect_ratio, double distance_to_focus, double aperture) : origin_(point_to_look_from), thin_lens_radius(aperture / 2.0) {
    // Implement a vertical fov. This determines the plane that the rays intersect with. 
    // The larger the fov, the more of the scene will be present.

    double theta = DegreesToRadians(vertical_fov);
    double height_factor = tan(theta/2);
    double view_height = height_factor;
    double view_width = aspect_ratio * view_height;

    // Allows the camera to be movable. In order to do this, we must find the orthonormal vectors that
    // describe the camera's orientation. The vector normal to this plane is in the direction of the point that we are looking at.

    Vector3D up_vector = Vector3D(0, 1, 0); // Prevents camera rotation in the xy plane
    Vector3D vector_towards_point_to_look_at = (point_to_look_from - point_to_look_at).UnitVector();
    u_ = up_vector.Cross(vector_towards_point_to_look_at).UnitVector(); //first orthonormal vector
    v_ = vector_towards_point_to_look_at.Cross(u_); //second orthonormal vector

    horizontal_ = distance_to_focus * view_width * u_;
    vertical_ = distance_to_focus * view_height * v_;
    lower_left_ = origin_ - horizontal_/2 - vertical_/2 - distance_to_focus * vector_towards_point_to_look_at;
}

double Camera::DegreesToRadians(double degrees) {
    return degrees * (M_PI / 180);
}

Ray Camera::GetRayAt(double u, double v) {
    // In order to add focus and blur, we can generate random rays originating 
    // from inside a unit disk centered at the point that we are looking from. 
    Vector3D rd = thin_lens_radius * randomInUnitDisk();
    Vector3D offset = u_ * rd.GetX() + v_ * rd.GetY();

    Ray r(origin_ + offset, lower_left_ + u*horizontal_ + v*vertical_ - origin_ - offset);
    return r;
}