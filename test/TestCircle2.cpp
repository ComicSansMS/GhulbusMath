#include <gbMath/Circle2.hpp>
#include <gbMath/VectorIO.hpp>

#include <catch.hpp>

#include <limits>

TEST_CASE("Circle2")
{
    using GHULBUS_MATH_NAMESPACE::Circle2;
    using GHULBUS_MATH_NAMESPACE::Point2;
    using GHULBUS_MATH_NAMESPACE::Line2;
    using GHULBUS_MATH_NAMESPACE::Vector2;

    SECTION("Value initialization initializes to 0")
    {
        Circle2<int> circle{};
        CHECK(circle.center == Point2<int>(0, 0));
        CHECK(circle.radius == 0);
    }

    SECTION("Construction from point and radius")
    {
        Circle2<float> c(Point2<float>(1.f, 2.f), 3.f);
        CHECK(c.center == Point2<float>(1.f, 2.f));
        CHECK(c.radius == 3.f);
    }

    SECTION("Point-circle collision test")
    {
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 1.f), 2.f),
                       Point2<float>(2.f, 1.f)));
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 1.f), 2.f),
                       Point2<float>(3.f, 1.f)));
        CHECK(!collides(Circle2<float>(Point2<float>(1.f, 1.f), 2.f),
                        Point2<float>(3.f + 1.e-6f, 1.f)));
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 2.f), 2.f + 1e-6f),
                       Point2<float>(1.f + std::sqrt(2.f), 2.f + std::sqrt(2.f))));
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 2.f), 2.f + 1e-6f),
                       Point2<float>(1.f + std::sqrt(2.f), 2.f)));
        CHECK(!collides(Circle2<float>(Point2<float>(1.f, 2.f), 2.f),
                        Point2<float>(1.f + std::sqrt(2.f), 2.f + std::sqrt(2.f))));
    }

    SECTION("Circle-Circle collision test")
    {
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 1.f), 2.f),
                         Circle2<float>(Point2<float>(1.f, 1.f), 2.f)));
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 1.f), 2.f),
                         Circle2<float>(Point2<float>(5.f, 1.f), 2.f)));
        CHECK(!collides(Circle2<float>(Point2<float>(1.f, 1.f), 2.f),
                          Circle2<float>(Point2<float>(5.f + 1.e-6f, 1.f), 2.f)));
        CHECK(!collides(Circle2<float>(Point2<float>(1.f, 1.f), 2.f),
                          Circle2<float>(Point2<float>(5.f, 1.f + 1.e-3f), 2.f)));
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 2.f), 1.f + 1e-6f),
                         Circle2<float>(Point2<float>(1.f + std::sqrt(2.f), 2.f + std::sqrt(2.f)), 1.f)));
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 2.f), 1.f + 1e-6f),
                         Circle2<float>(Point2<float>(1.f + std::sqrt(2.f), 2.f), 1.f)));
        CHECK(collides(Circle2<float>(Point2<float>(1.f, 2.f), 1.f + 1e-6f),
                         Circle2<float>(Point2<float>(1.f, 2.f + std::sqrt(2.f)), 1.f)));
        CHECK(!collides(Circle2<float>(Point2<float>(1.f, 2.f), 1.f),
                          Circle2<float>(Point2<float>(1.f + std::sqrt(2.f), 2.f + std::sqrt(2.f)), 1.f)));
    }

    SECTION("Circle2Line2Intersection Zero Initialisation")
    {
        using GHULBUS_MATH_NAMESPACE::Circle2Line2Intersection;
        Circle2Line2Intersection<int> cli{};
        CHECK(cli.a == 0);
        CHECK(cli.b == 0);
        CHECK(cli.c == 0);
    }

    SECTION("Circle2Line2Intersection Construction From Values")
    {
        using GHULBUS_MATH_NAMESPACE::Circle2Line2Intersection;
        Circle2Line2Intersection<int> cli(1, 2, 3);
        CHECK(cli.a == 1);
        CHECK(cli.b == 2);
        CHECK(cli.c == 3);
    }

    SECTION("Circle2Line2Intersection Copy Construction")
    {
        using GHULBUS_MATH_NAMESPACE::Circle2Line2Intersection;
        Circle2Line2Intersection<int> cli(1, 2, 3);
        Circle2Line2Intersection<int> cli2(cli);
        CHECK(cli2.a == 1);
        CHECK(cli2.b == 2);
        CHECK(cli2.c == 3);
    }

    SECTION("Circle2Line2Intersection Copy Assignment")
    {
        using GHULBUS_MATH_NAMESPACE::Circle2Line2Intersection;
        Circle2Line2Intersection<int> cli(1, 2, 3);
        cli = Circle2Line2Intersection<int>(4, 5, 6);
        CHECK(cli.a == 4);
        CHECK(cli.b == 5);
        CHECK(cli.c == 6);
    }

    SECTION("Circle2Line2Intersection Discriminant Check")
    {
        using GHULBUS_MATH_NAMESPACE::Circle2Line2Intersection;
        Circle2Line2Intersection<int> cli(0, 0, 0);
        CHECK(cli);
        cli = Circle2Line2Intersection<int>(1, 2, 3);
        CHECK_FALSE(cli);
        cli = Circle2Line2Intersection<int>(1, 3, 2);
        CHECK(cli);
        cli = Circle2Line2Intersection<int>(12, 54, 5);
        CHECK(cli);
        cli = Circle2Line2Intersection<int>(1, -2, 2);
        CHECK_FALSE(cli);
        cli = Circle2Line2Intersection<int>(1, -2, 1);
        CHECK(cli);
        cli = Circle2Line2Intersection<int>(1, 2, -1);
        CHECK(cli);
        cli = Circle2Line2Intersection<int>(3, 6, 3);
        CHECK(cli);
    }

    SECTION("Circle2Line2Intersection Parameter Evaluation")
    {
        using GHULBUS_MATH_NAMESPACE::Circle2Line2Intersection;
        Circle2Line2Intersection<int> cli(1, 3, 2);
        CHECK(cli.evaluateT().t1 == -1);
        CHECK(cli.evaluateT().t2 == -2);
        cli = Circle2Line2Intersection<int>(64, 32, 4);
        CHECK(cli.evaluateT<double>().t1 == -0.25);
        CHECK(cli.evaluateT<double>().t2 == -0.25);
    }

    SECTION("Circle-Line Intersection")
    {
        Circle2<float> c(Point2<float>(1.f, 1.f), 2.f);
        {
            // Radius parallel X
            Line2<float> l(Point2<float>(1.f, 1.f), Vector2<float>(1.f, 0.f));
            auto const intersection = intersect(c, l);
            CHECK(intersection);
            CHECK(intersection.evaluateT().t1 == 2.0f);
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1) == Point2<float>(3.f, 1.f));
            CHECK(intersection.evaluateT().t2 == -2.0f);
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2) == Point2<float>(-1.f, 1.f));
        }
        {
            // Radius parallel Y
            Line2<float> l(Point2<float>(1.f, 1.f), Vector2<float>(0.f, 1.f));
            auto const intersection = intersect(c, l);
            CHECK(intersection);
            CHECK(intersection.evaluateT().t1 == 2.0f);
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1) == Point2<float>(1.f, 3.f));
            CHECK(intersection.evaluateT().t2 == -2.0f);
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2) == Point2<float>(1.f, -1.f));
        }
        {
            // X-Axis
            Line2<float> l(Point2<float>(0.f, 0.f), Vector2<float>(1.f, 0.f));
            auto const intersection = intersect(c, l);
            CHECK(intersection);
            CHECK(intersection.evaluateT().t1 == Approx(2.73205f));
            CHECK(intersection.evaluateT().t2 == Approx(-0.73205f));
        }
        {
            // Y-Axis
            Line2<float> l(Point2<float>(0.f, 0.f), Vector2<float>(0.f, 1.f));
            auto const intersection = intersect(c, l);
            CHECK(intersection);
            CHECK(intersection.evaluateT().t1 == Approx(2.73205f));
            CHECK(intersection.evaluateT().t2 == Approx(-0.73205f));
        }
        {
            // Line origin inside circle
            Line2<float> l(Point2<float>(0.25f, 0.5f), Vector2<float>(-1.f, 1.f));
            auto const intersection = intersect(c, l);
            CHECK(intersection);
            CHECK(intersection.evaluateT().t1 == Approx(1.14361f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1).x == Approx(-0.893611f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1).y == Approx(1.64361));
            CHECK(intersection.evaluateT().t2 == Approx(-1.39361f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2).x == Approx(1.64361));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2).y == Approx(-0.893611f));
        }
        {
            // Line origin inside circle
            Line2<float> l(Point2<float>(1.5f, 0.5f), Vector2<float>(1.f, 2.5f));
            auto const intersection = intersect(c, l);
            CHECK(intersection);
            CHECK(intersection.evaluateT().t1 == Approx(0.80592f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1).x == Approx(2.30592f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1).y == Approx(2.51479f));
            CHECK(intersection.evaluateT().t2 == Approx(-0.59902f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2).x == Approx(0.90098f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2).y == Approx(-0.99755f));
        }
        {
            // Line origin outside circle
            Line2<float> l(Point2<float>(-2.f, 4.f), Vector2<float>(3.f, -1.f));
            auto const intersection = intersect(c, l);
            CHECK(intersection);
            CHECK(intersection.evaluateT().t1 == Approx(1.4f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1).x == Approx(2.2f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1).y == Approx(2.6f));
            CHECK(intersection.evaluateT().t2 == Approx(1.f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2).x == Approx(1.f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2).y == Approx(3.f));
        }
        {
            // Tangent
            Line2<float> l(Point2<float>(0.f, -1.f), Vector2<float>(1.f, 0.f));
            auto const intersection = intersect(c, l);
            CHECK(intersection);
            CHECK(intersection.evaluateT().t1 == Approx(1.f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1).x == Approx(1.f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t1).y == Approx(-1.f));
            CHECK(intersection.evaluateT().t2 == Approx(1.f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2).x == Approx(1.f));
            CHECK(l.evaluate_at_parameter(intersection.evaluateT().t2).y == Approx(-1.f));
        }
        {
            // No intersection
            Line2<float> l(Point2<float>(0.f, -1.f), Vector2<float>(-1.f, 1.f));
            auto const intersection = intersect(c, l);
            CHECK_FALSE(intersection);
            CHECK(std::isnan(intersection.evaluateT().t1));
            CHECK(std::isnan(intersection.evaluateT().t2));
        }
        {
            // No intersection
            Line2<float> l(Point2<float>(55.f, -3.f), Vector2<float>(-12.f, 20.f));
            auto const intersection = intersect(c, l);
            CHECK_FALSE(intersection);
            CHECK(std::isnan(intersection.evaluateT().t1));
            CHECK(std::isnan(intersection.evaluateT().t2));
        }
    }

    SECTION("Circle-Circle Intersection")
    {
        Circle2<float> c1(Point2<float>(1.f, 1.f), 2.f);
        Circle2<float> c2(Point2<float>(2.f, 4.f), 3.f);
        Circle2<float> c3(Point2<float>(-5.5f, 1.f), 4.5f);
        Circle2<float> c4(Point2<float>(-7.f, 2.f), 2.f);
        {
            // 2 intersection points
            auto intersection = intersect(c1, c2);
            CHECK(intersection.p1.x == Approx(2.99284f));
            CHECK(intersection.p1.y == Approx(1.16905f));
            CHECK(intersection.p2.x == Approx(-0.49284f));
            CHECK(intersection.p2.y == Approx(2.33095f));
            // symmetric
            intersection = intersect(c2, c1);
            CHECK(intersection.p2.x == Approx(2.99284f));
            CHECK(intersection.p2.y == Approx(1.16905f));
            CHECK(intersection.p1.x == Approx(-0.49284f));
            CHECK(intersection.p1.y == Approx(2.33095f));
        }
        {
            // single intersection point
            auto intersection = intersect(c1, c3);
            CHECK(intersection.p1.x == Approx(-1.f));
            CHECK(intersection.p1.y == Approx(1.f));
            CHECK(intersection.p2.x == Approx(-1.f));
            CHECK(intersection.p2.y == Approx(1.f));
            // symmetric
            intersection = intersect(c3, c1);
            CHECK(intersection.p1.x == Approx(-1.f));
            CHECK(intersection.p1.y == Approx(1.f));
            CHECK(intersection.p2.x == Approx(-1.f));
            CHECK(intersection.p2.y == Approx(1.f));
        }
        {
            // no intersection points (circles apart)
            auto intersection = intersect(c2, c3);
            REQUIRE_FALSE(collides(c2, c3));
            CHECK(std::isnan(intersection.p1.x));
            CHECK(std::isnan(intersection.p1.y));
            CHECK(std::isnan(intersection.p2.x));
            CHECK(std::isnan(intersection.p2.y));
            // symmetric
            intersection = intersect(c2, c3);
            CHECK(std::isnan(intersection.p1.x));
            CHECK(std::isnan(intersection.p1.y));
            CHECK(std::isnan(intersection.p2.x));
            CHECK(std::isnan(intersection.p2.y));
        }
        {
            // no intersection points (circle fully contained)
            auto intersection = intersect(c3, c4);
            REQUIRE(collides(c3, c4));
            CHECK(std::isnan(intersection.p1.x));
            CHECK(std::isnan(intersection.p1.y));
            CHECK(std::isnan(intersection.p2.x));
            CHECK(std::isnan(intersection.p2.y));
            // symmetric
            intersection = intersect(c4, c3);
            CHECK(std::isnan(intersection.p1.x));
            CHECK(std::isnan(intersection.p1.y));
            CHECK(std::isnan(intersection.p2.x));
            CHECK(std::isnan(intersection.p2.y));
        }
        {
            // same circle
            auto intersection = intersect(c1, Circle2<float>(c1));
            REQUIRE(collides(c1, c1));
            CHECK(std::isnan(intersection.p1.x));
            CHECK(std::isnan(intersection.p1.y));
            CHECK(std::isnan(intersection.p2.x));
            CHECK(std::isnan(intersection.p2.y));
        }
    }
}
