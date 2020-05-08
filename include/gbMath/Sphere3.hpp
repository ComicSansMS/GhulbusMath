#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_SPHERE3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_SPHERE3_HPP

/** @file
*
* @brief 3D Bounding sphere.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Line3.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector3.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#ifndef  __APPLE__
#include <optional>
#else
#include <experimental/optional>
namespace std { using std::experimental::optional; using std::experimental::nullopt; }
#endif
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
inline bool contains(Sphere3<T> const& s, Point3<T> const& p)
{
    Vector3<T> const dist = s.center - p;
    T const squared_dist = dot(dist, dist);
    if(s.radius*s.radius < squared_dist) {
        return false;
    }
    return true;
}

template<typename T>
inline bool intersects(Sphere3<T> const& s1, Sphere3<T> const& s2)
{
    Vector3<T> const dist = s1.center - s2.center;
    T const squared_dist = dot(dist, dist);
    T const radii_sum = s1.radius + s2.radius;
    if(radii_sum*radii_sum < squared_dist) {
        return false;
    }
    return true;
}

template<typename T>
inline bool intersects(Sphere3<T> const& s, Line3<T> const& l)
{
    Vector3<T> const m = l.p - s.center;
    T const c = dot(m, m) - (s.radius * s.radius);
    if(c <= traits::Constants<T>::Zero()) {
        return true;
    }
    T const b = dot(m, normalized(l.v));
    if(b > traits::Constants<T>::Zero()) {
        return false;
    }
    T const disc = b*b - c;
    if(disc < traits::Constants<T>::Zero()) {
        return false;
    }
    return true;
}

template<typename T>
inline std::optional<T> intersect_p(Sphere3<T> const& s, Line3<T> const& l)
{
    Vector3<T> const m = l.p - s.center;
    T const b = dot(m, normalized(l.v));
    T const c = dot(m, m) - (s.radius * s.radius);
    if(c > traits::Constants<T>::Zero() && b > traits::Constants<T>::Zero()) {
        // ray origin is outside of sphere and ray is pointing away from sphere: no intersection
        return std::nullopt;
    }
    T const discr = b*b - c;
    if(discr < traits::Constants<T>::Zero()) {
        // negative discriminant: ray is not hitting sphere
        return std::nullopt;
    }
    T t = -b - std::sqrt(discr);
    if(t < traits::Constants<T>::Zero()) {
        // ray origin is inside sphere; clamp t to 0
        // this means we consider spheres solid; rays starting inside the sphere intersect at the ray origin
        t = 0.f;
    }
    return t;
}
}
#endif
