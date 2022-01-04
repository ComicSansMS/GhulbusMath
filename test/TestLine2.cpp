#include <gbMath/Line2.hpp>
#include <gbMath/VectorIO.hpp>

#include <cmath>
#include <limits>

#include <catch.hpp>

#ifdef _MSC_VER
#   pragma warning(disable: 4723)
#endif

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

    SECTION("Evaluate line equation at a specific parameter")
    {
        Line2<int> l(Point2<int>(1, 2), Point2<int>(-3, 5));
        CHECK(l.evaluate_at_parameter(0) == l.p);
        CHECK(l.evaluate_at_parameter(1) == l.p + l.v);
        CHECK(l.evaluate_at_parameter(0.5f) == Point2<float>(l.p) + (Vector2<float>(l.v) / 2.f));
        CHECK(l.evaluate_at_parameter(2.5) == Point2<double>(l.p) + (Vector2<double>(l.v) * 2.5));
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

    SECTION("Scaled Line2 Intersection Zero Initialization")
    {
        using GHULBUS_MATH_NAMESPACE::ScaledLine2Intersection;
        ScaledLine2Intersection<int> sli{};
        CHECK(sli.t1 == 0);
        CHECK(sli.t2 == 0);
        CHECK(sli.inverse_scale_factor == 0);
    }

    SECTION("Scaled Line2 Intersection Construction From Values")
    {
        using GHULBUS_MATH_NAMESPACE::ScaledLine2Intersection;
        ScaledLine2Intersection<int> sli(11, 22, 33);
        CHECK(sli.t1 == 11);
        CHECK(sli.t2 == 22);
        CHECK(sli.inverse_scale_factor == 33);
    }

    SECTION("Scaled Line2 Intersection Copy Construction")
    {
        using GHULBUS_MATH_NAMESPACE::ScaledLine2Intersection;
        ScaledLine2Intersection<int> sli(11, 22, 33);
        ScaledLine2Intersection<int> sli_copy(sli);
        CHECK(sli_copy.t1 == 11);
        CHECK(sli_copy.t2 == 22);
        CHECK(sli_copy.inverse_scale_factor == 33);
    }

    SECTION("Scaled Line2 Intersection Copy Assignment")
    {
        using GHULBUS_MATH_NAMESPACE::ScaledLine2Intersection;
        ScaledLine2Intersection<int> sli(11, 22, 33);
        ScaledLine2Intersection<int> sli2(5, 6, 7);
        CHECK(sli.t1 == 11);
        CHECK(sli.t2 == 22);
        CHECK(sli.inverse_scale_factor == 33);
        sli = sli2;
        CHECK(sli.t1 == 5);
        CHECK(sli.t2 == 6);
        CHECK(sli.inverse_scale_factor == 7);
    }

    SECTION("Scaled Line2 Intersection Evaluation")
    {
        using GHULBUS_MATH_NAMESPACE::ScaledLine2Intersection;
        ScaledLine2Intersection<int> sli(1, 2, 4);
        CHECK(sli.evaluate_t1<float>() == 0.25f);
        CHECK(sli.evaluate_t2<float>() == 0.5f);

        ScaledLine2Intersection<int> sli_weird_values(0, 1, 0);
        CHECK(std::isnan(sli_weird_values.evaluate_t1<float>()));
        CHECK(sli_weird_values.evaluate_t2<float>() == std::numeric_limits<float>::infinity());
    }

    SECTION("Scaled Line-Line Intersection")
    {
        {
            Line2<int> l1(Point2<int>(0, 0), Vector2<int>(1, 1));
            Line2<int> l2(Point2<int>(1, 0), Vector2<int>(-1, 1));
            auto const sli = intersect_scaled(l1, l2);
            CHECK(sli.t1 == -1);
            CHECK(sli.t2 == -1);
            CHECK(sli.inverse_scale_factor == -2);
            auto const p1 = l1.evaluate_at_parameter(sli.evaluate_t1<float>());
            auto const p2 = l2.evaluate_at_parameter(sli.evaluate_t2<float>());
            CHECK(p1 == p2);
        }
        {
            Line2<int> l1(Point2<int>(0, 0), Vector2<int>(10, 1));
            Line2<int> l2(Point2<int>(50, 0), Vector2<int>(0, -2));
            auto const sli = intersect_scaled(l1, l2);
            CHECK(sli.t1 == 100);
            CHECK(sli.t2 == -50);
            CHECK(sli.inverse_scale_factor == 20);
            CHECK(l1.evaluate_at_parameter(sli.evaluate_t1<float>()) ==
                  l2.evaluate_at_parameter(sli.evaluate_t2<float>()));
        }
        {
            // parallel lines
            Line2<int> l1(Point2<int>(0, 0), Vector2<int>(10, 15));
            Line2<int> l2(Point2<int>(50, 0), Vector2<int>(20, 30));
            auto const sli = intersect_scaled(l1, l2);
            CHECK(sli.inverse_scale_factor == 0);
        }
        {
            // identical lines (same parameters)
            Line2<int> l(Point2<int>(50, 0), Vector2<int>(20, 30));
            auto const sli = intersect_scaled(l, l);
            CHECK(sli.t1 == 0);
            CHECK(sli.t2 == 0);
            CHECK(sli.inverse_scale_factor == 0);
        }
        {
            // identical lines (different parameters)
            Line2<int> l1(Point2<int>(-10, -90), Vector2<int>(20, 30));
            Line2<int> l2(Point2<int>(50, 0), Vector2<int>(20, 30));
            auto const sli = intersect_scaled(l1, l2);
            CHECK(sli.t1 == 0);
            CHECK(sli.t2 == 0);
            CHECK(sli.inverse_scale_factor == 0);
        }
    }

    SECTION("Line-Line Intersection Point")
    {
        {
            Line2<float> l1(Point2<float>(0, 0), Vector2<float>(1, 1));
            Line2<float> l2(Point2<float>(1, 0), Vector2<float>(-1, 1));
            auto const p = intersect_p(l1, l2);
            CHECK(p == Point2<float>(0.5f, 0.5f));
        }
        {
            Line2<float> l1(Point2<float>(0, 0), Vector2<float>(10, 1));
            Line2<float> l2(Point2<float>(50, 0), Vector2<float>(0, -2));
            auto const p = intersect_p(l1, l2);
            CHECK(p == Point2<float>(50.f, 5.f));
        }
        {
            // parallel lines
            Line2<float> l1(Point2<float>(0, 0), Vector2<float>(10, 15));
            Line2<float> l2(Point2<float>(50, 0), Vector2<float>(20, 30));
            auto const p = intersect_p(l1, l2);
            CHECK(p == Point2<float>(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()));
        }
        {
            // identical lines (same parameters)
            Line2<float> l(Point2<float>(50, 0), Vector2<float>(20, 30));
            auto const p = intersect_p(l, l);
            CHECK(std::isnan(p.x));
            CHECK(std::isnan(p.y));
        }
        {
            // identical lines (different parameters)
            Line2<float> l1(Point2<float>(-10, -90), Vector2<float>(20, 30));
            Line2<float> l2(Point2<float>(50, 0), Vector2<float>(20, 30));
            auto const p = intersect_p(l1, l2);
            CHECK(std::isnan(p.x));
            CHECK(std::isnan(p.y));
        }
    }
}
