#include <gbMath/Vector2.hpp>

#include <catch.hpp>

#include <xmmintrin.h>

#include <random>

TEST_CASE("Vector2")
{
    using GHULBUS_MATH_NAMESPACE::Vector2;
    std::mt19937 gen(42);

    SECTION("Default construction initializes to 0")
    {
        Vector2<float> v;

        CHECK(v.x == 0.0f);
        CHECK(v.y == 0.0f);
    }

    SECTION("Construction from 2 values")
    {
        Vector2<float> v(42.0f, 23.5f);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
    }

    SECTION("Copy construction")
    {
        Vector2<float> v(42.0f, 23.5f);

        Vector2<float> v2(v);
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
    }

    SECTION("Copy assignment")
    {
        Vector2<float> v(42.0f, 23.5f);

        Vector2<float> v2(GHULBUS_MATH_NAMESPACE::leave_uninitialized{});

        v2 = v;
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
    }

    SECTION("Equality comparison")
    {
        Vector2<float> v(42.0f, 23.5f);
        Vector2<float> v2(v);

        CHECK(v == v2);
        v2.x = 55.0f;
        CHECK_FALSE(v == v2);

        CHECK(v != v2);
        v.x = v2.x;
        CHECK_FALSE(v != v2);
    }

    SECTION("Array index operator")
    {
        Vector2<float> v(42.0f, 23.5f);
        CHECK(v[0] == 42.0f);
        CHECK(v[1] == 23.5f);
        v[1] = 55.0f;
        CHECK(v[1] == 55.0f);

        Vector2<float> v_arr[] = { Vector2<float>(1.0f, 2.0f), Vector2<float>(3.0f, 4.0f) };
        CHECK(v_arr[0][0] == 1.0f);
        CHECK(v_arr[0][1] == 2.0f);
        CHECK(v_arr[1][0] == 3.0f);
        CHECK(v_arr[1][1] == 4.0f);
    }

    SECTION("Array index const operator")
    {
        Vector2<float> const v_const(42.0f, 23.5f);
        CHECK(v_const[0] == 42.0f);
        CHECK(v_const[1] == 23.5f);
    }

    SECTION("Vector Addition Member")
    {
        Vector2<float> v1(11.f, 22.f);
        v1 += Vector2<float>(33.f, 44.f);

        CHECK(v1.x == 44.f);
        CHECK(v1.y == 66.f);
        CHECK((v1 += Vector2<float>()) == v1);
    }

    SECTION("Vector Addition Non-Member")
    {
        Vector2<float> v = Vector2<float>(11.f, 22.f) + Vector2<float>(33.f, 44.f);

        CHECK(v.x == 44.f);
        CHECK(v.y == 66.f);
    }

    SECTION("Vector Subtraction Member")
    {
        Vector2<float> v1(11.f, 22.f);
        v1 -= Vector2<float>(5.f, 14.f);

        CHECK(v1.x == 6.f);
        CHECK(v1.y == 8.f);
        CHECK((v1 -= Vector2<float>()) == v1);
    }

    SECTION("Vector Subtraction Non-Member")
    {
        Vector2<float> v = Vector2<float>(11.f, 22.f) - Vector2<float>(5.f, 14.f);

        CHECK(v.x == 6.f);
        CHECK(v.y == 8.f);
    }
}
