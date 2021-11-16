#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ray.hpp"
#include "shapes/sphere.hpp"

TEST_CASE("Sphere", "") {

    SECTION("Constructor") {
        Vector3D loc(1, 2, 3);
        Sphere s(loc, 5.0);

        REQUIRE( s.GetLoc() == loc );
        REQUIRE( s.GetRadius() == 5.0 );

        Vector3D loc2(2, 1, -1);
        Sphere s2(loc2, -5.0);

        REQUIRE( s2.GetLoc() == loc2 );
        REQUIRE( s2.GetRadius() == 5.0 );
    }

}

#endif

