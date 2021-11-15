#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ray.hpp"

TEST_CASE("Vectors", "") {

    SECTION("Constructor") {
        Vector3D vec{};
        Vector3D vec2(0, 0, 0);
        Vector3D vec3(1, 2, 3);

        REQUIRE(vec == vec2);
        REQUIRE_FALSE(vec2 == vec3);
    }

    SECTION("Negating") {
        Vector3D vec{1, 2, 3};
        Vector3D vec2(-1, -2, -3);
        Vector3D vec3(-1, 2, -3);

        REQUIRE(-vec == vec2);
        REQUIRE_FALSE(-vec == vec3);
    }

    SECTION("Addition Operations") {
        Vector3D vec{1, 2, 3};
        Vector3D vec2{4, 0, 3};
        Vector3D vec3{5, 2, 6};
        vec += vec2;

        REQUIRE(vec == vec3);

        Vector3D vec4 = vec2 + vec3;
        Vector3D vec5{9, 2, 9};

        REQUIRE(vec4 == vec5);
    }

    SECTION("Subtraction Operations") {
        Vector3D vec{1, 2, 3};
        Vector3D vec2{4, 0, 3};
        Vector3D vec3{-3, 2, 0};
        vec -= vec2;

        REQUIRE(vec == vec3);

        Vector3D vec4 = vec2 - vec3;
        Vector3D vec5{7, -2, 3};

        REQUIRE(vec4 == vec5);
    }

    SECTION("Scalar Multiplication Operations") {
        Vector3D vec{1, 2, 3};
        Vector3D vec2{-2, -4, -6};

        vec *= -2;

        REQUIRE(vec == vec2);

        Vector3D vec3 = -0.5 * vec2;

        REQUIRE(vec3 == Vector3D{1, 2, 3});
    }

    SECTION("Element-Wise Multiplication Operations") {
        Vector3D vec4{2, 3, 4};
        Vector3D vec5{5, 4, -1};
        Vector3D vec6{10, 12, -4};

        REQUIRE(vec4 * vec5 == vec6);
    }

    SECTION("Division Operations") {
        Vector3D vec{1, 2, 3};
        Vector3D vec2{-0.5, -1, -1.5};

        vec /= -2;

        REQUIRE(vec == vec2);

        Vector3D vec3 = vec2 / -0.5;

        REQUIRE(vec3 == Vector3D{1, 2, 3});
    }

    SECTION("Magnitude & Unit Vector") {
        Vector3D vec{6, -7, 2};
        double magnitude = sqrt(89);

        REQUIRE(vec.Magnitude() == magnitude);

        REQUIRE(vec.UnitVector() == Vector3D{6/magnitude, -7/magnitude, 2/magnitude}); 
    }

    SECTION("Dot Product") {
        Vector3D a{2, 3, 4};
        Vector3D b{5, 6, 7};

        REQUIRE(a.Dot(b) == 56);
    }

    SECTION("Cross Product") {
        Vector3D a{2, 3, 4};
        Vector3D b{5, 6, 7};

        REQUIRE(a.Cross(b) == Vector3D{-3, 6, -3});
    }
}

TEST_CASE("Rays", "") {

    SECTION("Constructor") {

        Vector3D source{1, 2, 3};
        Vector3D direction{2, 4, 6};

        Ray ray{source, direction};

        REQUIRE(ray.GetSource() == source);
        REQUIRE(ray.GetDirection() == direction);
    }

    SECTION("Get At") {
        Vector3D source{0, 1, 0};
        Vector3D direction{1, -1, 2};

        Ray ray{source, direction};

        REQUIRE(ray.GetAt(0) == source);
        REQUIRE(ray.GetAt(10) == Vector3D{10, -9, 20});
        REQUIRE(ray.GetAt(-2) == Vector3D{-2, 3, -4});
    }
}

#endif

