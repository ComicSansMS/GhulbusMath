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

}
