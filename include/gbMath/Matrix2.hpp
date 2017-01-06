#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX2_HPP

/** @file
*
* @brief 2D Matrix.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/MatrixPolicies.hpp>
#include <gbMath/Vector2.hpp>

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

    explicit Matrix2(T const* arr, MatrixPolicies::InputOrder_RowMajor)
        :m11(arr[0]), m12(arr[1]),
         m21(arr[2]), m22(arr[3])
    {}

    explicit Matrix2(T const* arr, MatrixPolicies::InputOrder_ColumnMajor)
        :m11(arr[0]), m12(arr[2]),
         m21(arr[1]), m22(arr[3])
    {}

    T& operator[](std::size_t idx)
    {
        return (&m11)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&m11)[idx];
    }

    Vector2<T> row(std::size_t idx) const
    {
        auto const& m = *this;
        return Vector2<T>(m[idx*2], m[idx*2 + 1]);
    }

    Vector2<T> column(std::size_t idx) const
    {
        auto const& m = *this;
        return Vector2<T>(m[idx], m[idx + 2]);
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

    Matrix2<T>& operator/=(T f)
    {
        m11 /= f;
        m12 /= f;
        m21 /= f;
        m22 /= f;
        return *this;
    }

    Matrix2<T>& operator*=(Matrix2<T> const& rhs)
    {
        float const n11 = m11 * rhs.m11 + m12 * rhs.m21;
        m12 = m11 * rhs.m12 + m12 * rhs.m22;
        m11 = n11;
        float const n21 = m21 * rhs.m11 + m22 * rhs.m21;
        m22 = m21 * rhs.m12 + m22 * rhs.m22;
        m21 = n21;
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

template<typename T>
inline Matrix2<T> operator/(Matrix2<T> const& lhs, T f)
{
    return Matrix2<T>(lhs.m11 / f, lhs.m12 / f,
                      lhs.m21 / f, lhs.m22 / f);
}

template<typename T>
inline Matrix2<T> operator*(Matrix2<T> const& lhs, Matrix2<T> const& rhs)
{
    return Matrix2<T>(lhs.m11*rhs.m11 + lhs.m12*rhs.m21, lhs.m11*rhs.m12 + lhs.m12*rhs.m22,
                      lhs.m21*rhs.m11 + lhs.m22*rhs.m21, lhs.m21*rhs.m12 + lhs.m22*rhs.m22);
}

template<typename T>
inline Matrix2<T> matrixFromRowVectors(Vector2<T> const& r1, Vector2<T> const& r2)
{
    return Matrix2<T>(r1.x, r1.y,
                      r2.x, r2.y);
}

template<typename T>
inline Matrix2<T> matrixFromColumnVectors(Vector2<T> const& c1, Vector2<T> const& c2)
{
    return Matrix2<T>(c1.x, c2.x,
                      c1.y, c2.y);
}

template<typename T>
inline Vector2<T> operator*(Matrix2<T> const& m, Vector2<T> const& v)
{
    return Vector2<T>(m.m11*v.x + m.m12*v.y, m.m21*v.x + m.m22*v.y);
}

template<typename T>
inline Matrix2<T> transpose(Matrix2<T> const& m)
{
    return Matrix2<T>(m.m11, m.m21, m.m12, m.m22);
}

template<typename T>
inline T determinant(Matrix2<T> const& m)
{
    return m.m11*m.m22 - m.m21*m.m12;
}

/** Represents a matrix together with a 1/n scaling factor.
 * Use this to model matrices with fractional indices using integral types.
 */
template<typename T>
struct ScaledMatrix2
{
    Matrix2<T> m;
    T inverse_scale_factor;

    ScaledMatrix2() = default;
    ScaledMatrix2(ScaledMatrix2 const&) = default;
    ScaledMatrix2& operator=(ScaledMatrix2 const&) = default;

    ScaledMatrix2(Matrix2<T> const& mat, T n_inverse_scale_factor)
        :m(mat), inverse_scale_factor(n_inverse_scale_factor)
    {}

    template<typename U>
    Matrix2<U> evaluate() const
    {
        Matrix2<U> ret(m);
        ret /= static_cast<U>(inverse_scale_factor);
        return ret;
    }
};

/** Computes the inverse of a matrix.
 * To allow lossless computation of the inverse for integral types, the resulting inverse matrix is given
 * as a ScaledMatrix, where the scaling factor is stored separately from the matrix itself.
 * To obtain the true inverse, call ScaledMatrix2::evaluate() on the return value.
 */
template<typename T>
inline ScaledMatrix2<T> inverse_scaled(Matrix2<T> const& m)
{
    T const det = determinant(m);
    return ScaledMatrix2<T>(Matrix2<T>( m.m22, -m.m12,
                                       -m.m21,  m.m11),
                            det);
}

/** Computes the inverse of a matrix.
 * This function is not defined for integral types, as the division by the determinant might mess up
 * the entries of the inverse for integer matrices. Use inverse_scaled() instead.
 * @note This implementation assumes that multiplying by the inverse is more efficient than division, which
 * is true for floating point types, but might not be true for custom types.
 * If this is undesired, inverse_scaled() instead which evaluates by division instead.
 */
template<typename T>
inline std::enable_if_t<!std::is_integral<T>::value, Matrix2<T>> inverse(Matrix2<T> const& m)
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    T const invDet = Constants<T>::One() / determinant(m);
    return Matrix2<T>( m.m22*invDet, -m.m12*invDet,
                      -m.m21*invDet,  m.m11*invDet);
}

template<typename T>
inline Matrix2<T> identity2()
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    return Matrix2<T>(Constants<T>::One(),  Constants<T>::Zero(),
                      Constants<T>::Zero(), Constants<T>::One());
}
}
#endif
