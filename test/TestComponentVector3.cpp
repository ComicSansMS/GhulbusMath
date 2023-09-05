#include <gbMath/ComponentVector3.hpp>

#include <test_utils/MultiplicationOrderAwareOperand.hpp>

#include <catch.hpp>

#include <vector>


TEST_CASE("ComponentVector3")
{
    using GHULBUS_MATH_NAMESPACE::ComponentVector3;

    SECTION("Construction from 3 values")
    {
        ComponentVector3<float> v(42.0f, 23.5f, 17.0f);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
        CHECK(v.z == 17.0f);
    }

    SECTION("Copy construction")
    {
        ComponentVector3<float> v(42.0f, 23.5f, 17.0f);

        ComponentVector3<float> v2(v);
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
        CHECK(v2.z == 17.0f);
    }

    SECTION("Copy assignment")
    {
        ComponentVector3<float> v(42.0f, 23.5f, 17.0f);

        ComponentVector3<float> v2{0.f, 0.f, 0.f};

        v2 = v;
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
        CHECK(v2.z == 17.0f);
    }

    SECTION("Construction from array")
    {
        float arr[] = { 42.0f, 23.5f, 17.0f };
        ComponentVector3<float> v(arr);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
        CHECK(v.z == 17.0f);
    }

    SECTION("Equality and not-equal comparisons")
    {
        ComponentVector3<float> v(42.0f, 23.5f, 17.0f);
        ComponentVector3<float> v2(v);

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

    SECTION("Array index operator")
    {
        ComponentVector3<float> v(42.0f, 23.5f, 17.0f);
        CHECK(v[0] == 42.0f);
        CHECK(v[1] == 23.5f);
        CHECK(v[2] == 17.0f);
        v[1] = 55.0f;
        CHECK(v[1] == 55.0f);

        ComponentVector3<float> v_arr[] = { ComponentVector3<float>(1.0f, 2.0f, 3.0f),
                                            ComponentVector3<float>(4.0f, 5.0f, 6.0f) };
        CHECK(v_arr[0][0] == 1.0f);
        CHECK(v_arr[0][1] == 2.0f);
        CHECK(v_arr[0][2] == 3.0f);
        CHECK(v_arr[1][0] == 4.0f);
        CHECK(v_arr[1][1] == 5.0f);
        CHECK(v_arr[1][2] == 6.0f);
    }

    SECTION("Array index const operator")
    {
        ComponentVector3<float> const v_const(42.0f, 23.5f, 17.0f);
        CHECK(v_const[0] == 42.0f);
        CHECK(v_const[1] == 23.5f);
        CHECK(v_const[2] == 17.0f);
    }

    SECTION("Vector Addition Member")
    {
        ComponentVector3<float> v1(11.f, 22.f, 33.f);
        v1 += ComponentVector3<float>(44.f, 55.f, 66.f);

        CHECK(v1.x == 55.f);
        CHECK(v1.y == 77.f);
        CHECK(v1.z == 99.f);
        CHECK((v1 += ComponentVector3<float>(0.f, 0.f, 0.f)) == v1);

        auto const& v_ref = (v1 += ComponentVector3<float>(0.f, 0.f, 0.f));
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Addition Non-Member")
    {
        ComponentVector3<float> v =
            ComponentVector3<float>(11.f, 22.f, 33.f) + ComponentVector3<float>(44.f, 55.f, 66.f);

        CHECK(v.x == 55.f);
        CHECK(v.y == 77.f);
        CHECK(v.z == 99.f);
    }

    SECTION("Vector Subtraction Member")
    {
        ComponentVector3<float> v1(11.f, 22.f, 33.f);
        v1 -= ComponentVector3<float>(5.f, 14.f, 42.f);

        CHECK(v1.x == 6.f);
        CHECK(v1.y == 8.f);
        CHECK(v1.z == -9.f);
        CHECK((v1 -= ComponentVector3<float>(0.f, 0.f, 0.f)) == v1);

        auto const& v_ref = (v1 -= ComponentVector3<float>(0.f, 0.f, 0.f));
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Subtraction Non-Member")
    {
        ComponentVector3<float> v =
            ComponentVector3<float>(11.f, 22.f, 33.f) - ComponentVector3<float>(5.f, 14.f, 42.f);

        CHECK(v.x == 6.f);
        CHECK(v.y == 8.f);
        CHECK(v.z == -9.f);
    }

    SECTION("Scalar Multiplication Member")
    {
        ComponentVector3<float> v1(5.5f, 11.f, 16.5f);

        CHECK(&(v1 *= 2.f) == &v1);
        CHECK(v1.x == 11.f);
        CHECK(v1.y == 22.f);
        CHECK(v1.z == 33.f);
    }

    SECTION("Scalar Multiplication Non-Member")
    {
        ComponentVector3<float> v1 = 2.f * ComponentVector3<float>(5.5f, 11.f, 16.5f);
        CHECK(v1.x == 11.f);
        CHECK(v1.y == 22.f);
        CHECK(v1.z == 33.f);

        ComponentVector3<float> v2 = ComponentVector3<float>(5.5f, 11.f, 16.5f) * 2.f;
        CHECK(v2.x == 11.f);
        CHECK(v2.y == 22.f);
        CHECK(v2.z == 33.f);
    }

    SECTION("Scalar Multiplication Non-Member - Order of operands is preserved")
    {
        std::vector<int> lhsIds;
        std::vector<int> rhsIds;
        ComponentVector3<MultiplicationOrderAwareOperand> v3(
            MultiplicationOrderAwareOperand(1, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(2, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(3, lhsIds, rhsIds));
        MultiplicationOrderAwareOperand s(4, lhsIds, rhsIds);
        auto const vl = v3 * s;
        REQUIRE(lhsIds.size() == 3);
        REQUIRE(rhsIds.size() == 3);
        CHECK(std::find(begin(lhsIds), end(lhsIds), 1) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 2) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 3) != end(lhsIds));
        CHECK(rhsIds[0] == 4);
        CHECK(rhsIds[1] == 4);
        CHECK(vl.x.id() == 11);
        CHECK(vl.y.id() == 12);
        CHECK(vl.z.id() == 13);

        lhsIds.clear();
        rhsIds.clear();
        auto const vr = s * v3;
        REQUIRE(lhsIds.size() == 3);
        REQUIRE(rhsIds.size() == 3);
        CHECK(lhsIds[0] == 4);
        CHECK(lhsIds[1] == 4);
        CHECK(std::find(begin(rhsIds), end(rhsIds), 1) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 2) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 3) != end(rhsIds));
        CHECK(vr.x.id() == 14);
        CHECK(vr.y.id() == 14);
        CHECK(vr.z.id() == 14);
    }

    SECTION("Scalar Division Member")
    {
        ComponentVector3<float> v1(11.f, 22.f, 33.f);

        v1 /= 2.f;
        CHECK(v1.x == 5.5f);
        CHECK(v1.y == 11.f);
        CHECK(v1.z == 16.5f);

        // integer vector uses integer division
        ComponentVector3<int> vi(11, 22, 33);
        vi /= 2;
        CHECK(vi.x == 5);
        CHECK(vi.y == 11);
        CHECK(vi.z == 16);
    }

    SECTION("Scalar Division Non-Member")
    {
        ComponentVector3<float> v2 = ComponentVector3<float>(11.f, 22.f, 33.f) / 2.f;
        CHECK(v2.x == 5.5f);
        CHECK(v2.y == 11.f);
        CHECK(v2.z == 16.5f);

        // integer vector uses integer division
        ComponentVector3<int> vi = ComponentVector3<int>(11, 22, 33) / 2;
        CHECK(vi.x == 5);
        CHECK(vi.y == 11);
        CHECK(vi.z == 16);
    }
}
