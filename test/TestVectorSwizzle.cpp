#include <gbMath/VectorSwizzle.hpp>

#include <catch.hpp>

#include <random>

TEST_CASE("VectorSwizzle")
{
    SECTION("Vector2")
    {
        using GHULBUS_MATH_NAMESPACE::Vector2;
        Vector2<int> v(1, 2);
        CHECK(swizzle(v).xx() == Vector2<int>(1, 1));
        CHECK(swizzle(v).xy() == Vector2<int>(1, 2));
        CHECK(swizzle(v).yx() == Vector2<int>(2, 1));
        CHECK(swizzle(v).yy() == Vector2<int>(2, 2));
    }

    SECTION("Vector3")
    {
        using GHULBUS_MATH_NAMESPACE::Vector3;
        Vector3<int> v(1, 2, 3);
        CHECK(swizzle(v).xxx() == Vector3<int>(1, 1, 1));
        CHECK(swizzle(v).xxy() == Vector3<int>(1, 1, 2));
        CHECK(swizzle(v).xxz() == Vector3<int>(1, 1, 3));
        CHECK(swizzle(v).xyx() == Vector3<int>(1, 2, 1));
        CHECK(swizzle(v).xyy() == Vector3<int>(1, 2, 2));
        CHECK(swizzle(v).xyz() == Vector3<int>(1, 2, 3));
        CHECK(swizzle(v).xzx() == Vector3<int>(1, 3, 1));
        CHECK(swizzle(v).xzy() == Vector3<int>(1, 3, 2));
        CHECK(swizzle(v).xzz() == Vector3<int>(1, 3, 3));
        CHECK(swizzle(v).yxx() == Vector3<int>(2, 1, 1));
        CHECK(swizzle(v).yxy() == Vector3<int>(2, 1, 2));
        CHECK(swizzle(v).yxz() == Vector3<int>(2, 1, 3));
        CHECK(swizzle(v).yyx() == Vector3<int>(2, 2, 1));
        CHECK(swizzle(v).yyy() == Vector3<int>(2, 2, 2));
        CHECK(swizzle(v).yyz() == Vector3<int>(2, 2, 3));
        CHECK(swizzle(v).yzx() == Vector3<int>(2, 3, 1));
        CHECK(swizzle(v).yzy() == Vector3<int>(2, 3, 2));
        CHECK(swizzle(v).yzz() == Vector3<int>(2, 3, 3));
        CHECK(swizzle(v).zxx() == Vector3<int>(3, 1, 1));
        CHECK(swizzle(v).zxy() == Vector3<int>(3, 1, 2));
        CHECK(swizzle(v).zxz() == Vector3<int>(3, 1, 3));
        CHECK(swizzle(v).zyx() == Vector3<int>(3, 2, 1));
        CHECK(swizzle(v).zyy() == Vector3<int>(3, 2, 2));
        CHECK(swizzle(v).zyz() == Vector3<int>(3, 2, 3));
        CHECK(swizzle(v).zzx() == Vector3<int>(3, 3, 1));
        CHECK(swizzle(v).zzy() == Vector3<int>(3, 3, 2));
        CHECK(swizzle(v).zzz() == Vector3<int>(3, 3, 3));
    }
}
