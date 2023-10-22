#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR_IO4_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR_IO4_HPP

/** @file
 *
 * @brief Formatters and ostream inserters for Vector4.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Vector4.hpp>

#include <ostream>
#include <version>

#ifdef __cpp_lib_format
#include <concepts>
#include <format>

template<class T, class Char_T>
struct std::formatter<GHULBUS_MATH_NAMESPACE::Vector4<T>, Char_T>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(GHULBUS_MATH_NAMESPACE::Vector4<T> const& v, FormatContext& ctx) const
    {
        if constexpr (std::same_as<T, char>) {
            return std::format_to(ctx.out(), "[{} {} {} {}]",
                static_cast<int>(v.x), static_cast<int>(v.y), static_cast<int>(v.z), static_cast<int>(v.w));
        } else {
            return std::format_to(ctx.out(), "[{} {} {} {}]", v.x, v.y, v.z, v.w);
        }
    }
};

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
inline std::ostream& operator<<(std::ostream& os, Vector4<T> const& rhs)
{
    return os << std::format("{}", rhs);
}
}

#else

namespace GHULBUS_MATH_NAMESPACE
{
    template<typename T>
    inline std::ostream& operator<<(std::ostream& os, Vector4<T> const& rhs)
    {
        os << '[' << rhs.x << ' ' << rhs.y << ' ' << rhs.z << ' ' << rhs.w << ']';
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, Vector4<char> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ' ' << static_cast<int>(rhs.w) << ']';
        return os;
    }


    inline std::ostream& operator<<(std::ostream& os, Vector4<signed char> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ' ' << static_cast<int>(rhs.w) << ']';
        return os;
    }


    inline std::ostream& operator<<(std::ostream& os, Vector4<unsigned char> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ' ' << static_cast<int>(rhs.w) << ']';
        return os;
    }
}

#endif

#endif
