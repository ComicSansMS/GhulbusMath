#include <gbMath/Vector2.hpp>

#include <catch.hpp>

#include <random>
#include <vector>

namespace {
/* Helper type to track order of operands in multiplication operations */
struct MultiplicationOrderAwareOperand {
private:
    int id_;
    std::vector<int>* lhsIds_;
    std::vector<int>* rhsIds_;
public:
    MultiplicationOrderAwareOperand(int id, std::vector<int>& lhsIds, std::vector<int>& rhsIds)
        :id_(id), lhsIds_(&lhsIds), rhsIds_(&rhsIds)
    {}

    int id() const {
        return id_;
    }

    MultiplicationOrderAwareOperand operator*(MultiplicationOrderAwareOperand const& rhs) const {
        lhsIds_->push_back(id());
        rhsIds_->push_back(rhs.id());
        return MultiplicationOrderAwareOperand(id_ + 10, *lhsIds_, *rhsIds_);
    }
};
}

TEST_CASE("Vector2")
{
    using GHULBUS_MATH_NAMESPACE::Vector2;
    std::mt19937 gen(42);

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
    }

    SECTION("Less-than comparison (lexicographic order)")
    {
        // first element takes precedence
        CHECK(Vector2<float>(1.0f, 2.0f) < Vector2<float>(3.0f, 4.0f));
        CHECK(Vector2<float>(1.0f, 4.0f) < Vector2<float>(3.0f, 2.0f));
        CHECK(!(Vector2<float>(3.0f, 2.0f) < Vector2<float>(1.0f, 4.0f)));
        CHECK(!(Vector2<float>(3.0f, 4.0f) < Vector2<float>(1.0f, 2.0f)));
        // second element used if first element is equal
        CHECK(Vector2<float>(1.0f, 2.0f) < Vector2<float>(1.0f, 4.0f));
        CHECK(!(Vector2<float>(1.0f, 2.0f) < Vector2<float>(1.0f, 1.0f)));
        // not less if both equal
        CHECK(!(Vector2<float>(1.0f, 1.0f) < Vector2<float>(1.0f, 1.0f)));
    }

    SECTION("Greater-than comparison (lexicographic order)")
    {
        // first element takes precedence
        CHECK(!(Vector2<float>(1.0f, 2.0f) > Vector2<float>(3.0f, 4.0f)));
        CHECK(!(Vector2<float>(1.0f, 4.0f) > Vector2<float>(3.0f, 2.0f)));
        CHECK(Vector2<float>(3.0f, 2.0f) > Vector2<float>(1.0f, 4.0f));
        CHECK(Vector2<float>(3.0f, 4.0f) > Vector2<float>(1.0f, 2.0f));
        // second element used if first element is equal
        CHECK(!(Vector2<float>(1.0f, 2.0f) > Vector2<float>(1.0f, 4.0f)));
        CHECK(Vector2<float>(1.0f, 2.0f) > Vector2<float>(1.0f, 1.0f));
        // not greater if both equal
        CHECK(!(Vector2<float>(1.0f, 1.0f) > Vector2<float>(1.0f, 1.0f)));
    }

    SECTION("Less-or-equal comparison (lexicographic order)")
    {
        // first element takes precedence
        CHECK(Vector2<float>(1.0f, 2.0f) <= Vector2<float>(3.0f, 4.0f));
        CHECK(Vector2<float>(1.0f, 4.0f) <= Vector2<float>(3.0f, 2.0f));
        CHECK(!(Vector2<float>(3.0f, 2.0f) <= Vector2<float>(1.0f, 4.0f)));
        CHECK(!(Vector2<float>(3.0f, 4.0f) <= Vector2<float>(1.0f, 2.0f)));
        // second element used if first element is equal
        CHECK(Vector2<float>(1.0f, 2.0f) <= Vector2<float>(1.0f, 4.0f));
        CHECK(!(Vector2<float>(1.0f, 2.0f) <= Vector2<float>(1.0f, 1.0f)));
        // not less if both equal
        CHECK(Vector2<float>(1.0f, 1.0f) <= Vector2<float>(1.0f, 1.0f));
    }

    SECTION("Greater-or-equal comparison (lexicographic order)")
    {
        // first element takes precedence
        CHECK(!(Vector2<float>(1.0f, 2.0f) >= Vector2<float>(3.0f, 4.0f)));
        CHECK(!(Vector2<float>(1.0f, 4.0f) >= Vector2<float>(3.0f, 2.0f)));
        CHECK(Vector2<float>(3.0f, 2.0f) >= Vector2<float>(1.0f, 4.0f));
        CHECK(Vector2<float>(3.0f, 4.0f) >= Vector2<float>(1.0f, 2.0f));
        // second element used if first element is equal
        CHECK(!(Vector2<float>(1.0f, 2.0f) >= Vector2<float>(1.0f, 4.0f)));
        CHECK(Vector2<float>(1.0f, 2.0f) >= Vector2<float>(1.0f, 1.0f));
        // not greater if both equal
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
    }

    SECTION("Scalar Division Non-Member")
    {
        Vector2<float> v2 = Vector2<float>(11.f, 22.f) / 2.f;
        CHECK(v2.x == 5.5f);
        CHECK(v2.y == 11.f);
    }

}
