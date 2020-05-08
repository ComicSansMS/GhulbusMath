#include <gbMath/Vector2.hpp>
#include <gbMath/VectorIO.hpp>

#include <test_utils/MultiplicationOrderAwareOperand.hpp>

#include <catch.hpp>

#include <type_traits>
#include <vector>

TEST_CASE("Vector2")
{
    using GHULBUS_MATH_NAMESPACE::Normal2;
    using GHULBUS_MATH_NAMESPACE::Point2;
    using GHULBUS_MATH_NAMESPACE::Vector2;

    SECTION("Value initialization initializes to 0")
    {
        Vector2<float> v{};

        CHECK(v.x == 0.0f);
        CHECK(v.y == 0.0f);
    }

    SECTION("Construction from 2 values")
    {
        Vector2<float> v(42.0f, 23.5f);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
    }

    SECTION("Copy construction")
    {
        Vector2<float> v(42.0f, 23.5f);

        Vector2<float> v2(v);
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
    }

    SECTION("Copy assignment")
    {
        Vector2<float> v(42.0f, 23.5f);

        Vector2<float> v2;

        v2 = v;
        CHECK(v2.x == 42.0f);
        CHECK(v2.y == 23.5f);
    }

    SECTION("Construction from array")
    {
        float arr[] = { 42.0f, 23.5f };
        Vector2<float> v(arr);

        CHECK(v.x == 42.0f);
        CHECK(v.y == 23.5f);
    }

    SECTION("Conversion construction")
    {
        Vector2<float> v(42.f, 23.5f);

        Vector2<int> vi(v);
        CHECK(vi.x == 42);
        CHECK(vi.y == 23);
    }

    SECTION("Equality and not-equal comparisons")
    {
        Vector2<float> v(42.0f, 23.5f);
        Vector2<float> v2(v);

        CHECK(v == v2);
        v2.x = 55.0f;
        CHECK_FALSE(v == v2);

        CHECK(v != v2);
        v.x = v2.x;
        CHECK_FALSE(v != v2);

        v2.y = 55.0f;
        CHECK_FALSE(v == v2);
        CHECK(v != v2);
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        // first element takes precedence
        CHECK(Vector2<float>(1.0f, 2.0f) < Vector2<float>(3.0f, 4.0f));
        CHECK(Vector2<float>(1.0f, 4.0f) < Vector2<float>(3.0f, 2.0f));
        CHECK_FALSE(Vector2<float>(3.0f, 2.0f) < Vector2<float>(1.0f, 4.0f));
        CHECK_FALSE(Vector2<float>(3.0f, 4.0f) < Vector2<float>(1.0f, 2.0f));
        // second element used if first element is equal
        CHECK(Vector2<float>(1.0f, 2.0f) < Vector2<float>(1.0f, 4.0f));
        CHECK_FALSE(Vector2<float>(1.0f, 2.0f) < Vector2<float>(1.0f, 1.0f));
        // not less if both equal
        CHECK_FALSE(Vector2<float>(1.0f, 1.0f) < Vector2<float>(1.0f, 1.0f));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        // first element takes precedence
        CHECK_FALSE(Vector2<float>(1.0f, 2.0f) > Vector2<float>(3.0f, 4.0f));
        CHECK_FALSE(Vector2<float>(1.0f, 4.0f) > Vector2<float>(3.0f, 2.0f));
        CHECK(Vector2<float>(3.0f, 2.0f) > Vector2<float>(1.0f, 4.0f));
        CHECK(Vector2<float>(3.0f, 4.0f) > Vector2<float>(1.0f, 2.0f));
        // second element used if first element is equal
        CHECK_FALSE(Vector2<float>(1.0f, 2.0f) > Vector2<float>(1.0f, 4.0f));
        CHECK(Vector2<float>(1.0f, 2.0f) > Vector2<float>(1.0f, 1.0f));
        // not greater if both equal
        CHECK_FALSE(Vector2<float>(1.0f, 1.0f) > Vector2<float>(1.0f, 1.0f));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        // first element takes precedence
        CHECK(Vector2<float>(1.0f, 2.0f) <= Vector2<float>(3.0f, 4.0f));
        CHECK(Vector2<float>(1.0f, 4.0f) <= Vector2<float>(3.0f, 2.0f));
        CHECK_FALSE(Vector2<float>(3.0f, 2.0f) <= Vector2<float>(1.0f, 4.0f));
        CHECK_FALSE(Vector2<float>(3.0f, 4.0f) <= Vector2<float>(1.0f, 2.0f));
        // second element used if first element is equal
        CHECK(Vector2<float>(1.0f, 2.0f) <= Vector2<float>(1.0f, 4.0f));
        CHECK_FALSE(Vector2<float>(1.0f, 2.0f) <= Vector2<float>(1.0f, 1.0f));
        // both equal
        CHECK(Vector2<float>(1.0f, 1.0f) <= Vector2<float>(1.0f, 1.0f));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        // first element takes precedence
        CHECK_FALSE(Vector2<float>(1.0f, 2.0f) >= Vector2<float>(3.0f, 4.0f));
        CHECK_FALSE(Vector2<float>(1.0f, 4.0f) >= Vector2<float>(3.0f, 2.0f));
        CHECK(Vector2<float>(3.0f, 2.0f) >= Vector2<float>(1.0f, 4.0f));
        CHECK(Vector2<float>(3.0f, 4.0f) >= Vector2<float>(1.0f, 2.0f));
        // second element used if first element is equal
        CHECK_FALSE(Vector2<float>(1.0f, 2.0f) >= Vector2<float>(1.0f, 4.0f));
        CHECK(Vector2<float>(1.0f, 2.0f) >= Vector2<float>(1.0f, 1.0f));
        // both equal
        CHECK(Vector2<float>(1.0f, 1.0f) >= Vector2<float>(1.0f, 1.0f));
    }

    SECTION("Array index operator")
    {
        Vector2<float> v(42.0f, 23.5f);
        CHECK(v[0] == 42.0f);
        CHECK(v[1] == 23.5f);
        v[1] = 55.0f;
        CHECK(v[1] == 55.0f);

        Vector2<float> v_arr[] = { Vector2<float>(1.0f, 2.0f), Vector2<float>(3.0f, 4.0f) };
        CHECK(v_arr[0][0] == 1.0f);
        CHECK(v_arr[0][1] == 2.0f);
        CHECK(v_arr[1][0] == 3.0f);
        CHECK(v_arr[1][1] == 4.0f);
    }

    SECTION("Array index const operator")
    {
        Vector2<float> const v_const(42.0f, 23.5f);
        CHECK(v_const[0] == 42.0f);
        CHECK(v_const[1] == 23.5f);
    }

    SECTION("Vector Addition Member")
    {
        Vector2<float> v1(11.f, 22.f);
        v1 += Vector2<float>(33.f, 44.f);

        CHECK(v1.x == 44.f);
        CHECK(v1.y == 66.f);
        CHECK((v1 += Vector2<float>()) == v1);

        auto const& v_ref = (v1 += Vector2<float>());
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Addition Non-Member")
    {
        Vector2<float> v = Vector2<float>(11.f, 22.f) + Vector2<float>(33.f, 44.f);

        CHECK(v.x == 44.f);
        CHECK(v.y == 66.f);
    }

    SECTION("Vector Subtraction Member")
    {
        Vector2<float> v1(11.f, 22.f);
        v1 -= Vector2<float>(5.f, 14.f);

        CHECK(v1.x == 6.f);
        CHECK(v1.y == 8.f);
        CHECK((v1 -= Vector2<float>()) == v1);

        auto const& v_ref = (v1 -= Vector2<float>());
        CHECK(&v_ref == &v1);
    }

    SECTION("Vector Subtraction Non-Member")
    {
        Vector2<float> v = Vector2<float>(11.f, 22.f) - Vector2<float>(5.f, 14.f);

        CHECK(v.x == 6.f);
        CHECK(v.y == 8.f);
    }

    SECTION("Scalar Multiplication Member")
    {
        Vector2<float> v1(5.5f, 11.f);

        v1 *= 2.f;
        CHECK(v1.x == 11.f);
        CHECK(v1.y == 22.f);
    }

    SECTION("Scalar Multiplication Non-Member")
    {
        Vector2<float> v1 = 2.f * Vector2<float>(5.5f, 11.f);
        CHECK(v1.x == 11.f);
        CHECK(v1.y == 22.f);

        Vector2<float> v2 = Vector2<float>(5.5f, 11.f) * 2.f;
        CHECK(v2.x == 11.f);
        CHECK(v2.y == 22.f);
    }

    SECTION("Scalar Multiplication Non-Member - Order of operands is preserved")
    {
        std::vector<int> lhsIds;
        std::vector<int> rhsIds;
        Vector2<MultiplicationOrderAwareOperand> v3(
            MultiplicationOrderAwareOperand(1, lhsIds, rhsIds),
            MultiplicationOrderAwareOperand(2, lhsIds, rhsIds));
        MultiplicationOrderAwareOperand s(3, lhsIds, rhsIds);
        v3 * s;
        REQUIRE(lhsIds.size() == 2);
        REQUIRE(rhsIds.size() == 2);
        CHECK(std::find(begin(lhsIds), end(lhsIds), 1) != end(lhsIds));
        CHECK(std::find(begin(lhsIds), end(lhsIds), 2) != end(lhsIds));
        CHECK(rhsIds[0] == 3);
        CHECK(rhsIds[1] == 3);

        lhsIds.clear();
        rhsIds.clear();
        s * v3;
        REQUIRE(lhsIds.size() == 2);
        REQUIRE(rhsIds.size() == 2);
        CHECK(lhsIds[0] == 3);
        CHECK(lhsIds[1] == 3);
        CHECK(std::find(begin(rhsIds), end(rhsIds), 1) != end(rhsIds));
        CHECK(std::find(begin(rhsIds), end(rhsIds), 2) != end(rhsIds));
    }

    SECTION("Scalar Division Member")
    {
        Vector2<float> v1(11.f, 22.f);

        v1 /= 2.f;
        CHECK(v1.x == 5.5f);
        CHECK(v1.y == 11.f);

        // integer vector uses integer division
        Vector2<int> vi(11, 22);
        vi /= 2;
        CHECK(vi.x == 5);
        CHECK(vi.y == 11);
    }

    SECTION("Scalar Division Non-Member")
    {
        Vector2<float> v2 = Vector2<float>(11.f, 22.f) / 2.f;
        CHECK(v2.x == 5.5f);
        CHECK(v2.y == 11.f);

        // integer vector uses integer division
        Vector2<int> vi = Vector2<int>(11, 22) / 2;
        CHECK(vi.x == 5);
        CHECK(vi.y == 11);
    }

    SECTION("Dot product")
    {
        CHECK(dot(Vector2<float>(3.f, 5.f), Vector2<float>(7.f, 11.f)) == 76.f);
    }

    SECTION("Vector length")
    {
        CHECK(length(Vector2<int>(3, -5)) == Approx(std::sqrt(34.0)));
        CHECK(length(Vector2<float>(3.f, -5.f)) == Approx(std::sqrt(34.f)));
        CHECK(length(Vector2<long double>(3.0, -5.0)) == Approx(std::sqrt(static_cast<long double>(34.0))));
    }

    SECTION("Vector normalization")
    {
        CHECK(normalized(Vector2<float>(10.f, 0.f)) == Vector2<float>(1.f, 0.f));
        CHECK(normalized(Vector2<float>(0.f, 10.f)) == Vector2<float>(0.f, 1.f));
        CHECK(normalized(Vector2<float>(-10.f, 0.f)) == Vector2<float>(-1.f, 0.f));
        CHECK(normalized(Vector2<float>(5.f, 5.f)) == Vector2<float>(1.f / std::sqrt(2.f), 1.f / std::sqrt(2.f)));
    }

    SECTION("Perp vector")
    {
        Vector2<float> v(1.f, 2.f);
        CHECK(perp(v) == Normal2<float>(-2.f, 1.f));
    }

    SECTION("Perp-dot product")
    {
        Vector2<float> v1(1.f, 2.f);
        Vector2<float> v2(4.f, 8.f);
        CHECK(perp_dot(v1, v2) == 0.f);

        Vector2<float> v3(3.f, 4.f);
        CHECK(perp_dot(v1, v3) == -2.f);
    }

    SECTION("Angle between two Vectors")
    {
        // 90 degrees
        {
            Vector2<float> v1(5.f, 0.f);
            Vector2<float> v2(0.f, 20.f);
            CHECK(angle_vector(v1, v2) == Approx(std::acos(0.f)));
        }
        // 45 degrees
        {
            Vector2<float> v1(1.f, 1.f);
            Vector2<float> v2(0.f, 20.f);
            CHECK(angle_vector(v1, v2) == Approx(std::acos(std::sqrt(0.5f))));
        }
        // 180 degrees
        {
            Vector2<float> v1(1.f, 1.f);
            Vector2<float> v2(-10.f, -10.f);
            CHECK(angle_vector(v1, v2) == Approx(std::acos(-1.f)));
        }
    }

    SECTION("Angle between two Unit Vectors")
    {
        // 90 degrees
        {
            Vector2<float> v1(1.f, 0.f);
            Vector2<float> v2(0.f, 1.f);
            CHECK(angle_vector_unit(v1, v2) == std::acos(0.f));
        }
        // 45 degrees
        {
            Vector2<float> v1(std::sqrt(0.5f), std::sqrt(0.5f));
            Vector2<float> v2(0.f, 1.f);
            CHECK(angle_vector_unit(v1, v2) == std::acos(std::sqrt(0.5f)));
        }
        // 180 degrees
        {
            Vector2<float> v1(1.f, 0.f);
            Vector2<float> v2(-1.f, 0.f);
            CHECK(angle_vector_unit(v1, v2) == std::acos(-1.f));
        }
    }

    SECTION("Projection")
    {
        {
            Vector2<float> v1(1.f, 2.f);
            Vector2<float> v2(5.f, 0.f);
            Vector2<float> v3(0.f, 5.f);
            CHECK(project(v1, v2) == Vector2<float>(1.f, 0.f));
            CHECK(project(v1, v3) == Vector2<float>(0.f, 2.f));
        }
        {
            Vector2<float> v1(1.f, 2.f);
            Vector2<float> v2(1.f, 1.f);
            CHECK(project(v1, v2) == Vector2<float>(1.5f, 1.5f));
        }
    }

    SECTION("Projection Unit Vector")
    {
        {
            Vector2<float> v1(1.f, 2.f);
            Vector2<float> v2(1.f, 0.f);
            Vector2<float> v3(0.f, 1.f);
            CHECK(project_unit(v1, v2) == Vector2<float>(1.f, 0.f));
            CHECK(project_unit(v1, v3) == Vector2<float>(0.f, 2.f));
        }
        {
            Vector2<float> v1(1.f, 2.f);
            Vector2<float> v2(std::sqrt(0.5f), std::sqrt(0.5f));
            Vector2<float> proj = project_unit(v1, v2);
            CHECK(std::abs(proj.x - 1.5f) <= std::numeric_limits<float>::epsilon());
            CHECK(std::abs(proj.y - 1.5f) <= std::numeric_limits<float>::epsilon());
        }
    }

    SECTION("Rejection")
    {
        {
            Vector2<float> v1(1.f, 2.f);
            Vector2<float> v2(5.f, 0.f);
            Vector2<float> v3(0.f, 5.f);
            CHECK(reject(v1, v2) == Vector2<float>(0.f, 2.f));
            CHECK(reject(v1, v3) == Vector2<float>(1.f, 0.f));
        }
        {
            Vector2<float> v1(1.f, 2.f);
            Vector2<float> v2(1.f, 1.f);
            CHECK(reject(v1, v2) == Vector2<float>(-0.5f, 0.5f));
        }
    }

    SECTION("Rejection Unit Vector")
    {
        {
            Vector2<float> v1(1.f, 2.f);
            Vector2<float> v2(1.f, 0.f);
            Vector2<float> v3(0.f, 1.f);
            CHECK(reject_unit(v1, v2) == Vector2<float>(0.f, 2.f));
            CHECK(reject_unit(v1, v3) == Vector2<float>(1.f, 0.f));
        }
        {
            Vector2<float> v1(1.f, 2.f);
            Vector2<float> v2(std::sqrt(0.5f), std::sqrt(0.5f));
            Vector2<float> rej = reject_unit(v1, v2);
            CHECK(std::abs(rej.x + 0.5f) <= std::numeric_limits<float>::epsilon());
            CHECK(std::abs(rej.y - 0.5f) <= std::numeric_limits<float>::epsilon());
        }
    }

    SECTION("Mixing Points, Vectors, and Normals")
    {
        Point2<float> p(1.f, 2.f);
        Vector2<float> v(3.f, 4.f);
        Normal2<float> n(5.f, 6.f);

        p += v;
        CHECK(p.x == 4.f);
        CHECK(p.y == 6.f);

        p += n;
        CHECK(p.x == 9.f);
        CHECK(p.y == 12.f);

        p -= v;
        CHECK(p.x == 6.f);
        CHECK(p.y == 8.f);

        p -= n;
        CHECK(p.x == 1.f);
        CHECK(p.y == 2.f);

        {
            auto p2 = p + v;
            static_assert(std::is_same<decltype(p2)::Tag, GHULBUS_MATH_NAMESPACE::VectorTag::Point>::value,
                          "Point + Vector is Point.");
            CHECK(p2.x == 4.f);
            CHECK(p2.y == 6.f);
        }
        {
            auto p2 = v + p;
            static_assert(std::is_same<decltype(p2)::Tag, GHULBUS_MATH_NAMESPACE::VectorTag::Point>::value,
                          "Vector + Point is Point.");
            CHECK(p2.x == 4.f);
            CHECK(p2.y == 6.f);
        }
        {
            auto p2 = p + n;
            static_assert(std::is_same<decltype(p2)::Tag, GHULBUS_MATH_NAMESPACE::VectorTag::Point>::value,
                          "Point + Normal is Point.");
            CHECK(p2.x == 6.f);
            CHECK(p2.y == 8.f);
        }
        {
            auto p2 = n + p;
            static_assert(std::is_same<decltype(p2)::Tag, GHULBUS_MATH_NAMESPACE::VectorTag::Point>::value,
                          "Normal + Point is Point.");
            CHECK(p2.x == 6.f);
            CHECK(p2.y == 8.f);
        }
        {
            auto p2 = p - v;
            static_assert(std::is_same<decltype(p2)::Tag, GHULBUS_MATH_NAMESPACE::VectorTag::Point>::value,
                          "Point - Vector is Point.");
            CHECK(p2.x == -2.f);
            CHECK(p2.y == -2.f);
        }
        {
            auto p2 = p - n;
            static_assert(std::is_same<decltype(p2)::Tag, GHULBUS_MATH_NAMESPACE::VectorTag::Point>::value,
                          "Point - Normal is Point.");
            CHECK(p2.x == -4.f);
            CHECK(p2.y == -4.f);
        }
        {
            auto p2 = p + v;
            auto v2 = p2 - p;
            static_assert(std::is_same<decltype(v2)::Tag, GHULBUS_MATH_NAMESPACE::VectorTag::Vector>::value,
                          "Point - Point is Vector.");
            CHECK(v2.x == v.x);
            CHECK(v2.y == v.y);
        }
    }

    SECTION("Points and Normals can be converted to Vectors")
    {
        CHECK(Point2<float>(1.f, 2.f).to_vector() == Vector2<float>(1.f, 2.f));
        CHECK(Normal2<float>(1.f, 2.f).to_vector() == Vector2<float>(1.f, 2.f));
    }

    SECTION("Points and Normals can be constructed from Vectors")
    {
        CHECK(Point2<float>::from_vector(Vector2<float>(1.f, 2.f)) == Point2<float>(1.f, 2.f));
        CHECK(Normal2<float>::from_vector(Vector2<float>(1.f, 2.f)) == Normal2<float>(1.f, 2.f));
        CHECK(Normal2<float>::from_vector(Point2<float>(1.f, 2.f).to_vector()) == Normal2<float>(1.f, 2.f));
    }

    SECTION("Max component")
    {
        CHECK(max_component(Vector2<int>(10, 5)) == 10);
        CHECK(max_component(Vector2<int>(10, 50)) == 50);
    }

    SECTION("Min component")
    {
        CHECK(min_component(Vector2<int>(10, 5)) == 5);
        CHECK(min_component(Vector2<int>(10, 50)) == 10);
    }

    SECTION("Linear interpolation")
    {
        CHECK(lerp(Vector2<float>(0.f, 0.f), Vector2<float>(1.f, 2.f), 0.5f) == Vector2<float>(0.5f, 1.f));
        CHECK(lerp(Vector2<float>(5.f, 2.f), Vector2<float>(1.f, 2.f), 0.25f) == Vector2<float>(4.f, 2.f));
    }
}
