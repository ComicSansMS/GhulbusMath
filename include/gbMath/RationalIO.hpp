#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_RATIONAL_IO_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_RATIONAL_IO_HPP

/** @file
 *
 * @brief Formatters and ostream inserters for rational type.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Rational.hpp>

#include <ostream>
#include <version>

#ifdef __cpp_lib_format
#include <concepts>
#include <format>

template<class T, class Char_T>
struct std::formatter<GHULBUS_MATH_NAMESPACE::Rational<T>, Char_T>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(GHULBUS_MATH_NAMESPACE::Rational<T> const& r, FormatContext& ctx) const
    {
        if constexpr (std::same_as<T, char>) {
            return std::format_to(ctx.out(), "{}/{}", static_cast<int>(r.numerator()), static_cast<int>(r.denominator()));
        }
        else {
            return std::format_to(ctx.out(), "{}/{}", r.numerator(), r.denominator());
        }
    }
};

namespace GHULBUS_MATH_NAMESPACE
{
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, Rational<T> const& rhs)
    {
        return os << std::format("{}", rhs);
    }
}

#else

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
inline std::ostream& operator<<(std::ostream& os, Rational<T> const& rhs)
{
    return os << rhs.numerator() << '/' << rhs.denominator();
}

inline std::ostream& operator<<(std::ostream& os, Rational<char> const& rhs)
{
    return os << static_cast<int>(rhs.numerator()) << '/' << static_cast<int>(rhs.denominator());
}

inline std::ostream& operator<<(std::ostream& os, Rational<signed char> const& rhs)
{
    return os << static_cast<int>(rhs.numerator()) << '/' << static_cast<int>(rhs.denominator());
}

inline std::ostream& operator<<(std::ostream& os, Rational<unsigned char> const& rhs)
{
    return os << static_cast<int>(rhs.numerator()) << '/' << static_cast<int>(rhs.denominator());
}
}

#endif

#endif
