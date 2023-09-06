#include <gbMath/MatrixIO.hpp>

#include <catch.hpp>

#include <sstream>

TEST_CASE("MatrixIO")
{
    using GHULBUS_MATH_NAMESPACE::Matrix2;
    using GHULBUS_MATH_NAMESPACE::Matrix3;
    using GHULBUS_MATH_NAMESPACE::Matrix4;
    using GHULBUS_MATH_NAMESPACE::Matrix;

    std::stringstream sstr;

    SECTION("Matrix2 ostream insertion")
    {
        sstr << Matrix2<int>(1, 2,
            3, 4);
        CHECK(sstr.str() == "[ [1 2] [3 4] ]");
    }

    SECTION("Matrix3 ostream insertion")
    {
        sstr << Matrix3<int>(1, 2, 3,
                             4, 5, 6,
                             7, 8, 9);
        CHECK(sstr.str() == "[ [1 2 3] [4 5 6] [7 8 9] ]");
    }

    SECTION("Matrix4 ostream insertion")
    {
        sstr << Matrix4<int>( 1,  2,  3,  4,
                              5,  6,  7,  8,
                              9, 10, 11, 12,
                             13, 14, 15, 16);
        CHECK(sstr.str() == "[ [1 2 3 4] [5 6 7 8] [9 10 11 12] [13 14 15 16] ]");
    }

    SECTION("Matrix MxN ostream insertion")
    {
        sstr << Matrix<int, 3, 5>(1, 2, 3, 4, 5,
                                  6, 7, 8, 9, 10,
                                  11, 12, 13, 14, 15);
        CHECK(sstr.str() == "[ [1 2 3 4 5] [6 7 8 9 10] [11 12 13 14 15] ]");

        sstr = std::stringstream{};
        sstr << Matrix<int, 1, 1>(-42);
        CHECK(sstr.str() == "[ [-42] ]");

    }
}
