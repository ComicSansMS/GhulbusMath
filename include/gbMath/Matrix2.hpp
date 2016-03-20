#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX2_HPP

/** @file
*
* @brief 2D Matrix.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <cmath>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Matrix2
{
public:
    T m11, m12;
    T m21, m22;

    Matrix2() = default;
    Matrix2(Matrix2 const&) = default;
    Matrix2& operator=(Matrix2 const&) = default;

    Matrix2(T n11, T n12, T n21, T n22)
        :m11(n11), m12(n12), m21(n21), m22(n22)
    {}

    template<typename U>
    explicit Matrix2(Matrix2<U> const& rhs)
        :m11(static_cast<T>(rhs.m11)), m12(static_cast<T>(rhs.m12)),
         m21(static_cast<T>(rhs.m21)), m22(static_cast<T>(rhs.m22))
    {}

    T& operator[](std::size_t idx)
    {
        return (&m11)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&m11)[idx];
    }

    Matrix2<T>& operator+=(Matrix2<T> const& rhs)
    {
        m11 += rhs.m11;
        m12 += rhs.m12;
        m21 += rhs.m21;
        m22 += rhs.m22;
        return *this;
    }

    Matrix2<T>& operator-=(Matrix2<T> const& rhs)
    {
        m11 -= rhs.m11;
        m12 -= rhs.m12;
        m21 -= rhs.m21;
        m22 -= rhs.m22;
        return *this;
    }

    Matrix2<T>& operator*=(T f)
    {
        m11 *= f;
        m12 *= f;
        m21 *= f;
        m22 *= f;
        return *this;
    }
};

template<typename T>
inline bool operator==(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return ((lhs.m11 == rhs.m11) && (lhs.m12 == rhs.m12) && (lhs.m21 == rhs.m21) && (lhs.m22 == rhs.m22));
}

template<typename T>
inline bool operator<(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    std::size_t i;
    for(i = 0; (i < 3) && (lhs[i] == rhs[i]); ++i) ;
    return (lhs[i] < rhs[i]);
}

template<typename T>
inline bool operator!=(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline bool operator<=(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T>
inline bool operator>(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator>=(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
inline Matrix2<T> operator+(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return Matrix2<T>(lhs.m11 + rhs.m11, lhs.m12 + rhs.m12,
                      lhs.m21 + rhs.m21, lhs.m22 + rhs.m22);
}

template<typename T>
inline Matrix2<T> operator-(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return Matrix2<T>(lhs.m11 - rhs.m11, lhs.m12 - rhs.m12,
                      lhs.m21 - rhs.m21, lhs.m22 - rhs.m22);
}

template<typename T>
inline Matrix2<T> operator*(Matrix2<T> const& lhs, T f)
{
    return Matrix2<T>(lhs.m11 * f, lhs.m12 * f,
                      lhs.m21 * f, lhs.m22 * f);
}

template<typename T>
inline Matrix2<T> operator*(T f, Matrix2<T> const& rhs)
{
    return Matrix2<T>(f * rhs.m11, f * rhs.m12,
                      f * rhs.m21, f * rhs.m22);
}
}
#endif
