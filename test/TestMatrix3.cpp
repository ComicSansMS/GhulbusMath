#include <gbMath/Matrix3.hpp>
#include <gbMath/MatrixIO.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("Matrix3")
{
    using GHULBUS_MATH_NAMESPACE::Matrix3;

    SECTION("Value initialization initializes to 0")
    {
        Matrix3<float> const m{};

        CHECK(m.m11 == 0.0f);
        CHECK(m.m12 == 0.0f);
        CHECK(m.m13 == 0.0f);
        CHECK(m.m21 == 0.0f);
        CHECK(m.m22 == 0.0f);
        CHECK(m.m23 == 0.0f);
        CHECK(m.m31 == 0.0f);
        CHECK(m.m32 == 0.0f);
        CHECK(m.m33 == 0.0f);
    }

    SECTION("Construction from values")
    {
        Matrix3<float> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);

        CHECK(m.m11 == 1.f);
        CHECK(m.m12 == 2.f);
        CHECK(m.m13 == 3.f);
        CHECK(m.m21 == 4.f);
        CHECK(m.m22 == 5.f);
        CHECK(m.m23 == 6.f);
        CHECK(m.m31 == 7.f);
        CHECK(m.m32 == 8.f);
        CHECK(m.m33 == 9.f);
    }

    SECTION("Construction from array")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        float const arr[] = {
            1.f, 2.f, 3.f,
            4.f, 5.f, 6.f,
            7.f, 8.f, 9.f
        };

        {
            Matrix3<float> m(arr, InputOrder_RowMajor());
            CHECK(m.m11 == 1.f);
            CHECK(m.m12 == 2.f);
            CHECK(m.m13 == 3.f);
            CHECK(m.m21 == 4.f);
            CHECK(m.m22 == 5.f);
            CHECK(m.m23 == 6.f);
            CHECK(m.m31 == 7.f);
            CHECK(m.m32 == 8.f);
            CHECK(m.m33 == 9.f);
        }

        {
            Matrix3<float> m_col(arr, InputOrder_ColumnMajor());
            CHECK(m_col.m11 == 1.f);
            CHECK(m_col.m12 == 4.f);
            CHECK(m_col.m13 == 7.f);
            CHECK(m_col.m21 == 2.f);
            CHECK(m_col.m22 == 5.f);
            CHECK(m_col.m23 == 8.f);
            CHECK(m_col.m31 == 3.f);
            CHECK(m_col.m32 == 6.f);
            CHECK(m_col.m33 == 9.f);
        }
    }

    SECTION("Equality and not-equal comparison")
    {
        Matrix3<float> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        Matrix3<float> m2(42.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);

        CHECK_FALSE(m1 == m2);
        CHECK(m1 != m2);
        m2.m11 = m1.m11;
        CHECK(m1 == m2);
        CHECK_FALSE(m1 != m2);

        m2.m12 = 42.f;
        CHECK_FALSE(m1 == m2);
        CHECK(m1 != m2);
        m2.m12 = m1.m12;
        m2.m21 = 42.f;
        CHECK_FALSE(m1 == m2);
        CHECK(m1 != m2);
        m2.m21 = m1.m21;
        m2.m22 = 42.f;
        CHECK_FALSE(m1 == m2);
        CHECK(m1 != m2);
    }

    SECTION("Copy construction")
    {
        Matrix3<float> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        Matrix3<float> const m2(m1);

        CHECK(m2 == m1);
    }

    SECTION("Copy assignment")
    {
        Matrix3<float> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        Matrix3<float> m2{};

        CHECK(m2 != m1);
        m2 = m1;
        CHECK(m2 == m1);
    }

    SECTION("Conversion construction")
    {
        Matrix3<float> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        Matrix3<int> mi(m1);

        CHECK(mi == Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
    }

    SECTION("Array index operator")
    {
        Matrix3<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        CHECK(m[0] == 1.f);
        CHECK(m[1] == 2.f);
        CHECK(m[2] == 3.f);
        CHECK(m[3] == 4.f);
        CHECK(m[4] == 5.f);
        CHECK(m[5] == 6.f);
        CHECK(m[6] == 7.f);
        CHECK(m[7] == 8.f);
        CHECK(m[8] == 9.f);
        m[1] = 55.f;
        CHECK(m[1] == 55.f);

        Matrix3<float> m_arr[] = { Matrix3<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f),
                                   Matrix3<float>(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f) };
        CHECK(m_arr[0][0] == 1.f);
        CHECK(m_arr[0][1] == 2.f);
        CHECK(m_arr[0][2] == 3.f);
        CHECK(m_arr[0][3] == 4.f);
        CHECK(m_arr[0][4] == 5.f);
        CHECK(m_arr[0][5] == 6.f);
        CHECK(m_arr[0][6] == 7.f);
        CHECK(m_arr[0][7] == 8.f);
        CHECK(m_arr[0][8] == 9.f);
        CHECK(m_arr[1][0] == 10.f);
        CHECK(m_arr[1][1] == 11.f);
        CHECK(m_arr[1][2] == 12.f);
        CHECK(m_arr[1][3] == 13.f);
        CHECK(m_arr[1][4] == 14.f);
        CHECK(m_arr[1][5] == 15.f);
        CHECK(m_arr[1][6] == 16.f);
        CHECK(m_arr[1][7] == 17.f);
        CHECK(m_arr[1][8] == 18.f);
    }

    SECTION("Array index const operator")
    {
        Matrix3<float> const m_const(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        CHECK(m_const[0] == 1.f);
        CHECK(m_const[1] == 2.f);
        CHECK(m_const[2] == 3.f);
        CHECK(m_const[3] == 4.f);
        CHECK(m_const[4] == 5.f);
        CHECK(m_const[5] == 6.f);
        CHECK(m_const[6] == 7.f);
        CHECK(m_const[7] == 8.f);
        CHECK(m_const[8] == 9.f);
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        // lower elements take precedence
        int arr[9] = {};
        for(int i=0; i<9; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9) < Matrix3<int>(arr, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<9; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9) < Matrix3<int>(arr, InputOrder_RowMajor()));
        }
        // not less if both sides are equal
        CHECK_FALSE(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9) < Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        // lower elements take precedence
        int arr[9] = {};
        for(int i=0; i<9; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix3<int>(arr, InputOrder_RowMajor()) > Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<9; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix3<int>(arr, InputOrder_RowMajor()) > Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
        }
        // not greater if both sides are equal
        CHECK_FALSE(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9) > Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        // lower elements take precedence
        int arr[9] = {};
        for(int i=0; i<9; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9) <= Matrix3<int>(arr, InputOrder_RowMajor()));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<9; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9) <= Matrix3<int>(arr, InputOrder_RowMajor()));
        }
        // both sides are equal
        CHECK(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9) <= Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        // lower elements take precedence
        int arr[9] = {};
        for(int i=0; i<9; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Matrix3<int>(arr, InputOrder_RowMajor()) >= Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<9; ++j) { arr[j] = 99; }
            CHECK_FALSE(Matrix3<int>(arr, InputOrder_RowMajor()) >= Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
        }
        // both sides are equal
        CHECK(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9) >= Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
    }

    SECTION("Addition")
    {
        Matrix3<float> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        m1 += Matrix3<float>(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
        CHECK(m1 == Matrix3<float>(11.f, 13.f, 15.f, 17.f, 19.f, 21.f, 23.f, 25.f, 27.f));
    }

    SECTION("Non-member addition")
    {
        Matrix3<float> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        Matrix3<float> const m2(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
        Matrix3<float> const sum = m1 + m2;
        CHECK(sum == Matrix3<float>(11.f, 13.f, 15.f, 17.f, 19.f, 21.f, 23.f, 25.f, 27.f));
    }

    SECTION("Subtraction")
    {
        Matrix3<float> m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        m1 -= Matrix3<float>(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
        CHECK(m1 == Matrix3<float>(-9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f));
    }

    SECTION("Non-member subtraction")
    {
        Matrix3<float> const m1(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        Matrix3<float> const m2(10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f);
        Matrix3<float> const diff = m1 - m2;
        CHECK(diff == Matrix3<float>(-9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f, -9.f));
    }

    SECTION("Scalar multiplication")
    {
        Matrix3<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        m *= 5.f;
        CHECK(m == Matrix3<float>(5.f, 10.f, 15.f, 20.f, 25.f, 30.f, 35.f, 40.f, 45.f));
    }

    SECTION("Scalar multiplication non-member")
    {
        Matrix3<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        CHECK((m * 5.f) == Matrix3<float>(5.f, 10.f, 15.f, 20.f, 25.f, 30.f, 35.f, 40.f, 45.f));
        CHECK((5.f * m) == Matrix3<float>(5.f, 10.f, 15.f, 20.f, 25.f, 30.f, 35.f, 40.f, 45.f));
    }

    SECTION("Scalar division")
    {
        Matrix3<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        m /= 2.f;
        CHECK(m == Matrix3<float>(0.5f, 1.f, 1.5f, 2.f, 2.5f, 3.f, 3.5f, 4.f, 4.5f));
    }

    SECTION("Scalar division non-member")
    {
        Matrix3<float> m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        CHECK((m / 2.f) == Matrix3<float>(0.5f, 1.f, 1.5f, 2.f, 2.5f, 3.f, 3.5f, 4.f, 4.5f));
    }

    SECTION("Matrix-matrix multiplication")
    {
        Matrix3<float> m1(1.f, 2.f, 3.f,
                          4.f, 5.f, 6.f,
                          7.f, 8.f, 9.f);
        Matrix3<float> const m2(0.5f,  0.25f, 0.75f,
                                1.f,   1.5f,  2.25f,
                                1.75f, 0.5f,  2.0f);
        m1 *= m2;
        CHECK(m1 == Matrix3<float>( 7.75f,  4.75f, 11.25f,
                                   17.5f,  11.5f,  26.25f,
                                   27.25,  18.25f, 41.25f));

        Matrix3<float> m3(1.f, 2.f, 3.f,
                          4.f, 5.f, 6.f,
                          7.f, 8.f, 9.f);
        m3 *= m3;
        CHECK(m3 == Matrix3<float>( 30.f,  36.f,  42.f,
                                    66.f,  81.f,  96.f,
                                   102.f, 126.f, 150.f));
    }

    SECTION("Matrix-matrix multiplication non-member")
    {
        Matrix3<float> const m1(1.f, 2.f, 3.f,
                                4.f, 5.f, 6.f,
                                7.f, 8.f, 9.f);
        Matrix3<float> const m2(0.5f,  0.25f, 0.75f,
                                1.f,   1.5f,  2.25f,
                                1.75f, 0.5f,  2.0f);
        CHECK(m1 * m2 == Matrix3<float>( 7.75f,  4.75f, 11.25f,
                                        17.5f,  11.5f,  26.25f,
                                        27.25,  18.25f, 41.25f));
    }

    SECTION("Matrix transpose")
    {
        CHECK(transpose(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9)) == Matrix3<int>(1, 4, 7, 2, 5, 8, 3, 6, 9));
    }

    SECTION("Determinant")
    {
        CHECK(determinant(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9)) == 0);
        CHECK(determinant(Matrix3<int>(10, 2, 3, 4, 25, 6, 7, 8, 12)) == 2079);
    }

    SECTION("Adjugate")
    {
        CHECK(adjugate(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9)) == Matrix3<int>(-3, 6, -3, 6, -12, 6, -3, 6, -3));
        CHECK(adjugate(Matrix3<int>(10, 2, 3, 4, 25, 6, 7, 8, 12)) == Matrix3<int>(252, 0, -63, -6, 99, -48, -143, -66, 242));
    }

    SECTION("Inverse")
    {
        CHECK(inverse(Matrix3<float>(-4.f, 6.f, -8.f,
                                      5.f, 1.f, 22.f,
                                     -3.f, 3.f, -8.f)) ==
            Matrix3<float>( 18.5f, -6.f, -35.f,
                             6.5f, -2.f, -12.f,
                            -4.5f,  1.5f,  8.5f));

        CHECK(inverse(Matrix3<float>(3.f, 5.f, 14.f,
                                     5.f, 1.f,  7.f,
                                     2.f, 9.f, 22.f)) ==
                      Matrix3<float>( 41.f,-16.f,-21.f,
                                      96.f,-38.f,-49.f,
                                     -43.f, 17.f, 22.f));
    }

    SECTION("Inverse scaled")
    {
        {
            auto const scaled_inv = inverse_scaled(Matrix3<int>(3, 1, 3, 2, 1, -1, 3, 2, 4));
            CHECK(scaled_inv.m == Matrix3<int>(6, 2, -4, -11, 3, 9, 1, -3, 1));
            CHECK(scaled_inv.inverse_scale_factor == 10);
        }
        {
            auto const scaled_inv = inverse_scaled(Matrix3<int>(-4, 6, -8, 5, 1, 22, -3, 3, -8));
            CHECK(scaled_inv.m == Matrix3<int>(-74, 24, 140, -26, 8, 48, 18, -6, -34));
            CHECK(scaled_inv.inverse_scale_factor == -4);
            CHECK(scaled_inv.evaluate<float>() ==
                        Matrix3<float>(18.5f, -6.f, -35.f, 6.5f, -2.f, -12.f, -4.5f, 1.5f, 8.5f));
        }

        auto const noninvertible = inverse_scaled(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
        CHECK(noninvertible.inverse_scale_factor == 0);
    }

    SECTION("Identity")
    {
        Matrix3<float> const m = GHULBUS_MATH_NAMESPACE::identity3<float>();
        CHECK(m == Matrix3<float>(1.f, 0.f, 0.f,
                                  0.f, 1.f, 0.f,
                                  0.f, 0.f, 1.f));

        Matrix3<unsigned char> const mi = GHULBUS_MATH_NAMESPACE::identity3<unsigned char>();
        CHECK(mi == Matrix3<unsigned char>(1, 0, 0,
                                           0, 1, 0,
                                           0, 0, 1));
    }
}

TEST_CASE("Matrix3-Vector3 Interaction")
{
    using GHULBUS_MATH_NAMESPACE::Matrix3;
    using GHULBUS_MATH_NAMESPACE::Vector3;

    SECTION("Matrix from row vectors")
    {
        Vector3<float> row1(1.f, 2.f, 3.f);
        Vector3<float> row2(4.f, 5.f, 6.f);
        Vector3<float> row3(7.f, 8.f, 9.f);

        CHECK(matrix_from_row_vectors(row1, row2, row3) ==
                Matrix3<float>(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f));
    }

    SECTION("Matrix from column vectors")
    {
        Vector3<float> col1(1.f, 2.f, 3.f);
        Vector3<float> col2(4.f, 5.f, 6.f);
        Vector3<float> col3(7.f, 8.f, 9.f);

        CHECK(matrix_from_column_vectors(col1, col2, col3) ==
                Matrix3<float>(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f));
    }

    SECTION("Row access")
    {
        Matrix3<float> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        CHECK(m.row(0) == Vector3<float>(1.f, 2.f, 3.f));
        CHECK(m.row(1) == Vector3<float>(4.f, 5.f, 6.f));
        CHECK(m.row(2) == Vector3<float>(7.f, 8.f, 9.f));
    }

    SECTION("Column access")
    {
        Matrix3<float> const m(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
        CHECK(m.column(0) == Vector3<float>(1.f, 4.f, 7.f));
        CHECK(m.column(1) == Vector3<float>(2.f, 5.f, 8.f));
        CHECK(m.column(2) == Vector3<float>(3.f, 6.f, 9.f));
    }

    SECTION("Matrix-vector multiplication")
    {
        Vector3<float> const v(1.f, 2.f, 3.f);
        Matrix3<float> const m1(0.5f,  0.25f, 0.75f,
                               1.f,   1.5f,  2.25f,
                               1.75f, 0.5f,  2.f);
        Matrix3<float> const m2(1.f, 2.f, 3.f,
                                0.f, 1.f, 5.f,
                                5.f, 6.f, 0.f);

        CHECK((m1 * v) == Vector3<float>(3.25f, 10.75f, 8.75f));
        CHECK((m2 * v) == Vector3<float>(14.f, 17.f, 17.f));
    }
}

TEST_CASE("ScaledMatrix3")
{
    using GHULBUS_MATH_NAMESPACE::ScaledMatrix3;
    using GHULBUS_MATH_NAMESPACE::Matrix3;

    SECTION("Value initialization initializes to 0")
    {
        ScaledMatrix3<int> const sm{};
        CHECK(sm.m == Matrix3<int>{});
        CHECK(sm.inverse_scale_factor == 0);
    }

    SECTION("Construction")
    {
        ScaledMatrix3<int> const m(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9), 42);
        CHECK(m.m == Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
        CHECK(m.inverse_scale_factor == 42);
    }

    SECTION("Copy construction")
    {
        ScaledMatrix3<int> const m(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9), 42);

        ScaledMatrix3<int> const m_copy(m);
        CHECK(m_copy.m == Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
        CHECK(m_copy.inverse_scale_factor == 42);
    }

    SECTION("Copy assignment")
    {
        ScaledMatrix3<int> const m(Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9), 42);

        ScaledMatrix3<int> m_copy{};

        m_copy = m;
        CHECK(m_copy.m == Matrix3<int>(1, 2, 3, 4, 5, 6, 7, 8, 9));
        CHECK(m_copy.inverse_scale_factor == 42);
    }

    SECTION("Evaluate")
    {
        ScaledMatrix3<int> m(Matrix3<int>(2, 4, 12, 15, 0, 16, 40, 20, 3), 4);
        CHECK(m.evaluate<float>() == Matrix3<float>(0.5f, 1.f, 3.f, 3.75f, 0.f, 4.f, 10.f, 5.f, 0.75f));
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

TEST_CASE("Matrix3CustomType")
{
    using GHULBUS_MATH_NAMESPACE::Matrix3;
    Matrix3<DynType> m;

    CHECK(*m.m11.f == 0.f);
    CHECK(*m.m12.f == 0.f);
    CHECK(*m.m13.f == 0.f);
    CHECK(*m.m21.f == 0.f);
    CHECK(*m.m22.f == 0.f);
    CHECK(*m.m23.f == 0.f);
    CHECK(*m.m31.f == 0.f);
    CHECK(*m.m32.f == 0.f);
    CHECK(*m.m33.f == 0.f);

    Matrix3<DynType> dt = GHULBUS_MATH_NAMESPACE::identity3<DynType>();
    CHECK(*dt.m11.f == 1.f);
    CHECK(*dt.m12.f == 0.f);
    CHECK(*dt.m13.f == 0.f);
    CHECK(*dt.m21.f == 0.f);
    CHECK(*dt.m22.f == 1.f);
    CHECK(*dt.m23.f == 0.f);
    CHECK(*dt.m31.f == 0.f);
    CHECK(*dt.m32.f == 0.f);
    CHECK(*dt.m33.f == 1.f);
}
