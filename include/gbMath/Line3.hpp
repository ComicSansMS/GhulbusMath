#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_LINE3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_LINE3_HPP

/** @file
*
* @brief 3D Line.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/Vector3.hpp>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Line3 {
public:
    Point3<T> p;
    Vector3<T> v;
public:
    Line3() = default;
    Line3(DoNotInitialize_Tag)
        :p(doNotInitialize), v(doNotInitialize)
    {}
    Line3(Line3<T> const&) = default;
    Line3<T>& operator=(Line3<T> const&) = default;

    Line3(Point3<T> const& np, Vector3<T> const& nv)
        :p(np), v(nv)
    {}

    Line3(Point3<T> const& p1, Point3<T> const& p2)
        :p(p1), v(p2 - p1)
    {}

    Point3<T> evaluate_at_parameter(T t) const
    {
        return p + v * t;
    }
};

template<typename T>
inline std::enable_if_t<std::is_floating_point<T>::value, Line3<T>> normalized(Line3<T> const& l)
{
    return Line3<T>(l.p, normalized(l.v));
}

template<typename T>
inline T distance_squared_unit(Line3<T> const& l, Point3<T> const& p)
{
    auto const a = cross(p - l.p, l.v);
    return dot(a, a);
}

template<typename T>
inline T distance_squared(Line3<T> const& l, Point3<T> const& p)
{
    return distance_squared_unit(l, p) / dot(l.v, l.v);
}

template<typename T>
inline T distance(Line3<T> const& l, Point3<T> const& p)
{
    return std::sqrt(static_cast<double>(distance_squared(l, p)));
}

template<>
inline float distance(Line3<float> const& l, Point3<float> const& p)
{
    return std::sqrt(distance_squared(l, p));
}

template<>
inline long double distance(Line3<long double> const& l, Point3<long double> const& p)
{
    return std::sqrt(distance_squared(l, p));
}

template<typename T>
inline T distance_unit(Line3<T> const& l, Point3<T> const& p)
{
    return std::sqrt(static_cast<double>(distance_squared_unit(l, p)));
}

template<>
inline float distance_unit(Line3<float> const& l, Point3<float> const& p)
{
    return std::sqrt(distance_squared_unit(l, p));
}

template<>
inline long double distance_unit(Line3<long double> const& l, Point3<long double> const& p)
{
    return std::sqrt(distance_squared_unit(l, p));
}

}
#endif
