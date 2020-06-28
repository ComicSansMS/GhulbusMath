#include <gbMath/Vector4.hpp>
#include <gbMath/VectorIO.hpp>

#include <test_utils/MultiplicationOrderAwareOperand.hpp>

#include <catch.hpp>

#include <vector>


TEST_CASE("Vector4")
{
    using GHULBUS_MATH_NAMESPACE::Vector4;

    SECTION("Value initialization initializes to 0")
    {
        Vector4<float> v{};

        CHECK(v.x == 0.0f);
        CHECK(v.y == 0.0f);
        CHECK(v.z == 0.0f);
        CHECK(v.w == 0.0f);
    }

    SECTION("Construction from 4 values")
    {
        Vector4<float> v(42.0f, 23.5f, 17.0f, 32.0f);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
        CHECK(v.z == 17.0f);
        CHECK(v.w == 32.0f);
    }

    SECTION("Copy construction")
    {
        Vector4<float> v(42.0f, 23.5f, 17.0f, 32.0f);

        Vector4<float> v2(v);
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
        CHECK(v2.z == 17.0f);
        CHECK(v2.w == 32.0f);
    }

    SECTION("Copy assignment")
    {
        Vector4<float> v(42.0f, 23.5f, 17.0f, 32.0f);

        Vector4<float> v2;

        v2 = v;
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
        CHECK(v2.z == 17.0f);
        CHECK(v2.w == 32.0f);
    }

    SECTION("Construction from array")
    {
        float arr[] = { 42.0f, 23.5f, 17.0f, 32.0f };
        Vector4<float> v(arr);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
        CHECK(v.z == 17.0f);
        CHECK(v.w == 32.0f);
    }

    SECTION("Conversion construction")
    {
        Vector4<float> v(42.f, 23.5f, 17.0f, 32.0f);

        Vector4<int> vi(v);
        CHECK(vi.x == 42);
        CHECK(vi.y == 23);
        CHECK(vi.z == 17);
        CHECK(vi.w == 32);
    }

    SECTION("Equality and not-equal comparisons")
    {
        Vector4<float> v(42.0f, 23.5f, 17.0f, 32.0f);
        Vector4<float> v2(v);

        CHECK(v == v2);
        CHECK_FALSE(v != v2);

        v2.x = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);

        v.x = v2.x;
        CHECK(v == v2);
        v2.y = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);

        v.y = v2.y;
        CHECK(v == v2);
        v2.z = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);

        v.z = v2.z;
        CHECK(v == v2);
        v2.w = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        int arr[4] = {};
        for(int i=0; i<4; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Vector4<int>(1, 2, 3, 4) < Vector4<int>(arr));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<4; ++j) { arr[j] = 99; }
            CHECK_FALSE(Vector4<int>(1, 2, 3, 4) < Vector4<int>(arr));
        }
        // not less if both equal
        CHECK_FALSE(Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f) < Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        int arr[4] = {};
        for(int i=0; i<4; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Vector4<int>(arr) > Vector4<int>(1, 2, 3, 4));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<4; ++j) { arr[j] = 99; }
            CHECK_FALSE(Vector4<int>(arr) > Vector4<int>(1, 2, 3, 4));
        }
        // not greater if both equal
        CHECK_FALSE(Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f) > Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        int arr[4] = {};
        for(int i=0; i<4; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Vector4<int>(1, 2, 3, 4) <= Vector4<int>(arr));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<4; ++j) { arr[j] = 99; }
            CHECK_FALSE(Vector4<int>(1, 2, 3, 4) <= Vector4<int>(arr));
        }
        // both equal
        CHECK(Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f) <= Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        int arr[4] = {};
        for(int i=0; i<4; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Vector4<int>(arr) >= Vector4<int>(1, 2, 3, 4));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<4; ++j) { arr[j] = 99; }
            CHECK_FALSE(Vector4<int>(arr) >= Vector4<int>(1, 2, 3, 4));
        }
        // both equal
        CHECK(Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f) >= Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Array index operator")
    {
        Vector4<float> v(42.0f, 23.5f, 17.0f, 32.0f);
        CHECK(v[0] == 42.0f);
        CHECK(v[1] == 23.5f);
        CHECK(v[2] == 17.0f);
        CHECK(v[3] == 32.0f);
        v[1] = 55.0f;
        CHECK(v[1] == 55.0f);

        Vector4<float> v_arr[] = { Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f), Vector4<float>(5.0f, 6.0f, 7.0f, 8.0f) };
        CHECK(v_arr[0][0] == 1.0f);
        CHECK(v_arr[0][1] == 2.0f);
        CHECK(v_arr[0][2] == 3.0f);
        CHECK(v_arr[0][3] == 4.0f);
        CHECK(v_arr[1][0] == 5.0f);
        CHECK(v_arr[1][1] == 6.0f);
        CHECK(v_arr[1][2] == 7.0f);
        CHECK(v_arr[1][3] == 8.0f);
    }

    SECTION("Array index const operator")
    {
        Vector4<float> const v_const(42.0f, 23.5f, 17.0f, 32.0f);
        CHECK(v_const[0] == 42.0f);
        CHECK(v_const[1] == 23.5f);
        CHECK(v_const[2] == 17.0f);
        CHECK(v_const[3] == 32.0f);
    }

    SECTION("Vector Addition Member")
    {
        Vector4<float> v1(11.f, 22.f, 33.f, 44.f);
        v1 += Vector4<float>(55.f, 66.f, 77.f, 88.f);

        CHECK(v1.x == 66.f);
        CHECK(v1.y == 88.f);
        CHECK(v1.z == 110.f);
        CHECK(v1.w == 132.f);
        CHECK((v1 += Vector4<float>()) == v1);

        auto const& v_ref = (v1 += Vector4<float>());
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Addition Non-Member")
    {
        Vector4<float> v = Vector4<float>(11.f, 22.f, 33.f, 44.f) + Vector4<float>(55.f, 66.f, 77.f, 88.f);

        CHECK(v.x == 66.f);
        CHECK(v.y == 88.f);
        CHECK(v.z == 110.f);
        CHECK(v.w == 132.f);
    }

    SECTION("Vector Subtraction Member")
    {
        Vector4<float> v1(11.f, 22.f, 33.f, 44.f);
        v1 -= Vector4<float>(5.f, 14.f, 42.f, 10.f);

        CHECK(v1.x == 6.f);
        CHECK(v1.y == 8.f);
        CHECK(v1.z == -9.f);
        CHECK(v1.w == 34.f);
        CHECK((v1 -= Vector4<float>()) == v1);

        auto const& v_ref = (v1 -= Vector4<float>());
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Subtraction Non-Member")
    {
        Vector4<float> v = Vector4<float>(11.f, 22.f, 33.f, 44.f) - Vector4<float>(5.f, 14.f, 42.f, 10.f);

        CHECK(v.x == 6.f);
        CHECK(v.y == 8.f);
        CHECK(v.z == -9.f);
        CHECK(v.w == 34.f);
    }

    SECTION("Scalar Multiplication Member")
    {
        Vector4<float> v1(5.5f, 11.f, 16.5f, 22.f);

        CHECK(&(v1 *= 2.f) == &v1);
        CHECK(v1.x == 11.f);
        CHECK(v1.y == 22.f);
        CHECK(v1.z == 33.f);
        CHECK(v1.w == 44.f);
    }

    SECTION("Scalar Multiplication Non-Member")
    {
        Vector4<float> v1 = 2.f * Vector4<float>(5.5f, 11.f, 16.5f, 22.f);
        CHECK(v1.x == 11.f);
        CHECK(v1.y == 22.f);
        CHECK(v1.z == 33.f);
        CHECK(v1.w == 44.f);

        Vector4<float> v2 = Vector4<float>(5.5f, 11.f, 16.5f, 22.f) * 2.f;
        CHECK(v2.x == 11.f);
        CHECK(v2.y == 22.f);
        CHECK(v2.z == 33.f);
        CHECK(v2.w == 44.f);
    }

    SECTION("Scalar Multiplication Non-Member - Order of operands is preserved")
    {
        std::vector<int> lhsIds;
        std::vector<int> rhsIds;
        Vector4<MultiplicationOrderAwareOperand> v4(
            MultiplicationOrderAwareOperand(1, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(2, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(3, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(4, lhsIds, rhsIds));
        MultiplicationOrderAwareOperand s(5, lhsIds, rhsIds);
        v4 * s;
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
        s * v4;
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
        Vector4<float> v1(11.f, 22.f, 33.f, 44.f);

        v1 /= 2.f;
        CHECK(v1.x == 5.5f);
        CHECK(v1.y == 11.f);
        CHECK(v1.z == 16.5f);
        CHECK(v1.w == 22.f);

        // integer vector uses integer division
        Vector4<int> vi(11, 22, 33, 44);
        vi /= 2;
        CHECK(vi.x == 5);
        CHECK(vi.y == 11);
        CHECK(vi.z == 16);
        CHECK(vi.w == 22);
    }

    SECTION("Scalar Division Non-Member")
    {
        Vector4<float> v2 = Vector4<float>(11.f, 22.f, 33.f, 44.f) / 2.f;
        CHECK(v2.x == 5.5f);
        CHECK(v2.y == 11.f);
        CHECK(v2.z == 16.5f);
        CHECK(v2.w == 22.f);

        // integer vector uses integer division
        Vector4<int> vi = Vector4<int>(11, 22, 33, 44) / 2;
        CHECK(vi.x == 5);
        CHECK(vi.y == 11);
        CHECK(vi.z == 16);
        CHECK(vi.w == 22);
    }

    SECTION("Dot product")
    {
        CHECK(dot(Vector4<float>(3.f, 5.f, 9.f, 2.f), Vector4<float>(7.f, 11.f, 0.5f, 4.f)) == 88.5f);
    }

    SECTION("Vector length")
    {
        CHECK(length(Vector4<int>(3, -5, 12, 1)) == std::sqrt(179.0));
        CHECK(length(Vector4<float>(3.f, -5.f, 12.f, 1.f)) == std::sqrt(179.f));
        CHECK(length(Vector4<long double>(3.0, -5.0, 12.0, 1.0)) == std::sqrt(static_cast<long double>(179.0)));
    }

    SECTION("Vector normalization")
    {
        CHECK(normalized(Vector4<float>(10.f, 0.f, 0.f, 0.f)) == Vector4<float>(1.f, 0.f, 0.f, 0.f));
        CHECK(normalized(Vector4<float>(0.f, 20.f, 0.f, 0.f)) == Vector4<float>(0.f, 1.f, 0.f, 0.f));
        CHECK(normalized(Vector4<float>(0.f, 0.f, 30.f, 0.f)) == Vector4<float>(0.f, 0.f, 1.f, 0.f));
        CHECK(normalized(Vector4<float>(0.f, 0.f, 0.f, 40.f)) == Vector4<float>(0.f, 0.f, 0.f, 1.f));
        CHECK(normalized(Vector4<float>(-10.f, 0.f, 0.f, 0.f)) == Vector4<float>(-1.f, 0.f, 0.f, 0.f));
        CHECK(normalized(Vector4<float>(5.f, 5.f, 5.f, 5.f)) ==
            Vector4<float>(1.f / std::sqrt(4.f), 1.f / std::sqrt(4.f), 1.f / std::sqrt(4.f), 1.f / std::sqrt(4.f)));
    }
}
