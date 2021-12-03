#include <cmath>
#include "shapes/triangle.hpp"


bool Triangle::Hit(const Ray& ray, [[maybe_unused]] double min, [[maybe_unused]] double max, HitRecord& out) const{
    
    // Vector3D dir_cross_e2 = ray.GetDirection().Cross( _e2 );
    // double det = _e1.Dot(dir_cross_e2);
    // if( std::abs(det) < EPSILON ){
    //     return false;
    // }

    // double f = 1.0 / det;
    // //std::cout << f << std::endl;

    // Vector3D pl_to_origin = ray.GetSource() - _p1;
    // double u = f * pl_to_origin.Dot( dir_cross_e2 );



    // if( u < 0 || u > 1 ){
    //     return false;
    // }


    // out.normal = _normal;

    // Vector3D origin_cross_e1 = ray.GetSource().Cross( _e1 );
    // double v = f * ray.GetDirection().Dot(origin_cross_e1);


    // std::cout << u << " " << v << std::endl;

    // if( v < 0 || (u + v) > 1){
    //     return false;
    // }
    // // Vector3D temp = _e1; 

    // // double t = temp.Dot(origin_cross_e1) *= f;
    // return true;

    float NdotRayDirection = _normal.Dot(ray.GetDirection());
    if( std::abs(NdotRayDirection) < EPSILON ){
        return false;
    }

    // std::cout << "past 1" << std::endl;

    float d = _normal.Dot(_p1);

    float t = (_normal.Dot(ray.GetSource()) + d ) / NdotRayDirection;


    double a = ray.GetDirection().Dot(ray.GetDirection()); 
    Vector3D A_minus_C = ray.GetSource() - _normal;
    double b = (2.0*ray.GetDirection()).Dot(A_minus_C); // (2b . (A - C))
    double c = A_minus_C.Dot(A_minus_C) - _normal.Dot(_normal);

    double discriminant = b*b - 4*a*c;


    if(t < min || t > max) {
        t = (-b + std::sqrt(discriminant))/(2.0 * a);
        if(t < min || t > max) {
            return false;
        }
    }
    // std::cout << "past 2" << std::endl;

    Vector3D P = ray.GetSource() + t * ray.GetDirection();

    if( std::isnan(P.GetX()) || std::isnan(P.GetY()) || std::isnan(P.GetZ()) ){
        return false;
    }

    // std::cout << P << std::endl;

    Vector3D C;

    Vector3D edge0 = _p2 - _p1;
    Vector3D vp0 = P - _p1;
    C = edge0.Cross(vp0);
    // std::cout << _normal.Dot(C) << std::endl;

    // std::cout << _normal.Dot(C) << std::endl;

    if( _normal.Dot(C) < 0 )
        return false;
      

    Vector3D edge1 = _p3 - _p2;
    Vector3D vp1 = P - _p2;
    C = edge1.Cross(vp1);

    // std::cout << _normal.Dot(C) << std::endl;

    if( _normal.Dot(C) < 0 )
        return false;    
    // std::cout << "past 4" << std::endl;
    
    Vector3D edge2 = _p1 - _p3;
    Vector3D vp2 = P - _p3;
    C = edge2.Cross(vp2);

    // std::cout << _normal.Dot(C) << std::endl;

    if( _normal.Dot(C) < 0 )
        return false;
    
    // std::cout << "past 5" << std::endl;

    // std::cout << "all tests passed" << std::endl;


    out.normal = _normal;
    out.mat = _mat;
    return true;
}