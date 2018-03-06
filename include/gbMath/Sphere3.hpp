#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_SPHERE3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_SPHERE3_HPP

/** @file
*
* @brief 3D Bounding sphere.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector3.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Sphere3
{
public:
    Point3<T> center;
    T radius;

    Sphere3() = default;
    Sphere3(Sphere3 const&) = default;
    Sphere3& operator=(Sphere3 const&) = default;

    Sphere3(Point3<T> const& n_center, T n_radius)
        :center(n_center), radius(n_radius)
    {}
};

template<typename T>
bool intersects(Sphere3<T> const& s, Point3<T> const& p)
{
    Vector3<T> const dist = s.center - p;
    T const squared_dist = dot(dist, dist);
    if(s.radius*s.radius < squared_dist) {
        return false;
    }
    return true;
}

template<typename T>
bool intersects(Sphere3<T> const& s1, Sphere3<T> const& s2)
{
    Vector3<T> const dist = s1.center - s2.center;
    T const squared_dist = dot(dist, dist);
    T const radii_sum = s1.radius + s2.radius;
    if(radii_sum*radii_sum < squared_dist) {
        return false;
    }
    return true;
}
}
#endif
