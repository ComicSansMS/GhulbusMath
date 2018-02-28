#include <gbMath/Transform2.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("Transform2")
{
    using GHULBUS_MATH_NAMESPACE::Matrix2;
    using GHULBUS_MATH_NAMESPACE::Matrix3;
    using GHULBUS_MATH_NAMESPACE::Normal2;
    using GHULBUS_MATH_NAMESPACE::Point2;
    using GHULBUS_MATH_NAMESPACE::Vector2;
    using GHULBUS_MATH_NAMESPACE::Transform2;

    SECTION("Default construction")
    {
        Transform2<float> t;
        CHECK(t.m == GHULBUS_MATH_NAMESPACE::identity3<float>());
    }

    SECTION("Construction from values")
    {
        Transform2<float> t(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        CHECK(t.m == Matrix3<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f));
    }

    SECTION("Vector transformation")
    {
        Vector2<float> v(1.f, -1.f);
        CHECK(Transform2<float>(1.f,  0.f,  5.f,
                                0.f,  1.f,  5.f,
                                5.f,  5.f,  5.f)*v == Vector2<float>(1.f, -1.f));
        CHECK(Transform2<float>(10.f,  20.f,  30.f,
                               -20.f, -40.f, -60.f,
                                75.f,  80.f,  95.f)*v == Vector2<float>(-10.f, 20.f));
    }

    SECTION("Point transformation")
    {
        Point2<float> p(1.f, -1.f);
        CHECK(Transform2<float>(1.f,  0.f,  5.f,
                                0.f,  1.f,  5.f,
                                5.f,  5.f,  5.f)*p == Point2<float>(6.f, 4.f));
        CHECK(Transform2<float>(10.f,  20.f,  30.f,
                               -20.f, -40.f, -60.f,
                                75.f,  80.f,  95.f)*p == Point2<float>(20.f, -40.f));
    }

    SECTION("Reciprocal transformation")
    {
        Transform2<float> t(1.f, 0.f, 0.f,
                            0.f, 2.f, 0.f,
                            0.f, 0.f, 1.f);
        CHECK(determinant(t.m) == 2.f);
        CHECK(t.reciprocal().m == Matrix2<float>(2.f, 0.f,
                                                 0.f, 1.f));
        CHECK(determinant(t.reciprocal().m) == 2.f);
    }

    SECTION("Reciprocal transformation of orthogonal")
    {
        Transform2<float> t(0.f, 1.f, 0.f,
                           -1.f, 0.f, 0.f,
                            0.f, 0.f, 1.f);
        REQUIRE(determinant(t.m) == 1.f);
        GHULBUS_MATH_NAMESPACE::assume_orthogonal_t orth{};
        CHECK(t.reciprocal(orth).m == Matrix2<float>(0.f,-1.f,
                                                     1.f, 0.f));
    }

    SECTION("Scale matrix")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_scale(4.f, 2.f);
        CHECK(scale.m == Matrix3<float>(4.f, 0.f, 0.f,
                                        0.f, 2.f, 0.f,
                                        0.f, 0.f, 1.f));
    }

    SECTION("Normal transformation")
    {
        Normal2<float> n(1.f, 1.f);
        Transform2<float> t = GHULBUS_MATH_NAMESPACE::make_scale(2.f, 1.f);
        CHECK(n*t.reciprocal() == Normal2<float>(1.f, 2.f));
    }
}
