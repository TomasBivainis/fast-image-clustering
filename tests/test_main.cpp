#include <catch2/catch_test_macros.hpp>
#include "Vec3.hpp"

TEST_CASE("Vec3 Math Works", "[vec3]") {
    Vec3 v1(1, 2, 3);
    Vec3 v2(4, 5, 6);
    Vec3 result = v1 + v2;

    REQUIRE(result.x == 5);
    REQUIRE(result.y == 7);
    REQUIRE(result.z == 9);
}