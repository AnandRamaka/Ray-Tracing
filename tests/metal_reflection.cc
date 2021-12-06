#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "materials/metal.hpp"

TEST_CASE("Metal Reflection", "")
{
    SECTION("Reflection")
    {
        //test with positive values
        Vector3D vec(1,1,1);
        Vector3D normal(1,2,3);
        Vector3D result(-11, -23, -35);

        Vector3D albedo = Vector3D::random(0.5, 1);
        Metal* metal = new Metal(albedo);

        REQUIRE(metal->Reflect(vec,normal) == result);

        //tests with negative values 

        Vector3D vec2(1,-1,1);
        Vector3D normal2(1,2,-3);
        
        Vector3D result2(9,15,-23);

        REQUIRE(metal->Reflect(vec2,normal2) == result2);
        


    }
}

#endif