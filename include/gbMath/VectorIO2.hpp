#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR_IO2_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR_IO2_HPP

/** @file
 *
 * @brief Formatters and ostream inserters for Vector2.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Vector2.hpp>

#include <ostream>
#include <version>

#ifdef __cpp_lib_format
#include <concepts>
#include <format>

template<class T, typename VectorTag_T, class Char_T>
struct std::formatter<GHULBUS_MATH_NAMESPACE::Vector2Impl<T, VectorTag_T>, Char_T>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(GHULBUS_MATH_NAMESPACE::Vector2Impl<T, VectorTag_T> const& v, FormatContext& ctx) const
    {
        if constexpr (std::same_as<T, char>) {
            return std::format_to(ctx.out(), "[{} {}]", static_cast<int>(v.x), static_cast<int>(v.y));
        } else {
            return std::format_to(ctx.out(), "[{} {}]", v.x, v.y);
        }
    }
};

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T, typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return os << std::format("{}", rhs);
}
}

#else

namespace GHULBUS_MATH_NAMESPACE
{
    template<typename T, typename VectorTag_T>
    inline std::ostream& operator<<(std::ostream& os, Vector2Impl<T, VectorTag_T> const& rhs)
    {
        os << '[' << rhs.x << ' ' << rhs.y << ']';
        return os;
    }

    template<typename VectorTag_T>
    inline std::ostream& operator<<(std::ostream& os, Vector2Impl<char, VectorTag_T> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ']';
        return os;
    }

    template<typename VectorTag_T>
    inline std::ostream& operator<<(std::ostream& os, Vector2Impl<signed char, VectorTag_T> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ']';
        return os;
    }

    template<typename VectorTag_T>
    inline std::ostream& operator<<(std::ostream& os, Vector2Impl<unsigned char, VectorTag_T> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ']';
        return os;
    }
}

#endif

#endif
