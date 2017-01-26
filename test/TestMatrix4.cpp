#include <gbMath/Matrix4.hpp>
#include <gbMath/MatrixIO.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

#include <iterator>
#include <numeric>

TEST_CASE("Matrix4")
{
    using GHULBUS_MATH_NAMESPACE::Matrix4;

    SECTION("Value initialization initializes to 0")
    {
        Matrix4<float> const m{};

        CHECK(m.m11 == 0.0f);
        CHECK(m.m12 == 0.0f);
        CHECK(m.m13 == 0.0f);
        CHECK(m.m14 == 0.0f);
        CHECK(m.m21 == 0.0f);
        CHECK(m.m22 == 0.0f);
        CHECK(m.m23 == 0.0f);
        CHECK(m.m24 == 0.0f);
        CHECK(m.m31 == 0.0f);
        CHECK(m.m32 == 0.0f);
        CHECK(m.m33 == 0.0f);
        CHECK(m.m34 == 0.0f);
        CHECK(m.m41 == 0.0f);
        CHECK(m.m42 == 0.0f);
        CHECK(m.m43 == 0.0f);
        CHECK(m.m44 == 0.0f);
    }

    SECTION("Construction from values")
    {
        Matrix4<float> const m( 1.f,  2.f,  3.f,  4.f,
                                5.f,  6.f,  7.f,  8.f,
                                9.f, 10.f, 11.f, 12.f,
                               13.f, 14.f, 15.f, 16.f);

        CHECK(m.m11 ==  1.f);
        CHECK(m.m12 ==  2.f);
        CHECK(m.m13 ==  3.f);
        CHECK(m.m14 ==  4.f);
        CHECK(m.m21 ==  5.f);
        CHECK(m.m22 ==  6.f);
        CHECK(m.m23 ==  7.f);
        CHECK(m.m24 ==  8.f);
        CHECK(m.m31 ==  9.f);
        CHECK(m.m32 == 10.f);
        CHECK(m.m33 == 11.f);
        CHECK(m.m34 == 12.f);
        CHECK(m.m41 == 13.f);
        CHECK(m.m42 == 14.f);
        CHECK(m.m43 == 15.f);
        CHECK(m.m44 == 16.f);
    }

    SECTION("Construction from array")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        float const arr[] = {
             1.f,  2.f,  3.f,  4.f,
             5.f,  6.f,  7.f,  8.f,
             9.f, 10.f, 11.f, 12.f,
            13.f, 14.f, 15.f, 16.f
        };

        {
            Matrix4<float> m(arr, InputOrder_RowMajor());
            CHECK(m.m11 == 1.f);
            CHECK(m.m12 == 2.f);
            CHECK(m.m13 == 3.f);
            CHECK(m.m14 == 4.f);
            CHECK(m.m21 == 5.f);
            CHECK(m.m22 == 6.f);
            CHECK(m.m23 == 7.f);
            CHECK(m.m24 == 8.f);
            CHECK(m.m31 == 9.f);
            CHECK(m.m32 == 10.f);
            CHECK(m.m33 == 11.f);
            CHECK(m.m34 == 12.f);
            CHECK(m.m41 == 13.f);
            CHECK(m.m42 == 14.f);
            CHECK(m.m43 == 15.f);
            CHECK(m.m44 == 16.f);
        }

        {
            Matrix4<float> m_col(arr, InputOrder_ColumnMajor());
            CHECK(m_col.m11 == 1.f);
            CHECK(m_col.m12 == 5.f);
            CHECK(m_col.m13 == 9.f);
            CHECK(m_col.m14 == 13.f);
            CHECK(m_col.m21 == 2.f);
            CHECK(m_col.m22 == 6.f);
            CHECK(m_col.m23 == 10.f);
            CHECK(m_col.m24 == 14.f);
            CHECK(m_col.m31 == 3.f);
            CHECK(m_col.m32 == 7.f);
            CHECK(m_col.m33 == 11.f);
            CHECK(m_col.m34 == 15.f);
            CHECK(m_col.m41 == 4.f);
            CHECK(m_col.m42 == 8.f);
            CHECK(m_col.m43 == 12.f);
            CHECK(m_col.m44 == 16.f);
        }
    }

    SECTION("Equality and not-equal comparison")
    {
        Matrix4<float> const m1( 1.f,  2.f,  3.f,  4.f,
                                 5.f,  6.f,  7.f,  8.f,
                                 9.f, 10.f, 11.f, 12.f,
                                13.f, 14.f, 15.f, 16.f);
        Matrix4<float> m2(m1);

        CHECK(m1 == m2);
        CHECK_FALSE(m1 != m2);

        for(int i=0; i<16; ++i) {
            m2[i] = static_cast<float>(i);
            CHECK_FALSE(m1 == m2);
            CHECK(m1 != m2);
            m2[i] = m1[i];
            CHECK(m1 == m2);
            CHECK_FALSE(m1 != m2);
        }
    }

    SECTION("Copy construction")
    {
        Matrix4<float> const m1( 1.f,  2.f,  3.f,  4.f,
                                 5.f,  6.f,  7.f,  8.f,
                                 9.f, 10.f, 11.f, 12.f,
                                13.f, 14.f, 15.f, 16.f);
        Matrix4<float> const m2(m1);

        CHECK(m2 == m1);
    }

    SECTION("Copy assignment")
    {
        Matrix4<float> const m1( 1.f,  2.f,  3.f,  4.f,
                                 5.f,  6.f,  7.f,  8.f,
                                 9.f, 10.f, 11.f, 12.f,
                                13.f, 14.f, 15.f, 16.f);
        Matrix4<float> m2{};

        CHECK(m2 != m1);
        m2 = m1;
        CHECK(m2 == m1);
    }

    SECTION("Conversion construction")
    {
        Matrix4<float> const m1( 1.f,  2.f,  3.f,  4.f,
                                 5.f,  6.f,  7.f,  8.f,
                                 9.f, 10.f, 11.f, 12.f,
                                13.f, 14.f, 15.f, 16.f);
        Matrix4<int> mi(m1);

        CHECK(mi == Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
    }

    SECTION("Array index operator")
    {
        Matrix4<float> m( 1.f,  2.f,  3.f,  4.f,
                          5.f,  6.f,  7.f,  8.f,
                          9.f, 10.f, 11.f, 12.f,
                         13.f, 14.f, 15.f, 16.f);
        CHECK(m[0] == 1.f);
        CHECK(m[1] == 2.f);
        CHECK(m[2] == 3.f);
        CHECK(m[3] == 4.f);
        CHECK(m[4] == 5.f);
        CHECK(m[5] == 6.f);
        CHECK(m[6] == 7.f);
        CHECK(m[7] == 8.f);
        CHECK(m[8] == 9.f);
        CHECK(m[9] == 10.f);
        CHECK(m[10] == 11.f);
        CHECK(m[11] == 12.f);
        CHECK(m[12] == 13.f);
        CHECK(m[13] == 14.f);
        CHECK(m[14] == 15.f);
        CHECK(m[15] == 16.f);
        m[1] = 55.f;
        CHECK(m[1] == 55.f);

        Matrix4<float> m_arr[] = { Matrix4<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f,
                                                  9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f),
                                   Matrix4<float>(17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f,
                                                  25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f, 32.f) };

        for(int i=0; i<16; ++i) {
            CHECK(m_arr[0][i] == static_cast<float>(i) + 1.f);
            CHECK(m_arr[1][i] == static_cast<float>(i) + 17.f);
        }
    }

    SECTION("Array index const operator")
    {
        Matrix4<float> const m_const( 1.f,  2.f,  3.f,  4.f,
                                      5.f,  6.f,  7.f,  8.f,
                                      9.f, 10.f, 11.f, 12.f,
                                     13.f, 14.f, 15.f, 16.f);
        CHECK(m_const[0] == 1.f);
        CHECK(m_const[1] == 2.f);
        CHECK(m_const[2] == 3.f);
        CHECK(m_const[3] == 4.f);
        CHECK(m_const[4] == 5.f);
        CHECK(m_const[5] == 6.f);
        CHECK(m_const[6] == 7.f);
        CHECK(m_const[7] == 8.f);
        CHECK(m_const[8] == 9.f);
        CHECK(m_const[9] == 10.f);
        CHECK(m_const[10] == 11.f);
        CHECK(m_const[11] == 12.f);
        CHECK(m_const[12] == 13.f);
        CHECK(m_const[13] == 14.f);
        CHECK(m_const[14] == 15.f);
        CHECK(m_const[15] == 16.f);
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        int iota[16];
        std::iota(std::begin(iota), std::end(iota), 1);
        // lower elements take precedence
        int arr[16] = {};
        for(int i=0; i<16; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix4<int>(iota, InputOrder_RowMajor()) < Matrix4<int>(arr, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<9; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix4<int>(iota, InputOrder_RowMajor()) < Matrix4<int>(arr, InputOrder_RowMajor()));
        }
        // not less if both sides are equal
        CHECK_FALSE(Matrix4<int>(iota, InputOrder_RowMajor()) < Matrix4<int>(iota, InputOrder_RowMajor()));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        int iota[16];
        std::iota(std::begin(iota), std::end(iota), 1);
        // lower elements take precedence
        int arr[16] = {};
        for(int i=0; i<16; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix4<int>(arr, InputOrder_RowMajor()) > Matrix4<int>(iota, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<9; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix4<int>(arr, InputOrder_RowMajor()) > Matrix4<int>(iota, InputOrder_RowMajor()));
        }
        // not greater if both sides are equal
        CHECK_FALSE(Matrix4<int>(iota, InputOrder_RowMajor()) > Matrix4<int>(iota, InputOrder_RowMajor()));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        int iota[16];
        std::iota(std::begin(iota), std::end(iota), 1);
        // lower elements take precedence
        int arr[16] = {};
        for(int i=0; i<16; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix4<int>(iota, InputOrder_RowMajor()) <= Matrix4<int>(arr, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<9; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix4<int>(iota, InputOrder_RowMajor()) <= Matrix4<int>(arr, InputOrder_RowMajor()));
        }
        // both sides are equal
        CHECK(Matrix4<int>(iota, InputOrder_RowMajor()) <= Matrix4<int>(iota, InputOrder_RowMajor()));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        int iota[16];
        std::iota(std::begin(iota), std::end(iota), 1);
        // lower elements take precedence
        int arr[16] = {};
        for(int i=0; i<16; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix4<int>(arr, InputOrder_RowMajor()) >= Matrix4<int>(iota, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<9; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix4<int>(arr, InputOrder_RowMajor()) >= Matrix4<int>(iota, InputOrder_RowMajor()));
        }
        // both sides are equal
        CHECK(Matrix4<int>(iota, InputOrder_RowMajor()) >= Matrix4<int>(iota, InputOrder_RowMajor()));
    }

    SECTION("Addition")
    {
        Matrix4<float> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        m1 += Matrix4<float>(17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f, 32.f);
        CHECK(m1 == Matrix4<float>(18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f, 32.f, 34.f, 36.f, 38.f, 40.f, 42.f, 44.f, 46.f, 48.f));
    }

    SECTION("Non-member addition")
    {
        Matrix4<float> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        Matrix4<float> const m2(17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f, 32.f);
        Matrix4<float> const sum = m1 + m2;
        CHECK(sum == Matrix4<float>(18.f, 20.f, 22.f, 24.f, 26.f, 28.f, 30.f, 32.f, 34.f, 36.f, 38.f, 40.f, 42.f, 44.f, 46.f, 48.f));
    }

    SECTION("Subtraction")
    {
        Matrix4<float> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        m1 -= Matrix4<float>(17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f, 32.f);
        CHECK(m1 == Matrix4<float>(-16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f,
                                   -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f));
    }

    SECTION("Non-member subtraction")
    {
        Matrix4<float> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        Matrix4<float> const m2(17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 26.f, 27.f, 28.f, 29.f, 30.f, 31.f, 32.f);
        Matrix4<float> const diff = m1 - m2;
        CHECK(diff == Matrix4<float>(-16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f,
                                     -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f, -16.f));
    }

    SECTION("Scalar multiplication")
    {
        Matrix4<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        m *= 5.f;
        CHECK(m == Matrix4<float>( 5.f, 10.f, 15.f, 20.f, 25.f, 30.f, 35.f, 40.f,
                                  45.f, 50.f, 55.f, 60.f, 65.f, 70.f, 75.f, 80.f));
    }

    SECTION("Scalar multiplication non-member")
    {
        Matrix4<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        CHECK((m * 5.f) == Matrix4<float>( 5.f, 10.f, 15.f, 20.f, 25.f, 30.f, 35.f, 40.f,
                                          45.f, 50.f, 55.f, 60.f, 65.f, 70.f, 75.f, 80.f));
        CHECK((5.f * m) == Matrix4<float>( 5.f, 10.f, 15.f, 20.f, 25.f, 30.f, 35.f, 40.f,
                                          45.f, 50.f, 55.f, 60.f, 65.f, 70.f, 75.f, 80.f));
    }

    SECTION("Scalar division")
    {
        Matrix4<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        m /= 2.f;
        CHECK(m == Matrix4<float>(0.5f, 1.f, 1.5f, 2.f, 2.5f, 3.f, 3.5f, 4.f,
                                  4.5f, 5.f, 5.5f, 6.f, 6.5f, 7.f, 7.5f, 8.f));
    }

    SECTION("Scalar division non-member")
    {
        Matrix4<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        CHECK((m / 2.f) == Matrix4<float>(0.5f, 1.f, 1.5f, 2.f, 2.5f, 3.f, 3.5f, 4.f,
                                          4.5f, 5.f, 5.5f, 6.f, 6.5f, 7.f, 7.5f, 8.f));
    }

    SECTION("Matrix-matrix multiplication")
    {
        Matrix4<float> m1(  1.f,  2.f,  3.f,  4.f,
                            5.f,  6.f,  7.f,  8.f,
                            9.f, 10.f, 11.f, 12.f,
                           13.f, 14.f, 15.f, 16.f);
        Matrix4<float> const m2(0.5f,    0.25f,  0.75f,   0.125f,
                                1.f,     1.5f,   2.25f,   0.625f,
                                1.75f,   0.5f,   2.0f,    0.875f,
                                0.0625f, 1.125f, 1.625f,  1.875f);
        m1 *= m2;
        CHECK(m1 == Matrix4<float>(  8.f,  9.25f,  17.75f, 11.5f,
                                   21.25f, 22.75f, 44.25f, 25.5f,
                                   34.5f,  36.25f, 70.75f, 39.5f,
                                   47.75f, 49.75f, 97.25f, 53.5f));

        Matrix4<float> m3(  1.f,  2.f,  3.f,  4.f,
                            5.f,  6.f,  7.f,  8.f,
                            9.f, 10.f, 11.f, 12.f,
                           13.f, 14.f, 15.f, 16.f);
        m3 *= m3;
        CHECK(m3 == Matrix4<float>( 90.f, 100.f, 110.f, 120.f,
                                   202.f, 228.f, 254.f, 280.f,
                                   314.f, 356.f, 398.f, 440.f,
                                   426.f, 484.f, 542.f, 600.f));
    }

    SECTION("Matrix-matrix multiplication non-member")
    {
        Matrix4<float> const m1(  1.f,  2.f,  3.f,  4.f,
                                 5.f,  6.f,  7.f,  8.f,
                                 9.f, 10.f, 11.f, 12.f,
                                13.f, 14.f, 15.f, 16.f);
        Matrix4<float> const m2(0.5f,    0.25f,  0.75f,   0.125f,
                                1.f,     1.5f,   2.25f,   0.625f,
                                1.75f,   0.5f,   2.0f,    0.875f,
                                0.0625f, 1.125f, 1.625f,  1.875f);
        CHECK(m1 * m2 == Matrix4<float>(  8.f,  9.25f,  17.75f, 11.5f,
                                         21.25f, 22.75f, 44.25f, 25.5f,
                                         34.5f,  36.25f, 70.75f, 39.5f,
                                         47.75f, 49.75f, 97.25f, 53.5f));
        CHECK(m1 * m1 == Matrix4<float>( 90.f, 100.f, 110.f, 120.f,
                                        202.f, 228.f, 254.f, 280.f,
                                        314.f, 356.f, 398.f, 440.f,
                                        426.f, 484.f, 542.f, 600.f));
    }

    SECTION("Matrix transpose")
    {
        CHECK(transpose(Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)) ==
                Matrix4<int>(1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16));
    }

    SECTION("Determinant")
    {
        CHECK(determinant(Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)) == 0);
        float const det = determinant(Matrix4<float>(0.5f,    0.25f,  0.75f,   0.125f,
                                                     1.f,     1.5f,   2.25f,   0.625f,
                                                     1.75f,   0.5f,   2.0f,    0.875f,
                                                     0.0625f, 1.125f, 1.625f,  1.875f));
        CHECK(std::fabs(det + 0.45459f) <= 1.5e-7f);
        CHECK(determinant(Matrix4<int>(10, 2, 3, 4, 25, 6, 7, 8, 12, 9, 16, 22, 7, 10, -3, 5)) == 3289);
    }

    SECTION("Adjugate")
    {
        CHECK(adjugate(Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)) ==
            Matrix4<int>(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
        CHECK(adjugate(Matrix4<int>(10, 2, 3, 4, 25, 6, 7, 8, 12, 9, 16, 22, 7, 10, -3, 5)) ==
            Matrix4<int>(605, -69, -84, -4, -3124, 1150, 113, 162,
                         -3355, 1334, 194, -304, 3388, -1403, 8, 157));
        CHECK(adjugate(Matrix4<int>( 15, -11,  6, -3,
                                     -6,   4, -2,  2,
                                      5,  -3,  2, -3,
                                     -3,   1,  0,  1)) ==
            Matrix4<int>(4, 16,  4,  -8,
                         8, 36, 12, -12,
                         8, 32, 12,  -4,
                         4, 12,  0,  -4));
    }

    SECTION("Inverse")
    {
        CHECK(inverse(Matrix4<float>(1.f, 4.f, 1.f, -2.f,
                                     2.f, 9.f, 3.f, -3.f,
                                     2.f, 8.f, 3.f, -1.f,
                                     1.f, 3.f, 0.f, -1.f)) ==
            Matrix4<float>( 7.5f, -5.5f, 3.f, -1.5f,
                           -3.f,   2.f, -1.f,  1.f,
                            2.5f, -1.5f, 1.f, -1.5f,
                           -1.5f,  0.5f, 0.f,  0.5f));

        CHECK(inverse(Matrix4<float>( 15.f, -11.f,  6.f, -3.f,
                                      -6.f,   4.f, -2.f,  2.f,
                                       5.f,  -3.f,  2.f, -3.f,
                                      -3.f,   1.f,  0.f,  1.f)) ==
            Matrix4<float>(0.5f, 2.f,  0.5f, -1.f,
                           1.f,  4.5f, 1.5f, -1.5f,
                           1.f,  4.f,  1.5f, -0.5f,
                           0.5f, 1.5f, 0.f,  -0.5f));
    }

    SECTION("Inverse scaled")
    {
        {
            auto const scaled_inv = inverse_scaled(Matrix4<int>(10, 2, 3, 4, 25, 6, 7, 8, 12, 9, 16, 22, 7, 10, -3, 5));
            CHECK(scaled_inv.m == Matrix4<int>(605, -69, -84, -4, -3124, 1150, 113, 162, -3355, 1334, 194, -304, 3388, -1403, 8, 157));
            CHECK(scaled_inv.inverse_scale_factor == 3289);
        }
        {
            auto const scaled_inv = inverse_scaled(Matrix4<int>(1, 4, 1, -2, 2, 9, 3, -3, 2, 8, 3, -1, 1, 3, 0, -1));
            CHECK(scaled_inv.m == Matrix4<int>(15, -11, 6, -3, -6, 4, -2, 2, 5, -3, 2, -3, -3, 1, 0, 1));
            CHECK(scaled_inv.inverse_scale_factor == 2);
            CHECK(scaled_inv.evaluate<float>() ==
                        Matrix4<float>(7.5f, -5.5f, 3.f, -1.5f, -3.f, 2.f, -1.f, 1.f, 2.5f, -1.5f, 1.f, -1.5f, -1.5f, 0.5f, 0.f, 0.5f));
        }
        auto const noninvertible = inverse_scaled(Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
        CHECK(noninvertible.inverse_scale_factor == 0);
    }

    SECTION("Identity")
    {
        Matrix4<float> const m = GHULBUS_MATH_NAMESPACE::identity4<float>();
        CHECK(m == Matrix4<float>(1.f, 0.f, 0.f, 0.f,
                                  0.f, 1.f, 0.f, 0.f,
                                  0.f, 0.f, 1.f, 0.f,
                                  0.f, 0.f, 0.f, 1.f));

        Matrix4<unsigned char> const mi = GHULBUS_MATH_NAMESPACE::identity4<unsigned char>();
        CHECK(mi == Matrix4<unsigned char>(1, 0, 0, 0,
                                           0, 1, 0, 0,
                                           0, 0, 1, 0,
                                           0, 0, 0, 1));
    }
}

TEST_CASE("Matrix4-Vector4 Interaction")
{
    using GHULBUS_MATH_NAMESPACE::Matrix4;
    using GHULBUS_MATH_NAMESPACE::Vector4;

    SECTION("Matrix from row vectors")
    {
        Vector4<float> row1(1.f, 2.f, 3.f, 4.f);
        Vector4<float> row2(5.f, 6.f, 7.f, 8.f);
        Vector4<float> row3(9.f, 10.f, 11.f, 12.f);
        Vector4<float> row4(13.f, 14.f, 15.f, 16.f);

        CHECK(matrixFromRowVectors(row1, row2, row3, row4) ==
                Matrix4<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f));
    }

    SECTION("Matrix from column vectors")
    {
        Vector4<float> col1(1.f, 2.f, 3.f, 4.f);
        Vector4<float> col2(5.f, 6.f, 7.f, 8.f);
        Vector4<float> col3(9.f, 10.f, 11.f, 12.f);
        Vector4<float> col4(13.f, 14.f, 15.f, 16.f);

        CHECK(matrixFromColumnVectors(col1, col2, col3, col4) ==
                Matrix4<float>(1.f, 5.f, 9.f, 13.f, 2.f, 6.f, 10.f, 14.f, 3.f, 7.f, 11.f, 15.f, 4.f, 8.f, 12.f, 16.f));
    }

    SECTION("Row access")
    {
        Matrix4<float> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        CHECK(m.row(0) == Vector4<float>(1.f, 2.f, 3.f, 4.f));
        CHECK(m.row(1) == Vector4<float>(5.f, 6.f, 7.f, 8.f));
        CHECK(m.row(2) == Vector4<float>(9.f, 10.f, 11.f, 12.f));
        CHECK(m.row(3) == Vector4<float>(13.f, 14.f, 15.f, 16.f));
    }

    SECTION("Column access")
    {
        Matrix4<float> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f);
        CHECK(m.column(0) == Vector4<float>(1.f, 5.f, 9.f, 13.f));
        CHECK(m.column(1) == Vector4<float>(2.f, 6.f, 10.f, 14.f));
        CHECK(m.column(2) == Vector4<float>(3.f, 7.f, 11.f, 15.f));
        CHECK(m.column(3) == Vector4<float>(4.f, 8.f, 12.f, 16.f));
    }

    SECTION("Matrix-vector multiplication")
    {
        Vector4<float> const v(1.f, 2.f, 3.f, 4.f);
        Matrix4<float> const m1(  1.f,  2.f,  3.f,  4.f,
                                 5.f,  6.f,  7.f,  8.f,
                                 9.f, 10.f, 11.f, 12.f,
                                13.f, 14.f, 15.f, 16.f);
        Matrix4<float> const m2(0.5f,    0.25f,  0.75f,   0.125f,
                                1.f,     1.5f,   2.25f,   0.625f,
                                1.75f,   0.5f,   2.0f,    0.875f,
                                0.0625f, 1.125f, 1.625f,  1.875f);

        CHECK((m1 * v) == Vector4<float>(30.f, 70.f, 110.f, 150.f));
        CHECK((m2 * v) == Vector4<float>(3.75f, 13.25f, 12.25f, 14.6875f));
    }
}

TEST_CASE("ScaledMatrix4")
{
    using GHULBUS_MATH_NAMESPACE::ScaledMatrix4;
    using GHULBUS_MATH_NAMESPACE::Matrix4;

    SECTION("Value initialization initializes to 0")
    {
        ScaledMatrix4<int> const sm{};
        CHECK(sm.m == Matrix4<int>{});
        CHECK(sm.inverse_scale_factor == 0);
    }

    SECTION("Construction")
    {
        ScaledMatrix4<int> const m(Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16), 42);
        CHECK(m.m == Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
        CHECK(m.inverse_scale_factor == 42);
    }

    SECTION("Copy construction")
    {
        ScaledMatrix4<int> const m(Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16), 42);

        ScaledMatrix4<int> const m_copy(m);
        CHECK(m_copy.m == Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
        CHECK(m_copy.inverse_scale_factor == 42);
    }

    SECTION("Copy assignment")
    {
        ScaledMatrix4<int> const m(Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16), 42);

        ScaledMatrix4<int> m_copy{};

        m_copy = m;
        CHECK(m_copy.m == Matrix4<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16));
        CHECK(m_copy.inverse_scale_factor == 42);
    }

    SECTION("Evaluate")
    {
        ScaledMatrix4<int> m(Matrix4<int>(2, 4, 12, 15, 0, 16, 40, 20, 3, 32, 44, 80, 92, 1, 36, 24), 4);
        CHECK(m.evaluate<float>() == Matrix4<float>(0.5f, 1.f, 3.f, 3.75f, 0.f, 4.f, 10.f, 5.f, 0.75f, 8.f, 11.f, 20.f, 23.f, 0.25f, 9.f, 6.f));
    }
}

namespace {
struct DynType
{
    float* f;
    DynType()
        :f(new float(0.f))
    {
    }

    ~DynType()
    {
        delete f;
    }

    DynType& operator=(DynType const& rhs)
    {
        *f = *(rhs.f);
        return *this;
    }

    DynType(DynType const& rhs)
        :f(new float(*rhs.f))
    {
    }
};
}

namespace GHULBUS_MATH_NAMESPACE {
namespace traits {
template<>
struct Constants<DynType>
{
    static DynType One()
    {
        DynType ret;
        *ret.f = 1.f;
        return ret;
    }

    static DynType Zero()
    {
        DynType ret;
        return ret;
    }
};
}
}

TEST_CASE("Matrix4CustomType")
{
    using GHULBUS_MATH_NAMESPACE::Matrix4;
    Matrix4<DynType> m;

    CHECK(*m.m11.f == 0.f);
    CHECK(*m.m12.f == 0.f);
    CHECK(*m.m13.f == 0.f);
    CHECK(*m.m14.f == 0.f);
    CHECK(*m.m21.f == 0.f);
    CHECK(*m.m22.f == 0.f);
    CHECK(*m.m23.f == 0.f);
    CHECK(*m.m24.f == 0.f);
    CHECK(*m.m31.f == 0.f);
    CHECK(*m.m32.f == 0.f);
    CHECK(*m.m33.f == 0.f);
    CHECK(*m.m34.f == 0.f);
    CHECK(*m.m41.f == 0.f);
    CHECK(*m.m42.f == 0.f);
    CHECK(*m.m43.f == 0.f);
    CHECK(*m.m44.f == 0.f);

    Matrix4<DynType> dt = GHULBUS_MATH_NAMESPACE::identity4<DynType>();
    CHECK(*dt.m11.f == 1.f);
    CHECK(*dt.m12.f == 0.f);
    CHECK(*dt.m13.f == 0.f);
    CHECK(*dt.m14.f == 0.f);
    CHECK(*dt.m21.f == 0.f);
    CHECK(*dt.m22.f == 1.f);
    CHECK(*dt.m23.f == 0.f);
    CHECK(*dt.m24.f == 0.f);
    CHECK(*dt.m31.f == 0.f);
    CHECK(*dt.m32.f == 0.f);
    CHECK(*dt.m33.f == 1.f);
    CHECK(*dt.m34.f == 0.f);
    CHECK(*dt.m41.f == 0.f);
    CHECK(*dt.m42.f == 0.f);
    CHECK(*dt.m43.f == 0.f);
    CHECK(*dt.m44.f == 1.f);
}
