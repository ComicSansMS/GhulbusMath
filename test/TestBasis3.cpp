#include <gbMath/Basis3.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("Basis3")
{
    using GHULBUS_MATH_NAMESPACE::Basis3;
    using GHULBUS_MATH_NAMESPACE::ComponentVector3;
    using GHULBUS_MATH_NAMESPACE::Matrix3;
    using GHULBUS_MATH_NAMESPACE::Vector3;

    SECTION("Default construction")
    {
        Basis3<float> b;
        CHECK(b.rowMatrix() == Matrix3<float>(1.f, 0.f, 0.f,
                                              0.f, 1.f, 0.f,
                                              0.f, 0.f, 1.f));
    }

    SECTION("Construction from base vectors")
    {
        Basis3<float> b(Vector3<float>(1.f, 2.f, 3.f), Vector3<float>(4.f, 5.f, 6.f), Vector3<float>(7.f, 8.f, 9.f));
        CHECK(b.rowMatrix() == Matrix3<float>(1.f, 2.f, 3.f,
                                              4.f, 5.f, 6.f,
                                              7.f, 8.f, 9.f));
    }

    SECTION("Base Axes Accessors")
    {
        Basis3<float> b;
        CHECK(b.x() == Vector3<float>(1.f, 0.f, 0.f));
        CHECK(b.y() == Vector3<float>(0.f, 1.f, 0.f));
        CHECK(b.z() == Vector3<float>(0.f, 0.f, 1.f));
    }

    SECTION("Column-Matrix Accessor")
    {
        Basis3<float> b(Vector3<float>(1.f, 2.f, 3.f), Vector3<float>(4.f, 5.f, 6.f), Vector3<float>(7.f, 8.f, 9.f));
        CHECK(b.columnMatrix() == Matrix3<float>(1.f, 4.f, 7.f,
                                                 2.f, 5.f, 8.f,
                                                 3.f, 6.f, 9.f));
    }

    SECTION("Transform ComponentVector to Vector")
    {
        Basis3<float> b(Vector3<float>(1.f, 0.f, 0.f), Vector3<float>(1.f, 1.f, 0.f), Vector3<float>(1.f, 1.f, 1.f));
        CHECK(b.fromComponentVector(ComponentVector3<float>(0.f, 1.f, 1.f)) == Vector3<float>(2.f, 2.f, 1.f));
        CHECK(b.fromComponentVector(ComponentVector3<float>(0.f, -5.f, 4.f)) == Vector3<float>(-1.f, -1.f, 4.f));
    }

    SECTION("Transform Vector into Basis")
    {
        Basis3<float> b(Vector3<float>(4.f, 0.f, 0.f), Vector3<float>(3.f, 5.f, 0.f), Vector3<float>(0.f, 0.f, 1.f));
        ComponentVector3<float> cv = b.toComponentVector(Vector3<float>(2.f, 10.f, 0.f));
        CHECK(cv.x == -1.f);
        CHECK(cv.y == 2.f);
        CHECK(cv.z == 0.f);
        CHECK(b.fromComponentVector(cv) == Vector3<float>(2.f, 10.f, 0.f));
    }

    SECTION("Contravariant Bases")
    {
        Basis3<float> b(Vector3<float>(1.f, 0.f, 0.f), Vector3<float>(1.f, 1.f, 0.f), Vector3<float>(1.f, 1.f, 1.f));
        Basis3<float> bc = contravariant(b);
        CHECK(bc.rowMatrix() == Matrix3<float>( 1.f,  0.f, 0.f,
                                               -1.f,  1.f, 0.f,
                                                0.f, -1.f, 1.f));
        CHECK(bc.rowMatrix() * b.rowMatrix() == GHULBUS_MATH_NAMESPACE::identity3<float>());
    }

}
