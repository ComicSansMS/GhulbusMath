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

    SECTION("Construction from values")
    {
        Transform3<float> t(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        CHECK(t.m == Matrix4<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
                                    9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f));
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

    SECTION("Scale matrix")
    {
        auto scale = GHULBUS_MATH_NAMESPACE::make_scale(4.f, 2.f, 5.f);
        CHECK(scale.m == Matrix4<float>(4.f, 0.f, 0.f, 0.f,
                                        0.f, 2.f, 0.f, 0.f,
                                        0.f, 0.f, 5.f, 0.f,
                                        0.f, 0.f, 0.f, 1.f));
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
