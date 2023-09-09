#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR_IO_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR_IO_HPP

/** @file
 *
 * @brief Formatters and ostream inserters for Vector types.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Vector.hpp>
#include <gbMath/Vector2.hpp>
#include <gbMath/Vector3.hpp>
#include <gbMath/Vector4.hpp>

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

template<class T, typename VectorTag_T, class Char_T>
struct std::formatter<GHULBUS_MATH_NAMESPACE::Vector3Impl<T, VectorTag_T>, Char_T>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(GHULBUS_MATH_NAMESPACE::Vector3Impl<T, VectorTag_T> const& v, FormatContext& ctx) const
    {
        if constexpr (std::same_as<T, char>) {
            return std::format_to(ctx.out(), "[{} {} {}]", static_cast<int>(v.x), static_cast<int>(v.y), static_cast<int>(v.z));
        } else {
            return std::format_to(ctx.out(), "[{} {} {}]", v.x, v.y, v.z);
        }
    }
};

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
template<typename T, typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector2Impl<T, VectorTag_T> const& rhs)
{
    return os << std::format("{}", rhs);
}

template<typename T, typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector3Impl<T, VectorTag_T> const& rhs)
{
    return os << std::format("{}", rhs);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Vector4<T> const& rhs)
{
    return os << std::format("{}", rhs);
}

template<typename T, std::size_t N>
inline std::ostream& operator<<(std::ostream& os, Vector<T, N> const& rhs)
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

    template<typename T, typename VectorTag_T>
    inline std::ostream& operator<<(std::ostream& os, Vector3Impl<T, VectorTag_T> const& rhs)
    {
        os << '[' << rhs.x << ' ' << rhs.y << ' ' << rhs.z << ']';
        return os;
    }

    template<typename VectorTag_T>
    inline std::ostream& operator<<(std::ostream& os, Vector3Impl<char, VectorTag_T> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ']';
        return os;
    }

    template<typename VectorTag_T>
    inline std::ostream& operator<<(std::ostream& os, Vector3Impl<signed char, VectorTag_T> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ']';
        return os;
    }

    template<typename VectorTag_T>
    inline std::ostream& operator<<(std::ostream& os, Vector3Impl<unsigned char, VectorTag_T> const& rhs)
    {
        os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ']';
        return os;
    }

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
