#include <gbMath/TransformLine3.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("TransformLine3")
{
    using GHULBUS_MATH_NAMESPACE::Line3;
    using GHULBUS_MATH_NAMESPACE::Point3;
    using GHULBUS_MATH_NAMESPACE::Vector3;
    using GHULBUS_MATH_NAMESPACE::Transform3;
    using Catch::Approx;

    Line3<float> const source_line(Point3<float>(1.f, 2.f, 3.f), Vector3<float>(1.f, 0.f, 0.f));

    SECTION("Translation of Line")
    {
        Transform3<float> translation = GHULBUS_MATH_NAMESPACE::make_translation(4.f, 5.f, 6.f);
        Line3<float> const l = translation * source_line;
        CHECK(l.p == Point3<float>(5.f, 7.f, 9.f));
        CHECK(l.v == source_line.v);
    }

    SECTION("Scaling of Line")
    {
        Transform3<float> scale = GHULBUS_MATH_NAMESPACE::make_scale(4.f, 5.f, 6.f);
        Line3<float> const l = scale * source_line;
        CHECK(l.p == Point3<float>(4.f, 10.f, 18.f));
        CHECK(l.v == Vector3<float>(4.f, 0.f, 0.f));
    }

    SECTION("Rotation of Line")
    {
        Transform3<float> rotation = GHULBUS_MATH_NAMESPACE::make_rotation_z(GHULBUS_MATH_NAMESPACE::traits::Pi<float>::value / 2.f);
        Line3<float> const l = rotation * source_line;
        CHECK(l.p.x == Approx(-2.f));
        CHECK(l.p.y == Approx(1.f));
        CHECK(l.p.z == 3.f);
        CHECK(l.v.x == Approx(0.f).margin(1e-6f));
        CHECK(l.v.y == Approx(1.f));
        CHECK(l.v.z == 0.f);
    }
}
