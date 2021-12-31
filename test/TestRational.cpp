#include <gbMath/Rational.hpp>
#include <gbMath/RationalIO.hpp>

#include <catch.hpp>

#include <limits>

TEST_CASE("Rational")
{
    using GHULBUS_MATH_NAMESPACE::Rational;

    SECTION("Default Construction constructs to 0")
    {
        Rational<int> r;
        CHECK(r.numerator() == 0);
        CHECK(r.denominator() == 1);
    }

    SECTION("Construction from integer")
    {
        Rational<int> r1(42);
        CHECK(r1.numerator() == 42);
        CHECK(r1.denominator() == 1);
        Rational<int> r2(-5);
        CHECK(r2.numerator() == -5);
        CHECK(r2.denominator() == 1);
    }

    SECTION("Construction from values reduces term")
    {
        {
            Rational<int> r(1, 2);
            CHECK(r.numerator() == 1);
            CHECK(r.denominator() == 2);
        }
        {
            Rational<int> r(25, 35);
            CHECK(r.numerator() == 5);
            CHECK(r.denominator() == 7);
        }
        {
            Rational<int> r(42, 21);
            CHECK(r.numerator() == 2);
            CHECK(r.denominator() == 1);
        }
        {
            Rational<int> r(-1, 2);
            CHECK(r.numerator() == -1);
            CHECK(r.denominator() == 2);
        }
        {
            Rational<int> r(-2, 4);
            CHECK(r.numerator() == -1);
            CHECK(r.denominator() == 2);
        }
        {
            Rational<int> r(1, -2);
            CHECK(r.numerator() == -1);
            CHECK(r.denominator() == 2);
        }
        {
            Rational<int> r(2, -4);
            CHECK(r.numerator() == -1);
            CHECK(r.denominator() == 2);
        }
        {
            Rational<int> r(-1, -2);
            CHECK(r.numerator() == 1);
            CHECK(r.denominator() == 2);
        }
        {
            Rational<int> r(-2, -4);
            CHECK(r.numerator() == 1);
            CHECK(r.denominator() == 2);
        }
        {
            Rational<int> r(255, 0);
            CHECK(r.numerator() == 1);
            CHECK(r.denominator() == 0);
        }
        {
            Rational<int> r(0, 0);
            CHECK(r.numerator() == 0);
            CHECK(r.denominator() == 0);
        }
    }

    SECTION("Is Integer")
    {
        CHECK(isInteger(Rational<int>(2, 1)));
        CHECK(!isInteger(Rational<int>(1, 2)));
    }

    SECTION("Equality")
    {
        CHECK(Rational<int>(1, 2) == Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) == Rational<int>(2, 4));
        CHECK_FALSE(Rational<int>(1, 2) == Rational<int>(1, 1));
        CHECK_FALSE(Rational<int>(1, 2) == Rational<int>(2, 2));
        CHECK_FALSE(Rational<int>(1, 2) == Rational<int>(54, 55));
    }

    SECTION("Not equal")
    {
        CHECK_FALSE(Rational<int>(1, 2) != Rational<int>(1, 2));
        CHECK_FALSE(Rational<int>(1, 2) != Rational<int>(2, 4));
        CHECK(Rational<int>(1, 2) != Rational<int>(1, 1));
        CHECK(Rational<int>(1, 2) != Rational<int>(2, 2));
        CHECK(Rational<int>(1, 2) != Rational<int>(54, 55));
    }

    SECTION("Less than")
    {
        CHECK_FALSE(Rational<int>(1, 2) < Rational<int>(1, 2));
        CHECK(Rational<int>(1, 3) < Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) < Rational<int>(2, 3));
        CHECK(Rational<int>(5, 2) < Rational<int>(21, 8));
        CHECK_FALSE(Rational<int>(2, 5) < Rational<int>(1, 4));
    }

    SECTION("Less than integer")
    {
        CHECK(Rational<int>(1, 2) < 1);
        CHECK(Rational<int>(3, 4) < 1);
        CHECK_FALSE(Rational<int>(8, 8) < 1);
        CHECK_FALSE(Rational<int>(17, 16) < 1);
        CHECK(Rational<int>(17, 16) < 2);
        CHECK(Rational<int>(3, 2) < 2);
        CHECK_FALSE(Rational<int>(9, 4) < 2);
        CHECK(Rational<int>(4121, 128) < 52);
        CHECK_FALSE(Rational<int>(6657, 128) < 52);

        CHECK_FALSE(1 < Rational<int>(1, 2));
        CHECK_FALSE(1 < Rational<int>(3, 4));
        CHECK_FALSE(1 < Rational<int>(8, 8));
        CHECK(1 < Rational<int>(17, 16));
        CHECK_FALSE(2 < Rational<int>(17, 16));
        CHECK_FALSE(2 < Rational<int>(3, 2));
        CHECK(2 < Rational<int>(9, 4));
        CHECK_FALSE(52 < Rational<int>(4121, 128));
        CHECK(52 < Rational<int>(6657, 128));
    }

    SECTION("Negation")
    {
        CHECK(-Rational<int>(1, 2) == Rational<int>(-1, 2));
        CHECK(-Rational<int>(2, 3) == Rational<int>(-2, 3));
        CHECK(-Rational<int>(-1, 2) == Rational<int>(1, 2));
        CHECK(-Rational<int>(-1, -2) == Rational<int>(-1, 2));
    }

    SECTION("Addition")
    {
        CHECK(Rational<int>(1, 2) + Rational<int>(1, 4) == Rational<int>(3, 4));
        CHECK(Rational<int>(1, 2) + Rational<int>(1, 3) == Rational<int>(5, 6));
        CHECK(Rational<int>(1, 2) + Rational<int>(1, 2) == Rational<int>(1, 1));
        CHECK(Rational<int>(6, 5) + Rational<int>(4, 5) == Rational<int>(2, 1));
        CHECK(Rational<int>(1, 2) + Rational<int>(-2, 3) == Rational<int>(-1, 6));
    }

    SECTION("Addition with integer")
    {
        CHECK(Rational<int>(1, 2) + 0 == Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) + 1 == Rational<int>(3, 2));
        CHECK(Rational<int>(1, 2) + 10 == Rational<int>(21, 2));
        CHECK(Rational<int>(2, 3) + 2 == Rational<int>(8, 3));
        CHECK(Rational<int>(25, 5) + 3 == Rational<int>(8, 1));
        CHECK(Rational<int>(25, 5) + (-3) == Rational<int>(2, 1));

        CHECK(0 + Rational<int>(1, 2) == Rational<int>(1, 2));
        CHECK(1 + Rational<int>(1, 2) == Rational<int>(3, 2));
        CHECK(10 + Rational<int>(1, 2) == Rational<int>(21, 2));
        CHECK(2 + Rational<int>(2, 3) == Rational<int>(8, 3));
        CHECK(3 + Rational<int>(25, 5) == Rational<int>(8, 1));

        CHECK(2 + Rational<int>(1, 2) + 1 == Rational<int>(7, 2));
    }

    SECTION("Subtraction")
    {
        CHECK(Rational<int>(1, 2) - Rational<int>(1, 2) == Rational<int>(0, 1));
        CHECK(Rational<int>(1, 2) - Rational<int>(1, 4) == Rational<int>(1, 4));
        CHECK(Rational<int>(1, 2) - Rational<int>(2, 3) == Rational<int>(-1, 6));
        CHECK(Rational<int>(5, 2) - Rational<int>(5, 3) == Rational<int>(5, 6));
        CHECK(Rational<int>(1, 2) - Rational<int>(-2, 3) == Rational<int>(7, 6));
    }

    SECTION("Subtraction with integer")
    {
        CHECK(Rational<int>(1, 2) - 0 == Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) - 1 == Rational<int>(-1, 2));
        CHECK(Rational<int>(1, 2) - 2 == Rational<int>(-3, 2));
        CHECK(Rational<int>(5, 2) - 2 == Rational<int>(1, 2));
        CHECK(Rational<int>(5, 3) - 2 == Rational<int>(-1, 3));

        CHECK(0 - Rational<int>(1, 2) == Rational<int>(-1, 2));
        CHECK(1 - Rational<int>(1, 2) == Rational<int>(1, 2));
        CHECK(2 - Rational<int>(1, 2) == Rational<int>(3, 2));
        CHECK(2 - Rational<int>(5, 2) == Rational<int>(-1, 2));
        CHECK(2 - Rational<int>(5, 3) == Rational<int>(1, 3));

        CHECK(10 - Rational<int>(5, 2) - 7 == Rational<int>(1, 2));
    }

    SECTION("Multiplication")
    {
        CHECK(Rational<int>(1, 2) * Rational<int>(2, 3) == Rational<int>(1, 3));
        CHECK(Rational<int>(1, 2) * Rational<int>(1, 2) == Rational<int>(1, 4));
        CHECK(Rational<int>(1, 2) * Rational<int>(-1, 2) == Rational<int>(-1, 4));
        CHECK(Rational<int>(-1, 2) * Rational<int>(-1, 2) == Rational<int>(1, 4));
        CHECK(Rational<int>(2, 5) * Rational<int>(5, 2) == Rational<int>(1, 1));
        CHECK(Rational<int>(12, 5) * Rational<int>(2, 5) == Rational<int>(24, 25));
    }

    SECTION("Multiplication with integer")
    {
        CHECK(Rational<int>(1, 2) * 0 == Rational<int>(0, 1));
        CHECK(Rational<int>(1, 2) * 1 == Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) * 2 == Rational<int>(1, 1));
        CHECK(Rational<int>(1, 2) * 3 == Rational<int>(3, 2));
        CHECK(Rational<int>(1, 4) * 4 == Rational<int>(1, 1));
        CHECK(Rational<int>(2, 5) * 2 == Rational<int>(4, 5));
        CHECK(Rational<int>(-2, 5) * -2 == Rational<int>(4, 5));
        CHECK(Rational<int>(2, 5) * -2 == Rational<int>(-4, 5));

        CHECK(0 * Rational<int>(1, 2) == Rational<int>(0, 1));
        CHECK(1 * Rational<int>(1, 2) == Rational<int>(1, 2));
        CHECK(2 * Rational<int>(1, 2) == Rational<int>(1, 1));
        CHECK(3 * Rational<int>(1, 2) == Rational<int>(3, 2));
        CHECK(4 * Rational<int>(1, 4) == Rational<int>(1, 1));
        CHECK(2 * Rational<int>(2, 5) == Rational<int>(4, 5));
        CHECK(-2 * Rational<int>(-2, 5) == Rational<int>(4, 5));
        CHECK(-2 * Rational<int>(2, 5) == Rational<int>(-4, 5));

        CHECK(-2 * Rational<int>(2, 6) * -3 == Rational<int>(2, 1));
    }

    SECTION("Division")
    {
        CHECK(Rational<int>(1, 2) / Rational<int>(1, 2) == Rational<int>(1, 1));
        CHECK(Rational<int>(1, 2) / Rational<int>(2, 1) == Rational<int>(1, 4));
        CHECK(Rational<int>(1, 3) / Rational<int>(1, 2) == Rational<int>(2, 3));
        CHECK(Rational<int>(-1, 3) / Rational<int>(1, 2) == Rational<int>(-2, 3));
        CHECK(Rational<int>(1, 3) / Rational<int>(-1, 2) == Rational<int>(-2, 3));
        CHECK(Rational<int>(-1, 3) / Rational<int>(-1, 2) == Rational<int>(2, 3));
    }

    SECTION("Division with integer")
    {
        CHECK(Rational<int>(1, 2) / 1 == Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) / 2 == Rational<int>(1, 4));
        CHECK(Rational<int>(5, 5) / 5 == Rational<int>(1, 5));
        CHECK(Rational<int>(3, 4) / 2 == Rational<int>(3, 8));
        CHECK(Rational<int>(-3, 4) / 2 == Rational<int>(-3, 8));
        CHECK(Rational<int>(3, 4) / -2 == Rational<int>(-3, 8));
        CHECK(Rational<int>(-3, 4) / -2 == Rational<int>(3, 8));

        CHECK(0 / Rational<int>(1, 2) == Rational<int>(0, 1));
        CHECK(1 / Rational<int>(1, 2) == Rational<int>(2, 1));
        CHECK(2 / Rational<int>(1, 2) == Rational<int>(4, 1));
        CHECK(5 / Rational<int>(5, 5) == Rational<int>(5, 1));
        CHECK(2 / Rational<int>(3, 4) == Rational<int>(8, 3));
        CHECK(2 / Rational<int>(-3, 4) == Rational<int>(-8, 3));
        CHECK(-2 / Rational<int>(3, 4) == Rational<int>(-8, 3));
        CHECK(-2 / Rational<int>(-3, 4) == Rational<int>(8, 3));

        CHECK(4 / Rational<int>(1, 2) / 6 == Rational<int>(4, 3));
    }
}
