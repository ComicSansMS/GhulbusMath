#include <gbMath/Sphere3.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

#include <limits>

TEST_CASE("Sphere3")
{
    using GHULBUS_MATH_NAMESPACE::Sphere3;
    using GHULBUS_MATH_NAMESPACE::Point3;

    SECTION("Value initialization initializes to 0")
    {
        Sphere3<int> sphere{};
        CHECK(sphere.center == Point3<int>(0, 0, 0));
        CHECK(sphere.radius == 0);
    }

    SECTION("Construction from point and radius")
    {
        Sphere3<float> s(Point3<float>(1.f, 2.f, 3.f), 4.f);
        CHECK(s.center == Point3<float>(1.f, 2.f, 3.f));
        CHECK(s.radius == 4.f);
    }

    SECTION("Point-sphere intersection")
    {
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 1.f, 1.f), 2.f),
                         Point3<float>(2.f, 1.f, 1.f)));
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 1.f, 1.f), 2.f),
                         Point3<float>(3.f, 1.f, 1.f)));
        CHECK(!intersects(Sphere3<float>(Point3<float>(1.f, 1.f, 1.f), 2.f),
                          Point3<float>(3.f + 1.e-6f, 1.f, 1.f)));
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 2.f, 3.f), 2.f + 1e-6f),
                         Point3<float>(1.f + std::sqrt(2.f), 2.f + std::sqrt(2.f), 3.f)));
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 2.f, 3.f), 2.f + 1e-6f),
                         Point3<float>(1.f + std::sqrt(2.f), 2.f, 3.f + std::sqrt(2.f))));
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 2.f, 3.f), 2.f + 1e-6f),
                         Point3<float>(1.f, 2.f + std::sqrt(2.f), 3.f + std::sqrt(2.f))));
        CHECK(!intersects(Sphere3<float>(Point3<float>(1.f, 2.f, 3.f), 2.f),
                          Point3<float>(1.f + std::sqrt(2.f), 2.f + std::sqrt(2.f), 3.f)));
    }

    SECTION("Sphere-sphere intersection")
    {
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 1.f, 1.f), 2.f),
                         Sphere3<float>(Point3<float>(1.f, 1.f, 1.f), 2.f)));
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 1.f, 1.f), 2.f),
                         Sphere3<float>(Point3<float>(5.f, 1.f, 1.f), 2.f)));
        CHECK(!intersects(Sphere3<float>(Point3<float>(1.f, 1.f, 1.f), 2.f),
                          Sphere3<float>(Point3<float>(5.f + 1.e-6f, 1.f, 1.f), 2.f)));
        CHECK(!intersects(Sphere3<float>(Point3<float>(1.f, 1.f, 1.f), 2.f),
                          Sphere3<float>(Point3<float>(5.f + 1.e-6f, 1.f, 1.f), 2.f)));
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 2.f, 3.f), 1.f + 1e-6f),
                         Sphere3<float>(Point3<float>(1.f + std::sqrt(2.f), 2.f + std::sqrt(2.f), 3.f), 1.f)));
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 2.f, 3.f), 1.f + 1e-6f),
                         Sphere3<float>(Point3<float>(1.f + std::sqrt(2.f), 2.f, 3.f + std::sqrt(2.f)), 1.f)));
        CHECK(intersects(Sphere3<float>(Point3<float>(1.f, 2.f, 3.f), 1.f + 1e-6f),
                         Sphere3<float>(Point3<float>(1.f, 2.f + std::sqrt(2.f), 3.f + std::sqrt(2.f)), 1.f)));
        CHECK(!intersects(Sphere3<float>(Point3<float>(1.f, 2.f, 3.f), 1.f),
                          Sphere3<float>(Point3<float>(1.f + std::sqrt(2.f), 2.f + std::sqrt(2.f), 3.f), 1.f)));
    }
}