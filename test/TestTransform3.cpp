#include <gbMath/Transform3.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("Transform3")
{
    using GHULBUS_MATH_NAMESPACE::Matrix3;
    using GHULBUS_MATH_NAMESPACE::Matrix4;
    using GHULBUS_MATH_NAMESPACE::Normal3;
    using GHULBUS_MATH_NAMESPACE::Point3;
    using GHULBUS_MATH_NAMESPACE::Vector3;
    using GHULBUS_MATH_NAMESPACE::Transform3;

    SECTION("Default construction")
    {
        Transform3<float> t;
        CHECK(t.m == GHULBUS_MATH_NAMESPACE::identity4<float>());
    }

    SECTION("Construction from Matrix4")
    {
        Transform3<float> t(Matrix4<float>(1.f,  2.f,  3.f,  4.f,  5.f,  6.f,  7.f,  8.f,
                                           9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f));
        CHECK(t.m == Matrix4<float>(1.f,  2.f,  3.f,  4.f,  5.f,  6.f,  7.f,  8.f,
                                    9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f));
    }

    SECTION("Construction from values")
    {
        Transform3<float> t(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        CHECK(t.m == Matrix4<float>(1.f,  2.f,  3.f,  4.f,  5.f,  6.f,  7.f,  8.f,
                                    9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f));
    }

    SECTION("Transform concatenation")
    {
        Transform3<float> t1(Matrix4<float>(  1.f,  2.f,  3.f,  4.f,
                                              5.f,  6.f,  7.f,  8.f,
                                              9.f, 10.f, 11.f, 12.f,
                                             13.f, 14.f, 15.f, 16.f));
        Transform3<float> const t2(Matrix4<float>(0.5f,    0.25f,  0.75f,   0.125f,
                                                  1.f,     1.5f,   2.25f,   0.625f,
                                                  1.75f,   0.5f,   2.0f,    0.875f,
                                                  0.0625f, 1.125f, 1.625f,  1.875f));
        CHECK(&(t1 *= t2) == &t1);
        CHECK(t1.m == Matrix4<float>(  8.f,  9.25f,  17.75f, 11.5f,
                                      21.25f, 22.75f, 44.25f, 25.5f,
                                      34.5f,  36.25f, 70.75f, 39.5f,
                                      47.75f, 49.75f, 97.25f, 53.5f));
    }

    SECTION("Transform concatenation non-member")
    {
        Transform3<float> const t1(Matrix4<float>(  1.f,  2.f,  3.f,  4.f,
                                                    5.f,  6.f,  7.f,  8.f,
                                                    9.f, 10.f, 11.f, 12.f,
                                                   13.f, 14.f, 15.f, 16.f));
        Transform3<float> const t2(Matrix4<float>(0.5f,    0.25f,  0.75f,   0.125f,
                                                  1.f,     1.5f,   2.25f,   0.625f,
                                                  1.75f,   0.5f,   2.0f,    0.875f,
                                                  0.0625f, 1.125f, 1.625f,  1.875f));
        CHECK((t1 * t2).m == Matrix4<float>(  8.f,  9.25f,  17.75f, 11.5f,
                                            21.25f, 22.75f, 44.25f, 25.5f,
                                            34.5f,  36.25f, 70.75f, 39.5f,
                                            47.75f, 49.75f, 97.25f, 53.5f));
    }

    SECTION("Vector transformation")
    {
        Vector3<float> v(1.f, -1.f, 2.f);
        CHECK(Transform3<float>(1.f,  0.f,  0.f,  5.f,
                                0.f,  1.f,  0.f,  5.f,
                                0.f,  0.f,  1.f,  5.f,
                                5.f,  5.f,  5.f,  5.f)*v == Vector3<float>(1.f, -1.f, 2.f));
        CHECK(Transform3<float>(10.f,  20.f,  30.f,  40.f,
                               -20.f, -40.f, -60.f, -80.f,
                                 5.f,  10.f,  15.f,  20.f,
                                75.f,  80.f,  95.f, 105.f)*v == Vector3<float>(50.f, -100.f, 25.f));
    }

    SECTION("Point transformation")
    {
        Point3<float> p(1.f, -1.f, 2.f);
        CHECK(Transform3<float>(1.f,  0.f,  0.f,  5.f,
                                0.f,  1.f,  0.f,  5.f,
                                0.f,  0.f,  1.f,  5.f,
                                5.f,  5.f,  5.f,  5.f)*p == Point3<float>(6.f, 4.f, 7.f));
        CHECK(Transform3<float>(10.f,  20.f,  30.f,  40.f,
                               -20.f, -40.f, -60.f, -80.f,
                                 5.f,  10.f,  15.f,  20.f,
                                75.f,  80.f,  95.f, 105.f)*p == Point3<float>(90.f, -180.f, 45.f));
    }

    SECTION("Reciprocal transformation")
    {
        Transform3<float> t(1.f, 0.f, 0.f, 0.f,
                            0.f, 2.f, 0.f, 0.f,
                            0.f, 0.f, 4.f, 0.f,
                            0.f, 0.f, 0.f, 1.f);
        CHECK(determinant(t.m) == 8.f);
        CHECK(t.reciprocal().m == Matrix3<float>(8.f, 0.f, 0.f,
                                                 0.f, 4.f, 0.f,
                                                 0.f, 0.f, 2.f));
        CHECK(determinant(t.reciprocal().m) == 64.f);
    }

    SECTION("Reciprocal transformation of orthogonal")
    {
        Transform3<float> t(0.f, 1.f, 0.f, 0.f,
                           -1.f, 0.f, 0.f, 0.f,
                            0.f, 0.f, 1.f, 0.f,
                            0.f, 0.f, 0.f, 1.f);
        REQUIRE(determinant(t.m) == 1.f);
        GHULBUS_MATH_NAMESPACE::assume_orthogonal_t orth{};
        CHECK(t.reciprocal(orth).m == Matrix3<float>(0.f,-1.f, 0.f,
                                                     1.f, 0.f, 0.f,
                                                     0.f, 0.f, 1.f));
    }

    SECTION("Scale matrix from components")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_scale(4.f, 2.f, 5.f);
        CHECK(scale.m == Matrix4<float>(4.f, 0.f, 0.f, 0.f,
                                        0.f, 2.f, 0.f, 0.f,
                                        0.f, 0.f, 5.f, 0.f,
                                        0.f, 0.f, 0.f, 1.f));
    }

    SECTION("Scale matrix from Vector3")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_scale(Vector3<float>(4.f, 2.f, 5.f));
        CHECK(scale.m == Matrix4<float>(4.f, 0.f, 0.f, 0.f,
                                        0.f, 2.f, 0.f, 0.f,
                                        0.f, 0.f, 5.f, 0.f,
                                        0.f, 0.f, 0.f, 1.f));
    }

    SECTION("Translation matrix from components")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_translation(9.f, 5.f, -2.f);
        CHECK(scale.m == Matrix4<float>(1.f, 0.f, 0.f, 9.f,
                                        0.f, 1.f, 0.f, 5.f,
                                        0.f, 0.f, 1.f,-2.f,
                                        0.f, 0.f, 0.f, 1.f));
    }

    SECTION("Translation matrix from Vector3")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_translation(Vector3<float>(9.f, 5.f, -2.f));
        CHECK(scale.m == Matrix4<float>(1.f, 0.f, 0.f, 9.f,
                                        0.f, 1.f, 0.f, 5.f,
                                        0.f, 0.f, 1.f,-2.f,
                                        0.f, 0.f, 0.f, 1.f));
    }

    SECTION("X-Rotation matrix")
    {
        auto rotation1 = GHULBUS_MATH_NAMESPACE::make_rotation_x(0.f);
        CHECK(rotation1.m == Matrix4<float>(1.f,           0.f,            0.f, 0.f,
                                            0.f, std::cos(0.f), -std::sin(0.f), 0.f,
                                            0.f, std::sin(0.f),  std::cos(0.f), 0.f,
                                            0.f,           0.f,            0.f, 1.f));
        float const pi = GHULBUS_MATH_NAMESPACE::traits::Pi<float>::value;
        auto rotation2 = GHULBUS_MATH_NAMESPACE::make_rotation_x(pi);
        CHECK(rotation2.m == Matrix4<float>(1.f,          0.f,           0.f, 0.f,
                                            0.f, std::cos(pi), -std::sin(pi), 0.f,
                                            0.f, std::sin(pi),  std::cos(pi), 0.f,
                                            0.f,          0.f,           0.f, 1.f));
        float const pi_1_2 = pi / 2.f;
        auto rotation3 = GHULBUS_MATH_NAMESPACE::make_rotation_x(pi_1_2);
        CHECK(rotation3.m == Matrix4<float>(1.f,              0.f,               0.f, 0.f,
                                            0.f, std::cos(pi_1_2), -std::sin(pi_1_2), 0.f,
                                            0.f, std::sin(pi_1_2),  std::cos(pi_1_2), 0.f,
                                            0.f,              0.f,               0.f, 1.f));
    }

    SECTION("Y-Rotation matrix")
    {
        auto rotation1 = GHULBUS_MATH_NAMESPACE::make_rotation_y(0.f);
        CHECK(rotation1.m == Matrix4<float>( std::cos(0.f), 0.f, std::sin(0.f), 0.f,
                                                       0.f, 1.f,           0.f, 0.f,
                                            -std::sin(0.f), 0.f, std::cos(0.f), 0.f,
                                                       0.f, 0.f,           0.f, 1.f));
        float const pi = GHULBUS_MATH_NAMESPACE::traits::Pi<float>::value;
        auto rotation2 = GHULBUS_MATH_NAMESPACE::make_rotation_y(pi);
        CHECK(rotation2.m == Matrix4<float>( std::cos(pi), 0.f, std::sin(pi), 0.f,
                                                      0.f, 1.f,          0.f, 0.f,
                                            -std::sin(pi), 0.f, std::cos(pi), 0.f,
                                                      0.f, 0.f,          0.f, 1.f));
        float const pi_1_2 = pi / 2.f;
        auto rotation3 = GHULBUS_MATH_NAMESPACE::make_rotation_y(pi_1_2);
        CHECK(rotation3.m == Matrix4<float>( std::cos(pi_1_2), 0.f, std::sin(pi_1_2), 0.f,
                                                          0.f, 1.f,              0.f, 0.f,
                                            -std::sin(pi_1_2), 0.f, std::cos(pi_1_2), 0.f,
                                                          0.f, 0.f,              0.f, 1.f));
    }

    SECTION("Z-Rotation matrix")
    {
        auto rotation1 = GHULBUS_MATH_NAMESPACE::make_rotation_z(0.f);
        CHECK(rotation1.m == Matrix4<float>(std::cos(0.f), -std::sin(0.f), 0.f, 0.f,
                                            std::sin(0.f),  std::cos(0.f), 0.f, 0.f,
                                                      0.f,            0.f, 1.f, 0.f,
                                                      0.f,            0.f, 0.f, 1.f));
        float const pi = GHULBUS_MATH_NAMESPACE::traits::Pi<float>::value;
        auto rotation2 = GHULBUS_MATH_NAMESPACE::make_rotation_z(pi);
        CHECK(rotation2.m == Matrix4<float>(std::cos(pi), -std::sin(pi), 0.f, 0.f,
                                            std::sin(pi),  std::cos(pi), 0.f, 0.f,
                                                     0.f,           0.f, 1.f, 0.f,
                                                     0.f,           0.f, 0.f, 1.f));
        float const pi_1_2 = pi / 2.f;
        auto rotation3 = GHULBUS_MATH_NAMESPACE::make_rotation_z(pi_1_2);
        CHECK(rotation3.m == Matrix4<float>(std::cos(pi_1_2), -std::sin(pi_1_2), 0.f, 0.f,
                                            std::sin(pi_1_2),  std::cos(pi_1_2), 0.f, 0.f,
                                                         0.f,               0.f, 1.f, 0.f,
                                                         0.f,               0.f, 0.f, 1.f));
    }

    SECTION("Angle-Axis-Rotation matrix")
    {
        float const pi_1_2 = GHULBUS_MATH_NAMESPACE::traits::Pi<float>::value / 2.f;
        auto rotation1 = GHULBUS_MATH_NAMESPACE::make_rotation(pi_1_2, Vector3<float>(1.f, 0.f, 0.f));
        Matrix4<float> reference1(1.f,              0.f,               0.f, 0.f,
                                  0.f, std::cos(pi_1_2), -std::sin(pi_1_2), 0.f,
                                  0.f, std::sin(pi_1_2),  std::cos(pi_1_2), 0.f,
                                  0.f,              0.f,               0.f, 1.f);
        for (int i = 0; i < 16; ++i) { CHECK(rotation1.m[i] == Approx(reference1[i])); }

        auto rotation2 = GHULBUS_MATH_NAMESPACE::make_rotation(pi_1_2, Vector3<float>(0.f, 1.f, 0.f));
        Matrix4<float> reference2( std::cos(pi_1_2), 0.f, std::sin(pi_1_2), 0.f,
                                                0.f, 1.f,              0.f, 0.f,
                                  -std::sin(pi_1_2), 0.f, std::cos(pi_1_2), 0.f,
                                                0.f, 0.f,              0.f, 1.f);
        for (int i = 0; i < 16; ++i) { CHECK(rotation2.m[i] == Approx(reference2[i])); }

        auto rotation3 = GHULBUS_MATH_NAMESPACE::make_rotation(pi_1_2, Vector3<float>(0.f, 0.f, 1.f));
        Matrix4<float> reference3(std::cos(pi_1_2), -std::sin(pi_1_2), 0.f, 0.f,
                                  std::sin(pi_1_2),  std::cos(pi_1_2), 0.f, 0.f,
                                               0.f,               0.f, 1.f, 0.f,
                                               0.f,               0.f, 0.f, 1.f);
        for (int i = 0; i < 16; ++i) { CHECK(rotation3.m[i] == Approx(reference3[i])); }

        auto rotation4 = GHULBUS_MATH_NAMESPACE::make_rotation(pi_1_2, Vector3<float>(1.f, 1.f, 1.f));
        auto const v = rotation4 * Vector3<float>(1.f, 1.f, 1.f);
        for (int i = 0; i < 3; ++i) { CHECK(v[i] == Approx(1.f)); }
    }

    SECTION("Perspective Projection")
    {
        auto proj = GHULBUS_MATH_NAMESPACE::make_perspective_projection(10.f, 20.f, 1.f, 2.f);
        CHECK(proj.m == Matrix4<float>(0.2f,  0.f, 0.f,  0.f,
                                        0.f, 0.1f, 0.f,  0.f,
                                        0.f,  0.f, 2.f, -2.f,
                                        0.f,  0.f, 1.f,  0.f));
    }

    SECTION("Perspective Projection FoV")
    {
        float const pi_1_2 = GHULBUS_MATH_NAMESPACE::traits::Pi<float>::value / 2.f;
        auto proj = GHULBUS_MATH_NAMESPACE::make_perspective_projection_fov(pi_1_2, 2.f, 1.f, 2.f);
        CHECK(proj.m == Matrix4<float>(0.5f, 0.f, 0.f,  0.f,
                                        0.f, 1.f, 0.f,  0.f,
                                        0.f, 0.f, 2.f, -2.f,
                                        0.f, 0.f, 1.f,  0.f));
    }

    SECTION("Perspective Projection Frustum")
    {
        auto proj = GHULBUS_MATH_NAMESPACE::make_perspective_projection_frustum(5.f, 10.f, 20.f, 40.f, 1.f, 2.f);
        CHECK(proj.m == Matrix4<float>(0.4f,  0.f, 0.f,  0.f,
                                        0.f, 0.1f, 0.f,  0.f,
                                       -3.f, -3.f, 2.f, -2.f,
                                        0.f,  0.f, 1.f,  0.f));
    }

    SECTION("Perspective Projection Orthographic")
    {
        auto proj = GHULBUS_MATH_NAMESPACE::make_perspective_projection_orthographic(10.f, 20.f, 1.f, 2.f);
        CHECK(proj.m == Matrix4<float>(0.2f, 0.f, 0.f,  0.f,
                                       0.f, 0.1f, 0.f,  0.f,
                                       0.f,  0.f, 1.f, -1.f,
                                       0.f,  0.f, 0.f,  1.f));
    }

    SECTION("Perspective Projection Orthographic Frustum")
    {
        auto proj =
            GHULBUS_MATH_NAMESPACE::make_perspective_projection_orthographic_frustum(5.f, 10.f, 20.f, 40.f, 1.f, 2.f);
        CHECK(proj.m == Matrix4<float>(0.4f, 0.f, 0.f, -3.f,
                                       0.f, 0.1f, 0.f, -3.f,
                                       0.f,  0.f, 1.f, -1.f,
                                       0.f,  0.f, 0.f,  1.f));
    }

    SECTION("View Transformation Look At")
    {
        Vector3<float> eye(1.f, 1.f, 1.f);
        Vector3<float> target(0.f, 0.f, 0.f);
        Vector3<float> up(0.f, 1.f, 0.f);
        auto view = GHULBUS_MATH_NAMESPACE::make_view_look_at(eye, target, up);
        auto const sqrt2 = std::sqrt(2.f);
        auto const sqrt3 = std::sqrt(3.f);
        auto const sqrt6 = std::sqrt(6.f);
        Matrix4<float> reference(-1.f/sqrt2,                0.f,  1.f/sqrt2,   0.f,
                                 -1.f/sqrt6, std::sqrt(2.f/3.f), -1.f/sqrt6,   0.f,
                                 -1.f/sqrt3,         -1.f/sqrt3, -1.f/sqrt3, sqrt3,
                                        0.f,                0.f,        0.f,   1.f);
        for (int i = 0; i < 16; ++i) { CHECK(view.m[i] == Approx(reference[i])); }
    }

    SECTION("Normal transformation")
    {
        Normal3<float> n(1.f, 1.f, 1.f);
        Transform3<float> t = GHULBUS_MATH_NAMESPACE::make_scale(4.f, 2.f, 1.f);
        CHECK(n*t.reciprocal() == Normal3<float>(2.f, 4.f, 8.f));
    }

    SECTION("Projective point transform with perspective divide")
    {
        CHECK(project(Transform3<float>(1.f, 0.f, 0.f, 0.f,
                                        0.f, 1.f, 0.f, 0.f,
                                        0.f, 0.f, 1.f, 0.f,
                                       42.f, 0.f, 0.f, 1.f),
                      Point3<float>(1.f, 2.f, 3.f)) == Point3<float>(1.f/43.f, 2.f/43.f, 3.f/43.f));
        CHECK(project(Transform3<float>(1.f, 0.f, 0.f, 0.f,
                                        0.f, 1.f, 0.f, 0.f,
                                        0.f, 0.f, 1.f, 0.f,
                                        0.f,42.f, 0.f, 1.f),
                      Point3<float>(1.f, 2.f, 3.f)) == Point3<float>(1.f/85.f, 2.f/85.f, 3.f/85.f));
        CHECK(project(Transform3<float>(1.f, 0.f, 0.f, 0.f,
                                        0.f, 1.f, 0.f, 0.f,
                                        0.f, 0.f, 1.f, 0.f,
                                        0.f, 0.f,42.f, 1.f),
                      Point3<float>(1.f, 2.f, 3.f)) == Point3<float>(1.f/127.f, 2.f/127.f, 3.f/127.f));
        CHECK(project(Transform3<float>(0.f, 1.f, 0.f, 0.f,
                                       -1.f, 0.f, 0.f, 0.f,
                                        0.f, 0.f, 0.f, 0.f,
                                        0.f,42.f, 0.f, 1.f),
                      Point3<float>(1.f, 2.f, 3.f)) == Point3<float>(2.f/85.f, -1.f/85.f, 0.f));
    }

    SECTION("Projective point transform with explicit w")
    {
        int w = 1;
        CHECK(project(Transform3<int>(1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                     42, 0, 0, 1),
                      Point3<int>(1, 2, 3), w) == Point3<int>(1, 2, 3));
        CHECK(w == 43);
        w = 1;
        CHECK(project(Transform3<int>(1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0,42, 0, 1),
                      Point3<int>(1, 2, 3), w) == Point3<int>(1, 2, 3));
        CHECK(w == 85);
        w = 1;
        CHECK(project(Transform3<int>(1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0,42, 1),
                      Point3<int>(1, 2, 3), w) == Point3<int>(1, 2, 3));
        CHECK(w == 127);
        w = 1;

        CHECK(project(Transform3<int>(0, 1, 0, 0,
                                     -1, 0, 0, 0,
                                      0, 0, 1, 0,
                                      0,42, 0, 1),
                      Point3<int>(1, 2, 3), w) == Point3<int>(2, -1, 3));
        CHECK(w == 85);

        w = 2;
        CHECK(project(Transform3<int>(1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                     42, 0, 0, 1),
                      Point3<int>(1, 2, 3), w) == Point3<int>(1, 2, 3));
        CHECK(w == 44);

        w = 2;
        CHECK(project(Transform3<int>(1, 0, 0, 4,
                                      0, 1, 0, 5,
                                      0, 0, 1, 6,
                                     42, 0, 0, 1),
                      Point3<int>(1, 2, 3), w) == Point3<int>(9, 12, 15));
        CHECK(w == 44);
    }
}
