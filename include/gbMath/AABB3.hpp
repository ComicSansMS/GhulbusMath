#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_AABB3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_AABB3_HPP

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
#include <limits>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class AABB3
{
public:
    Point3<T> min;
    Point3<T> max;

    AABB3() = default;
    AABB3(DoNotInitialize_Tag)
        :min(doNotInitialize), max(doNotInitialize)
    {}
    AABB3(AABB3 const&) = default;
    AABB3& operator=(AABB3 const&) = default;

    AABB3(Point3<T> const& p)
        :min(p), max(p)
    {}

    AABB3(Point3<T> const& n_min, Point3<T> const& n_max)
        :min(n_min), max(n_max)
    {}

    friend bool operator==(AABB3<T> const& lhs, AABB3<T> const& rhs)
    {
        return (lhs.min == rhs.min) && (lhs.max == rhs.max);
    }

    friend bool operator!=(AABB3<T> const& lhs, AABB3<T> const& rhs)
    {
        return !(lhs == rhs);
    }
};

template<typename T>
inline AABB3<T> empty_aabb3()
{
    T const tmin = std::numeric_limits<T>::lowest();
    T const tmax = std::numeric_limits<T>::max();
    return AABB3<T>(Point3<T>(tmax, tmax, tmax), Point3<T>(tmin, tmin, tmin));
}

template<typename T>
inline Vector3<T> diagonal(AABB3<T> const& b)
{
    return b.max - b.min;
}

/** Grow the bounding volume to enclose an additional point.
 */
template<typename T>
inline AABB3<T> enclose(AABB3<T> const& b, Point3<T> const& p)
{
    return AABB3<T>(Point3<T>(std::min(b.min.x, p.x), std::min(b.min.y, p.y), std::min(b.min.z, p.z)),
                    Point3<T>(std::max(b.max.x, p.x), std::max(b.max.y, p.y), std::max(b.max.z, p.z)));
}

/** Grow the bounding volume to enclose another bounding volume.
 */
template<typename T>
inline AABB3<T> enclose(AABB3<T> const& b1, AABB3<T> const& b2)
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
inline bool intersects(AABB3<T> const& b, Point3<T> const& p)
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
inline bool intersects(AABB3<T> const& b1, AABB3<T> const& b2)
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
inline AABB3<T> union_aabb(AABB3<T> const& b1, AABB3<T> const& b2)
{
    return AABB3<T>(Point3<T>(std::min(b1.min.x, b2.min.x),
                              std::min(b1.min.y, b2.min.y),
                              std::min(b1.min.z, b2.min.z)),
                    Point3<T>(std::max(b1.max.x, b2.max.x),
                              std::max(b1.max.y, b2.max.y),
                              std::max(b1.max.z, b2.max.z)));
}

template<typename T>
inline AABB3<T> intersect_aabb(AABB3<T> const& b1, AABB3<T> const& b2)
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
