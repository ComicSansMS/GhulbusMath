#include <gbMath/Vector3.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

#include <vector>

TEST_CASE("Vector3")
{
    using GHULBUS_MATH_NAMESPACE::Vector3;

    SECTION("Value initialization initializes to 0")
    {
        Vector3<float> v{};

        CHECK(v.x == 0.0f);
        CHECK(v.y == 0.0f);
        CHECK(v.z == 0.0f);
    }

    SECTION("Construction from 3 values")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
        CHECK(v.z == 17.0f);
    }

    SECTION("Copy construction")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);

        Vector3<float> v2(v);
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
        CHECK(v2.z == 17.0f);
    }

    SECTION("Copy assignment")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);

        Vector3<float> v2;

        v2 = v;
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
        CHECK(v2.z == 17.0f);
    }

    SECTION("Conversion construction")
    {
        Vector3<float> v(42.f, 23.5f, 17.0f);

        Vector3<int> vi(v);
        CHECK(vi.x == 42);
        CHECK(vi.y == 23);
        CHECK(vi.z == 17);
    }

    SECTION("Equality and not-equal comparisons")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);
        Vector3<float> v2(v);

        CHECK(v == v2);
        CHECK_FALSE(v != v2);

        v2.x = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);

        v.x = v2.x;
        CHECK(v == v2);
        v2.y = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);

        v.y = v2.y;
        CHECK(v == v2);
        v2.z = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);
    }
}
