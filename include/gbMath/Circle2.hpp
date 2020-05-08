#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_CIRCLE2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_CIRCLE2_HPP

/** @file
*
* @brief 2D Bounding circle.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Line2.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector2.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#ifndef  __APPLE__
#include <optional>
#else
#include <experimental/optional>
namespace std { using std::experimental::optional; using std::experimental::nullopt; }
#endif
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Circle2
{
public:
    using ValueType = T;

    Point2<T> center;
    T radius;

    Circle2() = default;
    Circle2(Circle2 const&) = default;
    Circle2& operator=(Circle2 const&) = default;

    Circle2(Point2<T> const& n_center, T n_radius)
        :center(n_center), radius(n_radius)
    {}
};

template<typename T>
inline bool collides(Circle2<T> const& c, Point2<T> const& p)
{
    Vector2<T> const dist = c.center - p;
    T const squared_dist = dot(dist, dist);
    if (c.radius*c.radius < squared_dist) {
        return false;
    }
    return true;
}

template<typename T>
inline bool collides(Circle2<T> const& c1, Circle2<T> const& c2)
{
    Vector2<T> const dist = c1.center - c2.center;
    T const squared_dist = dot(dist, dist);
    T const radii_sum = c1.radius + c2.radius;
    return (squared_dist <= radii_sum*radii_sum);
}

template<typename T>
struct Circle2Line2IntersectionParameters
{
    T t1;
    T t2;
};

template<typename T>
struct Circle2Line2Intersection
{
    T a;
    T b;
    T c;

    Circle2Line2Intersection(T n_a, T n_b, T n_c)
        :a(n_a), b(n_b), c(n_c)
    {}

    Circle2Line2Intersection() = default;
    Circle2Line2Intersection(Circle2Line2Intersection const&) = default;
    Circle2Line2Intersection& operator=(Circle2Line2Intersection const&) = default;

    operator bool() const
    {
        return ((b*b - 4*a*c) >= 0);
    }

    template<typename U = T>
    Circle2Line2IntersectionParameters<U> evaluateT() const
    {
        auto const disc = std::sqrt(static_cast<U>(b*b - 4*a*c));
        U const a2 = static_cast<U>(2*a);
        U const neg_b = static_cast<U>(-b);
        return { static_cast<U>((neg_b + disc) / a2), static_cast<U>((neg_b - disc) / a2) };
    }
};

template<typename T>
[[nodiscard]] inline Circle2Line2Intersection<T> intersect(Circle2<T> const& c, Line2<T> const& l)
{
    Vector2<T> p = l.p - c.center;
    T const aa = dot(l.v, l.v);
    T const bb = 2 * dot(p, l.v);
    T const cc = dot(p, p) - (c.radius * c.radius);
    return Circle2Line2Intersection<T>(aa, bb, cc);
}

template<typename T>
struct Circle2Circle2IntersectionPoints
{
    Point2<T> p1;
    Point2<T> p2;
};

template<typename T>
[[nodiscard]] inline Circle2Circle2IntersectionPoints<T> intersect(Circle2<T> const& c1, Circle2<T> const& c2)
{
    Vector2<T> const v_dist = c2.center - c1.center;
    auto const d = length(v_dist);
    auto const a = (c1.radius*c1.radius - c2.radius*c2.radius + d*d) / (2*d);
    Point2<T> midpoint = c1.center + v_dist * (a / d);
    auto const h = std::sqrt(c1.radius*c1.radius - a*a);
    Vector2<T> const v_offset = v_dist * (h / d);
    Point2<T> const intersection1(midpoint.x + v_offset.y, midpoint.y - v_offset.x);
    Point2<T> const intersection2(midpoint.x - v_offset.y, midpoint.y + v_offset.x);
    return Circle2Circle2IntersectionPoints<T>{intersection1, intersection2};
}
}
#endif
