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
}
