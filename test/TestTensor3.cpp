#include <gbMath/Tensor3.hpp>
#include <gbMath/MatrixIO.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("Tensor3")
{
    using GHULBUS_MATH_NAMESPACE::Basis3;
    using GHULBUS_MATH_NAMESPACE::Matrix3;
    using GHULBUS_MATH_NAMESPACE::Tensor3;
    using GHULBUS_MATH_NAMESPACE::Vector3;

    SECTION("Default construction")
    {
        Tensor3<float> t;
        CHECK(t.m == Matrix3<float>(1.f, 0.f, 0.f,
                                    0.f, 1.f, 0.f,
                                    0.f, 0.f, 1.f));
    }

    SECTION("Construction from Basis")
    {
        Basis3<float> b;
        Tensor3<float> t(b);
        CHECK(t.m == Matrix3<float>(1.f, 0.f, 0.f,
                                    0.f, 1.f, 0.f,
                                    0.f, 0.f, 1.f));

        b = Basis3<float>(Vector3<float>(1.f, 0.f, 0.f), Vector3<float>(1.f, 1.f, 0.f), Vector3<float>(1.f, 1.f, 1.f));
        t = Tensor3<float>(b);
        CHECK(t.m == Matrix3<float>(1.f, 1.f, 1.f,
                                    1.f, 2.f, 2.f,
                                    1.f, 2.f, 3.f));
    }

    SECTION("Contravariant Tensor")
    {
        Basis3<float> b;
        Tensor3<float> t(b);
        t = contravariant(t);
        CHECK(t.m == Matrix3<float>(1.f, 0.f, 0.f,
                                    0.f, 1.f, 0.f,
                                    0.f, 0.f, 1.f));

        b = Basis3<float>(Vector3<float>(1.f, 0.f, 0.f), Vector3<float>(1.f, 1.f, 0.f), Vector3<float>(1.f, 1.f, 1.f));
        t = contravariant(Tensor3<float>(b));
        CHECK(t.m == Matrix3<float>( 2.f, -1.f,  0.f,
                                    -1.f,  2.f, -1.f,
                                     0.f, -1.f,  1.f));
    }
}
