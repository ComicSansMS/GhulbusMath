#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_MATRIX_IO4_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_MATRIX_IO4_HPP

/** @file
 *
 * @brief Formatters and ostream inserters for Matrix4.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Matrix4.hpp>

#include <ostream>
#include <version>

#ifdef __cpp_lib_format
#include <format>

template<class T, class Char_T>
struct std::formatter<GHULBUS_MATH_NAMESPACE::Matrix4<T>, Char_T>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(GHULBUS_MATH_NAMESPACE::Matrix4<T> const& m, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "[ [{} {} {} {}] [{} {} {} {}] [{} {} {} {}] [{} {} {} {}] ]",
            m.m11, m.m12, m.m13, m.m14,
            m.m21, m.m22, m.m23, m.m24,
            m.m31, m.m32, m.m33, m.m34,
            m.m41, m.m42, m.m43, m.m44);
    }
};

namespace GHULBUS_MATH_NAMESPACE
{
    template<typename T>
    std::ostream& operator<<(std::ostream& os, Matrix4<T> const& rhs)
    {
        return os << std::format("{}", rhs);
    }
}

#else

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix4<T> const& rhs)
{
    os << "[ [" << rhs.m11 << ' ' << rhs.m12 << ' ' << rhs.m13 << ' ' << rhs.m14
       << "] [" << rhs.m21 << ' ' << rhs.m22 << ' ' << rhs.m23 << ' ' << rhs.m24
       << "] [" << rhs.m31 << ' ' << rhs.m32 << ' ' << rhs.m33 << ' ' << rhs.m34
       << "] [" << rhs.m41 << ' ' << rhs.m42 << ' ' << rhs.m43 << ' ' << rhs.m44 << "] ]";
    return os;
}
}

#endif

#endif
