#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_RATIONAL_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_RATIONAL_HPP

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
namespace RationalPolicies {
    struct AbortOnDivByZero {
        [[noreturn]] inline static void divByZeroHandler() {
            std::abort();
        }
    };

    struct Permissive {};
}

template<typename T, typename RationalPolicy_T>
class RationalImpl {
    static_assert(std::is_integral_v<T>, "Rational requires integral type");
    static_assert(!std::is_same_v<T, bool>, "Rational cannot be instantiated with bool");
public:
    using ValueType = T;
    using PolicyType = RationalPolicy_T;
private:
    T num;
    T denom;
public:
    constexpr RationalImpl() noexcept
        :num(0), denom(1)
    {}

    constexpr explicit RationalImpl(T i) noexcept
        :num(i), denom(1)
    {}

    constexpr RationalImpl(T numerator, T denominator)
        noexcept(std::is_same_v<PolicyType, RationalPolicies::Permissive>)
        :num(0), denom(0)
    {
        if constexpr (!std::is_same_v<PolicyType, RationalPolicies::Permissive>) {
            if (denominator == 0) {
                PolicyType::divByZeroHandler();
            }
        }
        using std::gcd;
        auto const gcd_nd = gcd(numerator, denominator);
        if (gcd_nd != 0) {
            num = numerator / gcd_nd;
            denom = denominator / gcd_nd;
        }
        if constexpr (std::is_signed_v<T>) {
            if (denom < 0) {
                num *= T{ -1 };
                denom *= T{ -1 };
            }
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

    template<typename F, typename = std::enable_if_t<std::is_floating_point_v<F>>>
    explicit constexpr operator F() const noexcept {
        return static_cast<F>(numerator()) / static_cast<F>(denominator());
    }

    friend constexpr bool isValid(RationalImpl const& r) noexcept
    {
        return r.denominator() != 0;
    }

    friend constexpr bool isInteger(RationalImpl const& r) noexcept
    {
        return r.denominator() == 1;
    }

    friend constexpr bool operator==(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        return (lhs.numerator() == rhs.numerator()) && (lhs.denominator() == rhs.denominator());
    }

    friend constexpr bool operator!=(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    friend constexpr bool operator<(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        using std::gcd;
        auto const d1 = gcd(lhs.denominator(), rhs.denominator());
        return (lhs.numerator() * (rhs.denominator() / d1)) < (rhs.numerator() * (lhs.denominator() / d1));
    }

    friend constexpr bool operator<=(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        return !(rhs < lhs);
    }

    friend constexpr bool operator>(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        return rhs < lhs;
    }

    friend constexpr bool operator>=(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        return !(lhs < rhs);
    }

    friend constexpr bool operator<(RationalImpl const& lhs, T const& i) noexcept
    {
        return lhs.numerator() < (i * lhs.denominator());
    }

    friend constexpr bool operator<(T const& i, RationalImpl const& rhs) noexcept
    {
        return (i * rhs.denominator()) < rhs.numerator();
    }

    friend constexpr bool operator<=(RationalImpl const& lhs, T const& i) noexcept
    {
        return !(i < lhs);
    }

    friend constexpr bool operator<=(T const& i, RationalImpl const& rhs) noexcept
    {
        return !(rhs < i);
    }

    friend constexpr bool operator>(RationalImpl const& lhs, T const& i) noexcept
    {
        return i < lhs;
    }

    friend constexpr bool operator>(T const& i, RationalImpl const& rhs) noexcept
    {
        return rhs < i;
    }

    friend constexpr bool operator>=(RationalImpl const& lhs, T const& i) noexcept
    {
        return !(lhs < i);
    }

    friend constexpr bool operator>=(T const& i, RationalImpl const& rhs) noexcept
    {
        return !(i < rhs);
    }

    friend constexpr RationalImpl operator-(RationalImpl const& r) noexcept
    {
        RationalImpl ret;
        ret.num = -r.numerator();
        ret.denom = r.denominator();
        return ret;
    }

    friend constexpr RationalImpl operator+(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        using std::gcd;
        auto const d1 = gcd(lhs.denominator(), rhs.denominator());
        RationalImpl ret;
        if (d1 == 1) {
            ret.num = lhs.numerator() * rhs.denominator() + lhs.denominator() * rhs.numerator();
            ret.denom = lhs.denominator() * rhs.denominator();
        } else if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d1 != 0)) {
            auto const t = lhs.numerator() * (rhs.denominator() / d1) + rhs.numerator() * (lhs.denominator() / d1);
            auto const d2 = gcd(t, d1);
            ret.num = static_cast<T>(t / d2);
            ret.denom = static_cast<T>((lhs.denominator() / d1) * (rhs.denominator() / d2));
        } else [[unlikely]] {
            ret.num = (lhs.numerator() == rhs.numerator()) ? lhs.numerator() : 0;
            ret.denom = 0;
        }
        return ret;
    }

    constexpr RationalImpl& operator+=(RationalImpl const& rhs) noexcept
    {
        using std::gcd;
        auto const d1 = gcd(denominator(), rhs.denominator());
        if (d1 == 1) {
            num = numerator() * rhs.denominator() + denominator() * rhs.numerator();
            denom = denominator() * rhs.denominator();
        } else if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d1 != 0)) {
            auto const t = numerator() * (rhs.denominator() / d1) + rhs.numerator() * (denominator() / d1);
            auto const d2 = gcd(t, d1);
            num = static_cast<T>(t / d2);
            denom = static_cast<T>((denominator() / d1) * (rhs.denominator() / d2));
        } else [[unlikely]] {
            if (numerator() != rhs.numerator()) { num = 0; }
        }
        return *this;
    }

    friend constexpr RationalImpl operator+(RationalImpl const& lhs, T const& i) noexcept
    {
        RationalImpl ret;
        ret.num = lhs.numerator() + (i * lhs.denominator());
        ret.denom = lhs.denominator();
        return ret;
    }

    constexpr RationalImpl& operator+=(T const& i) noexcept
    {
        num += (i * denominator());
        return *this;
    }

    friend constexpr RationalImpl operator+(T const& i, RationalImpl const& rhs) noexcept
    {
        RationalImpl ret;
        ret.num = (i * rhs.denominator()) + rhs.numerator();
        ret.denom = rhs.denominator();
        return ret;
    }

    friend constexpr RationalImpl operator-(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        using std::gcd;
        auto const d1 = gcd(lhs.denominator(), rhs.denominator());
        RationalImpl ret;
        if (d1 == 1) {
            ret.num = lhs.numerator() * rhs.denominator() - lhs.denominator() * rhs.numerator();
            ret.denom = lhs.denominator() * rhs.denominator();
        } else if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d1 != 0)) {
            auto const t = lhs.numerator() * (rhs.denominator() / d1) - rhs.numerator() * (lhs.denominator() / d1);
            auto const d2 = gcd(t, d1);
            ret.num = static_cast<T>(t / d2);
            ret.denom = static_cast<T>((lhs.denominator() / d1) * (rhs.denominator() / d2));
        } else [[unlikely]] {
            if (lhs.numerator() + rhs.numerator() != 0) {
                ret.num = 0;
            } else {
                ret.num = lhs.numerator();
            }
            ret.denom = 0;
        }
        return ret;
    }

    constexpr RationalImpl& operator-=(RationalImpl const& rhs) noexcept
    {
        using std::gcd;
        auto const d1 = gcd(denominator(), rhs.denominator());
        if (d1 == 1) {
            num = numerator() * rhs.denominator() - denominator() * rhs.numerator();
            denom = denominator() * rhs.denominator();
        } else if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d1 != 0)) {
            auto const t = numerator() * (rhs.denominator() / d1) - rhs.numerator() * (denominator() / d1);
            auto const d2 = gcd(t, d1);
            num = static_cast<T>(t / d2);
            denom = static_cast<T>((denominator() / d1) * (rhs.denominator() / d2));
        } else [[unlikely]] {
            if (numerator() + rhs.numerator() != 0) {
                num = 0;
            }
        }
        return *this;
    }

    friend constexpr RationalImpl operator-(RationalImpl const& lhs, T const& i) noexcept
    {
        RationalImpl ret;
        ret.num = lhs.numerator() - (i * lhs.denominator());
        ret.denom = lhs.denominator();
        return ret;
    }

    constexpr RationalImpl& operator-=(T const& i) noexcept
    {
        num -= (i * denominator());
        return *this;
    }

    friend constexpr RationalImpl operator-(T const& i, RationalImpl const& rhs) noexcept
    {
        RationalImpl ret;
        ret.num = (i * rhs.denominator()) - rhs.numerator();
        ret.denom = rhs.denominator();
        return ret;
    }

    friend constexpr RationalImpl operator*(RationalImpl const& lhs, RationalImpl const& rhs) noexcept
    {
        using std::gcd;
        auto const d1 = gcd(lhs.numerator(), rhs.denominator());
        auto const d2 = gcd(lhs.denominator(), rhs.numerator());
        RationalImpl ret;
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || ((d1 != 0) && (d2 != 0))) {
            ret.num = static_cast<T>((lhs.numerator() / d1) * (rhs.numerator() / d2));
            ret.denom = static_cast<T>((lhs.denominator() / d2) * (rhs.denominator() / d1));
        } else [[unlikely]] {
            ret.num = 0;
            ret.denom = 0;
        }
        return ret;
    }

    constexpr RationalImpl& operator*=(RationalImpl const& rhs) noexcept
    {
        using std::gcd;
        auto const d1 = gcd(numerator(), rhs.denominator());
        auto const d2 = gcd(denominator(), rhs.numerator());
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || ((d1 != 0) && (d2 != 0))) {
            num = static_cast<T>((numerator() / d1) * (rhs.numerator() / d2));
            denom = static_cast<T>((denominator() / d2) * (rhs.denominator() / d1));
        } else [[unlikely]] {
            num = 0;
            denom = 0;
        }
        return *this;
    }

    friend constexpr RationalImpl operator*(RationalImpl const& lhs, T const& i) noexcept
    {
        using std::gcd;
        auto const d2 = gcd(lhs.denominator(), i);
        RationalImpl ret;
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d2 != 0)) {
            ret.num = static_cast<T>(lhs.numerator() * (i / d2));
            ret.denom = static_cast<T>(lhs.denominator() / d2);
        } else [[unlikely]] {
            ret.num = 0;
            ret.denom = 0;
        }
        return ret;
    }

    constexpr RationalImpl& operator*=(T const& i) noexcept
    {
        using std::gcd;
        auto const d2 = gcd(denominator(), i);
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d2 != 0)) {
            num *= (i / d2);
            denom /= d2;
        } else [[unlikely]] {
            num = 0;
        }
        return *this;
    }

    friend constexpr RationalImpl operator*(T const& i, RationalImpl const& rhs) noexcept
    {
        using std::gcd;
        auto const d1 = gcd(i, rhs.denominator());
        RationalImpl ret;
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d1 != 0)) {
            ret.num = static_cast<T>((i / d1) * rhs.numerator());
            ret.denom = static_cast<T>(rhs.denominator() / d1);
        } else [[unlikely]] {
            ret.num = 0;
            ret.denom = 0;
        }
        return ret;
    }

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable: 4127)
#endif
    friend constexpr RationalImpl operator/(RationalImpl const& lhs, RationalImpl const& rhs)
        noexcept(std::is_same_v<PolicyType, RationalPolicies::Permissive>)
    {
        if constexpr (!std::is_same_v<PolicyType, RationalPolicies::Permissive>) {
            if (rhs.numerator() == 0) {
                PolicyType::divByZeroHandler();
            }
        }
        using std::gcd;
        auto const d1 = gcd(lhs.numerator(), rhs.numerator()) * ((rhs.numerator() < 0) ? -1 : 1);
        auto const d2 = gcd(lhs.denominator(), rhs.denominator());
        RationalImpl ret;
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || ((d1 != 0) && (d2 != 0))) {
            ret.num = static_cast<T>((lhs.numerator() / d1) * (rhs.denominator() / d2));
            ret.denom = static_cast<T>((lhs.denominator() / d2) * (rhs.numerator() / d1));
        } else [[unlikely]] {
            ret.num = 0;
            ret.denom = 0;
        }
        return ret;
    }

    constexpr RationalImpl& operator/=(RationalImpl const& rhs)
        noexcept(std::is_same_v<PolicyType, RationalPolicies::Permissive>)
    {
        if constexpr (!std::is_same_v<PolicyType, RationalPolicies::Permissive>) {
            if (rhs.numerator() == 0) {
                PolicyType::divByZeroHandler();
            }
        }
        using std::gcd;
        auto const d1 = gcd(numerator(), rhs.numerator()) * ((rhs.numerator() < 0) ? -1 : 1);
        auto const d2 = gcd(denominator(), rhs.denominator());
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || ((d1 != 0) && (d2 != 0))) {
            num = static_cast<T>((numerator() / d1) * (rhs.denominator() / d2));
            denom = static_cast<T>((denominator() / d2) * (rhs.numerator() / d1));
        } else [[unlikely]] {
            num = 0;
        }
        return *this;
    }

    friend constexpr RationalImpl operator/(RationalImpl const& lhs, T const& i)
        noexcept(std::is_same_v<PolicyType, RationalPolicies::Permissive>)
    {
        if constexpr (!std::is_same_v<PolicyType, RationalPolicies::Permissive>) {
            if (i == 0) {
                PolicyType::divByZeroHandler();
            }
        }
        using std::gcd;
        auto const d1 = gcd(lhs.numerator(), i) * ((i < 0) ? -1 : 1);
        RationalImpl ret;
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d1 != 0)) {
            ret.num = static_cast<T>((lhs.numerator() / d1));
            ret.denom = static_cast<T>(lhs.denominator() * (i / d1));
        } else [[unlikely]] {
            ret.num = 0;
            ret.denom = 0;
        }
        return ret;
    }

    constexpr RationalImpl& operator/=(T const& i)
        noexcept(std::is_same_v<PolicyType, RationalPolicies::Permissive>)
    {
        if constexpr (!std::is_same_v<PolicyType, RationalPolicies::Permissive>) {
            if (i == 0) {
                PolicyType::divByZeroHandler();
            }
        }
        using std::gcd;
        auto const d1 = gcd(numerator(), i) * ((i < 0) ? -1 : 1);
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d1 != 0)) {
            num /= d1;
            denom *= (i / d1);
        } else [[unlikely]] {
            num = 0;
        }
        return *this;
    }

    friend constexpr RationalImpl operator/(T const& i, RationalImpl const& rhs)
        noexcept(std::is_same_v<PolicyType, RationalPolicies::Permissive>)
    {
        if constexpr (!std::is_same_v<PolicyType, RationalPolicies::Permissive>) {
            if (rhs.numerator() == 0) {
                PolicyType::divByZeroHandler();
            }
        }
        using std::gcd;
        auto const d1 = gcd(i, rhs.numerator()) * ((rhs.numerator() < 0) ? -1 : 1);
        RationalImpl ret;
        if (!std::is_same_v<PolicyType, RationalPolicies::Permissive> || (d1 != 0)) {
            ret.num = static_cast<T>((i / d1) * rhs.denominator());
            ret.denom = static_cast<T>((rhs.numerator() / d1));
        } else [[unlikely]] {
            ret.num = 0;
            ret.denom = 0;
        }
        return ret;
    }
#ifdef _MSC_VER
#   pragma warning(pop)
#endif
};

template<typename T>
using Rational = RationalImpl<T, RationalPolicies::Permissive>;

template<typename T>
using StrictRational = RationalImpl<T, RationalPolicies::AbortOnDivByZero>;
}
#endif
