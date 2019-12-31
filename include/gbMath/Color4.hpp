#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_COLOR4_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_COLOR4_HPP

/** @file
 *
 * @brief RGBA Color Vector.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector4.hpp>

#include <cstdint>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template <typename T>
class Color4;

using Color4f = Color4<float>;

template <typename T>
class Color4 {
public:
    using ValueType = T;

    T r;
    T g;
    T b;
    T a;

    Color4() = default;
    Color4(Color4 const&) = default;
    Color4& operator=(Color4 const&) = default;

    Color4(T red, T green, T blue) noexcept
        :r(red), g(green), b(blue), a(1)
    {}

    Color4(T red, T green, T blue, T alpha) noexcept
        :r(red), g(green), b(blue), a(alpha)
    {}

    explicit Color4(T const* arr) noexcept
        :r(arr[0]), g(arr[1]), b(arr[2]), a(arr[3])
    {}

    T& operator[](std::size_t idx) noexcept
    {
        return (&r)[idx];
    }

    T const& operator[](std::size_t idx) const noexcept
    {
        return (&r)[idx];
    }

    Color4& operator+=(Color4 const& rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        a += rhs.a;
        return *this;
    }

    Color4& operator-=(Color4 const& rhs) {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        a -= rhs.a;
        return *this;
    }

    Color4& operator*=(T rhs) {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        a *= rhs;
        return *this;
    }

    Color4& operator/=(T rhs) {
        r /= rhs;
        g /= rhs;
        b /= rhs;
        a /= rhs;
        return *this;
    }
};

template<typename T>
inline bool operator==(Color4<T> const& lhs, Color4<T> const& rhs)
{
    return (lhs.r == rhs.r) &&
           (lhs.g == rhs.g) &&
           (lhs.b == rhs.b) &&
           (lhs.a == rhs.a);
}

template<typename T>
inline bool operator<(Color4<T> const& lhs, Color4<T> const& rhs)
{
    if(lhs.r != rhs.r) {
        return lhs.r < rhs.r;
    } else if(lhs.g != rhs.g) {
        return lhs.g < rhs.g;
    } else if(lhs.b != rhs.b) {
        return lhs.b < rhs.b;
    } else {
        return lhs.a < rhs.a;
    }
}

template<typename T>
inline bool operator!=(Color4<T> const& lhs, Color4<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline bool operator<=(Color4<T> const& lhs, Color4<T> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T>
inline bool operator>(Color4<T> const& lhs, Color4<T> const& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator>=(Color4<T> const& lhs, Color4<T> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
inline Color4<T> operator+(Color4<T> const& lhs, Color4<T> const& rhs)
{
    return Color4<T>(lhs.r + rhs.r,
                     lhs.g + rhs.g,
                     lhs.b + rhs.b,
                     lhs.a + rhs.a);
}

template<typename T>
inline Color4<T> operator-(Color4<T> const& lhs, Color4<T> const& rhs)
{
    return Color4<T>(lhs.r - rhs.r,
                     lhs.g - rhs.g,
                     lhs.b - rhs.b,
                     lhs.a - rhs.a);
}

template<typename T>
inline Color4<T> operator*(Color4<T> const& v, T s)
{
    return Color4<T>(v.r * s, v.g * s, v.b * s, v.a * s);
}

template<typename T>
inline Color4<T> operator*(T s, Color4<T> const& v)
{
    return Color4<T>(s * v.r, s * v.g, s * v.b, s * v.a);
}

template<typename T>
inline Color4<T> operator/(Color4<T> const& v, T s)
{
    return Color4<T>(v.r / s, v.g / s, v.b / s, v.a / s);
}
}

#endif
