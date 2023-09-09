#include <gbMath/Vector.hpp>
#include <gbMath/VectorIO.hpp>

#include <test_utils/MultiplicationOrderAwareOperand.hpp>

#include <catch.hpp>

#include <algorithm>
#include <vector>


TEST_CASE("Vector")
{
    using GHULBUS_MATH_NAMESPACE::Vector;
    using GHULBUS_MATH_NAMESPACE::doNotInitialize;

    SECTION("Static Properties")
    {
        static_assert(std::same_as<Vector<float, 3>::ValueType, float>);
        static_assert(std::same_as<Vector<int, 3>::ValueType, int>);
        static_assert(std::same_as<Vector<double, 3>::ValueType, double>);
        static_assert(Vector<float, 3>::Dimension::value == 3);
        static_assert(Vector<double, 5>::Dimension::value == 5);
        static_assert(Vector<float, 42>::Dimension::value == 42);
    }

    SECTION("Default constructor initializes to 0")
    {
        Vector<float, 6> v;

        CHECK(std::all_of(begin(v.v), end(v.v), [](float f) { return f == 0.f; }));
    }
    SECTION("Construction to uninitialized")
    {
        Vector<float, 6> v(doNotInitialize);

        std::iota(begin(v.v), end(v.v), 1.f);
        CHECK(v.v[0] == 1.f);
        CHECK(v.v[1] == 2.f);
        CHECK(v.v[2] == 3.f);
        CHECK(v.v[3] == 4.f);
        CHECK(v.v[4] == 5.f);
        CHECK(v.v[5] == 6.f);
    }

    SECTION("Value initialization initializes to 0")
    {
        Vector<float, 6> v{};

        CHECK(std::all_of(begin(v.v), end(v.v), [](float f) { return f == 0.f; }));
    }

    SECTION("Construction from values")
    {
        Vector<float, 6> v(42.0f, 23.5f, 17.0f, 32.0f, 55.f, -5.f);

        CHECK(v.v[0] == 42.0f);
        CHECK(v.v[1] == 23.5f);
        CHECK(v.v[2] == 17.0f);
        CHECK(v.v[3] == 32.0f);
        CHECK(v.v[4] == 55.0f);
        CHECK(v.v[5] == -5.0f);
    }

    SECTION("Copy construction")
    {
        Vector<float, 6> v(42.0f, 23.5f, 17.0f, 32.0f, 55.0f, -5.0f);

        Vector v2(v);
        CHECK(v2.v[0] == 42.0f);
        CHECK(v2.v[1] == 23.5f);
        CHECK(v2.v[2] == 17.0f);
        CHECK(v2.v[3] == 32.0f);
        CHECK(v2.v[4] == 55.0f);
        CHECK(v2.v[5] == -5.0f);
    }

    SECTION("Copy assignment")
    {
        Vector<float, 6> v(42.0f, 23.5f, 17.0f, 32.0f, 55.0f, -5.0f);

        Vector<float, 6> v2(doNotInitialize);

        v2 = v;
        CHECK(v2.v[0] == 42.0f);
        CHECK(v2.v[1] == 23.5f);
        CHECK(v2.v[2] == 17.0f);
        CHECK(v2.v[3] == 32.0f);
        CHECK(v2.v[4] == 55.0f);
        CHECK(v2.v[5] == -5.0f);
    }

    SECTION("Construction from array")
    {
        float arr[] = { 42.0f, 23.5f, 17.0f, 32.0f, 55.0f, -5.f };
        Vector<float, 6> v(arr);

        CHECK(v.v[0] == 42.0f);
        CHECK(v.v[1] == 23.5f);
        CHECK(v.v[2] == 17.0f);
        CHECK(v.v[3] == 32.0f);
        CHECK(v.v[4] == 55.0f);
        CHECK(v.v[5] == -5.0f);
    }

    SECTION("Conversion construction")
    {
        Vector<float, 6> v(42.f, 23.5f, 17.0f, 32.0f, 55.0f, -5.0f);

        Vector<int, 6> vi(v);
        CHECK(vi.v[0] == 42);
        CHECK(vi.v[1] == 23);
        CHECK(vi.v[2] == 17);
        CHECK(vi.v[3] == 32);
        CHECK(vi.v[4] == 55);
        CHECK(vi.v[5] == -5);
    }

    SECTION("Equality and not-equal comparisons")
    {
        Vector<float, 2> v(42.0f, 23.5f);
        Vector<float, 2> v2(v);

        CHECK(v == v2);
        CHECK_FALSE(v != v2);

        v2.v[0] = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);

        v.v[0] = v2.v[0];
        CHECK(v == v2);
        v2.v[1] = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        int arr[6] = {};
        for(int i=0; i<6; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Vector<int, 6>(1, 2, 3, 4, 5, 6) < Vector<int, 6>(arr));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<6; ++j) { arr[j] = 99; }
            CHECK_FALSE(Vector<int, 6>(1, 2, 3, 4, 5, 6) < Vector<int, 6>(arr));
        }
        // not less if both equal
        CHECK_FALSE(Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f)
            < Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        // lower elements take precedence
        int arr[6] = {};
        for(int i=0; i<6; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Vector<int, 6>(arr) > Vector<int, 6>(1, 2, 3, 4, 5, 6));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<6; ++j) { arr[j] = 99; }
            CHECK_FALSE(Vector<int, 6>(arr) > Vector<int, 6>(1, 2, 3, 4, 5, 6));
        }
        // not greater if both equal
        CHECK_FALSE(Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f)
            > Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        int arr[6] = {};
        for(int i=0; i<6; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Vector<int, 6>(1, 2, 3, 4, 5, 6) <= Vector<int, 6>(arr));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<6; ++j) { arr[j] = 99; }
            CHECK_FALSE(Vector<int, 6>(1, 2, 3, 4, 5, 6) <= Vector<int, 6>(arr));
        }
        // both equal
        CHECK(Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f)
            <= Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        // lower elements take precedence
        int arr[6] = {};
        for(int i=0; i<6; ++i) {
            for(int j=0; j<i; ++j) { arr[j] = j + 1; }
            arr[i] = i+2;
            CHECK(Vector<int, 6>(arr) >= Vector<int, 6>(1, 2, 3, 4, 5, 6));
            for(int j=0; j<i+1; ++j) { arr[j] = j+1; }
            arr[i] = 0;
            for(int j=i+1; j<6; ++j) { arr[j] = 99; }
            CHECK_FALSE(Vector<int, 6>(arr) >= Vector<int, 6>(1, 2, 3, 4, 5, 6));
        }
        // both equal
        CHECK(Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f)
            >= Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f));
    }

    SECTION("Vector dimension")
    {
        Vector<int, 4> v4;
        CHECK(v4.dimension() == 4);
        Vector<int, 5> v5;
        CHECK(v5.dimension() == 5);
        Vector<int, 6> v6;
        CHECK(v6.dimension() == 6);
    }

    SECTION("Array index operator")
    {
        Vector<float, 6> v(42.0f, 23.5f, 17.0f, 32.0f, 55.0f, -5.0f);
        CHECK(v[0] == 42.0f);
        CHECK(v[1] == 23.5f);
        CHECK(v[2] == 17.0f);
        CHECK(v[3] == 32.0f);
        CHECK(v[4] == 55.0f);
        CHECK(v[5] == -5.0f);
        v[1] = 99.0f;
        CHECK(v[1] == 99.0f);

        Vector<float, 6> v_arr[] = { Vector<float, 6>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f),
                                      Vector<float, 6>(7.0f, 8.0f, 9.0f, 10.f, 11.f, 12.f) };
        CHECK(v_arr[0][0] == 1.0f);
        CHECK(v_arr[0][1] == 2.0f);
        CHECK(v_arr[0][2] == 3.0f);
        CHECK(v_arr[0][3] == 4.0f);
        CHECK(v_arr[0][4] == 5.0f);
        CHECK(v_arr[0][5] == 6.0f);
        CHECK(v_arr[1][0] == 7.0f);
        CHECK(v_arr[1][1] == 8.0f);
        CHECK(v_arr[1][2] == 9.0f);
        CHECK(v_arr[1][3] == 10.0f);
        CHECK(v_arr[1][4] == 11.0f);
        CHECK(v_arr[1][5] == 12.0f);
    }

    SECTION("Array index const operator")
    {
        Vector<float, 6> const v_const(42.0f, 23.5f, 17.0f, 32.0f, 55.0f, -5.0f);
        CHECK(v_const[0] == 42.0f);
        CHECK(v_const[1] == 23.5f);
        CHECK(v_const[2] == 17.0f);
        CHECK(v_const[3] == 32.0f);
        CHECK(v_const[4] == 55.0f);
        CHECK(v_const[5] == -5.0f);
    }

    SECTION("Unary minus")
    {
        Vector<float, 6> const v(11.f, -22.f, 33.f, 44.f, -55.f, -66.f);

        CHECK(-v == Vector<float, 6>(-11.f, 22.f, -33.f, -44.f, 55.f, 66.f));
    }

    SECTION("Vector Addition Member")
    {
        Vector<float, 6> v1(11.f, 22.f, 33.f, 44.f, 55.f, 66.f);
        v1 += Vector<float, 6>(77.f, 88.f, 99.f, 1010.f, 1111.f, 1212.f);

        CHECK(v1[0] == 88.f);
        CHECK(v1[1] == 110.f);
        CHECK(v1[2] == 132.f);
        CHECK(v1[3] == 1054.f);
        CHECK(v1[4] == 1166.f);
        CHECK(v1[5] == 1278.f);
        CHECK((v1 += Vector<float, 6>()) == v1);

        auto const& v_ref = (v1 += Vector<float, 6>());
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Addition Non-Member")
    {
        Vector<float, 6> v = Vector<float, 6>(11.f, 22.f, 33.f, 44.f, 55.f, 66.f)
            + Vector<float, 6>(77.f, 88.f, 99.f, 1010.f, 1111.f, 1212.f);

        CHECK(v[0] == 88.f);
        CHECK(v[1] == 110.f);
        CHECK(v[2] == 132.f);
        CHECK(v[3] == 1054.f);
        CHECK(v[4] == 1166.f);
        CHECK(v[5] == 1278.f);
    }

    SECTION("Vector Subtraction Member")
    {
        Vector<float, 6> v1(11.f, 22.f, 33.f, 44.f, 55.f, -5.f);
        v1 -= Vector<float, 6>(5.f, 14.f, 42.f, 10.f, -24.f, 15.f);

        CHECK(v1[0] == 6.f);
        CHECK(v1[1] == 8.f);
        CHECK(v1[2] == -9.f);
        CHECK(v1[3] == 34.f);
        CHECK(v1[4] == 79.f);
        CHECK(v1[5] == -20.f);
        CHECK((v1 -= Vector<float, 6>()) == v1);

        auto const& v_ref = (v1 -= Vector<float, 6>());
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Subtraction Non-Member")
    {
        Vector<float, 6> v = Vector<float, 6>(11.f, 22.f, 33.f, 44.f, 55.f, -5.f)
            - Vector<float, 6>(5.f, 14.f, 42.f, 10.f, -24.f, 15.f);

        CHECK(v[0] == 6.f);
        CHECK(v[1] == 8.f);
        CHECK(v[2] == -9.f);
        CHECK(v[3] == 34.f);
        CHECK(v[4] == 79.f);
        CHECK(v[5] == -20.f);
    }

    SECTION("Scalar Multiplication Member")
    {
        Vector<float, 6> v1(5.5f, 11.f, 16.5f, 22.f, 27.5f, 33.f);

        CHECK(&(v1 *= 2.f) == &v1);
        CHECK(v1[0] == 11.f);
        CHECK(v1[1] == 22.f);
        CHECK(v1[2] == 33.f);
        CHECK(v1[3] == 44.f);
        CHECK(v1[4] == 55.f);
        CHECK(v1[5] == 66.f);
    }

    SECTION("Scalar Multiplication Non-Member")
    {
        Vector<float, 6> v1 = 2.f * Vector<float, 6>(5.5f, 11.f, 16.5f, 22.f, 27.5f, 33.f);
        CHECK(v1[0] == 11.f);
        CHECK(v1[1] == 22.f);
        CHECK(v1[2] == 33.f);
        CHECK(v1[3] == 44.f);
        CHECK(v1[4] == 55.f);
        CHECK(v1[5] == 66.f);

        Vector<float, 6> v2 = Vector<float, 6>(5.5f, 11.f, 16.5f, 22.f, 27.5f, 33.f) * 2.f;
        CHECK(v2[0] == 11.f);
        CHECK(v2[1] == 22.f);
        CHECK(v2[2] == 33.f);
        CHECK(v2[3] == 44.f);
        CHECK(v2[4] == 55.f);
        CHECK(v2[5] == 66.f);
    }

    SECTION("Scalar Multiplication Non-Member - Order of operands is preserved")
    {
        std::vector<int> lhsIds;
        std::vector<int> rhsIds;
        Vector<MultiplicationOrderAwareOperand, 6> v6(
            MultiplicationOrderAwareOperand(1, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(2, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(3, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(4, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(5, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(6, lhsIds, rhsIds));
        MultiplicationOrderAwareOperand s(7, lhsIds, rhsIds);
        auto const vl = v6 * s;
        REQUIRE(lhsIds.size() == 6);
        REQUIRE(rhsIds.size() == 6);
        CHECK(std::find(begin(lhsIds), end(lhsIds), 1) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 2) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 3) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 4) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 5) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 6) != end(lhsIds));
        CHECK(rhsIds[0] == 7);
        CHECK(rhsIds[1] == 7);
        CHECK(vl[0].id() == 11);
        CHECK(vl[1].id() == 12);
        CHECK(vl[2].id() == 13);
        CHECK(vl[3].id() == 14);
        CHECK(vl[4].id() == 15);
        CHECK(vl[5].id() == 16);

        lhsIds.clear();
        rhsIds.clear();
        auto const vr = s * v6;
        REQUIRE(lhsIds.size() == 6);
        REQUIRE(rhsIds.size() == 6);
        CHECK(lhsIds[0] == 7);
        CHECK(lhsIds[1] == 7);
        CHECK(std::find(begin(rhsIds), end(rhsIds), 1) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 2) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 3) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 4) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 5) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 6) != end(rhsIds));
        CHECK(vr[0].id() == 17);
        CHECK(vr[1].id() == 17);
        CHECK(vr[2].id() == 17);
        CHECK(vr[3].id() == 17);
        CHECK(vr[4].id() == 17);
        CHECK(vr[5].id() == 17);
    }

    SECTION("Scalar Division Member")
    {
        Vector<float, 6> v1(11.f, 22.f, 33.f, 44.f, 55.f, 66.f);

        v1 /= 2.f;
        CHECK(v1[0] == 5.5f);
        CHECK(v1[1] == 11.f);
        CHECK(v1[2] == 16.5f);
        CHECK(v1[3] == 22.f);
        CHECK(v1[4] == 27.5f);
        CHECK(v1[5] == 33.f);

        // integer vector uses integer division
        Vector<int, 6> vi(11, 22, 33, 44, 55, 66);
        vi /= 2;
        CHECK(vi[0] == 5);
        CHECK(vi[1] == 11);
        CHECK(vi[2] == 16);
        CHECK(vi[3] == 22);
        CHECK(vi[4] == 27);
        CHECK(vi[5] == 33);
    }

    SECTION("Scalar Division Non-Member")
    {
        Vector<float, 6> v2 = Vector<float, 6>(11.f, 22.f, 33.f, 44.f, 55.f, 66.f) / 2.f;
        CHECK(v2[0] == 5.5f);
        CHECK(v2[1] == 11.f);
        CHECK(v2[2] == 16.5f);
        CHECK(v2[3] == 22.f);
        CHECK(v2[4] == 27.5f);
        CHECK(v2[5] == 33.f);

        // integer vector uses integer division
        Vector<int, 6> vi = Vector<int, 6>(11, 22, 33, 44, 55, 66) / 2;
        CHECK(vi[0] == 5);
        CHECK(vi[1] == 11);
        CHECK(vi[2] == 16);
        CHECK(vi[3] == 22);
        CHECK(vi[4] == 27);
        CHECK(vi[5] == 33);
    }

    SECTION("Dot product")
    {
        CHECK(dot(Vector<float, 6>(3.f, 5.f, 9.f, 2.f, -3.f, 4.f),
                  Vector<float, 6>(7.f, 11.f, 0.5f, 4.f, 13.f, 17.f)) == 117.5f);
    }

    SECTION("Vector length")
    {
        CHECK(length(Vector<int, 4>(3, -5, 12, 1)) == std::sqrt(179.0));
        CHECK(length(Vector<float, 4>(3.f, -5.f, 12.f, 1.f)) == std::sqrt(179.f));
        CHECK(length(Vector<long double, 4>(3.0l, -5.0l, 12.0l, 1.0l)) == std::sqrt(static_cast<long double>(179.0)));
    }

    SECTION("Vector normalization")
    {
        CHECK(normalized(Vector<float, 4>(10.f, 0.f, 0.f, 0.f)) == Vector<float, 4>(1.f, 0.f, 0.f, 0.f));
        CHECK(normalized(Vector<float, 4>(0.f, 20.f, 0.f, 0.f)) == Vector<float, 4>(0.f, 1.f, 0.f, 0.f));
        CHECK(normalized(Vector<float, 4>(0.f, 0.f, 30.f, 0.f)) == Vector<float, 4>(0.f, 0.f, 1.f, 0.f));
        CHECK(normalized(Vector<float, 4>(0.f, 0.f, 0.f, 40.f)) == Vector<float, 4>(0.f, 0.f, 0.f, 1.f));
        CHECK(normalized(Vector<float, 4>(-10.f, 0.f, 0.f, 0.f)) == Vector<float, 4>(-1.f, 0.f, 0.f, 0.f));
        CHECK(normalized(Vector<float, 4>(5.f, 5.f, 5.f, 5.f)) ==
            Vector<float, 4>(1.f / std::sqrt(4.f), 1.f / std::sqrt(4.f), 1.f / std::sqrt(4.f), 1.f / std::sqrt(4.f)));
    }

    SECTION("Max component")
    {
        CHECK(max_component(Vector<int, 6>(10, 5, -1, 3, 6, 7)) == 10);
        CHECK(max_component(Vector<int, 6>(10, 50, -1, 3, 6, 7)) == 50);
        CHECK(max_component(Vector<int, 6>(10, 50, 51, 3, 6, 7)) == 51);
        CHECK(max_component(Vector<int, 6>(10, 50, 51, 63, 6, 7)) == 63);
        CHECK(max_component(Vector<int, 6>(10, 50, 51, 63, 64, 7)) == 64);
        CHECK(max_component(Vector<int, 6>(10, 50, 51, 63, 64, 70)) == 70);
    }

    SECTION("Min component")
    {
        CHECK(min_component(Vector<int, 6>(10, 5, -1, 3, 11, 22)) == -1);
        CHECK(min_component(Vector<int, 6>(10, 5, 25, 3, 11, 22)) == 3);
        CHECK(min_component(Vector<int, 6>(10, 5, 25, 30, 11, 22)) == 5);
        CHECK(min_component(Vector<int, 6>(10, 50, 25, 30, 11, 22)) == 10);
        CHECK(min_component(Vector<int, 6>(25, 50, 25, 30, 11, 22)) == 11);
        CHECK(min_component(Vector<int, 6>(25, 50, 25, 30, 110, 22)) == 22);
    }

    SECTION("Construction from Vector2")
    {
        using GHULBUS_MATH_NAMESPACE::Vector2;
        Vector2<float> v2{ 11.f, 22.f };
        Vector v{ v2 };
        static_assert(std::same_as<decltype(v)::ValueType, float>);
        REQUIRE(v.dimension() == 2);
        CHECK(v[0] == 11.f);
        CHECK(v[1] == 22.f);

        Vector2<int> v2i{ 5, 23 };
        Vector vi{ v2i };
        static_assert(std::same_as<decltype(vi)::ValueType, int>);
        REQUIRE(vi.dimension() == 2);
        CHECK(vi[0] == 5);
        CHECK(vi[1] == 23);
    }

    SECTION("Construction from Vector3")
    {
        using GHULBUS_MATH_NAMESPACE::Vector3;
        Vector3<float> v3{ 11.f, 22.f, 33.f };
        Vector v{ v3 };
        static_assert(std::same_as<decltype(v)::ValueType, float>);
        REQUIRE(v.dimension() == 3);
        CHECK(v[0] == 11.f);
        CHECK(v[1] == 22.f);
        CHECK(v[2] == 33.f);

        Vector3<int> v3i{ 5, 23, 42 };
        Vector vi{ v3i };
        static_assert(std::same_as<decltype(vi)::ValueType, int>);
        REQUIRE(vi.dimension() == 3);
        CHECK(vi[0] == 5);
        CHECK(vi[1] == 23);
        CHECK(vi[2] == 42);
    }

    SECTION("Construction from Vector4")
    {
        using GHULBUS_MATH_NAMESPACE::Vector4;
        Vector4<float> v4{ 11.f, 22.f, 33.f, 44.f };
        Vector v{ v4 };
        static_assert(std::same_as<decltype(v)::ValueType, float>);
        REQUIRE(v.dimension() == 4);
        CHECK(v[0] == 11.f);
        CHECK(v[1] == 22.f);
        CHECK(v[2] == 33.f);
        CHECK(v[3] == 44.f);

        Vector4<int> v4i{ 5, 23, 42, 64 };
        Vector vi{ v4i };
        static_assert(std::same_as<decltype(vi)::ValueType, int>);
        REQUIRE(vi.dimension() == 4);
        CHECK(vi[0] == 5);
        CHECK(vi[1] == 23);
        CHECK(vi[2] == 42);
        CHECK(vi[3] == 64);
    }
}
