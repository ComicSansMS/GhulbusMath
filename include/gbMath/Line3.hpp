#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_LINE3_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_LINE3_HPP

/** @file
*
* @brief 3D Line.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/Vector3.hpp>

#include <concepts>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Line3 {
public:
    Point3<T> p;
    Vector3<T> v;
public:
    constexpr Line3() = default;
    constexpr explicit Line3(DoNotInitialize_Tag)
        :p(doNotInitialize), v(doNotInitialize)
    {}
    constexpr Line3(Line3 const&) = default;
    constexpr Line3& operator=(Line3 const&) = default;

    constexpr Line3(Point3<T> const& np, Vector3<T> const& nv)
        :p(np), v(nv)
    {}

    constexpr Line3(Point3<T> const& p1, Point3<T> const& p2)
        :p(p1), v(p2 - p1)
    {}

    [[nodiscard]] constexpr Point3<T> evaluate_at_parameter(T t) const
    {
        return p + v * t;
    }
};

template<std::floating_point T>
[[nodiscard]] constexpr inline Line3<T> normalized(Line3<T> const& l)
{
    return Line3<T>(l.p, normalized(l.v));
}

template<typename T>
[[nodiscard]] constexpr inline T distance_squared_unit(Line3<T> const& l, Point3<T> const& p)
{
    auto const a = cross(p - l.p, l.v);
    return dot(a, a);
}

template<typename T>
[[nodiscard]] constexpr inline T distance_squared(Line3<T> const& l, Point3<T> const& p)
{
    return distance_squared_unit(l, p) / dot(l.v, l.v);
}

template<typename T>
[[nodiscard]] constexpr inline T distance(Line3<T> const& l, Point3<T> const& p)
{
    return std::sqrt(static_cast<double>(distance_squared(l, p)));
}

template<>
[[nodiscard]] inline float distance(Line3<float> const& l, Point3<float> const& p)
{
    return std::sqrt(distance_squared(l, p));
}

template<>
[[nodiscard]] inline long double distance(Line3<long double> const& l, Point3<long double> const& p)
{
    return std::sqrt(distance_squared(l, p));
}

template<typename T>
[[nodiscard]] constexpr inline T distance_unit(Line3<T> const& l, Point3<T> const& p)
{
    return std::sqrt(static_cast<double>(distance_squared_unit(l, p)));
}

template<>
[[nodiscard]] inline float distance_unit(Line3<float> const& l, Point3<float> const& p)
{
    return std::sqrt(distance_squared_unit(l, p));
}

template<>
[[nodiscard]] inline long double distance_unit(Line3<long double> const& l, Point3<long double> const& p)
{
    return std::sqrt(distance_squared_unit(l, p));
}

}
#endif
