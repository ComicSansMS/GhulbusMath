#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_Vector3Impl_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_Vector3Impl_HPP

/** @file
 *
 * @brief 3D Vector.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/VectorTraits.hpp>

#include <cmath>
#include <cstdint>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T, typename VectorTag_T = VectorTag::Vector>
class Vector3Impl;

template<typename T>
using Vector3 = Vector3Impl<T, VectorTag::Vector>;
template<typename T>
using Point3 = Vector3Impl<T, VectorTag::Point>;
template<typename T>
using Normal3 = Vector3Impl<T, VectorTag::Normal>;

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3i = Vector3<std::int32_t>;

using Point3f = Point3<float>;
using Point3d = Point3<double>;
using Point3i = Point3<std::int32_t>;

using Normal3f = Normal3<float>;
using Normal3d = Normal3<double>;
using Normal3i = Normal3<std::int32_t>;


template<typename T, typename VectorTag_T>
class Vector3Impl {
public:
    using Tag = VectorTag_T;

    T x;
    T y;
    T z;

    Vector3Impl() = default;
    Vector3Impl(Vector3Impl<T, Tag> const&) = default;
    Vector3Impl<T, Tag>& operator=(Vector3Impl<T, Tag> const&) = default;

    Vector3Impl(T vx, T vy, T vz)
        :x(vx), y(vy), z(vz)
    {}

    Vector3Impl(T const* arr)
        :x(arr[0]), y(arr[1]), z(arr[2])
    {}

    template<typename U>
    explicit Vector3Impl(Vector3Impl<U, Tag> const& v)
        :x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
    {}

    Vector3<T> to_vector() const
    {
        return Vector3<T>(x, y, z);
    }

    T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    Vector3Impl<T, Tag>& operator+=(Vector3Impl<T, Tag> const& rhs)
    {
        static_assert(!VectorTraits::IsFinitePoint<Tag>::value, "Addition of points not allowed.");
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    template<typename TTag = Tag, typename RhsTag>
    std::enable_if_t<VectorTraits::IsFinitePoint<TTag>::value &&
                     !VectorTraits::IsFinitePoint<RhsTag>::value , Vector3Impl<T, TTag>>&
        operator+=(Vector3Impl<T, RhsTag> const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector3Impl<T, Tag>& operator-=(Vector3Impl<T, Tag> const& rhs)
    {
        static_assert(!VectorTraits::IsFinitePoint<Tag>::value, "Compound subtraction of points not allowed.");
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    template<typename TTag = Tag, typename RhsTag>
    std::enable_if_t<VectorTraits::IsFinitePoint<TTag>::value &&
                     !VectorTraits::IsFinitePoint<RhsTag>::value, Vector3Impl<T, TTag>>&
        operator-=(Vector3Impl<T, RhsTag> const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vector3Impl<T, Tag>& operator*=(T s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    Vector3Impl<T, Tag>& operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
};

template<typename T, typename VectorTag_T>
inline bool operator==(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return (lhs.x == rhs.x) &&
           (lhs.y == rhs.y) &&
           (lhs.z == rhs.z);
}

template<typename T, typename VectorTag_T>
inline bool operator<(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    if(lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    } else if(lhs.y != rhs.y) {
        return lhs.y < rhs.y;
    } else {
        return lhs.z < rhs.z;
    }
}

template<typename T, typename VectorTag_T>
inline bool operator!=(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename VectorTag_T>
inline bool operator<=(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T, typename VectorTag_T>
inline bool operator>(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return rhs < lhs;
}

template<typename T, typename VectorTag_T>
inline bool operator>=(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> operator+(Vector3Impl<T, VectorTag_T> const& lhs,
                                             Vector3Impl<T, VectorTag_T> const& rhs)
{
    static_assert(!VectorTraits::IsFinitePoint<VectorTag_T>::value, "Addition of points is not allowed.");
    return Vector3Impl<T, VectorTag_T>(lhs.x + rhs.x,
                                       lhs.y + rhs.y,
                                       lhs.z + rhs.z);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Point3<T>>
    operator+(Point3<T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return Point3<T>(lhs.x + rhs.x,
                     lhs.y + rhs.y,
                     lhs.z + rhs.z);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Point3<T>>
    operator+(Vector3Impl<T, VectorTag_T> const& lhs, Point3<T> const& rhs)
{
    return Point3<T>(lhs.x + rhs.x,
                     lhs.y + rhs.y,
                     lhs.z + rhs.z);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector3Impl<T, VectorTag_T>>
    operator-(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return Vector3Impl<T, VectorTag_T>(lhs.x - rhs.x,
                                       lhs.y - rhs.y,
                                       lhs.z - rhs.z);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector3<T>>
    operator-(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return Vector3<T>(lhs.x - rhs.x,
                      lhs.y - rhs.y,
                      lhs.z - rhs.z);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Point3<T>>
    operator-(Point3<T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return Point3<T>(lhs.x - rhs.x,
                     lhs.y - rhs.y,
                     lhs.z - rhs.z);
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> operator*(Vector3Impl<T, VectorTag_T> const& v, T s)
{
    return Vector3Impl<T, VectorTag_T>(v.x * s, v.y * s, v.z * s);
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> operator*(T s, Vector3Impl<T, VectorTag_T> const& v)
{
    return Vector3Impl<T, VectorTag_T>(s * v.x, s * v.y, s * v.z);
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> operator/(Vector3Impl<T, VectorTag_T> const& v, T s)
{
    return Vector3Impl<T, VectorTag_T>(v.x / s, v.y / s, v.z / s);
}

template<typename T, typename VectorTag_T>
inline T dot(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template<typename T, typename VectorTag_T>
inline double length(Vector3Impl<T, VectorTag_T> const& v)
{
    return std::sqrt(static_cast<double>(dot(v, v)));
}

template<typename VectorTag_T>
inline float length(Vector3Impl<float, VectorTag_T> const& v)
{
    return std::sqrt(dot(v, v));
}

template<typename VectorTag_T>
inline long double length(Vector3Impl<long double, VectorTag_T> const& v)
{
    return std::sqrt(dot(v, v));
}

template<typename T, typename VectorTag_T>
inline std::enable_if_t<std::is_floating_point<T>::value, Vector3Impl<T, VectorTag_T>>
normalized(Vector3Impl<T, VectorTag_T> const& v)
{
    T const len = length(v);
    return Vector3Impl<T, VectorTag_T>(v.x / len, v.y / len, v.z / len);
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> cross(Vector3Impl<T, VectorTag_T> const& lhs,
                                         Vector3Impl<T, VectorTag_T> const& rhs)
{
    return Vector3Impl<T, VectorTag_T>(lhs.y*rhs.z - lhs.z*rhs.y,
                                       lhs.z*rhs.x - lhs.x*rhs.z,
                                       lhs.x*rhs.y - lhs.y*rhs.x);
}

/** Computes a normal perpendicular to two other vectors, oriented in the natural handedness of the coordinate system.
 */
template<typename T>
inline Normal3<T> perp(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    auto const n = cross(lhs, rhs);
    return Normal3<T>(n.x, n.y, n.z);
}

/** Scalar triple product, aka box product.
 */
template<typename T, typename VectorTag_T>
inline T box(Vector3Impl<T, VectorTag_T> const& u,
             Vector3Impl<T, VectorTag_T> const& v,
             Vector3Impl<T, VectorTag_T> const& w)
{
    auto const cross_u_v = cross(u, v);
    return dot(cross_u_v, w);
}

template<typename T, typename VectorTag_T>
inline T angle_vector(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return std::acos(dot(lhs, rhs) / (length(lhs) * length(rhs)));
}

template<typename T, typename VectorTag_T>
inline T angle_vector_unit(Vector3Impl<T, VectorTag_T> const& lhs, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return std::acos(dot(lhs, rhs));
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> project(Vector3Impl<T, VectorTag_T> const& lhs,
                                           Vector3Impl<T, VectorTag_T> const& rhs)
{
    return rhs * (dot(lhs, rhs) / dot(rhs, rhs));
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> project_unit(Vector3Impl<T, VectorTag_T> const& lhs,
                                                Vector3Impl<T, VectorTag_T> const& rhs)
{
    return rhs * dot(lhs, rhs);
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> reject(Vector3Impl<T, VectorTag_T> const& lhs,
                                          Vector3Impl<T, VectorTag_T> const& rhs)
{
    return lhs - project(lhs, rhs);
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> reject_unit(Vector3Impl<T, VectorTag_T> const& lhs,
                                               Vector3Impl<T, VectorTag_T> const& rhs)
{
    return lhs - project_unit(lhs, rhs);
}

template<typename T, typename VectorTag_T>
inline T max_component(Vector3Impl<T, VectorTag_T> const& v)
{
    auto const max_yz = (v.y < v.z) ? v.z : v.y;
    return (v.x < max_yz) ? max_yz : v.x;
}

template<typename T, typename VectorTag_T>
inline T min_component(Vector3Impl<T, VectorTag_T> const& v)
{
    auto const min_yz = (v.y < v.z) ? v.y : v.z;
    return (v.x < min_yz) ? v.x : min_yz;
}

template<typename T, typename VectorTag_T>
inline Vector3Impl<T, VectorTag_T> lerp(Vector3Impl<T, VectorTag_T> const& v1,
                                        Vector3Impl<T, VectorTag_T> const& v2,
                                        T t)
{
    auto const one_minus_t = GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One() - t;
    return Vector3Impl<T, VectorTag_T>(one_minus_t * v1.x + t * v2.x,
                                       one_minus_t * v1.y + t * v2.y,
                                       one_minus_t * v1.z + t * v2.z);
}
}

#endif
