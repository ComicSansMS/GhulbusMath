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
};

template<typename T>
inline std::enable_if_t<std::is_floating_point<T>::value, Line2<T>> normalized(Line2<T> const& l)
{
    return Line2<T>(l.p, normalized(l.v));
}
}
#endif
