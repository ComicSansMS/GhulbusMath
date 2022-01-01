#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

#include <sstream>

TEST_CASE("VectorIO")
{
    using GHULBUS_MATH_NAMESPACE::Vector2;
    using GHULBUS_MATH_NAMESPACE::Vector3;
    using GHULBUS_MATH_NAMESPACE::Vector4;

    std::stringstream sstr;

    SECTION("Vector2 ostream insertion")
    {
        sstr << Vector2<int>(1, 2);
        CHECK(sstr.str() == "[1 2]");
    }

    SECTION("Vector2 ostream insertion char")
    {
        sstr << Vector2<char>(1, 2);
        CHECK(sstr.str() == "[1 2]");
    }

    SECTION("Vector2 ostream insertion signed char")
    {
        sstr << Vector2<signed char>(1, -2);
        CHECK(sstr.str() == "[1 -2]");
    }

    SECTION("Vector2 ostream insertion unsigned char")
    {
        sstr << Vector2<unsigned char>(1, 2);
        CHECK(sstr.str() == "[1 2]");
    }

    SECTION("Vector3 ostream insertion")
    {
        sstr << Vector3<int>(1, 2, 3);
        CHECK(sstr.str() == "[1 2 3]");
    }

    SECTION("Vector3 ostream insertion char")
    {
        sstr << Vector3<char>(1, 2, 3);
        CHECK(sstr.str() == "[1 2 3]");
    }

    SECTION("Vector3 ostream insertion signed char")
    {
        sstr << Vector3<signed char>(1, -2, 3);
        CHECK(sstr.str() == "[1 -2 3]");
    }

    SECTION("Vector3 ostream insertion unsigned char")
    {
        sstr << Vector3<unsigned char>(1, 2, 3);
        CHECK(sstr.str() == "[1 2 3]");
    }

    SECTION("Vector4 ostream insertion")
    {
        sstr << Vector4<int>(1, 2, 3, 4);
        CHECK(sstr.str() == "[1 2 3 4]");
    }

    SECTION("Vector4 ostream insertion char")
    {
        sstr << Vector4<char>(1, 2, 3, 4);
        CHECK(sstr.str() == "[1 2 3 4]");
    }

    SECTION("Vector4 ostream insertion signed char")
    {
        sstr << Vector4<signed char>(1, -2, 3, -4);
        CHECK(sstr.str() == "[1 -2 3 -4]");
    }

    SECTION("Vector4 ostream insertion unsigned char")
    {
        sstr << Vector4<unsigned char>(1, 2, 3, 4);
        CHECK(sstr.str() == "[1 2 3 4]");
    }
}
