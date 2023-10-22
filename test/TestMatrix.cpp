#include <gbMath/Matrix.hpp>

#include <gbMath/MatrixION.hpp>
#include <gbMath/VectorION.hpp>


#include <catch.hpp>

#include <iterator>
#include <numeric>

TEST_CASE("Matrix")
{
    using GHULBUS_MATH_NAMESPACE::Matrix;
    using GHULBUS_MATH_NAMESPACE::doNotInitialize;

    SECTION("Static Properties")
    {
        static_assert(std::same_as<Matrix<float, 3, 2>::ValueType, float>);
        static_assert(std::same_as<Matrix<int, 3, 2>::ValueType, int>);
        static_assert(std::same_as<Matrix<double, 3, 2>::ValueType, double>);
        static_assert(Matrix<float, 3, 2>::Rows::value == 3);
        static_assert(Matrix<float, 3, 2>::Columns::value == 2);
        static_assert(Matrix<double, 5, 2>::Rows::value == 5);
        static_assert(Matrix<double, 5, 2>::Columns::value == 2);
        static_assert(Matrix<float, 42, 2>::Rows::value == 42);
        static_assert(Matrix<float, 42, 4>::Columns::value == 4);
    }

    SECTION("Default constructor initializes to 0")
    {
        Matrix<float, 2, 3> const m;

        CHECK(m.m[0] == 0.0f);
        CHECK(m.m[1] == 0.0f);
        CHECK(m.m[2] == 0.0f);
        CHECK(m.m[3] == 0.0f);
        CHECK(m.m[4] == 0.0f);
        CHECK(m.m[5] == 0.0f);
    }

    SECTION("Construction to uninitialized")
    {
        Matrix<float, 2, 3> m(doNotInitialize);

        m.m[0] = 0.0f;
        CHECK(m.m[0] == 0.0f);
        m.m[1] = 0.0f;
        CHECK(m.m[1] == 0.0f);
        m.m[2] = 0.0f;
        CHECK(m.m[2] == 0.0f);
        m.m[3] = 0.0f;
        CHECK(m.m[3] == 0.0f);
        m.m[4] = 0.0f;
        CHECK(m.m[4] == 0.0f);
        m.m[5] = 0.0f;
        CHECK(m.m[5] == 0.0f);
    }


    SECTION("Value initialization initializes to 0")
    {
        Matrix<float, 2, 3> const m{};

        CHECK(m.m[0] == 0.0f);
        CHECK(m.m[1] == 0.0f);
        CHECK(m.m[2] == 0.0f);
        CHECK(m.m[3] == 0.0f);
        CHECK(m.m[4] == 0.0f);
        CHECK(m.m[5] == 0.0f);
    }

    SECTION("Construction from values")
    {
        Matrix<float, 2, 3> const m( 1.f, 2.f, 3.f,
                                     4.f, 5.f, 6.f);

        CHECK(m.m[0] == 1.f);
        CHECK(m.m[1] == 2.f);
        CHECK(m.m[2] == 3.f);
        CHECK(m.m[3] == 4.f);
        CHECK(m.m[4] == 5.f);
        CHECK(m.m[5] == 6.f);
    }

    SECTION("Construction from array")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        float const arr[] = { 1.f,  2.f,  3.f,  4.f, 5.f,  6.f };

        {
            Matrix<float, 2, 3> m(arr, InputOrder_RowMajor());
            CHECK(m.m[0] == 1.f);  CHECK(m.m[1] == 2.f);  CHECK(m.m[2] == 3.f);
            CHECK(m.m[3] == 4.f);  CHECK(m.m[4] == 5.f);  CHECK(m.m[5] == 6.f);
        }

        {
            Matrix<float, 2, 3> m_col(arr, InputOrder_ColumnMajor());
            CHECK(m_col.m[0] == 1.f);  CHECK(m_col.m[1] == 3.f);  CHECK(m_col.m[2] == 5.f);
            CHECK(m_col.m[3] == 2.f);  CHECK(m_col.m[4] == 4.f);  CHECK(m_col.m[5] == 6.f);
        }
    }

    SECTION("Equality and not-equal comparison")
    {
        Matrix<float, 2, 3> const m1( 1.f, 2.f, 3.f,
                                      4.f, 5.f, 6.f);
        Matrix<float, 2, 3> m2(m1);

        CHECK(m1 == m2);
        CHECK_FALSE(m1 != m2);

        for(int i=0; i<6; ++i) {
            m2.m[i] = static_cast<float>(i);
            CHECK_FALSE(m1 == m2);
            CHECK(m1 != m2);
            m2.m[i] = m1.m[i];
            CHECK(m1 == m2);
            CHECK_FALSE(m1 != m2);
        }
    }

    SECTION("Copy construction")
    {
        Matrix<float, 2, 3> const m1( 1.f, 2.f, 3.f,
                                      4.f, 5.f, 6.f);
        Matrix<float, 2, 3> const m2(m1);

        CHECK(m2 == m1);
    }

    SECTION("Copy assignment")
    {
        Matrix<float, 2, 3> const m1( 1.f, 2.f, 3.f,
                                      4.f, 5.f, 6.f);
        Matrix<float, 2, 3> m2{};

        CHECK(m2 != m1);
        m2 = m1;
        CHECK(m2 == m1);
    }

    SECTION("Conversion construction")
    {
        Matrix<float, 2, 3> const m1( 1.f, 2.f, 3.f,
                                      4.f, 5.f, 6.f);
        Matrix<int, 2, 3> mi(m1);

        CHECK(mi == Matrix<int, 2, 3>(1, 2, 3, 4, 5, 6));
    }

    SECTION("Matrix dimension")
    {
        Matrix<int, 2, 3> m23;
        CHECK(m23.dimension() == std::pair<std::size_t, std::size_t>(2, 3));
        Matrix<int, 3, 2> m32;
        CHECK(m32.dimension() == std::pair<std::size_t, std::size_t>(3, 2));
        Matrix<int, 15, 9> m159;
        CHECK(m159.dimension() == std::pair<std::size_t, std::size_t>(15, 9));
        Matrix<int, 1, 8> m18;
        CHECK(m18.dimension() == std::pair<std::size_t, std::size_t>(1, 8));
    }

    SECTION("Is square")
    {
        Matrix<int, 1, 1> m11;
        CHECK(m11.is_square());
        Matrix<int, 1, 2> m12;
        CHECK_FALSE(m12.is_square());
        Matrix<int, 2, 1> m21;
        CHECK_FALSE(m21.is_square());
        Matrix<int, 2, 2> m22;
        CHECK(m22.is_square());
        Matrix<int, 3, 1> m31;
        CHECK_FALSE(m31.is_square());
        Matrix<int, 9, 9> m99;
        CHECK(m99.is_square());
    }

    SECTION("Array index operator")
    {
        Matrix<float, 2, 3> m( 1.f, 2.f, 3.f,
                               4.f, 5.f, 6.f);
        CHECK(m[0] == 1.f);
        CHECK(m[1] == 2.f);
        CHECK(m[2] == 3.f);
        CHECK(m[3] == 4.f);
        CHECK(m[4] == 5.f);
        CHECK(m[5] == 6.f);
        m[1] = 55.f;
        CHECK(m[1] == 55.f);

        Matrix<float, 2, 3> m_arr[] = {
            Matrix<float, 2, 3>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f),
            Matrix<float, 2, 3>(7.f, 8.f, 9.f, 10.f, 11.f, 12.f)
        };

        for(int i=0; i<6; ++i) {
            CHECK(m_arr[0][i] == static_cast<float>(i) + 1.f);
            CHECK(m_arr[1][i] == static_cast<float>(i) + 7.f);
        }
    }

    SECTION("Array index const operator")
    {
        Matrix<float, 2, 3> const m_const( 1.f, 2.f, 3.f,
                                           4.f, 5.f, 6.f);
        CHECK(m_const[0] == 1.f);
        CHECK(m_const[1] == 2.f);
        CHECK(m_const[2] == 3.f);
        CHECK(m_const[3] == 4.f);
        CHECK(m_const[4] == 5.f);
        CHECK(m_const[5] == 6.f);
    }

    SECTION("Multi-dimensional index")
    {
        Matrix<float, 2, 3> m( 1.f, 2.f, 3.f,
                               4.f, 5.f, 6.f);
        CHECK(m(0, 0) == 1.f);
        CHECK(m(0, 1) == 2.f);
        CHECK(m(0, 2) == 3.f);
        CHECK(m(1, 0) == 4.f);
        CHECK(m(1, 1) == 5.f);
        CHECK(m(1, 2) == 6.f);
        
        m(0, 0) = 55.f;
        CHECK(m(0, 0) == 55.f);
    }

    SECTION("Multi-dimensional index")
    {
        Matrix<float, 2, 3> const m_const( 1.f, 2.f, 3.f,
                                           4.f, 5.f, 6.f);
        CHECK(m_const(0, 0) == 1.f);
        CHECK(m_const(0, 1) == 2.f);
        CHECK(m_const(0, 2) == 3.f);
        CHECK(m_const(1, 0) == 4.f);
        CHECK(m_const(1, 1) == 5.f);
        CHECK(m_const(1, 2) == 6.f);
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        int iota[6];
        std::iota(std::begin(iota), std::end(iota), 1);
        // lower elements take precedence
        int arr[6] = {};
        for(int i=0; i<6; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix<int, 2, 3>(iota, InputOrder_RowMajor()) < Matrix<int, 2, 3>(arr, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<6; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix<int, 2, 3>(iota, InputOrder_RowMajor()) < Matrix<int, 2, 3>(arr, InputOrder_RowMajor()));
        }
        // not less if both sides are equal
        CHECK_FALSE(Matrix<int, 2, 3>(iota, InputOrder_RowMajor()) < Matrix<int, 2, 3>(iota, InputOrder_RowMajor()));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        int iota[6];
        std::iota(std::begin(iota), std::end(iota), 1);
        // lower elements take precedence
        int arr[6] = {};
        for(int i=0; i<6; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix<int, 2, 3>(arr, InputOrder_RowMajor()) > Matrix<int, 2, 3>(iota, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<6; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix<int, 2, 3>(arr, InputOrder_RowMajor()) > Matrix<int, 2, 3>(iota, InputOrder_RowMajor()));
        }
        // not greater if both sides are equal
        CHECK_FALSE(Matrix<int, 2, 3>(iota, InputOrder_RowMajor()) > Matrix<int, 2, 3>(iota, InputOrder_RowMajor()));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        int iota[6];
        std::iota(std::begin(iota), std::end(iota), 1);
        // lower elements take precedence
        int arr[6] = {};
        for(int i=0; i<6; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix<int, 2, 3>(iota, InputOrder_RowMajor()) <= Matrix<int, 2, 3>(arr, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<6; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix<int, 2, 3>(iota, InputOrder_RowMajor()) <= Matrix<int, 2, 3>(arr, InputOrder_RowMajor()));
        }
        // both sides are equal
        CHECK(Matrix<int, 2, 3>(iota, InputOrder_RowMajor()) <= Matrix<int, 2, 3>(iota, InputOrder_RowMajor()));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        int iota[6];
        std::iota(std::begin(iota), std::end(iota), 1);
        // lower elements take precedence
        int arr[6] = {};
        for(int i=0; i<6; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix<int, 2, 3>(arr, InputOrder_RowMajor()) >= Matrix<int, 2, 3>(iota, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<6; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix<int, 2, 3>(arr, InputOrder_RowMajor()) >= Matrix<int, 2, 3>(iota, InputOrder_RowMajor()));
        }
        // both sides are equal
        CHECK(Matrix<int, 2, 3>(iota, InputOrder_RowMajor()) >= Matrix<int, 2, 3>(iota, InputOrder_RowMajor()));
    }

    SECTION("Swap rows")
    {
        Matrix<int, 5, 3> m1( 1,  2,  3,
                              4,  5,  6,
                              7,  8,  9,
                             10, 11, 12,
                             13, 14, 15);

        m1.swap_rows(0, 4);
        CHECK(m1 == Matrix<int, 5, 3>(13, 14, 15,
                                       4,  5,  6,
                                       7,  8,  9,
                                      10, 11, 12,
                                       1,  2,  3));

        m1.swap_rows(1, 2);
        CHECK(m1 == Matrix<int, 5, 3>(13, 14, 15,
                                       7,  8,  9,
                                       4,  5,  6,
                                      10, 11, 12,
                                       1,  2,  3));

        m1.swap_rows(3, 1);
        CHECK(m1 == Matrix<int, 5, 3>(13, 14, 15,
                                      10, 11, 12,
                                       4,  5,  6,
                                       7,  8,  9,
                                       1,  2,  3));

        m1.swap_rows(1, 1);
        CHECK(m1 == Matrix<int, 5, 3>(13, 14, 15,
                                      10, 11, 12,
                                       4,  5,  6,
                                       7,  8,  9,
                                       1,  2,  3));
    }

    SECTION("Swap columns")
    {
        Matrix<int, 5, 3> m1( 1,  2,  3,
                              4,  5,  6,
                              7,  8,  9,
                             10, 11, 12,
                             13, 14, 15);

        m1.swap_columns(0, 1);
        CHECK(m1 == Matrix<int, 5, 3>( 2,  1,  3,
                                       5,  4,  6,
                                       8,  7,  9,
                                      11, 10, 12,
                                      14, 13, 15));

        m1.swap_columns(0, 2);
        CHECK(m1 == Matrix<int, 5, 3>( 3,  1,  2,
                                       6,  4,  5,
                                       9,  7,  8,
                                      12, 10, 11,
                                      15, 13, 14));

        m1.swap_columns(1, 1);
        CHECK(m1 == Matrix<int, 5, 3>( 3,  1,  2,
                                       6,  4,  5,
                                       9,  7,  8,
                                      12, 10, 11,
                                      15, 13, 14));
    }

    SECTION("Addition")
    {
        Matrix<float, 2, 3> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
        m1 += Matrix<float, 2, 3>(7.f, 8.f, 9.f, 10.f, 11.f, 12.f);
        CHECK(m1 == Matrix<float, 2, 3>(8.f, 10.f, 12.f, 14.f, 16.f, 18.f));
    }

    SECTION("Non-member addition")
    {
        Matrix<float, 2, 3> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
        Matrix<float, 2, 3> const m2(7.f, 8.f, 9.f, 10.f, 11.f, 12.f);
        Matrix<float, 2, 3> const sum = m1 + m2;
        CHECK(sum == Matrix<float, 2, 3>(8.f, 10.f, 12.f, 14.f, 16.f, 18.f));
    }

    SECTION("Subtraction")
    {
        Matrix<float, 2, 3> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
        m1 -= Matrix<float, 2, 3>(7.f, 8.f, 9.f, 10.f, 11.f, 12.f);
        CHECK(m1 == Matrix<float, 2, 3>(-6.f, -6.f, -6.f, -6.f, -6.f, -6.f));
    }

    SECTION("Non-member subtraction")
    {
        Matrix<float, 2, 3> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
        Matrix<float, 2, 3> const m2(7.f, 8.f, 9.f, 10.f, 11.f, 12.f);
        Matrix<float, 2, 3> const diff = m1 - m2;
        CHECK(diff == Matrix<float, 2, 3>(-6.f, -6.f, -6.f, -6.f, -6.f, -6.f));
    }

    SECTION("Scalar multiplication")
    {
        Matrix<float, 2, 3> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
        CHECK(&(m *= 5.f) == &m);
        CHECK(m == Matrix<float, 2, 3>(5.f, 10.f, 15.f, 20.f, 25.f, 30.f));
    }

    SECTION("Scalar multiplication non-member")
    {
        Matrix<float, 2, 3> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
        CHECK((m * 5.f) == Matrix<float, 2, 3>(5.f, 10.f, 15.f, 20.f, 25.f, 30.f));
        CHECK((5.f * m) == Matrix<float, 2, 3>(5.f, 10.f, 15.f, 20.f, 25.f, 30.f));
    }

    SECTION("Scalar division")
    {
        Matrix<float, 2, 3> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
        CHECK(&(m /= 2.f) == &m);
        CHECK(m == Matrix<float, 2, 3>(0.5f, 1.f, 1.5f, 2.0f, 2.5f, 3.0f));
    }

    SECTION("Scalar division non-member")
    {
        Matrix<float, 2, 3> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
        CHECK((m / 2.f) == Matrix<float, 2, 3>(0.5f, 1.f, 1.5f, 2.0f, 2.5f, 3.0f));
    }

    SECTION("Matrix-matrix multiplication")
    {
        Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
                               4.f, 5.f, 6.f,
                               7.f, 8.f, 9.f);
        Matrix<float, 3, 3> const m2(0.5f,  0.25f, 0.75f,
                                     1.f,   1.5f,  2.25f,
                                     1.75f, 0.5f,  2.0f);
        CHECK(&(m1 *= m2) == &m1);
        CHECK(m1 == Matrix<float, 3, 3>( 7.75f,  4.75f, 11.25f,
                                        17.5f,  11.5f,  26.25f,
                                        27.25f, 18.25f, 41.25f));

        Matrix<float, 3, 3> m3(1.f, 2.f, 3.f,
                               4.f, 5.f, 6.f,
                               7.f, 8.f, 9.f);
        CHECK(&(m3 *= m3) == &m3);
        CHECK(m3 == Matrix<float, 3, 3>( 30.f,  36.f,  42.f,
                                         66.f,  81.f,  96.f,
                                        102.f, 126.f, 150.f));
    }

    SECTION("Matrix-matrix multiplication non-member")
    {
        Matrix<float, 2, 3> const m1(  1.f,  2.f,  3.f,
                                       4.f,  5.f,  6.f);
        Matrix<float, 3, 4> const m2( 3.f,  5.f,  7.f, 11.f,
                                     13.f, 17.f, 19.f, 23.f,
                                     29.f, 31.f, 37.f, 41.f);
        Matrix<float, 2, 4> const m3 = m1 * m2;

        CHECK(m3 == Matrix<float, 2, 4>(116.f, 132.f, 156.f, 180.f,
                                        251.f, 291.f, 345.f, 405.f));

        Matrix<float, 4, 4> const m4(  1.f,  2.f,  3.f,  4.f,
                                       5.f,  6.f,  7.f,  8.f,
                                       9.f, 10.f, 11.f, 12.f,
                                      13.f, 14.f, 15.f, 16.f);
        CHECK(m4 * m4 == Matrix<float, 4, 4>( 90.f, 100.f, 110.f, 120.f,
                                             202.f, 228.f, 254.f, 280.f,
                                             314.f, 356.f, 398.f, 440.f,
                                             426.f, 484.f, 542.f, 600.f));
    }

    SECTION("Matrix transpose")
    {
        CHECK(transpose(Matrix<int, 3, 5>( 1,  2,  3,  4,  5,
                                           6,  7,  8,  9, 10,
                                          11, 12, 13, 14, 15)) ==
                Matrix<int, 5, 3>( 1,  6, 11,
                                   2,  7, 12,
                                   3,  8, 13,
                                   4,  9, 14,
                                   5, 10, 15));
    }

    SECTION("Identity")
    {
        Matrix<float, 6, 6> const m = GHULBUS_MATH_NAMESPACE::identityN<float, 6>();
        CHECK(m == Matrix<float, 6, 6>(1.f, 0.f, 0.f, 0.f, 0.f, 0.f,
                                       0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
                                       0.f, 0.f, 1.f, 0.f, 0.f, 0.f,
                                       0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
                                       0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
                                       0.f, 0.f, 0.f, 0.f, 0.f, 1.f));

        Matrix<unsigned int, 4, 4> const mi = GHULBUS_MATH_NAMESPACE::identityN<unsigned int, 4>();
        CHECK(mi == Matrix<unsigned int, 4, 4>(1u, 0u, 0u, 0u,
                                               0u, 1u, 0u, 0u,
                                               0u, 0u, 1u, 0u,
                                               0u, 0u, 0u, 1u));
    }
}

TEST_CASE("Matrix-Vector Interaction")
{
    using GHULBUS_MATH_NAMESPACE::Matrix;
    using GHULBUS_MATH_NAMESPACE::Vector;

    SECTION("Matrix from row vectors")
    {
        Vector<float, 3> row1(1.f, 2.f, 3.f);
        Vector<float, 3> row2(4.f, 5.f, 6.f);
        Vector<float, 3> row3(7.f, 8.f, 9.f);
        Vector<float, 3> row4(10.f, 11.f, 12.f);

        CHECK(matrix_from_row_vectors<float, 4, 3>(row1, row2, row3, row4) ==
                Matrix<float, 4, 3>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f));
    }

    SECTION("Matrix from column vectors")
    {
        Vector<float, 3> col1(1.f, 2.f, 3.f);
        Vector<float, 3> col2(4.f, 5.f, 6.f);
        Vector<float, 3> col3(7.f, 8.f, 9.f);
        Vector<float, 3> col4(10.f, 11.f, 12.f);

        CHECK(matrix_from_column_vectors<float, 3, 4>(col1, col2, col3, col4) ==
                Matrix<float, 3, 4>(1.f, 4.f, 7.f, 10.f,
                                    2.f, 5.f, 8.f, 11.f,
                                    3.f, 6.f, 9.f, 12.f));
    }

    SECTION("Row access")
    {
        Matrix<float, 2, 8> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        CHECK(m.row(0) == Vector<float, 8>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f));
        CHECK(m.row(1) == Vector<float, 8>(9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f));
    }

    SECTION("Column access")
    {
        Matrix<float, 2, 8> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
                                    9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        CHECK(m.column(0) == Vector<float, 2>(1.f, 9.f));
        CHECK(m.column(1) == Vector<float, 2>(2.f, 10.f));
        CHECK(m.column(2) == Vector<float, 2>(3.f, 11.f));
        CHECK(m.column(3) == Vector<float, 2>(4.f, 12.f));
        CHECK(m.column(4) == Vector<float, 2>(5.f, 13.f));
        CHECK(m.column(5) == Vector<float, 2>(6.f, 14.f));
        CHECK(m.column(6) == Vector<float, 2>(7.f, 15.f));
        CHECK(m.column(7) == Vector<float, 2>(8.f, 16.f));
    }

    SECTION("Matrix-vector multiplication")
    {
        Vector<float, 4> const v(3.f, 5.f, 7.f, 11.f);
        Matrix<float, 5, 4> const m1(  1.f,  2.f,  3.f,  4.f,
                                       5.f,  6.f,  7.f,  8.f,
                                       9.f, 10.f, 11.f, 12.f,
                                      13.f, 14.f, 15.f, 16.f,
                                      17.f, 18.f, 19.f, 20.f);
        Matrix<float, 2, 4> const m2( 1.f,     1.5f,    1.25f, 1.125f,
                                      1.75f,   0.5f,    0.25f, 0.125f);

        CHECK((m1 * v) == Vector<float, 5>(78.f, 182.f, 286.f, 390.f, 494.f));
        CHECK((m2 * v) == Vector<float, 2>(31.625f, 10.875f));
    }

    
    SECTION("Trace")
    {
        Matrix<float, 6, 6> const m( 1.f,  2.f,  3.f,  4.f,  5.f,  6.f,
                                     7.f,  8.f,  9.f, 10.f, 11.f, 12.f,
                                    13.f, 14.f, 15.f, 16.f, 17.f, 18.f,
                                    19.f, 20.f, 21.f, 22.f, 23.f, 24.f,
                                    25.f, 26.f, 27.f, 28.f, 29.f, 30.f,
                                    31.f, 32.f, 33.f, 34.f, 35.f, 30.f);
        CHECK(trace(m) == 105.f);
    }
}

TEST_CASE("LU Decomposition")
{
    using GHULBUS_MATH_NAMESPACE::Matrix;
    using GHULBUS_MATH_NAMESPACE::Vector;
    using GHULBUS_MATH_NAMESPACE::LUDecomposition;

    {
        Matrix<float, 3, 3> const m(6.f, 18.f, 3.f,
                                    2.f, 12.f, 1.f,
                                    4.f, 15.f, 3.f);

        LUDecomposition<float, 3> const lud = lu_decompose(m);
        REQUIRE(static_cast<bool>(lud));
        REQUIRE(lud);
        auto l = lud.getL();
        CHECK(l == Matrix<float, 3, 3>(    1.f,  0.f, 0.f,
                                       1.f/3.f,  1.f, 0.f,
                                       2.f/3.f, 0.5f, 1.f));
        auto u = lud.getU();
        CHECK(u == Matrix<float, 3, 3>(6.f, 18.f,  3.f,
                                       0.f,  6.f,  0.f,
                                       0.f,  0.f,  1.f));
        auto lu = l * u;
        CHECK(lu == m);

        CHECK(lud.getDeterminant() == 36.f);
    }

    {
        using Catch::Approx;
        Matrix<float, 6, 6> const m(48.f, 51.f, 83.f, 56.f, 86.f, 32.f,
                                    34.f, 17.f, 48.f, 87.f, 80.f, 23.f,
                                     8.f, 51.f, 46.f,  3.f, 18.f, 28.f,
                                    88.f, 30.f, 55.f, 60.f, 69.f, 34.f,
                                    96.f, 88.f, 76.f, 45.f, 56.f, 44.f,
                                    20.f, 81.f, 24.f, 81.f, 29.f, 25.f);

        LUDecomposition<float, 6> const lud = lu_decompose(m);

        auto l = lud.getL();
        auto u = lud.getU();
        auto p = lud.getP();
        auto lu = p * l * u;

        auto const [r, c] = m.dimension();
        for (std::size_t i = 0; i < r; ++i) {
            for (std::size_t j = 0; j < c; ++j) {
                CHECK(lu(i, j) == Approx(m(i, j)));
            }
        }

        CHECK(lud.getDeterminant() == Approx(-29931807057498744.f/29041807.f));
    }

    SECTION("LUD Singular")
    {
        LUDecomposition<float, 4> lud;
        lud.mark_singular();
        CHECK_FALSE(static_cast<bool>(lud));
        CHECK(!lud);
        CHECK(lud.getDeterminant() == 0.f);
    }

    SECTION("Solve system of linear equations")
    {
        {
            Matrix<float, 3, 3> m(1.f, 2.f, 1.f,
                                  3.f, 2.f, 4.f,
                                  4.f, 4.f, 3.f);
            auto const lud = lu_decompose(m);
            REQUIRE(lud);
            auto const x = lud.solveFor(Vector<float, 3>(5.f, 17.f, 26.f));
            CHECK(x == Vector<float, 3>(9.f, -1.f, -2.f));
        }
        {
            Matrix<float, 4, 4> m(1.f, 2.f, 1.f, -1.f,
                                  3.f, 2.f, 4.f,  4.f,
                                  4.f, 4.f, 3.f,  4.f,
                                  2.f, 0.f, 1.f,  5.f);
            auto const lud = lu_decompose(m);
            REQUIRE(lud);
            auto const x = lud.solveFor(Vector<float, 4>(5.f, 16.f, 22.f, 15.f));
            CHECK(x == Vector<float, 4>(16.f, -6.f, -2.f, -3.f));
        }
        {
            Matrix<float, 4, 4> m(1.f, 2.f, 1.f, -1.f,
                                  3.f, 6.f, 4.f,  4.f,
                                  4.f, 4.f, 3.f,  4.f,
                                  2.f, 0.f, 1.f,  5.f);
            auto const lud = lu_decompose(m);
            REQUIRE(lud);
            auto const x = lud.solveFor(Vector<float, 4>(5.f, 16.f, 22.f, 15.f));
            using Catch::Approx;
            CHECK(x[0] == Approx(4.f));
            CHECK(x[1] == Approx(-12.f));
            CHECK(x[2] == Approx(22.f));
            CHECK(x[3] == Approx(-3.f));
        }
        {
            Matrix<float, 4, 4> m(1.f, 2.f, 1.f, -1.f,
                                  3.f, 6.f, 4.f,  4.f,
                                  4.f, 8.f, 3.f,  4.f,
                                  2.f, 4.f, 1.f,  5.f);
            auto const lud = lu_decompose(m);
            CHECK(!lud);
        }
    }
}

TEST_CASE("Fixed-Size Matrix Interaction")
{
    using GHULBUS_MATH_NAMESPACE::Matrix;

    SECTION("Construction from Matrix2")
    {
        using GHULBUS_MATH_NAMESPACE::Matrix2;
        Matrix2<float> m22{ 11.f, 22.f,
                            33.f, 44.f };
        Matrix m{ m22 };
        static_assert(std::same_as<decltype(m)::ValueType, float>);
        REQUIRE(m.dimension() == std::pair<std::size_t, std::size_t>(2, 2));
        CHECK(m(0, 0) == 11.f);  CHECK(m(0, 1) == 22.f);
        CHECK(m(1, 0) == 33.f);  CHECK(m(1, 1) == 44.f);

        Matrix2<int> m2i{  5, 23,
                          15, 55 };
        Matrix mi{ m2i };
        static_assert(std::same_as<decltype(mi)::ValueType, int>);
        REQUIRE(m.dimension() == std::pair<std::size_t, std::size_t>(2, 2));
        CHECK(mi(0, 0) ==  5);  CHECK(mi(0, 1) == 23);
        CHECK(mi(1, 0) == 15);  CHECK(mi(1, 1) == 55);
    }

    SECTION("Construction from Matrix3")
    {
        using GHULBUS_MATH_NAMESPACE::Matrix3;
        Matrix3<float> m33{ 11.f, 22.f, 33.f,
                            44.f, 55.f, 66.f,
                            77.f, 88.f, 99.f };
        Matrix m{ m33 };
        static_assert(std::same_as<decltype(m)::ValueType, float>);
        REQUIRE(m.dimension() == std::pair<std::size_t, std::size_t>(3, 3));
        CHECK(m(0, 0) == 11.f);  CHECK(m(0, 1) == 22.f);  CHECK(m(0, 2) == 33.f);
        CHECK(m(1, 0) == 44.f);  CHECK(m(1, 1) == 55.f);  CHECK(m(1, 2) == 66.f);
        CHECK(m(2, 0) == 77.f);  CHECK(m(2, 1) == 88.f);  CHECK(m(2, 2) == 99.f);

        Matrix3<int> m3i{  5, 23, 42,
                          15, 55, 65,
                          13, 17, 23, };
        Matrix mi{ m3i };
        static_assert(std::same_as<decltype(mi)::ValueType, int>);
        REQUIRE(m.dimension() == std::pair<std::size_t, std::size_t>(3, 3));
        CHECK(mi(0, 0) ==  5);  CHECK(mi(0, 1) == 23);  CHECK(mi(0, 2) == 42);
        CHECK(mi(1, 0) == 15);  CHECK(mi(1, 1) == 55);  CHECK(mi(1, 2) == 65);
        CHECK(mi(2, 0) == 13);  CHECK(mi(2, 1) == 17);  CHECK(mi(2, 2) == 23);
    }

    SECTION("Construction from Matrix4")
    {
        using GHULBUS_MATH_NAMESPACE::Matrix4;
        Matrix4<float> m44{ 11.f, 22.f, 33.f, 12.f,
                            44.f, 55.f, 66.f, 13.f,
                            77.f, 88.f, 99.f, 14.f,
                            15.f, 16.f, 17.f, 18.f };
        Matrix m{ m44 };
        static_assert(std::same_as<decltype(m)::ValueType, float>);
        REQUIRE(m.dimension() == std::pair<std::size_t, std::size_t>(4, 4));
        CHECK(m(0, 0) == 11.f);  CHECK(m(0, 1) == 22.f);  CHECK(m(0, 2) == 33.f);  CHECK(m(0, 3) == 12.f);
        CHECK(m(1, 0) == 44.f);  CHECK(m(1, 1) == 55.f);  CHECK(m(1, 2) == 66.f);  CHECK(m(1, 3) == 13.f);
        CHECK(m(2, 0) == 77.f);  CHECK(m(2, 1) == 88.f);  CHECK(m(2, 2) == 99.f);  CHECK(m(2, 3) == 14.f);
        CHECK(m(3, 0) == 15.f);  CHECK(m(3, 1) == 16.f);  CHECK(m(3, 2) == 17.f);  CHECK(m(3, 3) == 18.f);

        Matrix4<int> m4i{  5, 23, 42, 54,
                          15, 55, 65, 95,
                          13, 17, 23, 29,
                          48, 10, 79, 86 };
        Matrix mi{ m4i };
        static_assert(std::same_as<decltype(mi)::ValueType, int>);
        REQUIRE(m.dimension() == std::pair<std::size_t, std::size_t>(4, 4));
        CHECK(mi(0, 0) ==  5);  CHECK(mi(0, 1) == 23);  CHECK(mi(0, 2) == 42);  CHECK(mi(0, 3) == 54);
        CHECK(mi(1, 0) == 15);  CHECK(mi(1, 1) == 55);  CHECK(mi(1, 2) == 65);  CHECK(mi(1, 3) == 95);
        CHECK(mi(2, 0) == 13);  CHECK(mi(2, 1) == 17);  CHECK(mi(2, 2) == 23);  CHECK(mi(2, 3) == 29);
        CHECK(mi(3, 0) == 48);  CHECK(mi(3, 1) == 10);  CHECK(mi(3, 2) == 79);  CHECK(mi(3, 3) == 86);
    }

}
