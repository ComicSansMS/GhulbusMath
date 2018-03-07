#include <gbMath/OBB3.hpp>
#include <gbMath/MatrixIO.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

#include <limits>

TEST_CASE("OBB3")
{
    using GHULBUS_MATH_NAMESPACE::OBB3;
    using GHULBUS_MATH_NAMESPACE::Matrix3;
    using GHULBUS_MATH_NAMESPACE::Point3;
    using GHULBUS_MATH_NAMESPACE::Vector3;

    SECTION("Value initialization initializes to 0")
    {
        OBB3<float> obb{};
        CHECK(obb.center == Point3<float>(0.f, 0.f, 0.f));
        CHECK(obb.orientation == Matrix3<float>(0.f, 0.f, 0.f,
                                                0.f, 0.f, 0.f,
                                                0.f, 0.f, 0.f));
        CHECK(obb.halfwidth == Vector3<float>(0.f, 0.f, 0.f));
    }

    SECTION("Construction from point, orientation and halfwidth axes")
    {
        OBB3<float> obb(Point3<float>(1.f, 2.f, 3.f),
                        Matrix3<float>(1.5f, 2.5f, 3.5f,
                                       4.5f, 5.5f, 6.5f,
                                       7.5f, 8.5f, 9.5f),
                        Vector3<float>(4.f, 5.f, 6.f));
        CHECK(obb.center == Point3<float>(1.f, 2.f, 3.f));
        CHECK(obb.orientation == Matrix3<float>(1.5f, 2.5f, 3.5f,
                                                4.5f, 5.5f, 6.5f,
                                                7.5f, 8.5f, 9.5f));
        CHECK(obb.halfwidth == Vector3<float>(4.f, 5.f, 6.f));
    }

    SECTION("OBB-OBB intersection")
    {
        OBB3<float> ob1(Point3<float>(1.f, 2.f, 3.f),
                        Matrix3<float>(1.5f, 2.5f, 3.5f,
                                       4.5f, 5.5f, 6.5f,
                                       7.5f, 8.5f, 9.5f),
                        Vector3<float>(4.f, 5.f, 6.f));
        OBB3<float> ob2(Point3<float>(1.f, 2.f, 3.f),
                        Matrix3<float>(1.5f, 2.5f, 3.5f,
                                       4.5f, 5.5f, 6.5f,
                                       7.5f, 8.5f, 9.5f),
                        Vector3<float>(4.f, 5.f, 6.f));
        CHECK(intersects(ob1, ob2));
    }
}
