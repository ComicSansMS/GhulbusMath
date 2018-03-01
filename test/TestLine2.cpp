#include <gbMath/Line2.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("Line2")
{
    using GHULBUS_MATH_NAMESPACE::Line2;
    using GHULBUS_MATH_NAMESPACE::Point2;
    using GHULBUS_MATH_NAMESPACE::Vector2;

    SECTION("Zero Initialization")
    {
        Line2<float> l{};
        CHECK(l.p == Point2<float>(0.f, 0.f));
        CHECK(l.v == Vector2<float>(0.f, 0.f));
    }

    SECTION("Construction from point and vector")
    {
        Line2<float> l(Point2<float>(1.f, 2.f), Vector2<float>(-3.f, 4.f));
        CHECK(l.p == Point2<float>(1.f, 2.f));
        CHECK(l.v == Vector2<float>(-3.f, 4.f));
    }

    SECTION("Construction from two points")
    {
        Line2<float> l(Point2<float>(1.f, 2.f), Point2<float>(-3.f, 5.f));
        CHECK(l.p == Point2<float>(1.f, 2.f));
        CHECK(l.v == Vector2<float>(-4.f, 3.f));
    }

    SECTION("Normalization")
    {
        Line2<float> l = normalized(Line2<float>(Point2<float>(1.f, 2.f), Point2<float>(-3.f, 5.f)));
        CHECK(l.p == Point2<float>(1.f, 2.f));
        CHECK(l.v == Vector2<float>(-4.f/5.f, 3.f/5.f));
        CHECK(length(l.v) == 1.f);
    }

    SECTION("Distance Point-Line")
    {
        Line2<float> const l0(Point2<float>(0.f, 0.f), Vector2<float>(1.f, 1.f));
        auto const l0_norm = normalized(l0);
        Line2<float> const l1(Point2<float>(-3.f, 2.5f), Vector2<float>(3.f, -1.f));
        auto const l1_norm = normalized(l1);

        Point2<float> const p0(5.f, -2.f);
        CHECK(distance_squared(l0, p0) == 24.5f);
        CHECK(distance(l0, p0) == std::sqrt(24.5f));
        CHECK(distance_squared_unit(l0_norm, p0) == 24.5f);
        CHECK(distance_unit(l0_norm, p0) == std::sqrt(24.5f));

        CHECK(distance_squared(l1, p0) == Approx(3.025f));
        CHECK(distance(l1, p0) == Approx(std::sqrt(3.025f)));
        CHECK(distance_squared_unit(l1_norm, p0) == Approx(3.025f));
        CHECK(distance_unit(l1_norm, p0) == Approx(std::sqrt(3.025f)));

        Point2<float> const p1(-4.f, -1.f);
        CHECK(distance_squared(l0, p1) == 4.5f);
        CHECK(distance(l0, p1) == std::sqrt(4.5f));
        CHECK(distance_squared_unit(l0_norm, p1) == 4.5f);
        CHECK(distance_unit(l0_norm, p1) == std::sqrt(4.5f));

        CHECK(distance_squared(l1, p1) == 13.225f);
        CHECK(distance(l1, p1) == std::sqrt(13.225f));
        CHECK(distance_squared_unit(l1_norm, p1) == 13.225f);
        CHECK(distance_unit(l1_norm, p1) == std::sqrt(13.225f));
    }
}
