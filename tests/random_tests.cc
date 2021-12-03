#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "shapes/util.hpp"

TEST_CASE("Random", "") {
    
    SECTION ("Random in Unit Sphere")
    {
        Vector3D vec = randomInUnitSphere();
        REQUIRE (vec.GetX() >= -1 && vec.GetX() <= 1 && vec.GetY() >= -1 && vec.GetY() <= 1 && vec.GetZ()>=-1 && vec.GetZ() <= 1);

    }
    SECTION ("Random Unit Sphere")
    {
        Vector3D vec = randomUnitSphere();
        REQUIRE ((vec.GetX()^2 + vec.GetY()^2 + vec.GetZ()^2) == 1);
        REQUIRE (vec.GetX() >= -1 && vec.GetX() <= 1 && vec.GetY() >= -1 && vec.GetY() <= 1 && vec.GetZ()>=-1 && vec.GetZ() <= 1);
    }

    SECTION ("Random in Unit Disk")
    {
        Vector3D vec = randomInUnitDisk();
        REQUIRE (vec.GetX()^2 + vec.GetY()^2 == 1)
        REQUIRE (vec.GetX() >= -1 && vec.GetX() <= 1 && vec.GetY() >= -1 && vec.GetY() <= 1 && vec.GetZ() == 0);   

    }
}


