#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_RATIONAL_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_RATIONAL_HPP

/** @file
*
* @brief Rational number arithmetic.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Rational {
    static_assert(std::is_integral_v<T>, "Rational requires integral type");
    static_assert(!std::is_same_v<T, bool>, "Rational cannot be instantiated with bool");
private:
    T num;
    T denom;
public:
    constexpr Rational() noexcept
        :num(0), denom(1)
    {}

    explicit constexpr Rational(T i) noexcept
        :num(i), denom(1)
    {}

    constexpr Rational(T numerator, T denominator) noexcept
    {
        auto const gcd = std::gcd(numerator, denominator);
        if (gcd != 0) {
            num = numerator / gcd;
            denom = denominator / gcd;
        } else {
            num = 0;
            denom = 0;
        }
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }

    constexpr T numerator() const noexcept
    {
        return num;
    }

    constexpr T denominator() const noexcept
    {
        return denom;
    }

    friend constexpr bool isInteger(Rational<T> const& r) noexcept
    {
        return r.denominator() == 1;
    }

    friend constexpr bool operator==(Rational<T> const& lhs, Rational<T> const& rhs) noexcept
    {
        return (lhs.numerator() == rhs.numerator()) && (lhs.denominator() == rhs.denominator());
    }

    friend constexpr bool operator!=(Rational<T> const& lhs, Rational<T> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    friend constexpr bool operator<(Rational<T> const& lhs, Rational<T> const& rhs) noexcept
    {
        return (lhs.numerator() * rhs.denominator()) < (rhs.numerator() * lhs.denominator());
    }

    friend constexpr bool operator<(Rational<T> const& lhs, T const& i) noexcept
    {
        return lhs.numerator() < (i * lhs.denominator());
    }

    friend constexpr bool operator<(T const& i, Rational<T> const& rhs) noexcept
    {
        return (i * rhs.denominator()) < rhs.numerator();
    }

    friend constexpr Rational<T> operator-(Rational<T> const& r) noexcept
    {
        Rational<T> ret;
        ret.num = -r.numerator();
        ret.denom = r.denominator();
        return ret;
    }

    friend constexpr Rational<T> operator+(Rational<T> const& lhs, Rational<T> const& rhs) noexcept
    {
        if (lhs.denominator() == rhs.denominator()) {
            return Rational<T>(lhs.numerator() + rhs.numerator(), lhs.denominator());
        } else {
            return Rational<T>(lhs.numerator() * rhs.denominator() + rhs.numerator() * lhs.denominator(),
                               lhs.denominator() * rhs.denominator());
        }
    }

    friend constexpr Rational<T> operator+(Rational<T> const& lhs, T const& i) noexcept
    {
        Rational<T> ret;
        ret.num = lhs.numerator() + (i * lhs.denominator());
        ret.denom = lhs.denominator();
        return ret;
    }

    friend constexpr Rational<T> operator+(T const& i, Rational<T> const& rhs) noexcept
    {
        Rational<T> ret;
        ret.num = (i * rhs.denominator()) + rhs.numerator();
        ret.denom = rhs.denominator();
        return ret;
    }

    friend constexpr Rational<T> operator-(Rational<T> const& lhs, Rational<T> const& rhs) noexcept
    {
        return Rational<T>((lhs.numerator() * rhs.denominator()) - (rhs.numerator() * lhs.denominator()),
                           lhs.denominator() * rhs.denominator());
    }

    friend constexpr Rational<T> operator-(Rational<T> const& lhs, T const& i) noexcept
    {
        Rational<T> ret;
        ret.num = lhs.numerator() - (i * lhs.denominator());
        ret.denom = lhs.denominator();
        return ret;
    }

    friend constexpr Rational<T> operator-(T const& i, Rational<T> const& rhs) noexcept
    {
        Rational<T> ret;
        ret.num = (i * rhs.denominator()) - rhs.numerator();
        ret.denom = rhs.denominator();
        return ret;
    }

    friend constexpr Rational<T> operator*(Rational<T> const& lhs, Rational<T> const& rhs) noexcept
    {
        return Rational<T>(lhs.numerator() * rhs.numerator(),
                           lhs.denominator() * rhs.denominator());
    }

    friend constexpr Rational<T> operator*(Rational<T> const& lhs, T const& i) noexcept
    {
        return Rational<T>(lhs.numerator() * i, lhs.denominator());
    }

    friend constexpr Rational<T> operator*(T const& i, Rational<T> const& rhs) noexcept
    {
        return Rational<T>(i * rhs.numerator(), rhs.denominator());
    }

    friend constexpr Rational<T> operator/(Rational<T> const& lhs, Rational<T> const& rhs) noexcept
    {
        return Rational<T>(lhs.numerator() * rhs.denominator(),
                           lhs.denominator() * rhs.numerator());
    }

    friend constexpr Rational<T> operator/(Rational<T> const& lhs, T const& i) noexcept
    {
        return Rational<T>(lhs.numerator(),
                           lhs.denominator() * i);
    }

    friend constexpr Rational<T> operator/(T const& i, Rational<T> const& rhs) noexcept
    {
        return Rational<T>(i * rhs.denominator(),
                           rhs.numerator());
    }
};

}
#endif
