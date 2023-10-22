#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR_ION_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR_ION_HPP

/** @file
 *
 * @brief Formatters and ostream inserters for N-dimensional Vector.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Vector.hpp>

#include <ostream>
#include <version>

#ifdef __cpp_lib_format
#include <concepts>
#include <format>

template<class T, std::size_t N, class Char_T>
struct std::formatter<GHULBUS_MATH_NAMESPACE::Vector<T, N>, Char_T>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(GHULBUS_MATH_NAMESPACE::Vector<T, N> const& v, FormatContext& ctx) const
    {
        if constexpr (std::same_as<T, char>) {
            std::format_to(ctx.out(), "[{}", static_cast<int>(v.v[0]));
        } else {
            std::format_to(ctx.out(), "[{}", v.v[0]);
        }
        for (std::size_t i = 1; i < N; ++i) {
            if constexpr (std::same_as<T, char>) {
                std::format_to(ctx.out(), " {}", static_cast<int>(v.v[i]));
            } else {
                std::format_to(ctx.out(), " {}", v.v[i]);
            }
        }
        return std::format_to(ctx.out(), "]");
    }
};

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T, std::size_t N>
inline std::ostream& operator<<(std::ostream& os, Vector<T, N> const& rhs)
{
    return os << std::format("{}", rhs);
}
}

#else

namespace GHULBUS_MATH_NAMESPACE
{
    template<typename T, std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, Vector<T, N> const& rhs)
    {
        os << '[';
        if constexpr (std::same_as<T, char> || std::same_as<T, signed char> || std::same_as<T, unsigned char>) {
            os << static_cast<int>(rhs.v[0]);
        } else {
            os << rhs.v[0];
        }
        for (std::size_t i = 1; i < N; ++i) {
            if constexpr (std::same_as<T, char> || std::same_as<T, signed char> || std::same_as<T, unsigned char>)
            {
                os << ' ' << static_cast<int>(rhs.v[i]);

            } else {
                os << ' ' << rhs.v[i];
            }
        }
        os << ']';
        return os;
    }
}

#endif

#endif
