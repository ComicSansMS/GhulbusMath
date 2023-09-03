#include <gbMath/Color4.hpp>

#include <test_utils/MultiplicationOrderAwareOperand.hpp>

#include <catch.hpp>

#include <vector>


TEST_CASE("Color4")
{
    using GHULBUS_MATH_NAMESPACE::Color4;
    using GHULBUS_MATH_NAMESPACE::doNotInitialize;

    SECTION("Default constructor initializes to 0")
    {
        Color4 <float> c;

        CHECK(c.r == 0.0f);
        CHECK(c.g == 0.0f);
        CHECK(c.b == 0.0f);
        CHECK(c.a == 0.0f);
    }

    SECTION("Construction to uninitialized")
    {
        Color4<float> c(doNotInitialize);

        c.r = 1.f;
        c.g = 2.f;
        c.b = 3.f;
        c.a = 4.f;

        CHECK(c.r == 1.0f);
        CHECK(c.g == 2.0f);
        CHECK(c.b == 3.0f);
        CHECK(c.a == 4.0f);
    }

    SECTION("Value initialization initializes to 0")
    {
        Color4<float> c{};

        CHECK(c.r == 0.0f);
        CHECK(c.g == 0.0f);
        CHECK(c.b == 0.0f);
        CHECK(c.a == 0.0f);
    }

    SECTION("Construction from 3 values")
    {
        Color4<float> c(42.0f, 23.5f, 17.0f);

        CHECK(c.r == 42.0f);
        CHECK(c.g == 23.5f);
        CHECK(c.b == 17.0f);
        CHECK(c.a == 1.0f);
    }

    SECTION("Construction from 4 values")
    {
        Color4<float> c(42.0f, 23.5f, 17.0f, 32.0f);

        CHECK(c.r == 42.0f);
        CHECK(c.g == 23.5f);
        CHECK(c.b == 17.0f);
        CHECK(c.a == 32.0f);
    }

    SECTION("Copy construction")
    {
        Color4<float> c(42.0f, 23.5f, 17.0f, 32.0f);
        Color4<float> c2(c);

        CHECK(c2.r == 42.0f);
        CHECK(c2.g == 23.5f);
        CHECK(c2.b == 17.0f);
        CHECK(c2.a == 32.0f);
    }

    SECTION("Copy assignment")
    {
        Color4<float> c(42.0f, 23.5f, 17.0f, 32.0f);

        Color4<float> c2;

        c2 = c;
        CHECK(c2.r == 42.0f);
        CHECK(c2.g == 23.5f);
        CHECK(c2.b == 17.0f);
        CHECK(c2.a == 32.0f);
    }

    SECTION("Construction from array")
    {
        float arr[] = { 42.0f, 23.5f, 17.0f, 32.0f };
        Color4<float> c(arr);

        CHECK(c.r == 42.0f);
        CHECK(c.g == 23.5f);
        CHECK(c.b == 17.0f);
        CHECK(c.a == 32.0f);
    }

    SECTION("Equality and not-equal comparisons")
    {
        Color4<float> c(42.0f, 23.5f, 17.0f, 32.0f);
        Color4<float> c2(c);

        CHECK(c == c2);
        CHECK_FALSE(c != c2);

        c2.r = 55.0f;
        CHECK_FALSE(c == c2);
        CHECK(c != c2);

        c.r = c2.r;
        CHECK(c == c2);
        c2.g = 55.0f;
        CHECK_FALSE(c == c2);
        CHECK(c != c2);

        c.g = c2.g;
        CHECK(c == c2);
        c2.b = 55.0f;
        CHECK_FALSE(c == c2);
        CHECK(c != c2);

        c.b = c2.b;
        CHECK(c == c2);
        c2.a = 55.0f;
        CHECK_FALSE(c == c2);
        CHECK(c != c2);
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        float arr[4] = {};
        for(int i=0; i<4; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = static_cast<float>(j+1); }
            arr[i] = static_cast<float>(i+2);
            CHECK(Color4<float>(1, 2, 3, 4) < Color4<float>(arr));
            for(int j=0; j<i+1; ++j) { arr[j] = static_cast<float>(j+1); }
            arr[i] = 0;
            for(int j=i+1; j<4; ++j) { arr[j] = 99; }
            CHECK_FALSE(Color4<float>(1, 2, 3, 4) < Color4<float>(arr));
        }
        // not less if both equal
        CHECK_FALSE(Color4<float>(1.0f, 2.0f, 3.0f, 4.0f) < Color4<float>(1.0f, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        float arr[4] = {};
        for(int i=0; i<4; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = static_cast<float>(j+1); }
            arr[i] = static_cast<float>(i+2);
            CHECK(Color4<float>(arr) > Color4<float>(1, 2, 3, 4));
            for(int j=0; j<i+1; ++j) { arr[j] = static_cast<float>(j+1); }
            arr[i] = 0;
            for(int j=i+1; j<4; ++j) { arr[j] = 99; }
            CHECK_FALSE(Color4<float>(arr) > Color4<float>(1, 2, 3, 4));
        }
        // not greater if both equal
        CHECK_FALSE(Color4<float>(1.0f, 2.0f, 3.0f, 4.0f) > Color4<float>(1.0f, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        float arr[4] = {};
        for(int i=0; i<4; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = static_cast<float>(j+1); }
            arr[i] = static_cast<float>(i+2);
            CHECK(Color4<float>(1, 2, 3, 4) <= Color4<float>(arr));
            for(int j=0; j<i+1; ++j) { arr[j] = static_cast<float>(j+1); }
            arr[i] = 0;
            for(int j=i+1; j<4; ++j) { arr[j] = 99; }
            CHECK_FALSE(Color4<float>(1, 2, 3, 4) <= Color4<float>(arr));
        }
        // both equal
        CHECK(Color4<float>(1.0f, 2.0f, 3.0f, 4.0f) <= Color4<float>(1.0f, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        float arr[4] = {};
        for(int i=0; i<4; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = static_cast<float>(j+1); }
            arr[i] = static_cast<float>(i+2);
            CHECK(Color4<float>(arr) >= Color4<float>(1, 2, 3, 4));
            for(int j=0; j<i+1; ++j) { arr[j] = static_cast<float>(j+1); }
            arr[i] = 0;
            for(int j=i+1; j<4; ++j) { arr[j] = 99; }
            CHECK_FALSE(Color4<float>(arr) >= Color4<float>(1, 2, 3, 4));
        }
        // both equal
        CHECK(Color4<float>(1.0f, 2.0f, 3.0f, 4.0f) >= Color4<float>(1.0f, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Array index operator")
    {
        Color4<float> c(42.0f, 23.5f, 17.0f, 32.0f);
        CHECK(c[0] == 42.0f);
        CHECK(c[1] == 23.5f);
        CHECK(c[2] == 17.0f);
        CHECK(c[3] == 32.0f);
        c[1] = 55.0f;
        CHECK(c[1] == 55.0f);

        Color4<float> c_arr[] = { Color4<float>(1.0f, 2.0f, 3.0f, 4.0f), Color4<float>(5.0f, 6.0f, 7.0f, 8.0f) };
        CHECK(c_arr[0][0] == 1.0f);
        CHECK(c_arr[0][1] == 2.0f);
        CHECK(c_arr[0][2] == 3.0f);
        CHECK(c_arr[0][3] == 4.0f);
        CHECK(c_arr[1][0] == 5.0f);
        CHECK(c_arr[1][1] == 6.0f);
        CHECK(c_arr[1][2] == 7.0f);
        CHECK(c_arr[1][3] == 8.0f);
    }

    SECTION("Array index const operator")
    {
        Color4<float> const c_const(42.0f, 23.5f, 17.0f, 32.0f);
        CHECK(c_const[0] == 42.0f);
        CHECK(c_const[1] == 23.5f);
        CHECK(c_const[2] == 17.0f);
        CHECK(c_const[3] == 32.0f);
    }

    SECTION("Addition Member")
    {
        Color4<float> c1(11.f, 22.f, 33.f, 44.f);
        c1 += Color4<float>(55.f, 66.f, 77.f, 88.f);

        CHECK(c1.r == 66.f);
        CHECK(c1.g == 88.f);
        CHECK(c1.b == 110.f);
        CHECK(c1.a == 132.f);
        CHECK((c1 += Color4<float>()) == c1);

        auto const& c_ref = (c1 += Color4<float>());
        CHECK(&c_ref == &c1);
    }

    SECTION("Addition Non-Member")
    {
        Color4<float> c = Color4<float>(11.f, 22.f, 33.f, 44.f) + Color4<float>(55.f, 66.f, 77.f, 88.f);

        CHECK(c.r == 66.f);
        CHECK(c.g == 88.f);
        CHECK(c.b == 110.f);
        CHECK(c.a == 132.f);
    }

    SECTION("Subtraction Member")
    {
        Color4<float> c1(11.f, 22.f, 33.f, 44.f);
        c1 -= Color4<float>(5.f, 14.f, 42.f, 10.f);

        CHECK(c1.r == 6.f);
        CHECK(c1.g == 8.f);
        CHECK(c1.b == -9.f);
        CHECK(c1.a == 34.f);
        CHECK((c1 -= Color4<float>()) == c1);

        auto const& c_ref = (c1 -= Color4<float>());
        CHECK(&c_ref == &c1);
    }

    SECTION("Subtraction Non-Member")
    {
        Color4<float> c = Color4<float>(11.f, 22.f, 33.f, 44.f) - Color4<float>(5.f, 14.f, 42.f, 10.f);

        CHECK(c.r == 6.f);
        CHECK(c.g == 8.f);
        CHECK(c.b == -9.f);
        CHECK(c.a == 34.f);
    }

    SECTION("Scalar Multiplication Member")
    {
        Color4<float> c1(5.5f, 11.f, 16.5f, 22.f);

        c1 *= 2.f;
        CHECK(c1.r == 11.f);
        CHECK(c1.g == 22.f);
        CHECK(c1.b == 33.f);
        CHECK(c1.a == 44.f);

        auto const& c_ref = (c1 *= 2.f);
        CHECK(&c_ref == &c1);
    }

    SECTION("Scalar Multiplication Non-Member")
    {
        Color4<float> c1 = 2.f * Color4<float>(5.5f, 11.f, 16.5f, 22.f);
        CHECK(c1.r == 11.f);
        CHECK(c1.g == 22.f);
        CHECK(c1.b == 33.f);
        CHECK(c1.a == 44.f);

        Color4<float> c2 = Color4<float>(5.5f, 11.f, 16.5f, 22.f) * 2.f;
        CHECK(c2.r == 11.f);
        CHECK(c2.g == 22.f);
        CHECK(c2.b == 33.f);
        CHECK(c2.a == 44.f);
    }

    SECTION("Scalar Multiplication Non-Member - Order of operands is preserved")
    {
        std::vector<int> lhsIds;
        std::vector<int> rhsIds;
        Color4<MultiplicationOrderAwareOperand> c4(MultiplicationOrderAwareOperand(1, lhsIds, rhsIds),
                                                   MultiplicationOrderAwareOperand(2, lhsIds, rhsIds),
                                                   MultiplicationOrderAwareOperand(3, lhsIds, rhsIds),
                                                   MultiplicationOrderAwareOperand(4, lhsIds, rhsIds));
        MultiplicationOrderAwareOperand s(5, lhsIds, rhsIds);
        c4 * s;
        REQUIRE(lhsIds.size() == 4);
        REQUIRE(rhsIds.size() == 4);
        CHECK(std::find(begin(lhsIds), end(lhsIds), 1) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 2) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 3) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 4) != end(lhsIds));
        CHECK(rhsIds[0] == 5);
        CHECK(rhsIds[1] == 5);

        lhsIds.clear();
        rhsIds.clear();
        s * c4;
        REQUIRE(lhsIds.size() == 4);
        REQUIRE(rhsIds.size() == 4);
        CHECK(lhsIds[0] == 5);
        CHECK(lhsIds[1] == 5);
        CHECK(std::find(begin(rhsIds), end(rhsIds), 1) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 2) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 3) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 4) != end(rhsIds));
    }

    SECTION("Scalar Division Member")
    {
        Color4<float> c1(11.f, 22.f, 33.f, 44.f);

        c1 /= 2.f;
        CHECK(c1.r == 5.5f);
        CHECK(c1.g == 11.f);
        CHECK(c1.b == 16.5f);
        CHECK(c1.a == 22.f);

        // integer color uses integer division
        Color4<int> ci(11, 22, 33, 44);
        ci /= 2;
        CHECK(ci.r == 5);
        CHECK(ci.g == 11);
        CHECK(ci.b == 16);
        CHECK(ci.a == 22);
    }

    SECTION("Scalar Division Non-Member")
    {
        Color4<float> c2 = Color4<float>(11.f, 22.f, 33.f, 44.f) / 2.f;
        CHECK(c2.r == 5.5f);
        CHECK(c2.g == 11.f);
        CHECK(c2.b == 16.5f);
        CHECK(c2.a == 22.f);

        // integer vector uses integer division
        Color4<int> ci = Color4<int>(11, 22, 33, 44) / 2;
        CHECK(ci.r == 5);
        CHECK(ci.g == 11);
        CHECK(ci.b == 16);
        CHECK(ci.a == 22);
    }
}
