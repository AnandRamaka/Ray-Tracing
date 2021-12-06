#include <cmath>
#include "shapes/triangle.hpp"


bool Triangle::Hit(const Ray& ray, [[maybe_unused]] double min, [[maybe_unused]] double max, HitRecord& out) const{
    
    out.normal = _normal;
    out.mat = _mat;
   
    double NdotRayDirection = _normal.Dot(ray.GetDirection());
    if( std::abs(NdotRayDirection) < EPSILON ){
        std::cout << "case 1: " << _normal << std::endl;
        return false;
    }

    double d = _normal.Dot(_p1);
    double t = (_normal.Dot(ray.GetSource()) + d ) / NdotRayDirection;

    if(_normal.UnitVector().Dot(ray.GetDirection()) > 0.0) {
        t = (-_normal.Dot(ray.GetSource()) + d ) / NdotRayDirection;  
    }

    if(t < min || t > max) {
        return false;
    }

    Vector3D P = ray.GetAt(t);
    out.point = P;

    if( std::isnan(P.GetX()) || std::isnan(P.GetY()) || std::isnan(P.GetZ()) ){
        std::cout << "case 3" << std::endl;
        return false;

    }

    Vector3D C;
    Vector3D edge0 = _p2 - _p1;
    Vector3D vp0 = P - _p1;
    C = edge0.Cross(vp0);

    if( _normal.Dot(C) < 0 )
        return false;
      

    Vector3D edge1 = _p3 - _p2;
    Vector3D vp1 = P - _p2;
    C = edge1.Cross(vp1);

    if( _normal.Dot(C) < 0 )
        return false;    
    
    Vector3D edge2 = _p1 - _p3;
    Vector3D vp2 = P - _p3;
    C = edge2.Cross(vp2);

    if( _normal.Dot(C) < 0 )
        return false;
    
    return true;
}