#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_SPHERE3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_SPHERE3_HPP

/** @file
*
* @brief 3D Bounding sphere.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/Line3.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector3.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <optional>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Sphere3
{
public:
    Point3<T> center;
    T radius;

    constexpr Sphere3()
        :center{}, radius{}
    {}
    constexpr explicit Sphere3(DoNotInitialize_Tag)
        :center(doNotInitialize)
    {}
    constexpr Sphere3(Sphere3 const&) = default;
    constexpr Sphere3& operator=(Sphere3 const&) = default;

    constexpr Sphere3(Point3<T> const& n_center, T n_radius)
        :center(n_center), radius(n_radius)
    {}
};

template<typename T>
[[nodiscard]] constexpr inline bool collides(Sphere3<T> const& s, Point3<T> const& p)
{
    Vector3<T> const dist = s.center - p;
    T const squared_dist = dot(dist, dist);
    if(s.radius*s.radius < squared_dist) {
        return false;
    }
    return true;
}

template<typename T>
[[nodiscard]] constexpr inline bool collides(Sphere3<T> const& s1, Sphere3<T> const& s2)
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
[[nodiscard]] constexpr inline bool intersects(Sphere3<T> const& s, Line3<T> const& l)
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
[[nodiscard]] constexpr inline std::optional<T> intersect_p(Sphere3<T> const& s, Line3<T> const& l)
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

template<typename T>
struct Sphere3Line3IntersectionParameters
{
    T t1;
    T t2;
};

template<typename T>
struct Sphere3Line3Intersection
{
    T b;
    T c;
    T discr;

    constexpr Sphere3Line3Intersection(T n_b, T n_c)
        :b(n_b), c(n_c), discr(b*b - c)
    {}

    constexpr Sphere3Line3Intersection() = default;
    constexpr Sphere3Line3Intersection(Sphere3Line3Intersection const&) = default;
    constexpr Sphere3Line3Intersection& operator=(Sphere3Line3Intersection const&) = default;

    /** Returns true if an intersection point was found.
     */
    [[nodiscard]] constexpr bool doesHitSphere() const {
        // negative discriminant: ray is not hitting sphere
        return (discr >= traits::Constants<T>::Zero());
    }

    /** Returns true if all intersection points lie behind the ray origin, that is,
     * all values returned by evaluateT() will be negative. The return value is unspecified
     * if there is no intersection.
     */
    [[nodiscard]] constexpr bool allIntersectionsBehindRayOrigin() const {
        // returns true iff ray origin is outside of sphere and ray is pointing away from sphere
        return (c > traits::Constants<T>::Zero() && b > traits::Constants<T>::Zero());
    }

    /** Evaluates to true if an intersection point was found and at least one intersection point
     * lies along the direction of the ray.
     */
    [[nodiscard]] constexpr operator bool() const
    {
        return (!allIntersectionsBehindRayOrigin()) && doesHitSphere();
    }

    /** Evaluates the t value at which the ray reaches the intersection point.
     * \pre doesHitSphere() - The behavior is undefined if no intersection points exist.
     */
    template<typename U = T>
    [[nodiscard]] constexpr Sphere3Line3IntersectionParameters<U> evaluateT() const
    {
        auto const sqr_discr = std::sqrt(static_cast<U>(discr));
        U const neg_b = static_cast<U>(-b);
        return Sphere3Line3IntersectionParameters<U>{
                neg_b - static_cast<U>(sqr_discr),
                neg_b + static_cast<U>(sqr_discr)
        };
    }
};

template<typename T>
[[nodiscard]] constexpr inline Sphere3Line3Intersection<T> intersect(Sphere3<T> const& s, Line3<T> const& l)
{
    Vector3<T> const m = l.p - s.center;
    T const b = dot(m, normalized(l.v));
    T const c = dot(m, m) - (s.radius * s.radius);
    return Sphere3Line3Intersection(b, c);
}

}
#endif
