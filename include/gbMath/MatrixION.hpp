#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_MATRIX_ION_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_MATRIX_ION_HPP

/** @file
 *
 * @brief Formatters and ostream inserters for NxM Matrix.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Matrix.hpp>

#include <ostream>
#include <version>

#ifdef __cpp_lib_format
#include <format>

template<class T, std::size_t M, std::size_t N, class Char_T>
struct std::formatter<GHULBUS_MATH_NAMESPACE::Matrix<T, M, N>, Char_T>
{
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    template<class FormatContext>
    auto format(GHULBUS_MATH_NAMESPACE::Matrix<T, M, N> const& m, FormatContext& ctx) const
    {
        std::format_to(ctx.out(), "[");
        for (std::size_t i = 0; i < M; ++i) {
            std::format_to(ctx.out(), " [{}", m(i, 0));
            for (std::size_t j = 1; j < N; ++j) {
                std::format_to(ctx.out(), " {}", m(i, j));
            }
            std::format_to(ctx.out(), "]");
        }
        return std::format_to(ctx.out(), " ]");
    }
};

namespace GHULBUS_MATH_NAMESPACE
{
    template<typename T, std::size_t M, std::size_t N>
    std::ostream& operator<<(std::ostream& os, Matrix<T, M, N> const& rhs)
    {
        return os << std::format("{}", rhs);
    }
}

#else

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T, std::size_t M, std::size_t N>
std::ostream& operator<<(std::ostream& os, Matrix<T, M, N> const& rhs)
{
    os << "[";
    for (std::size_t i = 0; i < M; ++i) {
        os << " [" << rhs(i, 0);
        for (std::size_t j = 1; j < N; ++j) {
            os << ' ' << rhs(i, j);
        }
        os << ']';
    }
    os << " ]";
    return os;
}
}

#endif

#endif
