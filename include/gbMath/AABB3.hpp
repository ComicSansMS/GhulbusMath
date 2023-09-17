#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_AABB3_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_AABB3_HPP

/** @file
*
* @brief 3D Axis-aligned bounding box.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector3.hpp>

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <limits>
#include <numeric>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class AABB3;

using AABB3f = AABB3<float>;
using AABB3d = AABB3<double>;
using AABB3i = AABB3<std::int32_t>;

template<typename T>
[[nodiscard]] constexpr inline AABB3<T> empty_aabb3();
template<typename T>
[[nodiscard]] constexpr inline AABB3<T> enclose(AABB3<T> const& b, Point3<T> const& p);

template<typename T>
class AABB3
{
public:
    Point3<T> min;
    Point3<T> max;

    constexpr AABB3() = default;
    constexpr explicit AABB3(DoNotInitialize_Tag)
        :min(doNotInitialize), max(doNotInitialize)
    {}
    constexpr AABB3(AABB3 const&) = default;
    constexpr AABB3& operator=(AABB3 const&) = default;

    constexpr explicit AABB3(Point3<T> const& p)
        :min(p), max(p)
    {}

    constexpr AABB3(Point3<T> const& n_min, Point3<T> const& n_max)
        :min(n_min), max(n_max)
    {}

    [[nodiscard]] friend constexpr bool operator==(AABB3 const& lhs, AABB3 const& rhs) = default;

#ifndef __clang__
    template<std::ranges::range R>
    [[nodiscard]] static constexpr inline AABB3 from_points(R points)
        requires(std::same_as<typename std::ranges::range_value_t<R>, Point3<T>> )
#else
    // Clang is missing the range concept currently.
    template<typename R>
    [[nodiscard]] static constexpr inline AABB3 from_points(R points)
        requires(requires(R r) { std::ranges::begin(r); std::ranges::end(r); })
#endif
    {
        return std::accumulate(std::ranges::begin(points), std::ranges::end(points), empty_aabb3<T>(), enclose<T>);
    }

    [[nodiscard]] static constexpr inline AABB3 from_points(std::initializer_list<Point3<T>> l)
    {
        return std::accumulate(std::ranges::begin(l), std::ranges::end(l), empty_aabb3<T>(), enclose<T>);
    }
};

template<typename T>
[[nodiscard]] constexpr inline AABB3<T> empty_aabb3()
{
    T const tmin = std::numeric_limits<T>::lowest();
    T const tmax = std::numeric_limits<T>::max();
    return AABB3<T>(Point3<T>(tmax, tmax, tmax), Point3<T>(tmin, tmin, tmin));
}

template<typename T>
[[nodiscard]] constexpr inline Vector3<T> diagonal(AABB3<T> const& b)
{
    return b.max - b.min;
}

/** Grow the bounding volume to enclose an additional point.
 */
template<typename T>
[[nodiscard]] constexpr inline AABB3<T> enclose(AABB3<T> const& b, Point3<T> const& p)
{
    return AABB3<T>(Point3<T>(std::min(b.min.x, p.x), std::min(b.min.y, p.y), std::min(b.min.z, p.z)),
                    Point3<T>(std::max(b.max.x, p.x), std::max(b.max.y, p.y), std::max(b.max.z, p.z)));
}

/** Grow the bounding volume to enclose another bounding volume.
 */
template<typename T>
[[nodiscard]] constexpr inline AABB3<T> enclose(AABB3<T> const& b1, AABB3<T> const& b2)
{
    return AABB3<T>(Point3<T>(std::min(b1.min.x, b2.min.x),
                              std::min(b1.min.y, b2.min.y),
                              std::min(b1.min.z, b2.min.z)),
                    Point3<T>(std::max(b1.max.x, b2.max.x),
                              std::max(b1.max.y, b2.max.y),
                              std::max(b1.max.z, b2.max.z)));
}

/** Checks whether a point intersects with the volume.
 */
template<typename T>
[[nodiscard]] constexpr inline bool intersects(AABB3<T> const& b, Point3<T> const& p)
{
    if((p.x < b.min.x) || (p.x > b.max.x) ||
       (p.y < b.min.y) || (p.y > b.max.y) ||
       (p.z < b.min.z) || (p.z > b.max.z))
    {
        return false;
    }
    return true;
}

/** Checks whether two volumes intersect.
 */
template<typename T>
[[nodiscard]] constexpr inline bool intersects(AABB3<T> const& b1, AABB3<T> const& b2)
{
    // intersects only if there is an overlap on all axes
    if((b1.max.x < b2.min.x) || (b1.min.x > b2.max.x) ||
       (b1.max.y < b2.min.y) || (b1.min.y > b2.max.y) ||
       (b1.max.z < b2.min.z) || (b1.min.z > b2.max.z))
    {
        return false;
    }
    return true;
}

template<typename T>
[[nodiscard]] constexpr inline AABB3<T> union_aabb(AABB3<T> const& b1, AABB3<T> const& b2)
{
    return AABB3<T>(Point3<T>(std::min(b1.min.x, b2.min.x),
                              std::min(b1.min.y, b2.min.y),
                              std::min(b1.min.z, b2.min.z)),
                    Point3<T>(std::max(b1.max.x, b2.max.x),
                              std::max(b1.max.y, b2.max.y),
                              std::max(b1.max.z, b2.max.z)));
}

template<typename T>
[[nodiscard]] constexpr inline AABB3<T> intersect_aabb(AABB3<T> const& b1, AABB3<T> const& b2)
{
    return AABB3<T>(Point3<T>(std::max(b1.min.x, b2.min.x),
                              std::max(b1.min.y, b2.min.y),
                              std::max(b1.min.z, b2.min.z)),
                    Point3<T>(std::min(b1.max.x, b2.max.x),
                              std::min(b1.max.y, b2.max.y),
                              std::min(b1.max.z, b2.max.z)));
}
}
#endif
