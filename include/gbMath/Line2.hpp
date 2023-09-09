#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_LINE2_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_LINE2_HPP

/** @file
*
* @brief 2D Line.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/Vector2.hpp>

#include <concepts>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Line2 {
public:
    Point2<T> p;
    Vector2<T> v;
public:
    constexpr Line2() = default;
    constexpr explicit Line2(DoNotInitialize_Tag)
        :p(doNotInitialize), v(doNotInitialize)
    {}
    constexpr Line2(Line2 const&) = default;
    constexpr Line2& operator=(Line2 const&) = default;

    constexpr Line2(Point2<T> const& np, Vector2<T> const& nv)
        :p(np), v(nv)
    {}

    constexpr Line2(Point2<T> const& p1, Point2<T> const& p2)
        :p(p1), v(p2 - p1)
    {}

    template<typename U = T>
    [[nodiscard]] constexpr Point2<U> evaluate_at_parameter(U t) const
    {
        return Point2<U>(p) + Vector2<U>(v) * t;
    }
};

template<std::floating_point T>
[[nodiscard]] constexpr inline Line2<T> normalized(Line2<T> const& l)
{
    return Line2<T>(l.p, normalized(l.v));
}

template<typename T>
[[nodiscard]] constexpr inline T distance_squared(Line2<T> const& l, Point2<T> const& p)
{
    auto const r = reject((p - l.p), l.v);
    return dot(r, r);
}

template<typename T>
[[nodiscard]] constexpr inline T distance_squared_unit(Line2<T> const& l, Point2<T> const& p)
{
    auto const r = reject_unit((p - l.p), l.v);
    return dot(r, r);
}

template<typename T>
[[nodiscard]] constexpr inline T distance(Line2<T> const& l, Point2<T> const& p)
{
    return length(reject((p - l.p), l.v));
}

template<typename T>
[[nodiscard]] constexpr inline T distance_unit(Line2<T> const& l, Point2<T> const& p)
{
    return length(reject_unit((p - l.p), l.v));
}

/** Represents the result of a line-line intersection along with a scaling factor.
 * Use this to model intersections with fractional parameters using integral types.
 * The intersection point for two lines `l1` and `l2` can be retrieved from a ScaledLine2Intersection `sli` by calling
 * `l1.evaluate_at_parameter(sli.evaluate_t1())`
 * or
 * `l2.evaluate_at_parameter(sli.evaluate_t2())`.
 * @see intersect_scaled()
 */
template<typename T>
struct ScaledLine2Intersection {
    T t1;                       ///< The scaled parameter at which the first line reaches the intersection point.
    T t2;                       ///< The scaled parameter at which the first line reaches the intersection point.
    T inverse_scale_factor;     ///< The scale factor by which t1 and t2 need to be divided to retrieve the
                                ///<  line parameters. For parallel lines, this will be 0.

    constexpr ScaledLine2Intersection() = default;
    constexpr ScaledLine2Intersection(ScaledLine2Intersection const&) = default;
    constexpr ScaledLine2Intersection& operator=(ScaledLine2Intersection const&) = default;

    constexpr ScaledLine2Intersection(T n_t1, T n_t2, T n_inverse_scale_factor)
        :t1(n_t1), t2(n_t2), inverse_scale_factor(n_inverse_scale_factor)
    {}

    /**
     * @pre inverse_scale_factor != 0
     */
    template<typename U = T>
    [[nodiscard]] constexpr U evaluate_t1() const {
        return static_cast<U>(t1) / static_cast<U>(inverse_scale_factor);
    }

    /**
    * @pre inverse_scale_factor != 0
    */
    template<typename U = T>
    [[nodiscard]] constexpr U evaluate_t2() const {
        return static_cast<U>(t2) / static_cast<U>(inverse_scale_factor);
    }
};

/** Computes the intersection of two lines @p l1 and @p l2.
 * This function computes the line parameters for the intersection as a ScaledLine2Intersection, which is lossless
 * for integral types. If the lines are non-parallel, the `inverse_scale_factor` of the return value will be `!= 0`.
 * If the lines coincide, all fields of the return value will be `0`.
 * @code{.c}
 * Line2<int> l1;
 * Line2<int> l2;
 * // [...]
 * ScaledLine2Intersection<int> const sli = intersect_scaled(l1, l2);
 * if (sli.inverse_scale_factor != 0) {
 *   Point2<float> intersection_point = l1.evaluate_at_parameter(sli.evaluate_t1<float>());
 *   // [...]
 * }
 * @endcode
 */
template<typename T>
[[nodiscard]] constexpr  inline ScaledLine2Intersection<T> intersect_scaled(Line2<T> const& l1, Line2<T> const& l2)
{
    // The intersection point is obtained by solving the linear system
    //  [ l1.v -l2.v ] [ t ] = [ l2.p - l1.p ]
    // for t = (t1, t2), the vector of line parameters.
    // The linear system is solved by
    // [ t ] = [ l1.v -l2.v ]^(-1) [ l2.p - l1.p ]
    T const det = (l1.v.y * l2.v.x) - (l1.v.x * l2.v.y);
    Vector2<T> const dp = l2.p - l1.p;
    T const t1_scaled = dot(dp, Vector2<T>(-l2.v.y, l2.v.x));
    T const t2_scaled = dot(dp, Vector2<T>(-l1.v.y, l1.v.x));
    return ScaledLine2Intersection<T>(t1_scaled, t2_scaled, det);
}

/** Computes the intersection point of two lines @p l1 and @p l2.
 * @return The unique intersection point, if it exists.
 *         If the two lines are parallel, the point coordinates will be infinity.
 *         If the two lines coincide, the point coordinates will be NaN.
 */
template<typename T>
[[nodiscard]] constexpr  inline Point2<T> intersect_p(Line2<T> const& l1, Line2<T> const& l2)
{
    // We only need to solve one of the ts to get the intersection point.
    T const det = (l1.v.x * l2.v.y) - (l1.v.y * l2.v.x);
    Vector2<T> const dp = l2.p - l1.p;
    T const t1_scaled = dot(dp, Vector2<T>(l2.v.y, -l2.v.x));
    return l1.evaluate_at_parameter(t1_scaled / det);
}
}
#endif
