#include <gbMath/Line3.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

namespace {
    template<typename T> struct Test_PointLineDistance {
        void operator()()
        {
            using GHULBUS_MATH_NAMESPACE::Line3;
            using GHULBUS_MATH_NAMESPACE::Point3;
            using GHULBUS_MATH_NAMESPACE::Vector3;
            using Catch::Approx;

            Line3<T> const l0(Point3<T>(0.f, 0.f, 0.f), Vector3<T>(1.f, 1.f, 1.f));
            auto const l0_norm = normalized(l0);
            Line3<T> const l1(Point3<T>(-4.f, 2.5f, 4.5f), Vector3<T>(2.f, -2.5f, 2.5f));
            auto const l1_norm = normalized(l1);

            Point3<T> const p0(5.f, -2.f, 1.f);
            CHECK(distance_squared(l0, p0) == Approx(24.f + (2.f/3.f)));
            CHECK(distance(l0, p0) == Approx(std::sqrt(24.f + (2.f/3.f))));
            CHECK(distance_squared_unit(l0_norm, p0) == Approx(24.f + (2.f/3.f)));
            CHECK(distance_unit(l0_norm, p0) == Approx(std::sqrt(24.f + (2.f/3.f))));

            CHECK(distance_squared(l1, p0) == Approx(88.f + (1.f/33.f)));
            CHECK(distance(l1, p0) == Approx(std::sqrt(88.f + (1.f/33.f))));
            CHECK(distance_squared_unit(l1_norm, p0) == Approx(88.f + (1.f/33.f)));
            CHECK(distance_unit(l1_norm, p0) == Approx(std::sqrt(88.f + (1.f/33.f))));

            Point3<T> const p1(-4.f, -1.f, 16.f);
            CHECK(distance_squared(l0, p1) == Approx(232.f + (2.f/3.f)));
            CHECK(distance(l0, p1) == Approx(std::sqrt(232.f + (2.f/3.f))));
            CHECK(distance_squared_unit(l0_norm, p1) == Approx(232.f + (2.f/3.f)));
            CHECK(distance_unit(l0_norm, p1) == Approx(std::sqrt(232.f + (2.f/3.f))));

            CHECK(distance_squared(l1, p1) == Approx(59.f + (3.f/11.f)));
            CHECK(distance(l1, p1) == Approx(std::sqrt(59.f + (3.f/11.f))));
            CHECK(distance_squared_unit(l1_norm, p1) == Approx(59.f + (3.f/11.f)));
            CHECK(distance_unit(l1_norm, p1) == Approx(std::sqrt(59.f + (3.f/11.f))));
        }
    };
}

TEST_CASE("Line3")
{
    using GHULBUS_MATH_NAMESPACE::Line3;
    using GHULBUS_MATH_NAMESPACE::Point3;
    using GHULBUS_MATH_NAMESPACE::Vector3;
    using Catch::Approx;

    SECTION("Zero Initialization")
    {
        Line3<float> l{};
        CHECK(l.p == Point3<float>(0.f, 0.f, 0.f));
        CHECK(l.v == Vector3<float>(0.f, 0.f, 0.f));
    }

    SECTION("Construction from point and vector")
    {
        Line3<float> l(Point3<float>(1.f, 2.f, 3.f), Vector3<float>(-4.f, 5.f, -6.f));
        CHECK(l.p == Point3<float>(1.f, 2.f, 3.f));
        CHECK(l.v == Vector3<float>(-4.f, 5.f, -6.f));
    }

    SECTION("Construction from two points")
    {
        Line3<float> l(Point3<float>(1.f, 2.f, 3.f), Point3<float>(-4.f, 5.f, -6.f));
        CHECK(l.p == Point3<float>(1.f, 2.f, 3.f));
        CHECK(l.v == Vector3<float>(-5.f, 3.f, -9.f));
    }

    SECTION("Evaluate line equation at a specific parameter")
    {
        Line3<float> l(Point3<float>(1.f, 2.f, 3.f), Point3<float>(-4.f, 5.f, -6.f));
        CHECK(l.evaluate_at_parameter(0.f) == l.p);
        CHECK(l.evaluate_at_parameter(1.f) == l.p + l.v);
        CHECK(l.evaluate_at_parameter(0.5f) == l.p + (l.v / 2.f));
        CHECK(l.evaluate_at_parameter(2.5f) == l.p + (l.v * 2.5f));
    }

    SECTION("Normalization")
    {
        Line3<float> l = normalized(Line3<float>(Point3<float>(1.f, 2.f, 3.f), Point3<float>(-4.f, 5.f, -6.f)));
        CHECK(l.p == Point3<float>(1.f, 2.f, 3.f));
        CHECK(l.v == Vector3<float>(-5.f/std::sqrt(115.f), 3.f/std::sqrt(115.f), -9.f/std::sqrt(115.f)));
        CHECK(length(l.v) == Approx(1.f));
    }

    SECTION("Distance Point-Line")
    {
        Test_PointLineDistance<float>()();
        Test_PointLineDistance<double>()();
        Test_PointLineDistance<long double>()();
    }
}
