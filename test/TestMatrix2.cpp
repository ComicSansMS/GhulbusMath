#include <gbMath/Matrix2.hpp>
#include <gbMath/MatrixIO.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

TEST_CASE("Matrix2")
{
    using GHULBUS_MATH_NAMESPACE::Matrix2;
    using GHULBUS_MATH_NAMESPACE::doNotInitialize;

    SECTION("Static properties")
    {
        static_assert(std::same_as<Matrix2<float>::ValueType, float>);
        static_assert(std::same_as<Matrix2<int>::ValueType, int>);
        static_assert(std::same_as<Matrix2<double>::ValueType, double>);
    }

    SECTION("Default constructor initializes to 0")
    {
        Matrix2<float> const m;

        CHECK(m.m11 == 0.0f);
        CHECK(m.m12 == 0.0f);
        CHECK(m.m21 == 0.0f);
        CHECK(m.m22 == 0.0f);
    }

    SECTION("Construction to uninitialized")
    {
        Matrix2<float> m(doNotInitialize);

        m.m11 = 1.f;
        CHECK(m.m11 == 1.f);
        m.m12 = 2.f;
        CHECK(m.m12 == 2.f);
        m.m21 = 3.f;
        CHECK(m.m21 == 3.f);
        m.m22 = 4.f;
        CHECK(m.m22 == 4.f);
    }

    SECTION("Value initialization initializes to 0")
    {
        Matrix2<float> const m{};

        CHECK(m.m11 == 0.0f);
        CHECK(m.m12 == 0.0f);
        CHECK(m.m21 == 0.0f);
        CHECK(m.m22 == 0.0f);
    }

    SECTION("Construction from values")
    {
        Matrix2<float> const m(1.f, 2.f, 3.f, 4.f);

        CHECK(m.m11 == 1.f);
        CHECK(m.m12 == 2.f);
        CHECK(m.m21 == 3.f);
        CHECK(m.m22 == 4.f);
    }

    SECTION("Construction from array")
    {
        using namespace GHULBUS_MATH_NAMESPACE::MatrixPolicies;
        float const arr[] = {
            1.f, 2.f,
            3.f, 4.f
        };

        {
            Matrix2<float> m(arr, InputOrder_RowMajor());
            CHECK(m.m11 == 1.f);
            CHECK(m.m12 == 2.f);
            CHECK(m.m21 == 3.f);
            CHECK(m.m22 == 4.f);
        }

        {
            Matrix2<float> m_col(arr, InputOrder_ColumnMajor());
            CHECK(m_col.m11 == 1.f);
            CHECK(m_col.m12 == 3.f);
            CHECK(m_col.m21 == 2.f);
            CHECK(m_col.m22 == 4.f);
        }
    }

    SECTION("Equality and not-equal comparison")
    {
        Matrix2<float> const m1(1.f, 2.f, 3.f, 4.f);
        Matrix2<float> m2(42.f, 2.f, 3.f, 4.f);

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
        Matrix2<float> const m1(1.f, 2.f, 3.f, 4.f);
        Matrix2<float> const m2(m1);

        CHECK(m2 == m1);
    }

    SECTION("Copy assignment")
    {
        Matrix2<float> const m1(1.f, 2.f, 3.f, 4.f);
        Matrix2<float> m2{};

        CHECK(m2 != m1);
        m2 = m1;
        CHECK(m2 == m1);
    }

    SECTION("Conversion construction")
    {
        Matrix2<float> const m1(1.f, 2.f, 3.f, 4.f);
        Matrix2<int> mi(m1);

        CHECK(mi == Matrix2<int>(1, 2, 3, 4));
    }

    SECTION("Array index operator")
    {
        Matrix2<float> m(1.f, 2.f, 3.f, 4.f);
        CHECK(m[0] == 1.f);
        CHECK(m[1] == 2.f);
        CHECK(m[2] == 3.f);
        CHECK(m[3] == 4.f);
        m[1] = 55.f;
        CHECK(m[1] == 55.f);

        Matrix2<float> m_arr[] = { Matrix2<float>(1.f, 2.f, 3.f, 4.f), Matrix2<float>(5.f, 6.f, 7.f, 8.f) };
        CHECK(m_arr[0][0] == 1.f);
        CHECK(m_arr[0][1] == 2.f);
        CHECK(m_arr[0][2] == 3.f);
        CHECK(m_arr[0][3] == 4.f);
        CHECK(m_arr[1][0] == 5.f);
        CHECK(m_arr[1][1] == 6.f);
        CHECK(m_arr[1][2] == 7.f);
        CHECK(m_arr[1][3] == 8.f);
    }

    SECTION("Array index const operator")
    {
        Matrix2<float> const m_const(1.f, 2.f, 3.f, 4.f);
        CHECK(m_const[0] == 1.f);
        CHECK(m_const[1] == 2.f);
        CHECK(m_const[2] == 3.f);
        CHECK(m_const[3] == 4.f);
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        CHECK(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(2, 0, 0, 0));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(0, 99, 99, 99));
        CHECK(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(1, 3, 0, 0));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(1, 0, 99, 99));
        CHECK(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(1, 2, 4, 0));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(1, 2, 0, 99));
        CHECK(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(1, 2, 3, 5));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(1, 2, 3, 0));

        // not less if both sides are equal
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) < Matrix2<int>(1, 2, 3, 4));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        CHECK(Matrix2<int>(2, 0, 0, 0) > Matrix2<int>(1, 2, 3, 4));
        CHECK_FALSE(Matrix2<int>(0, 99, 99, 99) > Matrix2<int>(1, 2, 3, 4));
        CHECK(Matrix2<int>(1, 3, 0, 0) > Matrix2<int>(1, 2, 3, 4));
        CHECK_FALSE(Matrix2<int>(1, 0, 99, 99) > Matrix2<int>(1, 2, 3, 4));
        CHECK(Matrix2<int>(1, 2, 4, 0) > Matrix2<int>(1, 2, 3, 4));
        CHECK_FALSE(Matrix2<int>(1, 2, 0, 99) > Matrix2<int>(1, 2, 3, 4));
        CHECK(Matrix2<int>(1, 2, 3, 5) > Matrix2<int>(1, 2, 3, 4));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 0) > Matrix2<int>(1, 2, 3, 4));

        // not greater if both sides are equal
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) > Matrix2<int>(1, 2, 3, 4));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        CHECK(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(2, 0, 0, 0));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(0, 99, 99, 99));
        CHECK(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(1, 3, 0, 0));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(1, 0, 99, 99));
        CHECK(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(1, 2, 4, 0));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(1, 2, 0, 99));
        CHECK(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(1, 2, 3, 5));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(1, 2, 3, 0));

        // both sides are equal
        CHECK(Matrix2<int>(1, 2, 3, 4) <= Matrix2<int>(1, 2, 3, 4));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        CHECK(Matrix2<int>(2, 0, 0, 0) >= Matrix2<int>(1, 2, 3, 4));
        CHECK_FALSE(Matrix2<int>(0, 99, 99, 99) >= Matrix2<int>(1, 2, 3, 4));
        CHECK(Matrix2<int>(1, 3, 0, 0) >= Matrix2<int>(1, 2, 3, 4));
        CHECK_FALSE(Matrix2<int>(1, 0, 99, 99) >= Matrix2<int>(1, 2, 3, 4));
        CHECK(Matrix2<int>(1, 2, 4, 0) >= Matrix2<int>(1, 2, 3, 4));
        CHECK_FALSE(Matrix2<int>(1, 2, 0, 99) >= Matrix2<int>(1, 2, 3, 4));
        CHECK(Matrix2<int>(1, 2, 3, 5) >= Matrix2<int>(1, 2, 3, 4));
        CHECK_FALSE(Matrix2<int>(1, 2, 3, 0) >= Matrix2<int>(1, 2, 3, 4));

        // both sides are equal
        CHECK(Matrix2<int>(1, 2, 3, 4) >= Matrix2<int>(1, 2, 3, 4));
    }

    SECTION("Addition")
    {
        Matrix2<float> m1(1.f, 2.f, 3.f, 4.f);
        m1 += Matrix2<float>(5.f, 6.f, 7.f, 8.f);
        CHECK(m1 == Matrix2<float>(6.f, 8.f, 10.f, 12.f));
    }

    SECTION("Non-member addition")
    {
        Matrix2<float> const m1(1.f, 2.f, 3.f, 4.f);
        Matrix2<float> const m2(5.f, 6.f, 7.f, 8.f);
        Matrix2<float> const sum = m1 + m2;
        CHECK(sum == Matrix2<float>(6.f, 8.f, 10.f, 12.f));
    }

    SECTION("Subtraction")
    {
        Matrix2<float> m1(1.f, 2.f, 3.f, 4.f);
        m1 -= Matrix2<float>(5.f, 6.f, 7.f, 8.f);
        CHECK(m1 == Matrix2<float>(-4.f, -4.f, -4.f, -4.f));
    }

    SECTION("Non-member subtraction")
    {
        Matrix2<float> const m1(1.f, 2.f, 3.f, 4.f);
        Matrix2<float> const m2(5.f, 6.f, 7.f, 8.f);
        Matrix2<float> const diff = m1 - m2;
        CHECK(diff == Matrix2<float>(-4.f, -4.f, -4.f, -4.f));
    }

    SECTION("Scalar multiplication")
    {
        Matrix2<float> m(1.f, 2.f, 3.f, 4.f);
        CHECK(&(m *= 5.f) == &m);
        CHECK(m == Matrix2<float>(5.f, 10.f, 15.f, 20.f));
    }

    SECTION("Scalar multiplication non-member")
    {
        Matrix2<float> m(1.f, 2.f, 3.f, 4.f);
        CHECK((m * 5.f) == Matrix2<float>(5.f, 10.f, 15.f, 20.f));
        CHECK((5.f * m) == Matrix2<float>(5.f, 10.f, 15.f, 20.f));
    }

    SECTION("Scalar division")
    {
        Matrix2<float> m(1.f, 2.f, 3.f, 4.f);
        m /= 2.f;
        CHECK(m == Matrix2<float>(0.5f, 1.f, 1.5f, 2.f));
    }

    SECTION("Scalar division non-member")
    {
        Matrix2<float> m(1.f, 2.f, 3.f, 4.f);
        CHECK((m / 2.f) == Matrix2<float>(0.5f, 1.f, 1.5f, 2.f));
    }

    SECTION("Matrix-matrix multiplication")
    {
        Matrix2<float> m1(1.f, 2.f,
                          3.f, 4.f);
        Matrix2<float> const m2(0.5f,  0.25f,
                                0.75f, 1.f);
        CHECK(&(m1 *= m2) == &m1);
        CHECK(m1 == Matrix2<float>(2.f,  2.25f,
                                   4.5f, 4.75f));

        Matrix2<float> m3(1.f, 2.f,
                          3.f, 4.f);
        CHECK(&(m3 *= m3) == &m3);
        CHECK(m3 == Matrix2<float>( 7.f, 10.f,
                                   15.f, 22.f));
    }

    SECTION("Matrix-matrix multiplication non-member")
    {
        Matrix2<float> const m1(1.f, 2.f,
                                3.f, 4.f);
        Matrix2<float> const m2(0.5f,  0.25f,
                                0.75f, 1.f);
        CHECK(m1 * m2 == Matrix2<float>(2.f,  2.25f,
                                        4.5f, 4.75f));
    }

    SECTION("Matrix transpose")
    {
        CHECK(transpose(Matrix2<int>(1, 2, 3, 4)) == Matrix2<int>(1, 3, 2, 4));
    }

    SECTION("Determinant")
    {
        CHECK(determinant(Matrix2<int>(1, 2, 3, 4)) == -2);
        CHECK(determinant(Matrix2<int>(1, 2, 4, 8)) == 0);
    }

    SECTION("Adjugate")
    {
        CHECK(adjugate(Matrix2<int>(1, 2, 3, 4)) == Matrix2<int>(4, -2, -3, 1));
        CHECK(adjugate(Matrix2<int>(1, 2, 4, 8)) == Matrix2<int>(8, -2, -4, 1));
    }

    SECTION("Inverse")
    {
        CHECK(inverse(Matrix2<float>(1.f, 2.f, 3.f, 4.f)) == Matrix2<float>(-2.f, 1.f, 1.5f, -0.5f));
    }

    SECTION("Inverse scaled")
    {
        auto const scaled_inv = inverse_scaled(Matrix2<int>(1, 2, 3, 4));
        CHECK(scaled_inv.m == Matrix2<int>(4, -2, -3, 1));
        CHECK(scaled_inv.inverse_scale_factor == -2);
        CHECK(scaled_inv.evaluate<float>() == Matrix2<float>(-2.f, 1.f, 1.5f, -0.5f));

        auto const noninvertible = inverse_scaled(Matrix2<int>(1, 2, 4, 8));
        CHECK(noninvertible.inverse_scale_factor == 0);
    }

    SECTION("Identity")
    {
        Matrix2<float> const m = GHULBUS_MATH_NAMESPACE::identity2<float>();
        CHECK(m == Matrix2<float>(1.f, 0.f,
                                  0.f, 1.f));

        Matrix2<unsigned char> const mi = GHULBUS_MATH_NAMESPACE::identity2<unsigned char>();
        CHECK(mi == Matrix2<unsigned char>(1, 0,
                                           0, 1));
    }
}

TEST_CASE("Matrix2-Vector2 Interaction")
{
    using GHULBUS_MATH_NAMESPACE::Matrix2;
    using GHULBUS_MATH_NAMESPACE::Vector2;

    SECTION("Matrix from row vectors")
    {
        Vector2<float> row1(1.f, 2.f);
        Vector2<float> row2(3.f, 4.f);

        CHECK(matrix_from_row_vectors(row1, row2) == Matrix2<float>(1.f, 2.f, 3.f, 4.f));
    }

    SECTION("Matrix from column vectors")
    {
        Vector2<float> col1(1.f, 2.f);
        Vector2<float> col2(3.f, 4.f);

        CHECK(matrix_from_column_vectors(col1, col2) == Matrix2<float>(1.f, 3.f, 2.f, 4.f));
    }

    SECTION("Row access")
    {
        Matrix2<float> const m(1.f, 2.f, 3.f, 4.f);
        CHECK(m.row(0) == Vector2<float>(1.f, 2.f));
        CHECK(m.row(1) == Vector2<float>(3.f, 4.f));
    }

    SECTION("Column access")
    {
        Matrix2<float> const m(1.f, 2.f, 3.f, 4.f);
        CHECK(m.column(0) == Vector2<float>(1.f, 3.f));
        CHECK(m.column(1) == Vector2<float>(2.f, 4.f));
    }

    SECTION("Matrix-vector multiplication")
    {
        Vector2<float> const v(1.f, 2.f);
        Matrix2<float> const m(0.5f,  0.25f,
                               0.75f, 1.f);

        CHECK((m * v) == Vector2<float>(1.f, 2.75f));
    }
}

TEST_CASE("ScaledMatrix2")
{
    using GHULBUS_MATH_NAMESPACE::ScaledMatrix2;
    using GHULBUS_MATH_NAMESPACE::Matrix2;

    SECTION("Value initialization initializes to 0")
    {
        ScaledMatrix2<int> const sm{};
        CHECK(sm.m == Matrix2<int>{});
        CHECK(sm.inverse_scale_factor == 0);
    }

    SECTION("Construction")
    {
        ScaledMatrix2<int> const m(Matrix2<int>(1, 2, 3, 4), 42);
        CHECK(m.m == Matrix2<int>(1, 2, 3, 4));
        CHECK(m.inverse_scale_factor == 42);
    }

    SECTION("Copy construction")
    {
        ScaledMatrix2<int> const m(Matrix2<int>(1, 2, 3, 4), 42);

        ScaledMatrix2<int> const m_copy(m);
        CHECK(m_copy.m == Matrix2<int>(1, 2, 3, 4));
        CHECK(m_copy.inverse_scale_factor == 42);
    }

    SECTION("Copy assignment")
    {
        ScaledMatrix2<int> const m(Matrix2<int>(1, 2, 3, 4), 42);

        ScaledMatrix2<int> m_copy{};

        m_copy = m;
        CHECK(m_copy.m == Matrix2<int>(1, 2, 3, 4));
        CHECK(m_copy.inverse_scale_factor == 42);
    }

    SECTION("Evaluate")
    {
        ScaledMatrix2<int> m(Matrix2<int>(2, 4, 12, 15), 4);
        CHECK(m.evaluate<float>() == Matrix2<float>(0.5f, 1.f, 3.f, 3.75f));
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

TEST_CASE("Matrix2CustomType")
{
    using GHULBUS_MATH_NAMESPACE::Matrix2;
    Matrix2<DynType> m;

    CHECK(*m.m11.f == 0.f);
    CHECK(*m.m12.f == 0.f);
    CHECK(*m.m21.f == 0.f);
    CHECK(*m.m22.f == 0.f);

    Matrix2<DynType> dt = GHULBUS_MATH_NAMESPACE::identity2<DynType>();
    CHECK(*dt.m11.f == 1.f);
    CHECK(*dt.m12.f == 0.f);
    CHECK(*dt.m21.f == 0.f);
    CHECK(*dt.m22.f == 1.f);
}

