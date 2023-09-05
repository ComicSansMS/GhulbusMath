#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_AABB2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_AABB2_HPP

/** @file
*
* @brief 2D Axis-aligned bounding box.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector2.hpp>

#include <algorithm>
#include <cmath>
#include <concepts>
#include <initializer_list>
#include <limits>
#include <numeric>
#include <span>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class AABB2;

template<typename T>
[[nodiscard]] constexpr inline AABB2<T> empty_aabb2();
template<typename T>
[[nodiscard]] constexpr inline AABB2<T> enclose(AABB2<T> const& b, Point2<T> const& p);

template<typename T>
class AABB2
{
public:
    Point2<T> min;
    Point2<T> max;

    constexpr AABB2() = default;
    constexpr explicit AABB2(DoNotInitialize_Tag)
        :min(doNotInitialize), max(doNotInitialize)
    {}
    constexpr AABB2(AABB2 const&) = default;
    constexpr AABB2& operator=(AABB2 const&) = default;

    constexpr explicit AABB2(Point2<T> const& p)
        :min(p), max(p)
    {}

    constexpr AABB2(Point2<T> const& n_min, Point2<T> const& n_max)
        :min(n_min), max(n_max)
    {}

    [[nodiscard]] friend constexpr bool operator==(AABB2 const& lhs, AABB2 const& rhs) = default;

    template<std::ranges::range R>
    [[nodiscard]] static constexpr inline AABB2 from_points(R points)
        requires(std::same_as<typename std::ranges::range_value_t<R>, Point2<T>> )
    {
        return std::accumulate(std::ranges::begin(points), std::ranges::end(points), empty_aabb2<T>(), enclose<T>);
    }

    [[nodiscard]] static constexpr inline AABB2 from_points(std::initializer_list<Point2<T>> l)
    {
        return std::accumulate(std::ranges::begin(l), std::ranges::end(l), empty_aabb2<T>(), enclose<T>);
    }
};

template<typename T>
[[nodiscard]] constexpr inline AABB2<T> empty_aabb2()
{
    T const tmin = std::numeric_limits<T>::lowest();
    T const tmax = std::numeric_limits<T>::max();
    return AABB2<T>(Point2<T>(tmax, tmax), Point2<T>(tmin, tmin));
}

template<typename T>
[[nodiscard]] constexpr inline Vector2<T> diagonal(AABB2<T> const& b)
{
    return b.max - b.min;
}

/** Grow the bounding volume to enclose an additional point.
 */
template<typename T>
[[nodiscard]] constexpr inline AABB2<T> enclose(AABB2<T> const& b, Point2<T> const& p)
{
    return AABB2<T>(Point2<T>(std::min(b.min.x, p.x), std::min(b.min.y, p.y)),
                    Point2<T>(std::max(b.max.x, p.x), std::max(b.max.y, p.y)));
}

/** Grow the bounding volume to enclose another bounding volume.
 */
template<typename T>
[[nodiscard]] constexpr inline AABB2<T> enclose(AABB2<T> const& b1, AABB2<T> const& b2)
{
    return AABB2<T>(Point2<T>(std::min(b1.min.x, b2.min.x),
                              std::min(b1.min.y, b2.min.y)),
                    Point2<T>(std::max(b1.max.x, b2.max.x),
                              std::max(b1.max.y, b2.max.y)));
}


/** Checks whether a point intersects with the volume.
 */
template<typename T>
[[nodiscard]] constexpr inline bool intersects(AABB2<T> const& b, Point2<T> const& p)
{
    if((p.x < b.min.x) || (p.x > b.max.x) ||
       (p.y < b.min.y) || (p.y > b.max.y))
    {
        return false;
    }
    return true;
}

/** Checks whether two volumes intersect.
 */
template<typename T>
[[nodiscard]] constexpr inline bool intersects(AABB2<T> const& b1, AABB2<T> const& b2)
{
    // intersects only if there is an overlap on all axes
    if((b1.max.x < b2.min.x) || (b1.min.x > b2.max.x) ||
       (b1.max.y < b2.min.y) || (b1.min.y > b2.max.y))
    {
        return false;
    }
    return true;
}

template<typename T>
[[nodiscard]] constexpr inline AABB2<T> union_aabb(AABB2<T> const& b1, AABB2<T> const& b2)
{
    return AABB2<T>(Point2<T>(std::min(b1.min.x, b2.min.x),
                              std::min(b1.min.y, b2.min.y)),
                    Point2<T>(std::max(b1.max.x, b2.max.x),
                              std::max(b1.max.y, b2.max.y)));
}

template<typename T>
[[nodiscard]] constexpr inline AABB2<T> intersect_aabb(AABB2<T> const& b1, AABB2<T> const& b2)
{
    return AABB2<T>(Point2<T>(std::max(b1.min.x, b2.min.x),
                              std::max(b1.min.y, b2.min.y)),
                    Point2<T>(std::min(b1.max.x, b2.max.x),
                              std::min(b1.max.y, b2.max.y)));
}
}
#endif
