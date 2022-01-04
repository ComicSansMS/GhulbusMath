#include <gbMath/Rational.hpp>
#include <gbMath/RationalIO.hpp>

#include <catch.hpp>

#include <limits>

TEST_CASE("Rational")
{
    using GHULBUS_MATH_NAMESPACE::Rational;

    static_assert(std::is_same_v<Rational<int>::ValueType, int>);
    static_assert(std::is_same_v<Rational<unsigned int>::ValueType, unsigned int>);
    static_assert(std::is_same_v<Rational<int8_t>::ValueType, int8_t>);
    static_assert(std::is_same_v<Rational<int16_t>::ValueType, int16_t>);
    static_assert(std::is_same_v<Rational<int64_t>::ValueType, int64_t>);

    static_assert(std::is_same_v<Rational<int>::PolicyType,
                                 GHULBUS_MATH_NAMESPACE::RationalPolicies::Permissive>);
    static_assert(std::is_same_v<GHULBUS_MATH_NAMESPACE::StrictRational<int>::PolicyType,
                                 GHULBUS_MATH_NAMESPACE::RationalPolicies::AbortOnDivByZero>);

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
            Rational<int> r(0, 1);
            CHECK(r.numerator() == 0);
            CHECK(r.denominator() == 1);
        }
        {
            Rational<int> r(0, 255);
            CHECK(r.numerator() == 0);
            CHECK(r.denominator() == 1);
        }
        {
            Rational<int> r(0, -255);
            CHECK(r.numerator() == 0);
            CHECK(r.denominator() == 1);
        }
        {
            Rational<int> r(255, 0);
            CHECK(r.numerator() == 1);
            CHECK(r.denominator() == 0);
        }
        {
            Rational<int> r(-1, 0);
            CHECK(r.numerator() == -1);
            CHECK(r.denominator() == 0);
        }
        {
            Rational<int> r(-255, 0);
            CHECK(r.numerator() == -1);
            CHECK(r.denominator() == 0);
        }
        {
            Rational<int> r(0, 0);
            CHECK(r.numerator() == 0);
            CHECK(r.denominator() == 0);
        }
    }

    SECTION("Float conversion")
    {
        CHECK(static_cast<float>(Rational<int>(1, 2)) == 0.5f);
        CHECK(static_cast<float>(Rational<int>(1, 8)) == 0.125f);
        CHECK(static_cast<float>(Rational<int>(5, 8)) == 0.625f);
        CHECK(static_cast<float>(Rational<int>(1, 3)) == 1.f / 3.f);
        CHECK(static_cast<float>(Rational<int>(255, 256)) == 0.99609375f);
    }

    SECTION("Is Valid")
    {
        CHECK(isValid(Rational<int>(1, 2)));
        CHECK(isValid(Rational<int>(0, 1)));
        CHECK(isValid(Rational<int>(0, 5)));
        CHECK(isValid(Rational<int>(-1, 2)));
        CHECK_FALSE(isValid(Rational<int>(1, 0)));
        CHECK_FALSE(isValid(Rational<int>(-1, 0)));
        CHECK_FALSE(isValid(Rational<int>(100, 0)));
        CHECK_FALSE(isValid(Rational<int>(-100, 0)));
        CHECK_FALSE(isValid(Rational<int>(0, 0)));
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

    SECTION("Less than overflow")
    {
        // p        a
        // ----  < --- 
        // c*q     c*b
        //
        // c = 149
        // q = 59   --> c*q = 8791
        // b = 31   --> c*b = 4619
        CHECK(Rational<int16_t>(8293, 8791) < Rational<int16_t>(7879, 4619));
        //
        // 2'099'743'297 = 70'289 * 29'873
        CHECK(Rational<int32_t>(29'300, 2'099'743'297) < Rational<int32_t>(28'900, 29'873));
    }

    SECTION("Less or equal")
    {
        CHECK(Rational<int>(1, 2) <= Rational<int>(1, 2));
        CHECK(Rational<int>(1, 3) <= Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) <= Rational<int>(2, 3));
        CHECK(Rational<int>(5, 2) <= Rational<int>(21, 8));
        CHECK_FALSE(Rational<int>(2, 5) <= Rational<int>(1, 4));
    }

    SECTION("Greater than")
    {
        CHECK_FALSE(Rational<int>(1, 2) > Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) > Rational<int>(1, 3));
        CHECK(Rational<int>(2, 3) > Rational<int>(1, 2));
        CHECK(Rational<int>(21, 8) > Rational<int>(5, 2));
        CHECK_FALSE(Rational<int>(1, 4) > Rational<int>(2, 5));
    }

    SECTION("Greater or equal")
    {
        CHECK(Rational<int>(1, 2) >= Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) >= Rational<int>(1, 3));
        CHECK(Rational<int>(2, 3) >= Rational<int>(1, 2));
        CHECK(Rational<int>(21, 8) >= Rational<int>(5, 2));
        CHECK_FALSE(Rational<int>(1, 4) >= Rational<int>(2, 5));
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

    SECTION("Less or equal with integer")
    {
        CHECK(Rational<int>(1, 2) <= 1);
        CHECK(Rational<int>(3, 4) <= 1);
        CHECK(Rational<int>(8, 8) <= 1);
        CHECK_FALSE(Rational<int>(17, 16) <= 1);
        CHECK(Rational<int>(17, 16) <= 2);
        CHECK(Rational<int>(3, 2) <= 2);
        CHECK_FALSE(Rational<int>(9, 4) <= 2);
        CHECK(Rational<int>(4121, 128) <= 52);
        CHECK_FALSE(Rational<int>(6657, 128) <= 52);

        CHECK_FALSE(1 <= Rational<int>(1, 2));
        CHECK_FALSE(1 <= Rational<int>(3, 4));
        CHECK(1 <= Rational<int>(8, 8));
        CHECK(1 <= Rational<int>(17, 16));
        CHECK_FALSE(2 <= Rational<int>(17, 16));
        CHECK_FALSE(2 <= Rational<int>(3, 2));
        CHECK(2 <= Rational<int>(9, 4));
        CHECK_FALSE(52 <= Rational<int>(4121, 128));
        CHECK(52 <= Rational<int>(6657, 128));
    }

    SECTION("Greater than integer")
    {
        CHECK(1 > Rational<int>(1, 2));
        CHECK(1 > Rational<int>(3, 4));
        CHECK_FALSE(1 > Rational<int>(8, 8));
        CHECK_FALSE(1 > Rational<int>(17, 16));
        CHECK(2 > Rational<int>(17, 16));
        CHECK(2 > Rational<int>(3, 2));
        CHECK_FALSE(2 > Rational<int>(9, 4));
        CHECK(52 > Rational<int>(4121, 128));
        CHECK_FALSE(52 > Rational<int>(6657, 128));

        CHECK_FALSE(Rational<int>(1, 2) > 1);
        CHECK_FALSE(Rational<int>(3, 4) > 1);
        CHECK_FALSE(Rational<int>(8, 8) > 1);
        CHECK(Rational<int>(17, 16) > 1);
        CHECK_FALSE(Rational<int>(17, 16) > 2);
        CHECK_FALSE(Rational<int>(3, 2) > 2);
        CHECK(Rational<int>(9, 4) > 2);
        CHECK_FALSE(Rational<int>(4121, 128) > 52);
        CHECK(Rational<int>(6657, 128) > 52);
    }

    SECTION("Greater or equal")
    {
        CHECK(1 >= Rational<int>(1, 2));
        CHECK(1 >= Rational<int>(3, 4));
        CHECK(1 >= Rational<int>(8, 8));
        CHECK_FALSE(1 >= Rational<int>(17, 16));
        CHECK(2 >= Rational<int>(17, 16));
        CHECK(2 >= Rational<int>(3, 2));
        CHECK_FALSE(2 >= Rational<int>(9, 4));
        CHECK(52 >= Rational<int>(4121, 128));
        CHECK_FALSE(52 >= Rational<int>(6657, 128));

        CHECK_FALSE(Rational<int>(1, 2) >= 1);
        CHECK_FALSE(Rational<int>(3, 4) >= 1);
        CHECK(Rational<int>(8, 8) >= 1);
        CHECK(Rational<int>(17, 16) >= 1);
        CHECK_FALSE(Rational<int>(17, 16) >= 2);
        CHECK_FALSE(Rational<int>(3, 2) >= 2);
        CHECK(Rational<int>(9, 4) >= 2);
        CHECK_FALSE(Rational<int>(4121, 128) >= 52);
        CHECK(Rational<int>(6657, 128) >= 52);
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

    SECTION("Addition overflow")
    {
        CHECK(Rational<int16_t>(31393, 32) + Rational<int16_t>(2399, 32) == Rational<int16_t>(1056, 1));
        CHECK(Rational<int16_t>(21179, 25) + Rational<int16_t>(20428, 50) == Rational<int16_t>(31393, 25));
    }

    SECTION("Member Addition")
    {
        {
            Rational<int> r(1, 2);
            Rational<int>& ret = (r += Rational<int>(1, 4));
            CHECK(r  == Rational<int>(3, 4));
            CHECK(&ret == &r);
        }
        {
            Rational<int> r(1, 2);
            r += Rational<int>(1, 3);
            CHECK(r  == Rational<int>(5, 6));
        }
        {
            Rational<int> r(1, 2);
            r += r;
            CHECK(r == Rational<int>(1, 1));
        }
        {
            Rational<int> r(6, 5);
            r += Rational<int>(4, 5);
            CHECK(r == Rational<int>(2, 1));
        }
        {
            Rational<int> r(1, 2);
            r += Rational<int>(-2, 3);
            CHECK(r == Rational<int>(-1, 6));
        }
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

    SECTION("Member Addition with integer")
    {
        {
            Rational<int> r(1, 2);
            Rational<int>& ret = (r += 0);
            CHECK(r == Rational<int>(1, 2));
            CHECK(&ret == &r);
        }
        {
            Rational<int> r(1, 2);
            r += 1;
            CHECK(r == Rational<int>(3, 2));
        }
        {
            Rational<int> r(1, 2);
            r += 10;
            CHECK(r == Rational<int>(21, 2));
        }
        {
            Rational<int> r(2, 3);
            r += 2;
            CHECK(r == Rational<int>(8, 3));
        }
        {
            Rational<int> r(25, 5);
            r += 3;
            CHECK(r == Rational<int>(8, 1));
        } {
            Rational<int> r(25, 5);
            r += -3;
            CHECK(r == Rational<int>(2, 1));
        }
    }

    SECTION("Subtraction")
    {
        CHECK(Rational<int>(1, 2) - Rational<int>(1, 8) == Rational<int>(3, 8));
        CHECK(Rational<int>(1, 2) - Rational<int>(1, 2) == Rational<int>(0, 1));
        CHECK(Rational<int>(1, 2) - Rational<int>(1, 4) == Rational<int>(1, 4));
        CHECK(Rational<int>(1, 2) - Rational<int>(2, 3) == Rational<int>(-1, 6));
        CHECK(Rational<int>(5, 2) - Rational<int>(5, 3) == Rational<int>(5, 6));
        CHECK(Rational<int>(1, 2) - Rational<int>(-2, 3) == Rational<int>(7, 6));
    }

    SECTION("Member Subtraction")
    {
        {
            Rational<int> r(1, 2);
            Rational<int>& ret = (r -= Rational<int>(1, 8));
            CHECK(r == Rational<int>(3, 8));
            CHECK(&ret == &r);
        }
        {
            Rational<int> r(1, 2);
#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wself-assign-overloaded"
#endif
            r -= r;
#ifdef __clang__
#   pragma clang diagnostic pop
#endif
            CHECK(r == Rational<int>(0, 1));
        }
        {
            Rational<int> r(1, 2);
            r -= Rational<int>(1, 4);
            CHECK(r == Rational<int>(1, 4));
        }
        {
            Rational<int> r(1, 2);
            r -= Rational<int>(2, 3);
            CHECK(r == Rational<int>(-1, 6));
        }
        {
            Rational<int> r(5, 2);
            r -= Rational<int>(5, 3);
            CHECK(r  == Rational<int>(5, 6));
        }
        {
            Rational<int> r(1, 2);
            r -= Rational<int>(-2, 3);
            CHECK(r == Rational<int>(7, 6));
        }
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

    SECTION("Member Subtraction with integer")
    {
        {
            Rational<int> r(1, 2);
            Rational<int>& ret = (r -= 0);
            CHECK(r == Rational<int>(1, 2));
            CHECK(&ret == &r);
        }
        {
            Rational<int> r(1, 2);
            r -= 1;
            CHECK(r == Rational<int>(-1, 2));
        }
        {
            Rational<int> r(1, 2);
            r -= 2;
            CHECK(r == Rational<int>(-3, 2));
        }
        {
            Rational<int> r(5, 2);
            r -= 2;
            CHECK(r == Rational<int>(1, 2));
        }
        {
            Rational<int> r(5, 3);
            r -= 2;
            CHECK(r == Rational<int>(-1, 3));
        }
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

    SECTION("Multiplication overflow")
    {
        // 499 * 47 = 23453
        // 29 * 307 = 8903
        CHECK(Rational<int16_t>(23453, 307) * Rational<int16_t>(8903, 47) == Rational<int16_t>(14471, 1));
    }

    SECTION("Member Multiplication")
    {
        {
            Rational<int> r(1, 2);
            Rational<int>& ret = (r *= Rational<int>(2, 3));
            CHECK(r == Rational<int>(1, 3));
            CHECK(&ret == &r);
        }
        {
            Rational<int> r(1, 2);
            r *= r;
            CHECK(r == Rational<int>(1, 4));
        }
        {
            Rational<int> r(1, 2);
            r *= Rational<int>(-1, 2);
            CHECK(r == Rational<int>(-1, 4));
        }
        {
            Rational<int> r(-1, 2);
            r *= Rational<int>(-1, 2);
            CHECK(r == Rational<int>(1, 4));
        }
        {
            Rational<int> r(2, 5);
            r *= Rational<int>(5, 2);
            CHECK(r == Rational<int>(1, 1));
        }
        {
            Rational<int> r(12, 5);
            r *= Rational<int>(2, 5);
            CHECK(r == Rational<int>(24, 25));
        }
    }

    SECTION("Multiplication with integer")
    {
        CHECK(Rational<int>(1, 2) * 0 == Rational<int>(0, 1));
        CHECK(Rational<int>(1, 2) * 1 == Rational<int>(1, 2));
        CHECK(Rational<int>(1, 2) * 2 == Rational<int>(1, 1));
        CHECK(Rational<int>(1, 2) * 3 == Rational<int>(3, 2));
        CHECK(Rational<int>(1, 4) * 4 == Rational<int>(1, 1));
        CHECK(Rational<int>(2, 5) * 2 == Rational<int>(4, 5));
        CHECK(Rational<int>(-2, 5) * 2 == Rational<int>(-4, 5));
        CHECK(Rational<int>(-2, 5) * -2 == Rational<int>(4, 5));
        CHECK(Rational<int>(2, 5) * -2 == Rational<int>(-4, 5));

        CHECK(0 * Rational<int>(1, 2) == Rational<int>(0, 1));
        CHECK(1 * Rational<int>(1, 2) == Rational<int>(1, 2));
        CHECK(2 * Rational<int>(1, 2) == Rational<int>(1, 1));
        CHECK(3 * Rational<int>(1, 2) == Rational<int>(3, 2));
        CHECK(4 * Rational<int>(1, 4) == Rational<int>(1, 1));
        CHECK(2 * Rational<int>(2, 5) == Rational<int>(4, 5));
        CHECK(2 * Rational<int>(-2, 5) == Rational<int>(-4, 5));
        CHECK(-2 * Rational<int>(-2, 5) == Rational<int>(4, 5));
        CHECK(-2 * Rational<int>(2, 5) == Rational<int>(-4, 5));

        CHECK(-2 * Rational<int>(2, 6) * -3 == Rational<int>(2, 1));
    }

    SECTION("Member Multiplication with integer")
    {
        {
            Rational<int> r(1, 2);
            Rational<int>& ret = (r *= 0);
            CHECK(r == Rational<int>(0, 1));
            CHECK(&ret == &r);
        }
        {
            Rational<int> r(1, 2);
            r *= 1;
            CHECK(r == Rational<int>(1, 2));
        }
        {
            Rational<int> r(1, 2);
            r *= 2;
            CHECK(r == Rational<int>(1, 1));
        }
        {
            Rational<int> r(1, 2);
            r *= 3;
            CHECK(r == Rational<int>(3, 2));
        }
        {
            Rational<int> r(1, 4);
            r *= 4;
            CHECK(r == Rational<int>(1, 1));
        }
        {
            Rational<int> r(2, 5);
            r *= 2;
            CHECK(r == Rational<int>(4, 5));
        }
        {
            Rational<int> r(-2, 5);
            r *= 2;
            CHECK(r == Rational<int>(-4, 5));
        }
        {
            Rational<int> r(-2, 5);
            r *= -2;
            CHECK(r == Rational<int>(4, 5));
        }
        {
            Rational<int> r(2, 5);
            r *= -2;
            CHECK(r == Rational<int>(-4, 5));
        }
    }

    SECTION("Division")
    {
        CHECK(Rational<int>(1, 2) / Rational<int>(1, 2) == Rational<int>(1, 1));
        CHECK(Rational<int>(1, 2) / Rational<int>(2, 1) == Rational<int>(1, 4));
        CHECK(Rational<int>(1, 3) / Rational<int>(1, 2) == Rational<int>(2, 3));
        CHECK(Rational<int>(-1, 3) / Rational<int>(1, 2) == Rational<int>(-2, 3));
        CHECK(Rational<int>(1, 3) / Rational<int>(-1, 2) == Rational<int>(-2, 3));
        CHECK(Rational<int>(-1, 3) / Rational<int>(-1, 2) == Rational<int>(2, 3));
        CHECK(Rational<int>(3, 4) / Rational<int>(0, 1) == Rational<int>(1, 0));
        CHECK(Rational<int>(-3, 4) / Rational<int>(0, 1) == Rational<int>(-1, 0));
    }

    SECTION("Division overflow")
    {
        CHECK(Rational<int16_t>(23453, 307) / Rational<int16_t>(47, 8903) == Rational<int16_t>(14471, 1));
    }

    SECTION("Member Division")
    {
        {
            Rational<int> r(1, 2);
#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wself-assign-overloaded"
#endif
            r /= r;
#ifdef __clang__
#   pragma clang diagnostic pop
#endif
            CHECK(r == Rational<int>(1, 1));
        }
        {
            Rational<int> r(1, 2);
            Rational<int>& ret = (r /= Rational<int>(2, 1));
            CHECK(r == Rational<int>(1, 4));
            CHECK(&ret == &r);
        }
        {
            Rational<int> r(1, 3);
            r /= Rational<int>(1, 2);
            CHECK(r == Rational<int>(2, 3));
        }
        {
            Rational<int> r(-1, 3);
            r /= Rational<int>(1, 2);
            CHECK(r == Rational<int>(-2, 3));
        }
        {
            Rational<int> r(1, 3);
            r /= Rational<int>(-1, 2);
            CHECK(r == Rational<int>(-2, 3));
        }
        {
            Rational<int> r(-1, 3);
            r /= Rational<int>(-1, 2);
            CHECK(r == Rational<int>(2, 3));
        }
        {
            Rational<int> r(3, 4);
            r /= Rational<int>(0, 1);
            CHECK(r == Rational<int>(1, 0));
        }
        {
            Rational<int> r(-3, 4);
            r /= Rational<int>(0, 1);
            CHECK(r == Rational<int>(-1, 0));
        }
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

        CHECK(Rational<int>(3, 4) / 0 == Rational<int>(1, 0));
        CHECK(Rational<int>(-3, 4) / 0 == Rational<int>(-1, 0));

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

    SECTION("Member Division with integer")
    {
        {
            Rational<int> r(1, 2);
            Rational<int>& ret = (r /= 4);
            CHECK(r == Rational<int>(1, 8));
            CHECK(&ret == &r);
        }
        {
            Rational<int> r(1, 2);
            r /= 1;
            CHECK(r == Rational<int>(1, 2));
        }
        {
            Rational<int> r(1, 2);
            r /= 2;
            CHECK(r == Rational<int>(1, 4));
        }
        {
            Rational<int> r(5, 5);
            r /= 5;
            CHECK(r == Rational<int>(1, 5));
        }
        {
            Rational<int> r(3, 4);
            r /= 2;
            CHECK(r == Rational<int>(3, 8));
        }
        {
            Rational<int> r(-3, 4);
            r /= 2;
            CHECK(r == Rational<int>(-3, 8));
        }
        {
            Rational<int> r(3, 4);
            r /= -2;
            CHECK(r == Rational<int>(-3, 8));
        }
        {
            Rational<int> r(-3, 4);
            r /= -2;
            CHECK(r == Rational<int>(3, 8));
        }
        {
            Rational<int> r(3, 4);
            r /= 0;
            CHECK(r == Rational<int>(1, 0));
        }
        {
            Rational<int> r(-3, 4);
            r /= 0;
            CHECK(r == Rational<int>(-1, 0));
        }
    }

    SECTION("Div by Zero values propagate")
    {
        Rational<int> const divz(100, 0);       // ∞
        Rational<int> const ndivz(-100, 0);     // -∞
        Rational<int> const divzz(0, 0);        // nan
        REQUIRE(divz.numerator() == 1);
        REQUIRE(divz.denominator() == 0);
        REQUIRE(ndivz.numerator() == -1);
        REQUIRE(ndivz.denominator() == 0);
        REQUIRE(divzz.numerator() == 0);
        REQUIRE(divzz.denominator() == 0);
        SECTION("Float conversion")
        {
            CHECK(static_cast<float>(divz) == std::numeric_limits<float>::infinity());
            CHECK(static_cast<float>(ndivz) == -std::numeric_limits<float>::infinity());
            CHECK(std::isnan(static_cast<float>(divzz)));

            CHECK(static_cast<double>(divz) == std::numeric_limits<double>::infinity());
            CHECK(static_cast<double>(ndivz) == -std::numeric_limits<double>::infinity());
            CHECK(std::isnan(static_cast<double>(divzz)));
        }
        SECTION("Addition")
        {
            // ∞ + x = ∞
            CHECK(divz + Rational<int>(2, 3) == divz);
            CHECK(divz + Rational<int>(-1, 3) == divz);
            CHECK(divz + Rational<int>(5, 2) == divz);

            CHECK(Rational<int>(2, 3) + divz == divz);
            CHECK(Rational<int>(-1, 3) + divz == divz);
            CHECK(Rational<int>(5, 2) + divz == divz);

            CHECK(ndivz + Rational<int>(2, 3) == ndivz);
            CHECK(ndivz + Rational<int>(-1, 3) == ndivz);
            CHECK(ndivz + Rational<int>(5, 2) == ndivz);

            CHECK(Rational<int>(2, 3) + ndivz == ndivz);
            CHECK(Rational<int>(-1, 3) + ndivz == ndivz);
            CHECK(Rational<int>(5, 2) + ndivz == ndivz);

            CHECK(divzz + Rational<int>(2, 3) == divzz);
            CHECK(divzz + Rational<int>(-1, 3) == divzz);
            CHECK(divzz + Rational<int>(5, 2) == divzz);

            CHECK(Rational<int>(2, 3) + divzz == divzz);
            CHECK(Rational<int>(-1, 3) + divzz == divzz);
            CHECK(Rational<int>(5, 2) + divzz == divzz);

            // ∞ + ∞ = ∞
            CHECK(divz + divz == divz);
            // -∞ + -∞ = -∞
            CHECK(ndivz + ndivz == ndivz);
            // ∞ + -∞ = NaN
            CHECK(divz + ndivz == divzz);
            CHECK(ndivz + divz == divzz);
            // x + NaN = NaN + x = NaN
            CHECK(divz + divzz == divzz);
            CHECK(divzz + divz == divzz);
            CHECK(ndivz + divzz == divzz);
            CHECK(divzz + ndivz == divzz);
            CHECK(divzz + divzz == divzz);
        }
        SECTION("Member Addition")
        {
            Rational<int> r = divz;
            r += Rational<int>(2, 3);
            REQUIRE(r == divz);
            r += Rational<int>(-1, 3);
            REQUIRE(r == divz);
            r += Rational<int>(5, 2);
            REQUIRE(r == divz);

            r = Rational<int>(2, 3);
            r += divz;
            CHECK(r == divz);
            r = Rational<int>(-1, 3);
            r += divz;
            CHECK(r == divz);
            r = Rational<int>(5, 2);
            r += divz;
            CHECK(r == divz);

            r = ndivz;
            r += Rational<int>(2, 3);
            REQUIRE(r == ndivz);
            r += Rational<int>(-1, 3);
            REQUIRE(r == ndivz);
            r += Rational<int>(5, 2);
            REQUIRE(r == ndivz);

            r = Rational<int>(2, 3);
            r += ndivz;
            CHECK(r == ndivz);
            r = Rational<int>(-1, 3);
            r += ndivz;
            CHECK(r == ndivz);
            r = Rational<int>(5, 2);
            r += ndivz;
            CHECK(r == ndivz);

            r = divzz;
            r += Rational<int>(2, 3);
            REQUIRE(r == divzz);
            r += Rational<int>(-1, 3);
            REQUIRE(r == divzz);
            r += Rational<int>(5, 2);
            REQUIRE(r == divzz);

            r = Rational<int>(2, 3);
            r += divzz;
            CHECK(r == divzz);
            r = Rational<int>(-1, 3);
            r += divzz;
            CHECK(r == divzz);
            r = Rational<int>(5, 2);
            r += divzz;
            CHECK(r == divzz);

            // ∞ + ∞ = ∞
            r = divz;
            r += divz;
            CHECK(r == divz);
            // -∞ + -∞ = -∞
            r = ndivz;
            r += ndivz;
            CHECK(r == ndivz);
            // ∞ + -∞ = NaN
            r = divz;
            r += ndivz;
            CHECK(r == divzz);
            r = ndivz;
            r += divz;
            CHECK(r == divzz);
            // x + NaN = NaN + x = NaN
            r = divz;
            r += divzz;
            CHECK(r == divzz);
            r = divzz;
            r += divz;
            CHECK(r == divzz);
            r = ndivz;
            r += divzz;
            CHECK(r == divzz);
            r = divzz;
            r += ndivz;
            CHECK(r == divzz);
            r = divzz;
            r += divzz;
            CHECK(r == divzz);
        }
        SECTION("Integer Addition")
        {
            CHECK(divz + 0 == divz);
            CHECK(divz + 1000 == divz);
            CHECK(divz + (-1000) == divz);
            CHECK(ndivz + 0 == ndivz);
            CHECK(ndivz + 1000 == ndivz);
            CHECK(ndivz + (-1000) == ndivz);
            CHECK(divzz + 0 == divzz);
            CHECK(divzz + 1000 == divzz);
            CHECK(divzz + (-1000) == divzz);

            CHECK(0 + divz == divz);
            CHECK(1000 + divz == divz);
            CHECK((-1000) + divz == divz);
            CHECK(0 + ndivz == ndivz);
            CHECK(1000 + ndivz == ndivz);
            CHECK((-1000) + ndivz == ndivz);
            CHECK(0 + divzz == divzz);
            CHECK(1000 + divzz == divzz);
            CHECK((-1000) + divzz == divzz);
        }
        SECTION("Integer Addition Member")
        {
            Rational<int> r;
            r = divz;
            r += 0;
            CHECK(r == divz);
            r = divz;
            r += 1000;
            CHECK(r == divz);
            r = divz;
            r += (-1000);
            CHECK(r == divz);
            r = ndivz;
            r += 0;
            CHECK(r == ndivz);
            r = ndivz;
            r += 1000;
            CHECK(r == ndivz);
            r = ndivz;
            r += (-1000);
            CHECK(r == ndivz);
            r = divzz;
            r += 0;
            CHECK(r == divzz);
            r = divzz;
            r += 1000;
            CHECK(r == divzz);
            r = divzz;
            r += (-1000);
            CHECK(r == divzz);
        }
        SECTION("Subtraction")
        {
            // ∞ - x = ∞
            // x - ∞ = -∞
            CHECK(divz - Rational<int>(2, 3) == divz);
            CHECK(divz - Rational<int>(-1, 3) == divz);
            CHECK(divz - Rational<int>(5, 2) == divz);

            CHECK(Rational<int>(2, 3) - divz == ndivz);
            CHECK(Rational<int>(-1, 3) - divz == ndivz);
            CHECK(Rational<int>(5, 2) - divz == ndivz);

            CHECK(ndivz - Rational<int>(2, 3) == ndivz);
            CHECK(ndivz - Rational<int>(-1, 3) == ndivz);
            CHECK(ndivz - Rational<int>(5, 2) == ndivz);

            CHECK(Rational<int>(2, 3) - ndivz == divz);
            CHECK(Rational<int>(-1, 3) - ndivz == divz);
            CHECK(Rational<int>(5, 2) - ndivz == divz);

            CHECK(divzz - Rational<int>(2, 3) == divzz);
            CHECK(divzz - Rational<int>(-1, 3) == divzz);
            CHECK(divzz - Rational<int>(5, 2) == divzz);

            CHECK(Rational<int>(2, 3) - divzz == divzz);
            CHECK(Rational<int>(-1, 3) - divzz == divzz);
            CHECK(Rational<int>(5, 2) - divzz == divzz);

            // ∞ - ∞ = NaN
            CHECK(divz - divz == divzz);
            // -∞ - -∞ = NaN
            CHECK(ndivz - ndivz == divzz);
            // +∞ - -∞ = +∞
            CHECK(divz - ndivz == divz);
            // -∞ - +∞ = -∞
            CHECK(ndivz - divz == ndivz);
            // x - NaN = NaN - x = NaN
            CHECK(divz - divzz == divzz);
            CHECK(divzz - divz == divzz);
            CHECK(ndivz - divzz == divzz);
            CHECK(divzz - ndivz == divzz);
            CHECK(divzz - divzz == divzz);
        }
        SECTION("Member Subtraction")
        {
            Rational<int> r = divz;
            r -= Rational<int>(2, 3);
            REQUIRE(r == divz);
            r -= Rational<int>(-1, 3);
            REQUIRE(r == divz);
            r -= Rational<int>(5, 2);
            REQUIRE(r == divz);

            r = Rational<int>(2, 3);
            r -= divz;
            CHECK(r == ndivz);
            r = Rational<int>(-1, 3);
            r -= divz;
            CHECK(r == ndivz);
            r = Rational<int>(5, 2);
            r -= divz;
            CHECK(r == ndivz);

            r = ndivz;
            r -= Rational<int>(2, 3);
            REQUIRE(r == ndivz);
            r -= Rational<int>(-1, 3);
            REQUIRE(r == ndivz);
            r -= Rational<int>(5, 2);
            REQUIRE(r == ndivz);

            r = Rational<int>(2, 3);
            r -= ndivz;
            CHECK(r == divz);
            r = Rational<int>(-1, 3);
            r -= ndivz;
            CHECK(r == divz);
            r = Rational<int>(5, 2);
            r -= ndivz;
            CHECK(r == divz);

            r = divzz;
            r -= Rational<int>(2, 3);
            REQUIRE(r == divzz);
            r -= Rational<int>(-1, 3);
            REQUIRE(r == divzz);
            r -= Rational<int>(5, 2);
            REQUIRE(r == divzz);

            r = Rational<int>(2, 3);
            r -= divzz;
            CHECK(r == divzz);
            r = Rational<int>(-1, 3);
            r -= divzz;
            CHECK(r == divzz);
            r = Rational<int>(5, 2);
            r -= divzz;
            CHECK(r == divzz);

            // ∞ - ∞ = NaN
            r = divz;
            r -= divz;
            CHECK(r == divzz);
            // -∞ - -∞ = NaN
            r = ndivz;
            r -= ndivz;
            CHECK(r == divzz);
            // +∞ - -∞ = +∞
            r = divz;
            r -= ndivz;
            CHECK(r == divz);
            // -∞ - +∞ = -∞
            r = ndivz;
            r -= divz;
            CHECK(r == ndivz);
            // x - NaN = NaN - x = NaN
            r = divz;
            r -= divzz;
            CHECK(r == divzz);
            r = divzz;
            r -= divz;
            CHECK(r == divzz);
            r = ndivz;
            r -= divzz;
            CHECK(r == divzz);
            r = divzz;
            r -= ndivz;
            CHECK(r == divzz);
            r = divzz;
            r -= divzz;
            CHECK(r == divzz);
        }
        SECTION("Integer Subtraction")
        {
            CHECK(divz - 0 == divz);
            CHECK(divz - 1000 == divz);
            CHECK(divz - (-1000) == divz);
            CHECK(ndivz - 0 == ndivz);
            CHECK(ndivz - (-1000) == ndivz);
            CHECK(ndivz - 1000 == ndivz);
            CHECK(divzz - 0 == divzz);
            CHECK(divzz - 1000 == divzz);
            CHECK(divzz - (-1000) == divzz);

            CHECK(0 - divz == ndivz);
            CHECK(1000 - divz == ndivz);
            CHECK((-1000) - divz == ndivz);
            CHECK(0 - ndivz == divz);
            CHECK(1000 - ndivz == divz);
            CHECK((-1000) - ndivz == divz);
            CHECK(0 - divzz == divzz);
            CHECK(1000 - divzz == divzz);
            CHECK((-1000) - divzz == divzz);
        }
        SECTION("Integer Subtraction Member")
        {
            Rational<int> r;
            r = divz;
            r -= 0;
            CHECK(r == divz);
            r = divz;
            r -= 1000;
            CHECK(r == divz);
            r = divz;
            r -= (-1000);
            CHECK(r == divz);
            r = ndivz;
            r -= 0;
            CHECK(r == ndivz);
            r = ndivz;
            r -= 1000;
            CHECK(r == ndivz);
            r = ndivz;
            r -= (-1000);
            CHECK(r == ndivz);
            r = divzz;
            r -= 0;
            CHECK(r == divzz);
            r = divzz;
            r -= 1000;
            CHECK(r == divzz);
            r = divzz;
            r -= (-1000);
            CHECK(r == divzz);
        }
        SECTION("Multiplication")
        {
            // ∞ * x = ∞
            // ∞ * -x = -∞
            CHECK(divz * Rational<int>(2, 3) == divz);
            CHECK(divz * Rational<int>(-1, 3) == ndivz);
            CHECK(divz * Rational<int>(5, 2) == divz);
            CHECK(divz * Rational<int>(0, 1) == divzz);

            CHECK(Rational<int>(2, 3) * divz == divz);
            CHECK(Rational<int>(-1, 3) * divz == ndivz);
            CHECK(Rational<int>(5, 2) * divz == divz);
            CHECK(Rational<int>(0, 1) * divz == divzz);

            CHECK(ndivz * Rational<int>(2, 3) == ndivz);
            CHECK(ndivz * Rational<int>(-1, 3) == divz);
            CHECK(ndivz * Rational<int>(5, 2) == ndivz);
            CHECK(ndivz * Rational<int>(0, 1) == divzz);

            CHECK(Rational<int>(2, 3) * ndivz == ndivz);
            CHECK(Rational<int>(-1, 3) * ndivz == divz);
            CHECK(Rational<int>(5, 2) * ndivz == ndivz);
            CHECK(Rational<int>(0, 1) * ndivz == divzz);

            CHECK(divzz * Rational<int>(2, 3) == divzz);
            CHECK(divzz * Rational<int>(-1, 3) == divzz);
            CHECK(divzz * Rational<int>(5, 2) == divzz);
            CHECK(divzz * Rational<int>(0, 1) == divzz);

            CHECK(Rational<int>(2, 3) * divzz == divzz);
            CHECK(Rational<int>(-1, 3) * divzz == divzz);
            CHECK(Rational<int>(5, 2) * divzz == divzz);
            CHECK(Rational<int>(0, 1) * divzz == divzz);

            // ∞ * ∞ = ∞
            CHECK(divz * divz == divz);
            // -∞ * -∞ = ∞
            CHECK(ndivz * ndivz == divz);
            // +∞ * -∞ = -∞
            CHECK(divz * ndivz == ndivz);
            // -∞ * +∞ = -∞
            CHECK(ndivz * divz == ndivz);
            // x * NaN = NaN * x = NaN
            CHECK(divz * divzz == divzz);
            CHECK(divzz * divz == divzz);
            CHECK(ndivz * divzz == divzz);
            CHECK(divzz * ndivz == divzz);
            CHECK(divzz * divzz == divzz);
        }
        SECTION("Member Multiplication")
        {
            Rational<int> r = divz;
            r *= Rational<int>(2, 3);
            REQUIRE(r == divz);
            r *= Rational<int>(-1, 3);
            REQUIRE(r == ndivz);
            r = divz;
            r *= Rational<int>(5, 2);
            REQUIRE(r == divz);
            r = divz;
            r *= Rational<int>(0, 1);
            REQUIRE(r == divzz);

            r = Rational<int>(2, 3);
            r *= divz;
            CHECK(r == divz);
            r = Rational<int>(-1, 3);
            r *= divz;
            CHECK(r == ndivz);
            r = Rational<int>(5, 2);
            r *= divz;
            CHECK(r == divz);
            r = Rational<int>(0, 1);
            r *= divz;
            CHECK(r == divzz);

            r = ndivz;
            r *= Rational<int>(2, 3);
            REQUIRE(r == ndivz);
            r *= Rational<int>(-1, 3);
            REQUIRE(r == divz);
            r = ndivz;
            r *= Rational<int>(5, 2);
            REQUIRE(r == ndivz);
            r = ndivz;
            r *= Rational<int>(0, 1);
            REQUIRE(r == divzz);

            r = Rational<int>(2, 3);
            r *= ndivz;
            CHECK(r == ndivz);
            r = Rational<int>(-1, 3);
            r *= ndivz;
            CHECK(r == divz);
            r = Rational<int>(5, 2);
            r *= ndivz;
            CHECK(r == ndivz);
            r = Rational<int>(0, 1);
            r *= ndivz;
            CHECK(r == divzz);


            r = divzz;
            r *= Rational<int>(2, 3);
            REQUIRE(r == divzz);
            r *= Rational<int>(-1, 3);
            REQUIRE(r == divzz);
            r *= Rational<int>(5, 2);
            REQUIRE(r == divzz);
            r = divzz;
            r *= Rational<int>(0, 1);
            REQUIRE(r == divzz);

            r = Rational<int>(2, 3);
            r *= divzz;
            CHECK(r == divzz);
            r = Rational<int>(-1, 3);
            r *= divzz;
            CHECK(r == divzz);
            r = Rational<int>(5, 2);
            r *= divzz;
            CHECK(r == divzz);
            r = Rational<int>(0, 1);
            r *= divzz;
            CHECK(r == divzz);

            // ∞ * ∞ = ∞
            r = divz;
            r *= divz;
            CHECK(r == divz);
            // -∞ * -∞ = +∞
            r = ndivz;
            r *= ndivz;
            CHECK(r == divz);
            // +∞ * -∞ = -∞
            r = divz;
            r *= ndivz;
            CHECK(r == ndivz);
            // -∞ * +∞ = -∞
            r = ndivz;
            r *= divz;
            CHECK(r == ndivz);
            // x * NaN = NaN * x = NaN
            r = divz;
            r *= divzz;
            CHECK(r == divzz);
            r = divzz;
            r *= divz;
            CHECK(r == divzz);
            r = ndivz;
            r *= divzz;
            CHECK(r == divzz);
            r = divzz;
            r *= ndivz;
            CHECK(r == divzz);
            r = divzz;
            r *= divzz;
            CHECK(r == divzz);
        }
        SECTION("Integer Multiplication")
        {
            CHECK(divz * 0 == divzz);
            CHECK(divz * 1000 == divz);
            CHECK(divz * (-1000) == ndivz);
            CHECK(ndivz * 0 == divzz);
            CHECK(ndivz * 1000 == ndivz);
            CHECK(ndivz * (-1000) == divz);
            CHECK(divzz * 0 == divzz);
            CHECK(divzz * 1000 == divzz);
            CHECK(divzz * (-1000) == divzz);

            CHECK(0 * divz == divzz);
            CHECK(1000 * divz == divz);
            CHECK((-1000) * divz == ndivz);
            CHECK(0 * ndivz == divzz);
            CHECK(1000 * ndivz == ndivz);
            CHECK((-1000) * ndivz == divz);
            CHECK(0 * divzz == divzz);
            CHECK(1000 * divzz == divzz);
            CHECK((-1000) * divzz == divzz);
        }
        SECTION("Integer Multiplication Member")
        {
            Rational<int> r;
            r = divz;
            r *= 0;
            CHECK(r == divzz);
            r = divz;
            r *= 1000;
            CHECK(r == divz);
            r = divz;
            r *= (-1000);
            CHECK(r == ndivz);
            r = ndivz;
            r *= 0;
            CHECK(r == divzz);
            r = ndivz;
            r *= 1000;
            CHECK(r == ndivz);
            r = ndivz;
            r *= (-1000);
            CHECK(r == divz);
            r = divzz;
            r *= 0;
            CHECK(r == divzz);
            r = divzz;
            r *= 1000;
            CHECK(r == divzz);
            r = divzz;
            r *= (-1000);
            CHECK(r == divzz);
        }
        SECTION("Division")
        {
            // x / ∞ = 0
            // ∞ / x = ∞
            // ∞ / -x = -∞
            CHECK(divz / Rational<int>(2, 3) == divz);
            CHECK(divz / Rational<int>(-1, 3) == ndivz);
            CHECK(divz / Rational<int>(5, 2) == divz);
            CHECK(divz / Rational<int>(0, 1) == divz);

            CHECK(Rational<int>(2, 3) / divz == Rational<int>(0, 1));
            CHECK(Rational<int>(-1, 3) / divz == Rational<int>(0, 1));
            CHECK(Rational<int>(5, 2) / divz == Rational<int>(0, 1));
            CHECK(Rational<int>(0, 1) / divz == Rational<int>(0, 1));

            CHECK(ndivz / Rational<int>(2, 3) == ndivz);
            CHECK(ndivz / Rational<int>(-1, 3) == divz);
            CHECK(ndivz / Rational<int>(5, 2) == ndivz);
            CHECK(ndivz / Rational<int>(0, 1) == ndivz);

            CHECK(Rational<int>(2, 3) / ndivz == Rational<int>(0, 1));
            CHECK(Rational<int>(-1, 3) / ndivz == Rational<int>(0, 1));
            CHECK(Rational<int>(5, 2) / ndivz == Rational<int>(0, 1));
            CHECK(Rational<int>(0, 1) / ndivz == Rational<int>(0, 1));

            CHECK(divzz / Rational<int>(2, 3) == divzz);
            CHECK(divzz / Rational<int>(-1, 3) == divzz);
            CHECK(divzz / Rational<int>(5, 2) == divzz);
            CHECK(divzz / Rational<int>(0, 1) == divzz);

            CHECK(Rational<int>(2, 3) / divzz == divzz);
            CHECK(Rational<int>(-1, 3) / divzz == divzz);
            CHECK(Rational<int>(5, 2) / divzz == divzz);
            CHECK(Rational<int>(0, 1) / divzz == divzz);

            // ∞ / ∞ = NaN
            CHECK(divz / divz == divzz);
            // -∞ / -∞ = NaN
            CHECK(ndivz / ndivz == divzz);
            // +∞ / -∞ = NaN
            CHECK(divz / ndivz == divzz);
            // -∞ / +∞ = NaN
            CHECK(ndivz / divz == divzz);
            // x * NaN = NaN * x = NaN
            CHECK(divz / divzz == divzz);
            CHECK(divzz / divz == divzz);
            CHECK(ndivz / divzz == divzz);
            CHECK(divzz / ndivz == divzz);
            CHECK(divzz / divzz == divzz);
        }
        SECTION("Member Division")
        {
            Rational<int> r = divz;
            r /= Rational<int>(2, 3);
            REQUIRE(r == divz);
            r /= Rational<int>(-1, 3);
            REQUIRE(r == ndivz);
            r = divz;
            r /= Rational<int>(5, 2);
            REQUIRE(r == divz);

            r = Rational<int>(2, 3);
            r /= divz;
            CHECK(r == Rational<int>(0, 1));
            r = Rational<int>(-1, 3);
            r /= divz;
            CHECK(r == Rational<int>(0, 1));
            r = Rational<int>(5, 2);
            r /= divz;
            CHECK(r == Rational<int>(0, 1));

            r = ndivz;
            r /= Rational<int>(2, 3);
            REQUIRE(r == ndivz);
            r /= Rational<int>(-1, 3);
            REQUIRE(r == divz);
            r = ndivz;
            r /= Rational<int>(5, 2);
            REQUIRE(r == ndivz);

            r = Rational<int>(2, 3);
            r /= ndivz;
            CHECK(r == Rational<int>(0, 1));
            r = Rational<int>(-1, 3);
            r /= ndivz;
            CHECK(r == Rational<int>(0, 1));
            r = Rational<int>(5, 2);
            r /= ndivz;
            CHECK(r == Rational<int>(0, 1));


            r = divzz;
            r /= Rational<int>(2, 3);
            REQUIRE(r == divzz);
            r /= Rational<int>(-1, 3);
            REQUIRE(r == divzz);
            r /= Rational<int>(5, 2);
            REQUIRE(r == divzz);

            r = Rational<int>(2, 3);
            r /= divzz;
            CHECK(r == divzz);
            r = Rational<int>(-1, 3);
            r /= divzz;
            CHECK(r == divzz);
            r = Rational<int>(5, 2);
            r /= divzz;
            CHECK(r == divzz);

            // ∞ / ∞ = NaN
            r = divz;
            r /= divz;
            CHECK(r == divzz);
            // -∞ / -∞ = NaN
            r = ndivz;
            r /= ndivz;
            CHECK(r == divzz);
            // +∞ / -∞ = NaN
            r = divz;
            r /= ndivz;
            CHECK(r == divzz);
            // -∞ / +∞ = NaN
            r = ndivz;
            r /= divz;
            CHECK(r == divzz);
            // x / NaN = NaN * x = NaN
            r = divz;
            r /= divzz;
            CHECK(r == divzz);
            r = divzz;
            r /= divz;
            CHECK(r == divzz);
            r = ndivz;
            r /= divzz;
            CHECK(r == divzz);
            r = divzz;
            r /= ndivz;
            CHECK(r == divzz);
            r = divzz;
            r /= divzz;
            CHECK(r == divzz);
        }
        SECTION("Integer Division")
        {
            CHECK(divz / 0 == divz);
            CHECK(divz / 1000 == divz);
            CHECK(divz / (-1000) == ndivz);
            CHECK(ndivz / 0 == ndivz);
            CHECK(ndivz / 1000 == ndivz);
            CHECK(ndivz / (-1000) == divz);
            CHECK(divzz / 0 == divzz);
            CHECK(divzz / 1000 == divzz);
            CHECK(divzz / (-1000) == divzz);

            CHECK(0 / divz == Rational<int>(0, 1));
            CHECK(1000 / divz == Rational<int>(0, 1));
            CHECK((-1000) / divz == Rational<int>(0, 1));
            CHECK(0 / ndivz == Rational<int>(0, 1));
            CHECK(1000 / ndivz == Rational<int>(0, 1));
            CHECK((-1000) / ndivz == Rational<int>(0, 1));
            CHECK(0 / divzz == divzz);
            CHECK(1000 / divzz == divzz);
            CHECK((-1000) / divzz == divzz);
        }
        SECTION("Integer Division Member")
        {
            Rational<int> r;
            r = divz;
            r /= 0;
            CHECK(r == divz);
            r = divz;
            r /= 1000;
            CHECK(r == divz);
            r = divz;
            r /= (-1000);
            CHECK(r == ndivz);
            r = ndivz;
            r /= 0;
            CHECK(r == ndivz);
            r = ndivz;
            r /= 1000;
            CHECK(r == ndivz);
            r = ndivz;
            r /= (-1000);
            CHECK(r == divz);
            r = divzz;
            r /= 0;
            CHECK(r == divzz);
            r = divzz;
            r /= 1000;
            CHECK(r == divzz);
            r = divzz;
            r /= (-1000);
            CHECK(r == divzz);
        }
    }

    SECTION("Div-by-0 Policy")
    {
        struct DivBy0 {};
        struct TestPolicy {
            [[noreturn]] inline static void divByZeroHandler() {
                throw DivBy0{};
            }
        };
        using TestRational = GHULBUS_MATH_NAMESPACE::RationalImpl<int, TestPolicy>;

        static_assert(std::is_nothrow_default_constructible_v<TestRational>);
        static_assert(std::is_nothrow_constructible_v<TestRational, int>);
        static_assert(!std::is_nothrow_constructible_v<TestRational, int, int>);
        static_assert(std::is_nothrow_constructible_v<Rational<int>, int, int>);
        static_assert(noexcept(std::declval<Rational<int>>() / std::declval<Rational<int>>()));
        static_assert(!noexcept(std::declval<TestRational>() / std::declval<TestRational>()));
        static_assert(noexcept(std::declval<Rational<int>>() / std::declval<int>()));
        static_assert(!noexcept(std::declval<TestRational>() / std::declval<int>()));
        static_assert(noexcept(std::declval<int>() / std::declval<Rational<int>>()));
        static_assert(!noexcept(std::declval<int>() / std::declval<TestRational>()));
        static_assert(noexcept(std::declval<Rational<int>>() /= std::declval<Rational<int>>()));
        static_assert(!noexcept(std::declval<TestRational>() /= std::declval<TestRational>()));
        static_assert(noexcept(std::declval<Rational<int>>() /= std::declval<int>()));
        static_assert(!noexcept(std::declval<TestRational>() /= std::declval<int>()));

        SECTION("Construction")
        {
            CHECK(TestRational(1, 2) == TestRational(1, 2));
            CHECK(TestRational(0) == TestRational(0, 1));
            CHECK_THROWS_AS(TestRational(1, 0), DivBy0);
            CHECK_THROWS_AS(TestRational(255, 0), DivBy0);
            CHECK_THROWS_AS(TestRational(-255, 0), DivBy0);
            CHECK_THROWS_AS(TestRational(0, 0), DivBy0);
        }
        SECTION("Division")
        {
            CHECK(TestRational(1, 2) / TestRational(1, 2) == TestRational(1, 1));
            CHECK(TestRational(0, 1) / TestRational(1, 2) == TestRational(0, 1));
            CHECK_THROWS_AS(TestRational(1, 2) / TestRational(0, 1), DivBy0);
            CHECK_THROWS_AS(TestRational(3, 4) / TestRational(0, 1), DivBy0);
            CHECK_THROWS_AS(TestRational(-3, 4) / TestRational(0, 1), DivBy0);
            CHECK_THROWS_AS(TestRational(0, 1) / TestRational(0, 1), DivBy0);
        }
        SECTION("Division Member")
        {
            TestRational r(1, 2);
            r /= TestRational(1, 2);
            CHECK(r  == TestRational(1, 1));
            r = TestRational(0, 1);
            r /= TestRational(1, 2);
            CHECK(r == TestRational(0, 1));
            r = TestRational(1, 2);
            CHECK_THROWS_AS(r /= TestRational(0, 1), DivBy0);
            r = TestRational(3, 4);
            CHECK_THROWS_AS(r /= TestRational(0, 1), DivBy0);
            r = TestRational(-3, 4);
            CHECK_THROWS_AS(r /= TestRational(0, 1), DivBy0);
            r = TestRational(0, 1);
            CHECK_THROWS_AS(r /= TestRational(0, 1), DivBy0);
        }
        SECTION("Integer Division")
        {
            CHECK(TestRational(1, 2) / 2 == TestRational(1, 4));
            CHECK(TestRational(4, 3) / 2 == TestRational(2, 3));
            CHECK_THROWS_AS(TestRational(1, 2) / 0, DivBy0);
            CHECK_THROWS_AS(TestRational(3, 4) / 0, DivBy0);
            CHECK_THROWS_AS(TestRational(-3, 4) / 0, DivBy0);
            CHECK_THROWS_AS(TestRational(0, 1) / 0, DivBy0);

            CHECK(1 / TestRational(1, 2) == TestRational(2, 1));
            CHECK(5 / TestRational(4, 3) == TestRational(15, 4));
            CHECK_THROWS_AS(1 / TestRational(0, 1), DivBy0);
            CHECK_THROWS_AS(5 / TestRational(0, 1), DivBy0);
            CHECK_THROWS_AS(-5 / TestRational(0, 1), DivBy0);
            CHECK_THROWS_AS(0 / TestRational(0, 1), DivBy0);
        }
        SECTION("Integer Division Member")
        {
            TestRational r(1, 2);
            r /= 2;
            CHECK(r == TestRational(1, 4));
            r = TestRational(4, 3);
            r /= 2;
            CHECK(r == TestRational(2, 3));
            r = TestRational(1, 2);
            CHECK_THROWS_AS(r /= 0, DivBy0);
            r = TestRational(3, 4);
            CHECK_THROWS_AS(r /= 0, DivBy0);
            r = TestRational(-3, 4);
            CHECK_THROWS_AS(r /= 0, DivBy0);
            r = TestRational(0, 1);
            CHECK_THROWS_AS(r /= 0, DivBy0);
        }
    }
}
