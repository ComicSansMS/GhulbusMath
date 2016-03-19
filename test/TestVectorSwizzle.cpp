#include <gbMath/VectorSwizzle.hpp>

#include <catch.hpp>

#include <random>

TEST_CASE("VectorSwizzle")
{
    using GHULBUS_MATH_NAMESPACE::Vector2;
    SECTION("Vector2")
    {
        Vector2<int> v(1, 2);
        CHECK(swizzle(v).xx() == Vector2<int>(1, 1));
        CHECK(swizzle(v).xy() == Vector2<int>(1, 2));
        CHECK(swizzle(v).yx() == Vector2<int>(2, 1));
        CHECK(swizzle(v).yy() == Vector2<int>(2, 2));
        
    }
}
