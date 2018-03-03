#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR2_HPP

/** @file
 *
 * @brief 2D Vector.
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
class Vector2Impl;

template<typename T>
using Vector2 = Vector2Impl<T, VectorTag::Vector>;
template<typename T>
using Point2 = Vector2Impl<T, VectorTag::Point>;
template<typename T>
using Normal2 = Vector2Impl<T, VectorTag::Normal>;

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<std::int32_t>;

using Point2f = Point2<float>;
using Point2d = Point2<double>;
using Point2i = Point2<std::int32_t>;

using Normal2f = Normal2<float>;
using Normal2d = Normal2<double>;
using Normal2i = Normal2<std::int32_t>;

template<typename T, typename VectorTag_T>
class Vector2Impl {
public:
    using Tag = VectorTag_T;

    T x;
    T y;

    Vector2Impl() = default;
    Vector2Impl(Vector2Impl<T, Tag> const&) = default;
    Vector2Impl<T, Tag>& operator=(Vector2Impl<T, Tag> const&) = default;

    Vector2Impl(T vx, T vy)
        :x(vx), y(vy)
    {}

    Vector2Impl(T const* arr)
        :x(arr[0]), y(arr[1])
    {}

    template<typename U>
    explicit Vector2Impl(Vector2Impl<U, Tag> const& v)
        :x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {}

    Vector2<T> to_vector() const
    {
        return Vector2<T>(x, y);
    }

    T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    Vector2Impl<T, Tag>& operator+=(Vector2Impl<T, Tag> const& rhs)
    {
        static_assert(!VectorTraits::IsFinitePoint<Tag>::value, "Addition of points not allowed.");
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<typename TTag = Tag, typename RhsTag>
    std::enable_if_t<VectorTraits::IsFinitePoint<TTag>::value &&
                     !VectorTraits::IsFinitePoint<RhsTag>::value , Vector2Impl<T, TTag>>&
        operator+=(Vector2Impl<T, RhsTag> const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2Impl<T, Tag>& operator-=(Vector2Impl<T, Tag> const& rhs)
    {
        static_assert(!VectorTraits::IsFinitePoint<Tag>::value, "Compound subtraction of points not allowed.");
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template<typename TTag = Tag, typename RhsTag>
    std::enable_if_t<VectorTraits::IsFinitePoint<TTag>::value &&
                     !VectorTraits::IsFinitePoint<RhsTag>::value, Vector2Impl<T, TTag>>&
        operator-=(Vector2Impl<T, RhsTag> const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2Impl<T, Tag>& operator*=(T s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    Vector2Impl<T, Tag>& operator/=(T s)
    {
        x /= s;
        y /= s;
        return *this;
    }
};

template<typename T, typename VectorTag_T>
inline bool operator==(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return (lhs.x == rhs.x) &&
           (lhs.y == rhs.y);
}

template<typename T, typename VectorTag_T>
inline bool operator<(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return (lhs.x != rhs.x) ? (lhs.x < rhs.x) : (lhs.y < rhs.y);
}

template<typename T, typename VectorTag_T>
inline bool operator!=(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T, typename VectorTag_T>
inline bool operator<=(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T, typename VectorTag_T>
inline bool operator>(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return rhs < lhs;
}

template<typename T, typename VectorTag_T>
inline bool operator>=(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> operator+(Vector2Impl<T, VectorTag_T> const& lhs,
                                             Vector2Impl<T, VectorTag_T> const& rhs)
{
    static_assert(!VectorTraits::IsFinitePoint<VectorTag_T>::value, "Addition of points is not allowed.");
    return Vector2Impl<T, VectorTag_T>(lhs.x + rhs.x,
                                       lhs.y + rhs.y);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Point2<T>>
    operator+(Point2<T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return Point2<T>(lhs.x + rhs.x,
                     lhs.y + rhs.y);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Point2<T>>
    operator+(Vector2Impl<T, VectorTag_T> const& lhs, Point2<T> const& rhs)
{
    return Point2<T>(lhs.x + rhs.x,
                     lhs.y + rhs.y);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector2Impl<T, VectorTag_T>>
    operator-(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return Vector2Impl<T, VectorTag_T>(lhs.x - rhs.x,
                                       lhs.y - rhs.y);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector2<T>>
    operator-(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return Vector2<T>(lhs.x - rhs.x,
                      lhs.y - rhs.y);
}

template<typename T, typename VectorTag_T> inline
std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Point2<T>>
    operator-(Point2<T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return Point2<T>(lhs.x - rhs.x,
                     lhs.y - rhs.y);
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> operator*(Vector2Impl<T, VectorTag_T> const& v, T s)
{
    return Vector2Impl<T, VectorTag_T>(v.x * s, v.y * s);
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> operator*(T s, Vector2Impl<T, VectorTag_T> const& v)
{
    return Vector2Impl<T, VectorTag_T>(s * v.x, s * v.y);
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> operator/(Vector2Impl<T, VectorTag_T> const& v, T s)
{
    return Vector2Impl<T, VectorTag_T>(v.x / s, v.y / s);
}

template<typename T, typename VectorTag_T>
inline T dot(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

template<typename T, typename VectorTag_T>
inline double length(Vector2Impl<T, VectorTag_T> const& v)
{
    return std::sqrt(static_cast<double>(dot(v, v)));
}

template<typename VectorTag_T>
inline float length(Vector2Impl<float, VectorTag_T> const& v)
{
    return std::sqrt(dot(v, v));
}

template<typename VectorTag_T>
inline long double length(Vector2Impl<long double, VectorTag_T> const& v)
{
    return std::sqrt(dot(v, v));
}

template<typename T, typename VectorTag_T>
inline std::enable_if_t<std::is_floating_point<T>::value, Vector2Impl<T, VectorTag_T>>
normalized(Vector2Impl<T, VectorTag_T> const& v)
{
    T const len = length(v);
    return Vector2Impl<T, VectorTag_T>(v.x / len, v.y / len);
}

/** Computes the counter-clockwise perpendicular normal.
 */
template<typename T>
inline Normal2<T> perp(Vector2<T> const& v)
{
    return Normal2<T>(-v.y, v.x);
}

/** The 2D pseudo cross product, aka perp-dot product.
 * The result corresponds to the 2d bivector in Grassman algebra, ie. the wedge product of the two 2d vectors.
 */
template<typename T>
inline T perp_dot(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return dot(perp(lhs).to_vector(), rhs);
}

template<typename T, typename VectorTag_T>
inline T angle_vector(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return std::acos(dot(lhs, rhs) / (length(lhs) * length(rhs)));
}

template<typename T, typename VectorTag_T>
inline T angle_vector_unit(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return std::acos(dot(lhs, rhs));
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> project(Vector2Impl<T, VectorTag_T> const& lhs,
                                           Vector2Impl<T, VectorTag_T> const& rhs)
{
    return rhs * (dot(lhs, rhs) / dot(rhs, rhs));
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> project_unit(Vector2Impl<T, VectorTag_T> const& lhs,
                                                Vector2Impl<T, VectorTag_T> const& rhs)
{
    return rhs * dot(lhs, rhs);
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> reject(Vector2Impl<T, VectorTag_T> const& lhs,
                                          Vector2Impl<T, VectorTag_T> const& rhs)
{
    return lhs - project(lhs, rhs);
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> reject_unit(Vector2Impl<T, VectorTag_T> const& lhs,
                                               Vector2Impl<T, VectorTag_T> const& rhs)
{
    return lhs - project_unit(lhs, rhs);
}

template<typename T, typename VectorTag_T>
inline T max_component(Vector2Impl<T, VectorTag_T> const& v)
{
    return (v.x < v.y) ? v.y : v.x;
}

template<typename T, typename VectorTag_T>
inline T min_component(Vector2Impl<T, VectorTag_T> const& v)
{
    return (v.x < v.y) ? v.x : v.y;
}

template<typename T, typename VectorTag_T>
inline Vector2Impl<T, VectorTag_T> lerp(Vector2Impl<T, VectorTag_T> const& v1,
                                        Vector2Impl<T, VectorTag_T> const& v2,
                                        T t)
{
    auto const one_minus_t = GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One() - t;
    return Vector2Impl<T, VectorTag_T>(one_minus_t * v1.x + t * v2.x,
                                       one_minus_t * v1.y + t * v2.y);
}
}

#endif
