#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_CIRCLE2_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_CIRCLE2_HPP

/** @file
*
* @brief 2D Bounding circle.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/Line2.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector2.hpp>

#include <cmath>
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

    constexpr Circle2()
        :center{}, radius{}
    {}
    constexpr explicit Circle2(DoNotInitialize_Tag)
        :center(doNotInitialize)
    {}
    constexpr Circle2(Circle2 const&) = default;
    constexpr Circle2& operator=(Circle2 const&) = default;

    constexpr Circle2(Point2<T> const& n_center, T n_radius)
        :center(n_center), radius(n_radius)
    {}
};

template<typename T>
[[nodiscard]] constexpr inline bool collides(Circle2<T> const& c, Point2<T> const& p)
{
    Vector2<T> const dist = c.center - p;
    T const squared_dist = dot(dist, dist);
    if (c.radius*c.radius < squared_dist) {
        return false;
    }
    return true;
}

template<typename T>
[[nodiscard]] constexpr inline bool collides(Circle2<T> const& c1, Circle2<T> const& c2)
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

    constexpr Circle2Line2Intersection(T n_a, T n_b, T n_c)
        :a(n_a), b(n_b), c(n_c)
    {}

    constexpr Circle2Line2Intersection() = default;
    constexpr Circle2Line2Intersection(Circle2Line2Intersection const&) = default;
    constexpr Circle2Line2Intersection& operator=(Circle2Line2Intersection const&) = default;

    [[nodiscard]] constexpr operator bool() const
    {
        return ((b*b - 4*a*c) >= 0);
    }

    template<typename U = T>
    [[nodiscard]] constexpr Circle2Line2IntersectionParameters<U> evaluateT() const
    {
        auto const disc = std::sqrt(static_cast<U>(b*b - 4*a*c));
        U const a2 = static_cast<U>(2*a);
        U const neg_b = static_cast<U>(-b);
        return { static_cast<U>((neg_b + disc) / a2), static_cast<U>((neg_b - disc) / a2) };
    }
};

template<typename T>
[[nodiscard]] constexpr inline Circle2Line2Intersection<T> intersect(Circle2<T> const& c, Line2<T> const& l)
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
[[nodiscard]] constexpr inline Circle2Circle2IntersectionPoints<T> intersect(Circle2<T> const& c1, Circle2<T> const& c2)
{
    Vector2<T> const v_dist = c2.center - c1.center;
    auto const d = length(v_dist);
    auto const inv_d = decltype(d){1} / d;
    // midpoint is the point where the line connecting the intersection points crosses v_dist at a right angle
    // a is the distance from the c1.center to the midpoint
    auto const a = (c1.radius*c1.radius - c2.radius*c2.radius + d*d) * (decltype(d){0.5} * inv_d);
    Point2<T> midpoint = c1.center + v_dist * (a * inv_d);
    // h is the distance of each intersection point from the midpoint
    auto const h = std::sqrt(c1.radius*c1.radius - a*a);
    // we reach the intersection points by walking length h from midpoint in direction perpendicular to v_dist
    Normal2<T> const v_offset = perp(v_dist) * (h * inv_d);
    Point2<T> const intersection1 = midpoint - v_offset;
    Point2<T> const intersection2 = midpoint + v_offset;
    return Circle2Circle2IntersectionPoints<T>{intersection1, intersection2};
}
}
#endif
