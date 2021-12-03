#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "util.hpp"

TEST_CASE("Random", "") {
    
    SECTION ("Random in Unit Sphere")
    {
        Vector3D vec = randomInUnitSphere();
        REQUIRE (vec.Magnitude() < 1);
        REQUIRE ((vec.GetX() >= -1 && vec.GetX() <= 1 && vec.GetY() >= -1 && vec.GetY() <= 1 && vec.GetZ()>=-1 && vec.GetZ() <= 1));

    }
    SECTION ("Random Unit Sphere")
    {
        Vector3D vec = randomUnitSphere();
        REQUIRE (vec.Magnitude() == 1);
        REQUIRE ((vec.GetX() >= -1 && vec.GetX() <= 1 && vec.GetY() >= -1 && vec.GetY() <= 1 && vec.GetZ()>=-1 && vec.GetZ() <= 1));
    }

    SECTION ("Random in Unit Disk")
    {
        Vector3D vec = randomInUnitDisk();
        REQUIRE (vec.Magnitude() < 1);
        REQUIRE ((vec.GetX() >= -1 && vec.GetX() <= 1 && vec.GetY() >= -1 && vec.GetY() <= 1 && vec.GetZ() == 0));   
    }
}


#endif