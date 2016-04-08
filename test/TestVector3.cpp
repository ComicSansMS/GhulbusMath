#include <gbMath/Vector3.hpp>
#include <gbMath/VectorIO.hpp>

#include <test_utils/MultiplicationOrderAwareOperand.hpp>

#include <catch.hpp>

#include <vector>


TEST_CASE("Vector3")
{
    using GHULBUS_MATH_NAMESPACE::Vector3;

    SECTION("Value initialization initializes to 0")
    {
        Vector3<float> v{};

        CHECK(v.x == 0.0f);
        CHECK(v.y == 0.0f);
        CHECK(v.z == 0.0f);
    }

    SECTION("Construction from 3 values")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
        CHECK(v.z == 17.0f);
    }

    SECTION("Copy construction")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);

        Vector3<float> v2(v);
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
        CHECK(v2.z == 17.0f);
    }

    SECTION("Copy assignment")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);

        Vector3<float> v2;

        v2 = v;
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
        CHECK(v2.z == 17.0f);
    }

    SECTION("Conversion construction")
    {
        Vector3<float> v(42.f, 23.5f, 17.0f);

        Vector3<int> vi(v);
        CHECK(vi.x == 42);
        CHECK(vi.y == 23);
        CHECK(vi.z == 17);
    }

    SECTION("Equality and not-equal comparisons")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);
        Vector3<float> v2(v);

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
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        CHECK(Vector3<float>(1.0f, 2.0f, 3.0f) < Vector3<float>(4.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 7.0f, 3.0f) < Vector3<float>(4.0f, 2.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(4.5f, 2.0f, 3.0f) < Vector3<float>(4.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 2.0f, 3.0f) < Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 2.0f, 7.0f) < Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 5.5f, 3.0f) < Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 2.0f, 3.0f) < Vector3<float>(1.0f, 2.0f, 4.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 4.5f) < Vector3<float>(1.0f, 2.0f, 4.0f));
        // not less if both equal
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 3.0f) < Vector3<float>(1.0f, 2.0f, 3.0f));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 3.0f) > Vector3<float>(4.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 7.0f, 3.0f) > Vector3<float>(4.0f, 2.0f, 6.0f));
        CHECK(Vector3<float>(4.5f, 2.0f, 3.0f) > Vector3<float>(4.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 3.0f) > Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 7.0f) > Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 5.5f, 3.0f) > Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 3.0f) > Vector3<float>(1.0f, 2.0f, 4.0f));
        CHECK(Vector3<float>(1.0f, 2.0f, 4.5f) > Vector3<float>(1.0f, 2.0f, 4.0f));
        // not less if both equal
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 3.0f) > Vector3<float>(1.0f, 2.0f, 3.0f));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        CHECK(Vector3<float>(1.0f, 2.0f, 3.0f) <= Vector3<float>(4.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 7.0f, 3.0f) <= Vector3<float>(4.0f, 2.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(4.5f, 2.0f, 3.0f) <= Vector3<float>(4.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 2.0f, 3.0f) <= Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 2.0f, 7.0f) <= Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 5.5f, 3.0f) <= Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 2.0f, 3.0f) <= Vector3<float>(1.0f, 2.0f, 4.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 4.5f) <= Vector3<float>(1.0f, 2.0f, 4.0f));
        // both equal
        CHECK(Vector3<float>(1.0f, 2.0f, 3.0f) <= Vector3<float>(1.0f, 2.0f, 3.0f));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 3.0f) >= Vector3<float>(4.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 7.0f, 3.0f) >= Vector3<float>(4.0f, 2.0f, 6.0f));
        CHECK(Vector3<float>(4.5f, 2.0f, 3.0f) >= Vector3<float>(4.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 3.0f) >= Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 7.0f) >= Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK(Vector3<float>(1.0f, 5.5f, 3.0f) >= Vector3<float>(1.0f, 5.0f, 6.0f));
        CHECK_FALSE(Vector3<float>(1.0f, 2.0f, 3.0f) >= Vector3<float>(1.0f, 2.0f, 4.0f));
        CHECK(Vector3<float>(1.0f, 2.0f, 4.5f) >= Vector3<float>(1.0f, 2.0f, 4.0f));
        // both equal
        CHECK(Vector3<float>(1.0f, 2.0f, 3.0f) >= Vector3<float>(1.0f, 2.0f, 3.0f));
    }

    SECTION("Array index operator")
    {
        Vector3<float> v(42.0f, 23.5f, 17.0f);
        CHECK(v[0] == 42.0f);
        CHECK(v[1] == 23.5f);
        CHECK(v[2] == 17.0f);
        v[1] = 55.0f;
        CHECK(v[1] == 55.0f);

        Vector3<float> v_arr[] = { Vector3<float>(1.0f, 2.0f, 3.0f), Vector3<float>(4.0f, 5.0f, 6.0f) };
        CHECK(v_arr[0][0] == 1.0f);
        CHECK(v_arr[0][1] == 2.0f);
        CHECK(v_arr[0][2] == 3.0f);
        CHECK(v_arr[1][0] == 4.0f);
        CHECK(v_arr[1][1] == 5.0f);
        CHECK(v_arr[1][2] == 6.0f);
    }

    SECTION("Array index const operator")
    {
        Vector3<float> const v_const(42.0f, 23.5f, 17.0f);
        CHECK(v_const[0] == 42.0f);
        CHECK(v_const[1] == 23.5f);
        CHECK(v_const[2] == 17.0f);
    }

    SECTION("Vector Addition Member")
    {
        Vector3<float> v1(11.f, 22.f, 33.f);
        v1 += Vector3<float>(44.f, 55.f, 66.f);

        CHECK(v1.x == 55.f);
        CHECK(v1.y == 77.f);
        CHECK(v1.z == 99.f);
        CHECK((v1 += Vector3<float>()) == v1);

        auto const& v_ref = (v1 += Vector3<float>());
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Addition Non-Member")
    {
        Vector3<float> v = Vector3<float>(11.f, 22.f, 33.f) + Vector3<float>(44.f, 55.f, 66.f);

        CHECK(v.x == 55.f);
        CHECK(v.y == 77.f);
        CHECK(v.z == 99.f);
    }

    SECTION("Vector Subtraction Member")
    {
        Vector3<float> v1(11.f, 22.f, 33.f);
        v1 -= Vector3<float>(5.f, 14.f, 42.f);

        CHECK(v1.x == 6.f);
        CHECK(v1.y == 8.f);
        CHECK(v1.z == -9.f);
        CHECK((v1 -= Vector3<float>()) == v1);

        auto const& v_ref = (v1 -= Vector3<float>());
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Subtraction Non-Member")
    {
        Vector3<float> v = Vector3<float>(11.f, 22.f, 33.f) - Vector3<float>(5.f, 14.f, 42.f);

        CHECK(v.x == 6.f);
        CHECK(v.y == 8.f);
        CHECK(v.z == -9.f);
    }

    SECTION("Scalar Multiplication Member")
    {
        Vector3<float> v1(5.5f, 11.f, 16.5f);

        v1 *= 2.f;
        CHECK(v1.x == 11.f);
        CHECK(v1.y == 22.f);
        CHECK(v1.z == 33.f);
    }

    SECTION("Scalar Multiplication Non-Member")
    {
        Vector3<float> v1 = 2.f * Vector3<float>(5.5f, 11.f, 16.5f);
        CHECK(v1.x == 11.f);
        CHECK(v1.y == 22.f);
        CHECK(v1.z == 33.f);

        Vector3<float> v2 = Vector3<float>(5.5f, 11.f, 16.5f) * 2.f;
        CHECK(v2.x == 11.f);
        CHECK(v2.y == 22.f);
        CHECK(v2.z == 33.f);
    }

    SECTION("Scalar Multiplication Non-Member - Order of operands is preserved")
    {
        std::vector<int> lhsIds;
        std::vector<int> rhsIds;
        Vector3<MultiplicationOrderAwareOperand> v3(
            MultiplicationOrderAwareOperand(1, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(2, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(3, lhsIds, rhsIds));
        MultiplicationOrderAwareOperand s(4, lhsIds, rhsIds);
        v3 * s;
        REQUIRE(lhsIds.size() == 3);
        REQUIRE(rhsIds.size() == 3);
        CHECK(std::find(begin(lhsIds), end(lhsIds), 1) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 2) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 3) != end(lhsIds));
        CHECK(rhsIds[0] == 4);
        CHECK(rhsIds[1] == 4);

        lhsIds.clear();
        rhsIds.clear();
        s * v3;
        REQUIRE(lhsIds.size() == 3);
        REQUIRE(rhsIds.size() == 3);
        CHECK(lhsIds[0] == 4);
        CHECK(lhsIds[1] == 4);
        CHECK(std::find(begin(rhsIds), end(rhsIds), 1) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 2) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 3) != end(rhsIds));
    }

    SECTION("Scalar Division Member")
    {
        Vector3<float> v1(11.f, 22.f, 33.f);

        v1 /= 2.f;
        CHECK(v1.x == 5.5f);
        CHECK(v1.y == 11.f);
        CHECK(v1.z == 16.5f);

        // integer vector uses integer division
        Vector3<int> vi(11, 22, 33);
        vi /= 2;
        CHECK(vi.x == 5);
        CHECK(vi.y == 11);
        CHECK(vi.z == 16);
    }

    SECTION("Scalar Division Non-Member")
    {
        Vector3<float> v2 = Vector3<float>(11.f, 22.f, 33.f) / 2.f;
        CHECK(v2.x == 5.5f);
        CHECK(v2.y == 11.f);
        CHECK(v2.z == 16.5f);

        // integer vector uses integer division
        Vector3<int> vi = Vector3<int>(11, 22, 33) / 2;
        CHECK(vi.x == 5);
        CHECK(vi.y == 11);
        CHECK(vi.z == 16);
    }

    SECTION("Dot product")
    {
        CHECK(dot(Vector3<float>(3.f, 5.f, 9.f), Vector3<float>(7.f, 11.f, 0.5f)) == 80.5f);
    }

    SECTION("Vector length")
    {
        CHECK(length(Vector3<int>(3, -5, 12)) == std::sqrt(178.0));
        CHECK(length(Vector3<float>(3.f, -5.f, 12.f)) == std::sqrt(178.f));
        CHECK(length(Vector3<long double>(3.0, -5.0, 12.0)) == std::sqrt(static_cast<long double>(178.0)));
    }

    SECTION("Vector normalization")
    {
        CHECK(normalized(Vector3<float>(10.f, 0.f, 0.f)) == Vector3<float>(1.f, 0.f, 0.f));
        CHECK(normalized(Vector3<float>(0.f, 20.f, 0.f)) == Vector3<float>(0.f, 1.f, 0.f));
        CHECK(normalized(Vector3<float>(0.f, 0.f, 30.f)) == Vector3<float>(0.f, 0.f, 1.f));
        CHECK(normalized(Vector3<float>(-10.f, 0.f, 0.f)) == Vector3<float>(-1.f, 0.f, 0.f));
        CHECK(normalized(Vector3<float>(5.f, 5.f, 5.f)) ==
            Vector3<float>(1.f / std::sqrt(3.f), 1.f / std::sqrt(3.f), 1.f / std::sqrt(3.f)));
    }

    SECTION("Cross product")
    {
        CHECK(cross(Vector3<float>(1.f, 2.f, 3.f), Vector3<float>(4.f, 5.f, 6.f)) == Vector3<float>(-3.f, 6.f, -3.f));
        CHECK(cross(Vector3<float>(1.f, 0.f, 0.f), Vector3<float>(0.f, 1.f, 0.f)) == Vector3<float>(0.f, 0.f, 1.f));
        CHECK(cross(Vector3<float>(1.f, 0.f, 0.f), Vector3<float>(0.f, 0.f, 1.f)) == Vector3<float>(0.f, -1.f, 0.f));
        CHECK(cross(Vector3<float>(1.f, 2.f, 3.f), Vector3<float>(5.f, 10.f, 15.f)) == Vector3<float>());
    }

    SECTION("Box product")
    {
        CHECK(box(Vector3<float>(1.f, 2.f, 3.f), Vector3<float>(4.f, 5.f, 6.f), Vector3<float>(7.f, 8.f, 9.f)) == 0.f);
        CHECK(box(Vector3<float>(1.f, 0.f, 0.f), Vector3<float>(0.f, 1.f, 0.f), Vector3<float>(0.f, 0.f, 1.f)) == 1.f);
        CHECK(box(Vector3<int>(15, 42, 17), Vector3<int>(23, 55, 47), Vector3<int>(92, 13, 58)) == 83328);
    }
}
