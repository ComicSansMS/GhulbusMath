#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR2_HPP

/** @file
 *
 * @brief 2D Vector.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/VectorTraits.hpp>

#include <cmath>
#include <concepts>
#include <cstdint>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T, typename VectorTag_T = VectorTag::Vector>
class Vector2Impl;

namespace VectorTraits {
template<typename V>
struct IsVector2 : public std::false_type {};
template<typename T, typename VectorTag_T>
struct IsVector2<Vector2Impl<T, VectorTag_T>> : public std::true_type {};
}

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
    using ValueType = T;
    using Tag = VectorTag_T;

    T x;
    T y;

    constexpr Vector2Impl()
        :x{}, y{}
    {}
    constexpr Vector2Impl(DoNotInitialize_Tag)
    {}
    constexpr Vector2Impl(Vector2Impl<T, Tag> const&) = default;
    constexpr Vector2Impl<T, Tag>& operator=(Vector2Impl<T, Tag> const&) = default;

    constexpr Vector2Impl(T vx, T vy)
        :x(vx), y(vy)
    {}

    constexpr explicit Vector2Impl(T const* arr)
        :x(arr[0]), y(arr[1])
    {}

    template<typename U>
    constexpr explicit Vector2Impl(Vector2Impl<U, Tag> const& v)
        :x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {}

    [[nodiscard]] constexpr Vector2<T> to_vector() const
    {
        return Vector2<T>(x, y);
    }

    [[nodiscard]] static constexpr Vector2Impl from_vector(Vector2<T> const& v)
    {
        return Vector2Impl(v.x, v.y);
    }

    [[nodiscard]] constexpr T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    [[nodiscard]] constexpr T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    constexpr Vector2Impl& operator+=(Vector2Impl const& rhs)
    {
        static_assert(!VectorTraits::IsFinitePoint<Tag>::value, "Addition of points not allowed.");
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<typename RhsTag>
    constexpr Vector2Impl& operator+=(Vector2Impl<T, RhsTag> const& rhs)
        requires(VectorTraits::IsFinitePoint<Tag>::value && !VectorTraits::IsFinitePoint<RhsTag>::value)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    constexpr Vector2Impl& operator-=(Vector2Impl const& rhs)
    {
        static_assert(!VectorTraits::IsFinitePoint<Tag>::value, "Compound subtraction of points not allowed.");
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template<typename RhsTag>
    constexpr Vector2Impl& operator-=(Vector2Impl<T, RhsTag> const& rhs)
        requires(VectorTraits::IsFinitePoint<Tag>::value && !VectorTraits::IsFinitePoint<RhsTag>::value)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    constexpr Vector2Impl& operator*=(T s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    constexpr Vector2Impl& operator/=(T s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    [[nodiscard]] friend constexpr auto operator<=>(Vector2Impl const&, Vector2Impl const&) = default;

    [[nodiscard]] friend constexpr Vector2Impl operator+(Vector2Impl const& lhs,
                                                         Vector2Impl const& rhs)
    {
        static_assert(!VectorTraits::IsFinitePoint<VectorTag_T>::value, "Addition of points is not allowed.");
        return Vector2Impl(lhs.x + rhs.x,
                           lhs.y + rhs.y);
    }

    [[nodiscard]] friend constexpr Vector2Impl operator*(Vector2Impl const& v, T s)
    {
        return Vector2Impl(v.x * s, v.y * s);
    }

    [[nodiscard]] friend constexpr Vector2Impl operator*(T s, Vector2Impl const& v)
    {
        return Vector2Impl(s * v.x, s * v.y);
    }

    [[nodiscard]] friend constexpr Vector2Impl operator/(Vector2Impl const& v, T s)
    {
        return Vector2Impl(v.x / s, v.y / s);
    }

    [[nodiscard]] friend constexpr T dot(Vector2Impl const& lhs, Vector2Impl const& rhs)
    {
        return (lhs.x * rhs.x) + (lhs.y * rhs.y);
    }
};

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline
Point2<T> operator+(Point2<T> const& lhs,
                    Vector2Impl<T, VectorTag_T> const& rhs)
    requires(!VectorTraits::IsFinitePoint<VectorTag_T>::value)
{
    return Point2<T>(lhs.x + rhs.x,
                     lhs.y + rhs.y);
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline
Point2<T> operator+(Vector2Impl<T, VectorTag_T> const& lhs,
                    Point2<T> const& rhs)
    requires(!VectorTraits::IsFinitePoint<VectorTag_T>::value)
{
    return Point2<T>(lhs.x + rhs.x,
                     lhs.y + rhs.y);
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline
Vector2Impl<T, VectorTag_T> operator-(Vector2Impl<T, VectorTag_T> const& lhs,
                                      Vector2Impl<T, VectorTag_T> const& rhs)
    requires(!VectorTraits::IsFinitePoint<VectorTag_T>::value)
{
    return Vector2Impl<T, VectorTag_T>(lhs.x - rhs.x,
                                       lhs.y - rhs.y);
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline
Vector2<T> operator-(Vector2Impl<T, VectorTag_T> const& lhs,
                     Vector2Impl<T, VectorTag_T> const& rhs)
    requires(VectorTraits::IsFinitePoint<VectorTag_T>::value)
{
    return Vector2<T>(lhs.x - rhs.x,
                      lhs.y - rhs.y);
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline
Point2<T> operator-(Point2<T> const& lhs,
                    Vector2Impl<T, VectorTag_T> const& rhs)
    requires(!VectorTraits::IsFinitePoint<VectorTag_T>::value)
{
    return Point2<T>(lhs.x - rhs.x,
                     lhs.y - rhs.y);
}


template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline double length(Vector2Impl<T, VectorTag_T> const& v)
{
    return std::hypot(static_cast<double>(v.x), static_cast<double>(v.y));
}

template<typename VectorTag_T>
[[nodiscard]] constexpr inline float length(Vector2Impl<float, VectorTag_T> const& v)
{
    return std::hypot(v.x, v.y);
}

template<typename VectorTag_T>
[[nodiscard]] constexpr inline long double length(Vector2Impl<long double, VectorTag_T> const& v)
{
    return std::hypot(v.x, v.y);
}

template<std::floating_point T, typename VectorTag_T>
[[nodiscard]] constexpr inline Vector2Impl<T, VectorTag_T> normalized(Vector2Impl<T, VectorTag_T> const& v)
{
    T const len = length(v);
    return Vector2Impl<T, VectorTag_T>(v.x / len, v.y / len);
}

/** Computes the counter-clockwise perpendicular normal.
 */
template<typename T>
[[nodiscard]] constexpr inline Normal2<T> perp(Vector2<T> const& v)
{
    return Normal2<T>(-v.y, v.x);
}

/** The 2D pseudo cross product, aka perp-dot product.
 * The result corresponds to the 2d bivector in Grassman algebra, ie. the wedge product of the two 2d vectors.
 */
template<typename T>
[[nodiscard]] constexpr inline T perp_dot(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return dot(perp(lhs).to_vector(), rhs);
}

template<std::floating_point T, typename VectorTag_T>
[[nodiscard]] constexpr inline T angle_vector(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return std::acos(dot(lhs, rhs) / (length(lhs) * length(rhs)));
}

template<std::floating_point T, typename VectorTag_T>
[[nodiscard]] constexpr inline T angle_vector_unit(Vector2Impl<T, VectorTag_T> const& lhs, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return std::acos(dot(lhs, rhs));
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline Vector2Impl<T, VectorTag_T> project(Vector2Impl<T, VectorTag_T> const& lhs,
                                                                   Vector2Impl<T, VectorTag_T> const& rhs)
{
    return rhs * (dot(lhs, rhs) / dot(rhs, rhs));
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline Vector2Impl<T, VectorTag_T> project_unit(Vector2Impl<T, VectorTag_T> const& lhs,
                                                                        Vector2Impl<T, VectorTag_T> const& rhs)
{
    return rhs * dot(lhs, rhs);
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline Vector2Impl<T, VectorTag_T> reject(Vector2Impl<T, VectorTag_T> const& lhs,
                                                                  Vector2Impl<T, VectorTag_T> const& rhs)
{
    return lhs - project(lhs, rhs);
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline Vector2Impl<T, VectorTag_T> reject_unit(Vector2Impl<T, VectorTag_T> const& lhs,
                                                                       Vector2Impl<T, VectorTag_T> const& rhs)
{
    return lhs - project_unit(lhs, rhs);
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline T max_component(Vector2Impl<T, VectorTag_T> const& v)
{
    return (v.x < v.y) ? v.y : v.x;
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline T min_component(Vector2Impl<T, VectorTag_T> const& v)
{
    return (v.x < v.y) ? v.x : v.y;
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline Vector2Impl<T, VectorTag_T> lerp(Vector2Impl<T, VectorTag_T> const& v1,
                                                                Vector2Impl<T, VectorTag_T> const& v2,
                                                                T t)
{
    auto const one_minus_t = GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One() - t;
    return Vector2Impl<T, VectorTag_T>(one_minus_t * v1.x + t * v2.x,
                                       one_minus_t * v1.y + t * v2.y);
}
}

#endif
