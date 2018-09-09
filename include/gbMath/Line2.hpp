#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_LINE2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_LINE2_HPP

/** @file
*
* @brief 2D Line.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Vector2.hpp>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Line2 {
public:
    Point2<T> p;
    Vector2<T> v;
public:
    Line2() = default;
    Line2(Line2<T> const&) = default;
    Line2<T>& operator=(Line2<T> const&) = default;

    Line2(Point2<T> const& np, Vector2<T> const& nv)
        :p(np), v(nv)
    {}

    Line2(Point2<T> const& p1, Point2<T> const& p2)
        :p(p1), v(p2 - p1)
    {}

    Point2<T> evaluate_at_parameter(T t) const
    {
        return p + v * t;
    }
};

template<typename T>
inline std::enable_if_t<std::is_floating_point<T>::value, Line2<T>> normalized(Line2<T> const& l)
{
    return Line2<T>(l.p, normalized(l.v));
}

template<typename T>
inline T distance_squared(Line2<T> const& l, Point2<T> const& p)
{
    auto const r = reject((p - l.p), l.v);
    return dot(r, r);
}

template<typename T>
inline T distance_squared_unit(Line2<T> const& l, Point2<T> const& p)
{
    auto const r = reject_unit((p - l.p), l.v);
    return dot(r, r);
}

template<typename T>
inline T distance(Line2<T> const& l, Point2<T> const& p)
{
    return length(reject((p - l.p), l.v));
}

template<typename T>
inline T distance_unit(Line2<T> const& l, Point2<T> const& p)
{
    return length(reject_unit((p - l.p), l.v));
}
}
#endif
