#include <gbMath/Transform2.hpp>
#include <gbMath/MatrixIO2.hpp>
#include <gbMath/MatrixIO3.hpp>
#include <gbMath/VectorIO2.hpp>

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

    SECTION("Construction from Matrix3")
    {
        Transform2<float> t(Matrix3<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f));
        CHECK(t.m == Matrix3<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f));
    }

    SECTION("Construction from values")
    {
        Transform2<float> t(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        CHECK(t.m == Matrix3<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f));
    }

    SECTION("Transform Concatenation")
    {
        Transform2<float> t1(Matrix3<float>(1.f, 2.f, 3.f,
                                            4.f, 5.f, 6.f,
                                            7.f, 8.f, 9.f));
        Transform2<float> const t2(Matrix3<float>(0.5f,  0.25f, 0.75f,
                                                  1.f,   1.5f,  2.25f,
                                                  1.75f, 0.5f,  2.0f));
        CHECK(&(t1 *= t2) == &t1);
        CHECK(t1.m == Matrix3<float>( 7.75f,  4.75f, 11.25f,
                                     17.5f,  11.5f,  26.25f,
                                     27.25,  18.25f, 41.25f));
    }

    SECTION("Transform Concatenation non-member")
    {
        Transform2<float> const t1(Matrix3<float>(1.f, 2.f, 3.f,
                                                  4.f, 5.f, 6.f,
                                                  7.f, 8.f, 9.f));
        Transform2<float> const t2(Matrix3<float>(0.5f,  0.25f, 0.75f,
                                                  1.f,   1.5f,  2.25f,
                                                  1.75f, 0.5f,  2.0f));
        CHECK((t1 * t2).m == Matrix3<float>( 7.75f,  4.75f, 11.25f,
                                            17.5f,  11.5f,  26.25f,
                                            27.25,  18.25f, 41.25f));
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

    SECTION("Inverse")
    {
        Transform2<float> t(4.f, 0.f, 9.f,
                            0.f, 2.f, 5.f,
                            0.f, 0.f, 1.f);
        Transform2<float> t_inverse = inverse(t);
        CHECK(t_inverse.m == Matrix3<float>(1.f/4.f, 0.f,     -2.25f,
                                            0.f,     1.f/2.f, -2.5f,
                                            0.f,     0.f,      1.f));
        
    }

    SECTION("Scale matrix uniform")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_scale2(4.f);
        CHECK(scale.m == Matrix3<float>(4.f, 0.f, 0.f,
                                        0.f, 4.f, 0.f,
                                        0.f, 0.f, 1.f));
    }

    SECTION("Scale matrix from components")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_scale(4.f, 2.f);
        CHECK(scale.m == Matrix3<float>(4.f, 0.f, 0.f,
                                        0.f, 2.f, 0.f,
                                        0.f, 0.f, 1.f));
    }

    SECTION("Scale matrix from Vector2")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_scale(Vector2<float>(4.f, 2.f));
        CHECK(scale.m == Matrix3<float>(4.f, 0.f, 0.f,
                                        0.f, 2.f, 0.f,
                                        0.f, 0.f, 1.f));
    }

    SECTION("Translation matrix from components")
    {
        auto translation = GHULBUS_MATH_NAMESPACE::make_translation(9.f, 5.f);
        CHECK(translation.m == Matrix3<float>(1.f, 0.f, 9.f,
                                              0.f, 1.f, 5.f,
                                              0.f, 0.f, 1.f));
    }

    SECTION("Translation matrix from Vector2")
    {
        auto translation = GHULBUS_MATH_NAMESPACE::make_translation(Vector2<float>(9.f, 5.f));
        CHECK(translation.m == Matrix3<float>(1.f, 0.f, 9.f,
                                              0.f, 1.f, 5.f,
                                              0.f, 0.f, 1.f));
    }

    SECTION("Rotation matrix")
    {
        auto rotation1 = GHULBUS_MATH_NAMESPACE::make_rotation(0.f);
        CHECK(rotation1.m == Matrix3<float>(std::cos(0.f), -std::sin(0.f), 0.f,
                                            std::sin(0.f),  std::cos(0.f), 0.f,
                                                     0.f,           0.f, 1.f));
        float const pi = GHULBUS_MATH_NAMESPACE::traits::Pi<float>::value;
        auto rotation2 = GHULBUS_MATH_NAMESPACE::make_rotation(pi);
        CHECK(rotation2.m == Matrix3<float>(std::cos(pi), -std::sin(pi), 0.f,
                                            std::sin(pi),  std::cos(pi), 0.f,
                                                     0.f,           0.f, 1.f));
        float const pi_1_2 = pi / 2.f;
        auto rotation3 = GHULBUS_MATH_NAMESPACE::make_rotation(pi_1_2);
        CHECK(rotation3.m == Matrix3<float>( std::cos(pi_1_2), -std::sin(pi_1_2), 0.f,
                                             std::sin(pi_1_2),  std::cos(pi_1_2), 0.f,
                                                          0.f,               0.f, 1.f));
    }

    SECTION("Normal transformation")
    {
        Normal2<float> n(1.f, 1.f);
        Transform2<float> t = GHULBUS_MATH_NAMESPACE::make_scale(2.f, 1.f);
        CHECK(n*t.reciprocal() == Normal2<float>(1.f, 2.f));
    }

    SECTION("Projective point transform with perspective divide")
    {
        CHECK(project(Transform2<float>(1.f, 0.f, 0.f,
                                        0.f, 1.f, 0.f,
                                       42.f, 0.f, 1.f),
                      Point2<float>(1.f, 2.f)) == Point2<float>(1.f/43.f, 2.f/43.f));
        CHECK(project(Transform2<float>(1.f, 0.f, 0.f,
                                        0.f, 1.f, 0.f,
                                        0.f,42.f, 1.f),
                      Point2<float>(1.f, 2.f)) == Point2<float>(1.f/85.f, 2.f/85.f));
        CHECK(project(Transform2<float>(0.f, 1.f, 0.f,
                                       -1.f, 0.f, 0.f,
                                        0.f,42.f, 1.f),
                      Point2<float>(1.f, 2.f)) == Point2<float>(2.f/85.f, -1.f/85.f));
    }

    SECTION("Projective point transform with explicit w")
    {
        int w = 1;
        CHECK(project(Transform2<int>(1, 0, 0,
                                      0, 1, 0,
                                     42, 0, 1),
                      Point2<int>(1, 2), w) == Point2<int>(1, 2));
        CHECK(w == 43);
        w = 1;
        CHECK(project(Transform2<int>(1, 0, 0,
                                      0, 1, 0,
                                      0,42, 1),
                      Point2<int>(1, 2), w) == Point2<int>(1, 2));
        CHECK(w == 85);
        w = 1;
        CHECK(project(Transform2<int>(0, 1, 0,
                                     -1, 0, 0,
                                      0,42, 1),
                      Point2<int>(1, 2), w) == Point2<int>(2, -1));
        CHECK(w == 85);

        w = 2;
        CHECK(project(Transform2<int>(1, 0, 0,
                                      0, 1, 0,
                                     42, 0, 1),
                      Point2<int>(1, 2), w) == Point2<int>(1, 2));
        CHECK(w == 44);

        w = 2;
        CHECK(project(Transform2<int>(1, 0, 4,
                                      0, 1, 5,
                                     42, 0, 1),
                      Point2<int>(1, 2), w) == Point2<int>(9, 12));
        CHECK(w == 44);
    }
}
