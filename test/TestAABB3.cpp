#include <gbMath/AABB3.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("AABB3")
{
    using GHULBUS_MATH_NAMESPACE::AABB3;
    using GHULBUS_MATH_NAMESPACE::Point3;
    using GHULBUS_MATH_NAMESPACE::Vector3;

    SECTION("Value initialization initializes to 0")
    {
        AABB3<int> aabb{};
        CHECK(aabb.min == Point3<int>(0, 0, 0));
        CHECK(aabb.max == Point3<int>(0, 0, 0));
    }

    SECTION("Construction from single point")
    {
        Point3<int> const p(1, 2, 3);
        AABB3<int> aabb(p);
        CHECK(aabb.min == p);
        CHECK(aabb.max == p);
    }

    SECTION("Construction from explicitly provided min and max")
    {
        Point3<int> const pmin(2, 3, 6);
        Point3<int> const pmax(1, 4, 5);
        AABB3<int> aabb(pmin, pmax);
        CHECK(aabb.min == pmin);
        CHECK(aabb.max == pmax);
    }

    SECTION("Equality and not-equal comparisons")
    {
        CHECK(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) ==
              AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)));
        CHECK_FALSE(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) !=
                    AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)));

        CHECK_FALSE(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) ==
                    AABB3<int>(Point3<int>(2, 2, 3), Point3<int>(4, 5, 6)));
        CHECK_FALSE(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) ==
                    AABB3<int>(Point3<int>(2, 1, 3), Point3<int>(4, 5, 6)));
        CHECK_FALSE(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) ==
                    AABB3<int>(Point3<int>(1, 1, 3), Point3<int>(4, 5, 6)));
        CHECK_FALSE(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) ==
                    AABB3<int>(Point3<int>(1, 2, 1), Point3<int>(4, 5, 6)));
        CHECK_FALSE(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) ==
                    AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(1, 5, 6)));
        CHECK_FALSE(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) ==
                    AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 1, 6)));
        CHECK_FALSE(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) ==
                    AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 1)));
        CHECK(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) !=
              AABB3<int>(Point3<int>(2, 2, 3), Point3<int>(4, 5, 6)));
        CHECK(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) !=
              AABB3<int>(Point3<int>(2, 1, 3), Point3<int>(4, 5, 6)));
        CHECK(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) !=
              AABB3<int>(Point3<int>(1, 1, 3), Point3<int>(4, 5, 6)));
        CHECK(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) !=
              AABB3<int>(Point3<int>(1, 2, 1), Point3<int>(4, 5, 6)));
        CHECK(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) !=
              AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(1, 5, 6)));
        CHECK(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) !=
              AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 1, 6)));
        CHECK(AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 6)) !=
              AABB3<int>(Point3<int>(1, 2, 3), Point3<int>(4, 5, 1)));
    }


    SECTION("Empty box has min bigger and max smaller than any valid number")
    {
        AABB3<float> aabb = GHULBUS_MATH_NAMESPACE::empty_aabb3<float>();
        CHECK(aabb.min == Point3<float>(std::numeric_limits<float>::max(),
                                        std::numeric_limits<float>::max(),
                                        std::numeric_limits<float>::max()));
        CHECK(aabb.max == Point3<float>(std::numeric_limits<float>::lowest(),
                                        std::numeric_limits<float>::lowest(),
                                        std::numeric_limits<float>::lowest()));
    }

    SECTION("Diagonal is the vector from min to max")
    {
        CHECK(diagonal(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(4.f, 5.f, 6.f))) ==
            Vector3<float>(3.f, 3.f, 3.f));
        CHECK(diagonal(AABB3<float>(Point3<float>(5.f, 12.f, 4.5f), Point3<float>(15.f, 20.f, 5.f))) ==
            Vector3<float>(10.f, 8.f, 0.5f));
    }

    SECTION("Enclose encloses additional points into the bounding volume")
    {
        AABB3<float> aabb = GHULBUS_MATH_NAMESPACE::empty_aabb3<float>();
        aabb = enclose(aabb, Point3<float>(1.f, 2.f, 3.f));
        CHECK(aabb.min == Point3<float>(1.f, 2.f, 3.f));
        CHECK(aabb.max == Point3<float>(1.f, 2.f, 3.f));
        aabb = enclose(aabb, Point3<float>(0.f, 5.f, -3.f));
        CHECK(aabb.min == Point3<float>(0.f, 2.f, -3.f));
        CHECK(aabb.max == Point3<float>(1.f, 5.f, 3.f));
    }

    SECTION("Enclose encloses two volumes into one")
    {
        AABB3<float> aabb = GHULBUS_MATH_NAMESPACE::empty_aabb3<float>();
        aabb = enclose(aabb, AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(10.f, 20.f, 30.f)));
        CHECK(aabb.min == Point3<float>(1.f, 2.f, 3.f));
        CHECK(aabb.max == Point3<float>(10.f, 20.f, 30.f));
        aabb = enclose(aabb, AABB3<float>(Point3<float>(-1.f, 5.f, 2.f), Point3<float>(-10.f, 25.f, 32.f)));
        CHECK(aabb.min == Point3<float>(-1.f, 2.f, 2.f));
        CHECK(aabb.max == Point3<float>(10.f, 25.f, 32.f));
    }

    SECTION("AABB-Point intersect test")
    {
        CHECK(intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f)), Point3<float>(1.f, 2.f, 3.f)));
        CHECK(intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                         Point3<float>(1.5f, 2.5f, 3.5f)));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          Point3<float>(0.5f, 2.5f, 3.5f)));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          Point3<float>(1.5f, 1.5f, 3.5f)));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          Point3<float>(1.5f, 2.5f, 2.5f)));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          Point3<float>(2.5f, 2.5f, 3.5f)));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          Point3<float>(1.5f, 3.5f, 3.5f)));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          Point3<float>(1.5f, 2.5f, 4.5f)));
    }

    SECTION("AABB-AABB intersect test")
    {
        CHECK(intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                         AABB3<float>(Point3<float>(-1.f, -2.f, -3.f), Point3<float>(4.f, 6.f, 8.f))));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          AABB3<float>(Point3<float>(3.f, -2.f, -3.f), Point3<float>(4.f, 6.f, 8.f))));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          AABB3<float>(Point3<float>(-1.f, 4.f, -3.f), Point3<float>(4.f, 6.f, 8.f))));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          AABB3<float>(Point3<float>(-1.f, -2.f, 5.f), Point3<float>(4.f, 6.f, 8.f))));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          AABB3<float>(Point3<float>(-1.f, -2.f, -3.f), Point3<float>(0.f, 6.f, 8.f))));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          AABB3<float>(Point3<float>(-1.f, -2.f, -3.f), Point3<float>(4.f, -1.f, 8.f))));
        CHECK(!intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                          AABB3<float>(Point3<float>(-1.f, -2.f, -3.f), Point3<float>(4.f, 6.f, -2.f))));
        CHECK(intersects(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                         AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f))));
    }

    SECTION("AABB-AABB Union")
    {
        CHECK(union_aabb(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                         AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f))) ==
              AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)));
        CHECK(union_aabb(AABB3<float>(Point3<float>( 1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                         AABB3<float>(Point3<float>(-1.f, 1.f, 5.f), Point3<float>(4.f, 2.f, 6.f))) ==
              AABB3<float>(Point3<float>(-1.f, 1.f, 3.f), Point3<float>(4.f, 3.f, 6.f)));
    }

    SECTION("AABB-AABB Intersect")
    {
        CHECK(intersect_aabb(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                             AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f))) ==
              AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)));

        CHECK(intersect_aabb(AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                             AABB3<float>(Point3<float>(-1.f, -2.f, -3.f), Point3<float>(0.f, 0.f, 0.f))) ==
              AABB3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(0.f, 0.f, 0.f)));

        CHECK(intersect_aabb(AABB3<float>(Point3<float>( 1.f, 2.f, 3.f), Point3<float>(2.f, 3.f, 4.f)),
                             AABB3<float>(Point3<float>(-1.f, 1.f, 5.f), Point3<float>(4.f, 2.f, 6.f))) ==
              AABB3<float>(Point3<float>(1.f, 2.f, 5.f), Point3<float>(2.f, 2.f, 4.f)));
    }
}
