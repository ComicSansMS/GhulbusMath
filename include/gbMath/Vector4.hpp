#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR4_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR4_HPP

/** @file
 *
 * @brief 4D Vector.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>

#include <cmath>
#include <concepts>
#include <cstdint>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Vector4;

namespace VectorTraits {
template<typename V>
struct IsVector4 : public std::false_type {};
template<typename T>
struct IsVector4<Vector4<T>> : public std::true_type {};
}

template<typename T>
class Vector4 {
public:
    using ValueType = T;

    T x;
    T y;
    T z;
    T w;

    constexpr Vector4()
        :x{}, y{}, z{}, w{}
    {}
    constexpr Vector4(DoNotInitialize_Tag)
    {}
    constexpr Vector4(Vector4<T> const&) = default;
    constexpr Vector4<T>& operator=(Vector4<T> const&) = default;

    constexpr Vector4(T vx, T vy, T vz, T vw)
        :x(vx), y(vy), z(vz), w(vw)
    {}

    constexpr explicit Vector4(T const* arr)
        :x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3])
    {}

    template<typename U>
    constexpr explicit Vector4(Vector4<U> const& v)
        :x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(static_cast<T>(v.w))
    {}

    [[nodiscard]] constexpr T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    [[nodiscard]] constexpr T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    constexpr Vector4<T>& operator+=(Vector4<T> const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    constexpr Vector4<T>& operator-=(Vector4<T> const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    constexpr Vector4<T>& operator*=(T s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }

    constexpr Vector4<T>& operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
        return *this;
    }

    [[nodiscard]] friend constexpr auto operator<=>(Vector4 const&, Vector4 const&) = default;

    [[nodiscard]] friend constexpr Vector4 operator+(Vector4 const& lhs, Vector4 const& rhs)
    {
        return Vector4(lhs.x + rhs.x,
                       lhs.y + rhs.y,
                       lhs.z + rhs.z,
                       lhs.w + rhs.w);
    }

    [[nodiscard]] friend constexpr Vector4 operator-(Vector4 const& lhs, Vector4 const& rhs)
    {
        return Vector4<T>(lhs.x - rhs.x,
                          lhs.y - rhs.y,
                          lhs.z - rhs.z,
                          lhs.w - rhs.w);
    }

    [[nodiscard]] friend constexpr Vector4 operator*(Vector4 const& v, T s)
    {
        return Vector4(v.x * s, v.y * s, v.z * s, v.w * s);
    }

    [[nodiscard]] friend constexpr Vector4 operator*(T s, Vector4 const& v)
    {
        return Vector4(s * v.x, s * v.y, s * v.z, s * v.w);
    }

    [[nodiscard]] friend constexpr Vector4 operator/(Vector4 const& v, T s)
    {
        return Vector4(v.x / s, v.y / s, v.z / s, v.w / s);
    }

    [[nodiscard]] friend constexpr T dot(Vector4 const& lhs, Vector4 const& rhs)
    {
        return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
    }
};

template<typename T>
[[nodiscard]] inline double length(Vector4<T> const& v)
{
    return std::sqrt(static_cast<double>(dot(v, v)));
}

[[nodiscard]] inline float length(Vector4<float> const& v)
{
    return std::sqrt(dot(v, v));
}

[[nodiscard]] inline long double length(Vector4<long double> const& v)
{
    return std::sqrt(dot(v, v));
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Vector4<T> normalized(Vector4<T> const& v)
{
    T const len = length(v);
    return Vector4<T>(v.x / len, v.y / len, v.z / len, v.w / len);
}
}

#endif
