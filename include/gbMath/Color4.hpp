#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_COLOR4_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_COLOR4_HPP

/** @file
 *
 * @brief RGBA Color Vector.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
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

    constexpr Color4()
        :r{}, g{}, b{}, a{}
    {}
    constexpr Color4(DoNotInitialize_Tag)
    {}
    constexpr Color4(Color4 const&) = default;
    constexpr Color4& operator=(Color4 const&) = default;

    constexpr Color4(T red, T green, T blue) noexcept
        :r(red), g(green), b(blue), a(1)
    {}

    constexpr Color4(T red, T green, T blue, T alpha) noexcept
        :r(red), g(green), b(blue), a(alpha)
    {}

    constexpr explicit Color4(T const* arr) noexcept
        :r(arr[0]), g(arr[1]), b(arr[2]), a(arr[3])
    {}

    [[nodiscard]] constexpr T& operator[](std::size_t idx) noexcept
    {
        return (&r)[idx];
    }

    [[nodiscard]] constexpr T const& operator[](std::size_t idx) const noexcept
    {
        return (&r)[idx];
    }

    constexpr Color4& operator+=(Color4 const& rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        a += rhs.a;
        return *this;
    }

    constexpr Color4& operator-=(Color4 const& rhs) {
        r -= rhs.r;
        g -= rhs.g;
        b -= rhs.b;
        a -= rhs.a;
        return *this;
    }

    constexpr Color4& operator*=(T rhs) {
        r *= rhs;
        g *= rhs;
        b *= rhs;
        a *= rhs;
        return *this;
    }

    constexpr Color4& operator/=(T rhs) {
        r /= rhs;
        g /= rhs;
        b /= rhs;
        a /= rhs;
        return *this;
    }
    
    [[nodiscard]] friend constexpr auto operator<=>(Color4 const&, Color4 const&) = default;

    [[nodiscard]] friend constexpr Color4 operator+(Color4 const& lhs, Color4 const& rhs)
    {
        return Color4(lhs.r + rhs.r,
                      lhs.g + rhs.g,
                      lhs.b + rhs.b,
                      lhs.a + rhs.a);
    }

    [[nodiscard]] friend constexpr Color4 operator-(Color4 const& lhs, Color4 const& rhs)
    {
        return Color4(lhs.r - rhs.r,
                      lhs.g - rhs.g,
                      lhs.b - rhs.b,
                      lhs.a - rhs.a);
    }

    [[nodiscard]] friend constexpr Color4 operator*(Color4 const& v, T s)
    {
        return Color4(v.r * s, v.g * s, v.b * s, v.a * s);
    }

    [[nodiscard]] friend constexpr Color4 operator*(T s, Color4 const& v)
    {
        return Color4(s * v.r, s * v.g, s * v.b, s * v.a);
    }

    [[nodiscard]] friend constexpr Color4 operator/(Color4 const& v, T s)
    {
        return Color4(v.r / s, v.g / s, v.b / s, v.a / s);
    }

};
}

#endif
