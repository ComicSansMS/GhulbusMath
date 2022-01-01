#include <gbMath/RationalIO.hpp>

#include <catch.hpp>

#include <sstream>

TEST_CASE("RationalIO")
{
    using GHULBUS_MATH_NAMESPACE::Rational;
    
    std::stringstream sstr;

    SECTION("Rational ostream insertion")
    {
        sstr << Rational<int>(1, 2);
        CHECK(sstr.str() == "1/2");
        sstr.str("");
        sstr << Rational<int>(-1, 2);
        CHECK(sstr.str() == "-1/2");
        sstr.str("");
        sstr << Rational<int>(1, -2);
        CHECK(sstr.str() == "-1/2");
        sstr.str("");
        sstr << Rational<int>(-1, -2);
        CHECK(sstr.str() == "1/2");
    }

    SECTION("Rational ostream insertion char")
    {
        sstr << Rational<char>(42, 5);
        CHECK(sstr.str() == "42/5");
    }

    SECTION("Rational ostream insertion signed char")
    {
        sstr << Rational<signed char>(-42, 5);
        CHECK(sstr.str() == "-42/5");
    }

    SECTION("Rational ostream insertion unsigned char")
    {
        sstr << Rational<unsigned char>(42, 5);
        CHECK(sstr.str() == "42/5");
    }
}
