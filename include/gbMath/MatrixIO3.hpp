#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_MATRIX_IO3_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_MATRIX_IO3_HPP

/** @file
 *
 * @brief Formatters and ostream inserters for Matrix3.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Matrix3.hpp>

#include <ostream>
#include <version>

#ifdef __cpp_lib_format
#include <format>

template<class T, class Char_T>
struct std::formatter<GHULBUS_MATH_NAMESPACE::Matrix3<T>, Char_T>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(GHULBUS_MATH_NAMESPACE::Matrix3<T> const& m, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "[ [{} {} {}] [{} {} {}] [{} {} {}] ]",
            m.m11, m.m12, m.m13,
            m.m21, m.m22, m.m23,
            m.m31, m.m32, m.m33);
    }
};

namespace GHULBUS_MATH_NAMESPACE
{
    template<typename T>
    std::ostream& operator<<(std::ostream& os, Matrix3<T> const& rhs)
    {
        return os << std::format("{}", rhs);
    }
}

#else

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix3<T> const& rhs)
{
    os << "[ [" << rhs.m11 << ' ' << rhs.m12 << ' ' << rhs.m13
       << "] [" << rhs.m21 << ' ' << rhs.m22 << ' ' << rhs.m23
       << "] [" << rhs.m31 << ' ' << rhs.m32 << ' ' << rhs.m33 << "] ]";
    return os;
}
}

#endif

#endif
