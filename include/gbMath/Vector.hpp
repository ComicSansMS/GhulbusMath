#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_HPP

/** @file
 *
 * @brief N-dimensional Vector.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/NumberTypeTraits.hpp>

#include <array>
#include <algorithm>
#include <cmath>
#include <compare>
#include <concepts>
#include <cstdint>
#include <functional>
#include <numeric>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T, std::size_t N>
class Vector;

namespace VectorTraits {
template<typename V>
struct IsVector : public std::false_type {};
template<typename T, std::size_t N>
struct IsVector<Vector<T, N>> : public std::true_type {};
}

template<typename T, std::size_t N>
class Vector {
public:
    using ValueType = T;

    std::array<T, N> v;

    constexpr Vector()
        :v()
    {}
    constexpr Vector(DoNotInitialize_Tag)
    {}

    template<typename... Args>
    constexpr explicit Vector(Args... args)
        requires((sizeof...(args) == N) && (std::same_as<Args, T> && ...))
    : v{args...}
    {}

    constexpr explicit Vector(T* arr)
    {
        std::copy(arr, arr + N, begin(v));
    }

    constexpr Vector(Vector const&) = default;
    constexpr Vector& operator=(Vector const&) = default;

    template<std::convertible_to<T> U>
    constexpr explicit Vector(Vector<U, N> const& other)
    {
        std::transform(begin(other.v), end(other.v), begin(v),
            [](U const& u) -> T { return static_cast<T>(u); });
    }

    [[nodiscard]] constexpr std::size_t dimension() const
    {
        return N;
    }

    [[nodiscard]] constexpr T& operator[](std::size_t idx)
    {
        return v[idx];
    }

    [[nodiscard]] constexpr T const& operator[](std::size_t idx) const
    {
        return v[idx];
    }

    constexpr Vector& operator+=(Vector const& rhs)
    {
        std::transform(begin(v), end(v), begin(rhs.v), begin(v), std::plus<T>{});
        return *this;
    }

    constexpr Vector& operator-=(Vector const& rhs)
    {
        std::transform(begin(v), end(v), begin(rhs.v), begin(v), std::minus<T>{});
        return *this;
    }

    constexpr Vector& operator*=(T s)
    {
        std::transform(begin(v), end(v), begin(v), [s](T n) { return n * s; });
        return *this;
    }

    constexpr Vector& operator/=(T s)
    {
        std::transform(begin(v), end(v), begin(v), [s](T n) { return n / s; });
        return *this;
    }

    [[nodiscard]] friend constexpr auto operator<=>(Vector const&, Vector const&) = default;

    [[nodiscard]] friend constexpr Vector operator+(Vector const& lhs, Vector const& rhs)
    {
        Vector ret(doNotInitialize);
        std::transform(begin(lhs.v), end(lhs.v), begin(rhs.v), begin(ret.v), std::plus<T>{});
        return ret;
    }

    [[nodiscard]] friend constexpr Vector operator-(Vector const& lhs, Vector const& rhs)
    {
        Vector ret(doNotInitialize);
        std::transform(begin(lhs.v), end(lhs.v), begin(rhs.v), begin(ret.v), std::minus<T>{});
        return ret;
    }

    [[nodiscard]] friend constexpr Vector operator*(Vector const& v, T s)
    {
        Vector ret(doNotInitialize);
        std::transform(begin(v.v), end(v.v), begin(ret.v), [s](T n) { return n * s; });
        return ret;
    }

    [[nodiscard]] friend constexpr Vector operator*(T s, Vector const& v)
    {
        Vector ret(doNotInitialize);
        std::transform(begin(v.v), end(v.v), begin(ret.v), [s](T n) { return s * n; });
        return ret;
    }

    [[nodiscard]] friend constexpr Vector operator/(Vector const& v, T s)
    {
        Vector ret(doNotInitialize);
        std::transform(begin(v.v), end(v.v), begin(ret.v), [s](T n) { return n / s; });
        return ret;
    }

    [[nodiscard]] friend constexpr T dot(Vector const& lhs, Vector const& rhs)
    {
        return std::inner_product(begin(lhs.v), end(lhs.v),
            begin(rhs.v), traits::Constants<T>::Zero());
    }
};
template<typename T, std::size_t N>
[[nodiscard]] inline double length(Vector<T, N> const& v)
{
    return std::sqrt(static_cast<double>(dot(v, v)));
}

template<std::size_t N>
[[nodiscard]] inline float length(Vector<float, N> const& v)
{
    return std::sqrt(dot(v, v));
}

template<std::size_t N>
[[nodiscard]] inline long double length(Vector<long double, N> const& v)
{
    return std::sqrt(dot(v, v));
}

template<std::floating_point T, std::size_t N>
[[nodiscard]] constexpr inline Vector<T, N> normalized(Vector<T, N> const& v)
{
    T const len = length(v);
    return v / len;
}
}

#endif
