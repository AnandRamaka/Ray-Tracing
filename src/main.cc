#include <iostream>

#include "ray.hpp"

int main() {
    Vector3D v1 {0, 0, 0};
    Vector3D v2 {1, 2, 3};

    std::cout << v1 + v2 << std::endl;
    std::cout << v1.Dot(v2) << std::endl;

    Ray r {v1, v2};

    std::cout << r.GetAt(2) << std::endl;

    Vector3D a {2, 3, 4};
    Vector3D b {5, 6, 7};
    
    std::cout << a.Dot(b) << std::endl;
    std::cout << a.Cross(b).Dot(a) << std::endl;
}