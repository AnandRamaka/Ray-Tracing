#include "camera.hpp"

Camera::Camera(Vector3D point_to_look_from, Vector3D point_to_look_at, double vertical_fov, double aspect_ratio) : origin_(point_to_look_from) {
    
    // Implement a vertical fov. This determines the plane that the rays intersect with. 
    // The larger the fov, the more of the scene will be present.

    double theta = DegreesToRadians(vertical_fov);
    double h = tan(theta/2);
    double view_height = 2.0 * h;
    double view_width = aspect_ratio * view_height;

    // Allows the camera to be movable. In order to do this, we must find the orthonormal vectors that
    // describe the camera's orientation. The vector normal to this plane is in the direction of the point that we are looking at.

    Vector3D up_vector = Vector3D(0, 1, 0); // Prevents camera rotation in the xy plane
    Vector3D vector_towards_point_to_look_at = (point_to_look_from - point_to_look_at).UnitVector();
    Vector3D u = up_vector.Cross(vector_towards_point_to_look_at).UnitVector(); //first orthonormal vector
    Vector3D v = vector_towards_point_to_look_at.Cross(u); //second orthonormal vector

    horizontal_ = view_width * u;
    vertical_ = view_height * v;
    lower_left_ = origin_ - horizontal_/2 - vertical_/2 - vector_towards_point_to_look_at;
}

double Camera::DegreesToRadians(double degrees) {
    return degrees * (M_PI / 180);
}

Ray Camera::GetRayAt(double u, double v) {
    Ray r(origin_, lower_left_ + u*horizontal_ + v*vertical_ - origin_);
    return r;
}