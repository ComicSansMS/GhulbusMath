#include <gbMath/AABB2.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("AABB2")
{
    using GHULBUS_MATH_NAMESPACE::AABB2;
    using GHULBUS_MATH_NAMESPACE::Point2;

    SECTION("Value initialization initializes to 0")
    {
        AABB2<int> aabb{};
        CHECK(aabb.min == Point2<int>(0, 0));
        CHECK(aabb.max == Point2<int>(0, 0));
    }

    SECTION("Construction from single point")
    {
        Point2<int> const p(1, 2);
        AABB2<int> aabb(p);
        CHECK(aabb.min == p);
        CHECK(aabb.max == p);
    }

    SECTION("Construction from explicitly provided min and max")
    {
        Point2<int> const pmin(2, 3);
        Point2<int> const pmax(1, 4);
        AABB2<int> aabb(pmin, pmax);
        CHECK(aabb.min == pmin);
        CHECK(aabb.max == pmax);
    }

    SECTION("Empty box has min bigger and max smaller than any valid number")
    {
        AABB2<float> aabb = GHULBUS_MATH_NAMESPACE::empty_aabb2<float>();
        CHECK(aabb.min == Point2<float>(std::numeric_limits<float>::max(),
                                        std::numeric_limits<float>::max()));
        CHECK(aabb.max == Point2<float>(std::numeric_limits<float>::lowest(),
                                        std::numeric_limits<float>::lowest()));
    }

    SECTION("Enclose encloses additional points into the bounding volume")
    {
        AABB2<float> aabb = GHULBUS_MATH_NAMESPACE::empty_aabb2<float>();
        aabb = enclose(aabb, Point2<float>(1.f, 2.f));
        CHECK(aabb.min == Point2<float>(1.f, 2.f));
        CHECK(aabb.max == Point2<float>(1.f, 2.f));
        aabb = enclose(aabb, Point2<float>(0.f, 5.f));
        CHECK(aabb.min == Point2<float>(0.f, 2.f));
        CHECK(aabb.max == Point2<float>(1.f, 5.f));
    }

    SECTION("Enclose encloses two volumes into one")
    {
        AABB2<float> aabb = GHULBUS_MATH_NAMESPACE::empty_aabb2<float>();
        aabb = enclose(aabb, AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(10.f, 20.f)));
        CHECK(aabb.min == Point2<float>(1.f, 2.f));
        CHECK(aabb.max == Point2<float>(10.f, 20.f));
        aabb = enclose(aabb, AABB2<float>(Point2<float>(-1.f, 5.f), Point2<float>(-10.f, 25.f)));
        CHECK(aabb.min == Point2<float>(-1.f, 2.f));
        CHECK(aabb.max == Point2<float>(10.f, 25.f));
    }

    SECTION("AABB-Point intersect test")
    {
        CHECK(intersects(AABB2<float>(Point2<float>(1.f, 2.f)), Point2<float>(1.f, 2.f)));
        CHECK(intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                         Point2<float>(1.5f, 2.5f)));
        CHECK(!intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                          Point2<float>(0.5f, 2.5f)));
        CHECK(!intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                          Point2<float>(1.5f, 1.5f)));
        CHECK(!intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                          Point2<float>(2.5f, 2.5f)));
        CHECK(!intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                          Point2<float>(1.5f, 3.5f)));
    }

    SECTION("AABB-AABB intersect test")
    {
        CHECK(intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                         AABB2<float>(Point2<float>(-1.f, -2.f), Point2<float>(4.f, 6.f))));
        CHECK(!intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                          AABB2<float>(Point2<float>(3.f, -2.f), Point2<float>(4.f, 6.f))));
        CHECK(!intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                          AABB2<float>(Point2<float>(-1.f, 4.f), Point2<float>(4.f, 6.f))));
        CHECK(!intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                          AABB2<float>(Point2<float>(-1.f, -2.f), Point2<float>(0.f, 6.f))));
        CHECK(!intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                          AABB2<float>(Point2<float>(-1.f, -2.f), Point2<float>(4.f, -1.f))));
        CHECK(intersects(AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f)),
                         AABB2<float>(Point2<float>(1.f, 2.f), Point2<float>(2.f, 3.f))));
    }
}
