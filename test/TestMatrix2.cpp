#include <gbMath/Matrix2.hpp>
#include <gbMath/MatrixIO.hpp>

#include <catch.hpp>

#include <vector>

TEST_CASE("Matrix2")
{
    using GHULBUS_MATH_NAMESPACE::Matrix2;

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
        m *= 5.f;
        CHECK(m == Matrix2<float>(5.f, 10.f, 15.f, 20.f));
    }

    SECTION("Scalar multiplication non-member")
    {
        Matrix2<float> m(1.f, 2.f, 3.f, 4.f);
        CHECK((m * 5.f) == Matrix2<float>(5.f, 10.f, 15.f, 20.f));
        CHECK((5.f * m) == Matrix2<float>(5.f, 10.f, 15.f, 20.f));
    }
}
