#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX2_HPP

/** @file
 *
 * @brief 2D Matrix.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/MatrixPolicies.hpp>
#include <gbMath/Vector2.hpp>

#include <cmath>
#include <concepts>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Matrix2
{
public:
    using ValueType = T;

    T m11, m12;
    T m21, m22;

    constexpr Matrix2()
        :m11{}, m12{},
         m21{}, m22{}
    {}
    constexpr Matrix2(DoNotInitialize_Tag)
    {}
    constexpr Matrix2(Matrix2 const&) = default;
    constexpr Matrix2& operator=(Matrix2 const&) = default;

    constexpr Matrix2(T n11, T n12, T n21, T n22)
        :m11(n11), m12(n12), m21(n21), m22(n22)
    {}

    template<typename U>
    constexpr explicit Matrix2(Matrix2<U> const& rhs)
        :m11(static_cast<T>(rhs.m11)), m12(static_cast<T>(rhs.m12)),
         m21(static_cast<T>(rhs.m21)), m22(static_cast<T>(rhs.m22))
    {}

    constexpr explicit Matrix2(T const* arr, MatrixPolicies::InputOrder_RowMajor)
        :m11(arr[0]), m12(arr[1]),
         m21(arr[2]), m22(arr[3])
    {}

    constexpr explicit Matrix2(T const* arr, MatrixPolicies::InputOrder_ColumnMajor)
        :m11(arr[0]), m12(arr[2]),
         m21(arr[1]), m22(arr[3])
    {}

    [[nodiscard]] constexpr T& operator[](std::size_t idx)
    {
        return (&m11)[idx];
    }

    [[nodiscard]] constexpr T const& operator[](std::size_t idx) const
    {
        return (&m11)[idx];
    }

    [[nodiscard]] constexpr Vector2<T> row(std::size_t idx) const
    {
        auto const& m = *this;
        return Vector2<T>(m[idx*2], m[idx*2 + 1]);
    }

    [[nodiscard]] constexpr Vector2<T> column(std::size_t idx) const
    {
        auto const& m = *this;
        return Vector2<T>(m[idx], m[idx + 2]);
    }

    constexpr Matrix2& operator+=(Matrix2 const& rhs)
    {
        m11 += rhs.m11;
        m12 += rhs.m12;
        m21 += rhs.m21;
        m22 += rhs.m22;
        return *this;
    }

    constexpr Matrix2& operator-=(Matrix2 const& rhs)
    {
        m11 -= rhs.m11;
        m12 -= rhs.m12;
        m21 -= rhs.m21;
        m22 -= rhs.m22;
        return *this;
    }

    constexpr Matrix2& operator*=(T f)
    {
        m11 *= f;
        m12 *= f;
        m21 *= f;
        m22 *= f;
        return *this;
    }

    constexpr Matrix2& operator/=(T f)
    {
        m11 /= f;
        m12 /= f;
        m21 /= f;
        m22 /= f;
        return *this;
    }

    constexpr Matrix2& operator*=(Matrix2 const& rhs)
    {
        *this = (*this) * rhs;
        return *this;
    }

    [[nodiscard]] friend constexpr auto operator<=>(Matrix2 const&, Matrix2 const&) = default;

    [[nodiscard]] friend constexpr Matrix2 operator+(Matrix2 const& lhs, Matrix2 const& rhs)
    {
        return Matrix2(lhs.m11 + rhs.m11, lhs.m12 + rhs.m12,
                       lhs.m21 + rhs.m21, lhs.m22 + rhs.m22);
    }

    [[nodiscard]] friend constexpr Matrix2 operator-(Matrix2 const& lhs, Matrix2 const& rhs)
    {
        return Matrix2(lhs.m11 - rhs.m11, lhs.m12 - rhs.m12,
                       lhs.m21 - rhs.m21, lhs.m22 - rhs.m22);
    }

    [[nodiscard]] friend constexpr Matrix2 operator*(Matrix2 const& lhs, T f)
    {
        return Matrix2(lhs.m11 * f, lhs.m12 * f,
                       lhs.m21 * f, lhs.m22 * f);
    }

    [[nodiscard]] friend constexpr Matrix2 operator*(T f, Matrix2 const& rhs)
    {
        return Matrix2(f * rhs.m11, f * rhs.m12,
                       f * rhs.m21, f * rhs.m22);
    }


    [[nodiscard]] friend constexpr Matrix2 operator/(Matrix2 const& lhs, T f)
    {
        return Matrix2(lhs.m11 / f, lhs.m12 / f,
                       lhs.m21 / f, lhs.m22 / f);
    }

    [[nodiscard]] friend constexpr Matrix2 operator*(Matrix2 const& lhs, Matrix2 const& rhs)
    {
        return Matrix2<T>(lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21, lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22,
                          lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21, lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22);
    }

    [[nodiscard]] friend constexpr Vector2<T> operator*(Matrix2 const& m, Vector2<T> const& v)
    {
        return Vector2<T>(m.m11 * v.x + m.m12 * v.y, m.m21 * v.x + m.m22 * v.y);
    }
};

template<typename T>
[[nodiscard]] constexpr inline Matrix2<T> matrix_from_row_vectors(Vector2<T> const& r1, Vector2<T> const& r2)
{
    return Matrix2<T>(r1.x, r1.y,
                      r2.x, r2.y);
}

template<typename T>
[[nodiscard]] constexpr inline Matrix2<T> matrix_from_column_vectors(Vector2<T> const& c1, Vector2<T> const& c2)
{
    return Matrix2<T>(c1.x, c2.x,
                      c1.y, c2.y);
}

template<typename T>
[[nodiscard]] constexpr inline Matrix2<T> transpose(Matrix2<T> const& m)
{
    return Matrix2<T>(m.m11, m.m21, m.m12, m.m22);
}

template<typename T>
[[nodiscard]] constexpr inline T determinant(Matrix2<T> const& m)
{
    return m.m11*m.m22 - m.m21*m.m12;
}

template<typename T>
[[nodiscard]] constexpr inline Matrix2<T> adjugate(Matrix2<T> const& m)
{
    T const c11 = m.m22;
    T const c12 = -m.m12;
    T const c21 = -m.m21;
    T const c22 = m.m11;
    return Matrix2<T>(c11, c12,
                      c21, c22);
}

/** Represents a matrix together with a 1/n scaling factor.
 * Use this to model matrices with fractional indices using integral types.
 */
template<typename T>
struct ScaledMatrix2
{
    Matrix2<T> m;
    T inverse_scale_factor;

    constexpr ScaledMatrix2() = default;
    constexpr ScaledMatrix2(ScaledMatrix2 const&) = default;
    constexpr ScaledMatrix2& operator=(ScaledMatrix2 const&) = default;

    constexpr ScaledMatrix2(Matrix2<T> const& mat, T n_inverse_scale_factor)
        :m(mat), inverse_scale_factor(n_inverse_scale_factor)
    {}

    template<typename U>
    [[nodiscard]] constexpr Matrix2<U> evaluate() const
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
 * The matrix portion of the ScaledMatrix is the adjugate of the input matrix.
 * The inverse scale factor of the ScaledMatrix is the determinant of the input matrix.
 */
template<typename T>
[[nodiscard]] constexpr inline ScaledMatrix2<T> inverse_scaled(Matrix2<T> const& m)
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
template<std::floating_point T>
[[nodiscard]] constexpr inline Matrix2<T> inverse(Matrix2<T> const& m)
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    T const invDet = Constants<T>::One() / determinant(m);
    return Matrix2<T>( m.m22*invDet, -m.m12*invDet,
                      -m.m21*invDet,  m.m11*invDet);
}

template<typename T>
[[nodiscard]] constexpr inline Matrix2<T> identity2()
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    return Matrix2<T>(Constants<T>::One(),  Constants<T>::Zero(),
                      Constants<T>::Zero(), Constants<T>::One());
}
}
#endif
