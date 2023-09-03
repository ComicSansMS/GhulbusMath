#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX3_HPP

/** @file
 *
 * @brief 3D Matrix.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Common.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/MatrixPolicies.hpp>
#include <gbMath/Vector3.hpp>

#include <cmath>
#include <concepts>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Matrix3
{
public:
    using ValueType = T;

    T m11, m12, m13;
    T m21, m22, m23;
    T m31, m32, m33;

    constexpr Matrix3()
        :m11{}, m12{}, m13{},
         m21{}, m22{}, m23{},
         m31{}, m32{}, m33{}
    {}
    constexpr Matrix3(DoNotInitialize_Tag)
    {}
    constexpr Matrix3(Matrix3 const&) = default;
    constexpr Matrix3& operator=(Matrix3 const&) = default;

    constexpr Matrix3(T n11, T n12, T n13,
                      T n21, T n22, T n23,
                      T n31, T n32, T n33)
        :m11(n11), m12(n12), m13(n13),
         m21(n21), m22(n22), m23(n23),
         m31(n31), m32(n32), m33(n33)
    {}

    template<typename U>
    constexpr explicit Matrix3(Matrix3<U> const& rhs)
        :m11(static_cast<T>(rhs.m11)), m12(static_cast<T>(rhs.m12)), m13(static_cast<T>(rhs.m13)),
         m21(static_cast<T>(rhs.m21)), m22(static_cast<T>(rhs.m22)), m23(static_cast<T>(rhs.m23)),
         m31(static_cast<T>(rhs.m31)), m32(static_cast<T>(rhs.m32)), m33(static_cast<T>(rhs.m33))
    {}

    constexpr explicit Matrix3(T const* arr, MatrixPolicies::InputOrder_RowMajor)
        :m11(arr[0]), m12(arr[1]), m13(arr[2]),
         m21(arr[3]), m22(arr[4]), m23(arr[5]),
         m31(arr[6]), m32(arr[7]), m33(arr[8])
    {}

    constexpr explicit Matrix3(T const* arr, MatrixPolicies::InputOrder_ColumnMajor)
        :m11(arr[0]), m12(arr[3]), m13(arr[6]),
         m21(arr[1]), m22(arr[4]), m23(arr[7]),
         m31(arr[2]), m32(arr[5]), m33(arr[8])
    {}

    [[nodiscard]] constexpr T& operator[](std::size_t idx)
    {
        return (&m11)[idx];
    }

    [[nodiscard]] constexpr T const& operator[](std::size_t idx) const
    {
        return (&m11)[idx];
    }

    [[nodiscard]] constexpr Vector3<T> row(std::size_t idx) const
    {
        auto const& m = *this;
        return Vector3<T>(m[idx*3], m[idx*3 + 1], m[idx*3 + 2]);
    }

    [[nodiscard]] constexpr Vector3<T> column(std::size_t idx) const
    {
        auto const& m = *this;
        return Vector3<T>(m[idx], m[idx + 3], m[idx + 6]);
    }

    constexpr Matrix3& operator+=(Matrix3 const& rhs)
    {
        m11 += rhs.m11;
        m12 += rhs.m12;
        m13 += rhs.m13;
        m21 += rhs.m21;
        m22 += rhs.m22;
        m23 += rhs.m23;
        m31 += rhs.m31;
        m32 += rhs.m32;
        m33 += rhs.m33;
        return *this;
    }

    constexpr Matrix3& operator-=(Matrix3 const& rhs)
    {
        m11 -= rhs.m11;
        m12 -= rhs.m12;
        m13 -= rhs.m13;
        m21 -= rhs.m21;
        m22 -= rhs.m22;
        m23 -= rhs.m23;
        m31 -= rhs.m31;
        m32 -= rhs.m32;
        m33 -= rhs.m33;
        return *this;
    }

    constexpr Matrix3& operator*=(T f)
    {
        m11 *= f;
        m12 *= f;
        m13 *= f;
        m21 *= f;
        m22 *= f;
        m23 *= f;
        m31 *= f;
        m32 *= f;
        m33 *= f;
        return *this;
    }

    constexpr Matrix3& operator/=(T f)
    {
        m11 /= f;
        m12 /= f;
        m13 /= f;
        m21 /= f;
        m22 /= f;
        m23 /= f;
        m31 /= f;
        m32 /= f;
        m33 /= f;
        return *this;
    }

    constexpr Matrix3& operator*=(Matrix3 const& rhs)
    {
        *this = (*this) * rhs;
        return *this;
    }

    [[nodiscard]] friend constexpr auto operator<=>(Matrix3 const&, Matrix3 const&) = default;

    [[nodiscard]] friend constexpr Matrix3 operator+(Matrix3 const& lhs, Matrix3 const& rhs)
    {
        return Matrix3(lhs.m11 + rhs.m11, lhs.m12 + rhs.m12, lhs.m13 + rhs.m13,
                       lhs.m21 + rhs.m21, lhs.m22 + rhs.m22, lhs.m23 + rhs.m23,
                       lhs.m31 + rhs.m31, lhs.m32 + rhs.m32, lhs.m33 + rhs.m33);
    }

    [[nodiscard]] friend constexpr Matrix3 operator-(Matrix3 const& lhs, Matrix3 const& rhs)
    {
        return Matrix3(lhs.m11 - rhs.m11, lhs.m12 - rhs.m12, lhs.m13 - rhs.m13,
                       lhs.m21 - rhs.m21, lhs.m22 - rhs.m22, lhs.m23 - rhs.m23,
                       lhs.m31 - rhs.m31, lhs.m32 - rhs.m32, lhs.m33 - rhs.m33);
    }

    [[nodiscard]] friend constexpr Matrix3 operator*(Matrix3 const& lhs, T f)
    {
        return Matrix3(lhs.m11 * f, lhs.m12 * f, lhs.m13 * f,
                       lhs.m21 * f, lhs.m22 * f, lhs.m23 * f,
                       lhs.m31 * f, lhs.m32 * f, lhs.m33 * f);
    }

    [[nodiscard]] friend constexpr Matrix3 operator*(T f, Matrix3 const& rhs)
    {
        return Matrix3(f * rhs.m11, f * rhs.m12, f * rhs.m13,
                       f * rhs.m21, f * rhs.m22, f * rhs.m23,
                       f * rhs.m31, f * rhs.m32, f * rhs.m33);
    }

    [[nodiscard]] friend constexpr Matrix3 operator/(Matrix3 const& lhs, T f)
    {
        return Matrix3(lhs.m11 / f, lhs.m12 / f, lhs.m13 / f,
                       lhs.m21 / f, lhs.m22 / f, lhs.m23 / f,
                       lhs.m31 / f, lhs.m32 / f, lhs.m33 / f);
    }

    [[nodiscard]] friend constexpr Matrix3 operator*(Matrix3 const& lhs, Matrix3 const& rhs)
    {
        return Matrix3(lhs.m11*rhs.m11 + lhs.m12*rhs.m21 + lhs.m13*rhs.m31,
                       lhs.m11*rhs.m12 + lhs.m12*rhs.m22 + lhs.m13*rhs.m32,
                       lhs.m11*rhs.m13 + lhs.m12*rhs.m23 + lhs.m13*rhs.m33,
                       lhs.m21*rhs.m11 + lhs.m22*rhs.m21 + lhs.m23*rhs.m31,
                       lhs.m21*rhs.m12 + lhs.m22*rhs.m22 + lhs.m23*rhs.m32,
                       lhs.m21*rhs.m13 + lhs.m22*rhs.m23 + lhs.m23*rhs.m33,
                       lhs.m31*rhs.m11 + lhs.m32*rhs.m21 + lhs.m33*rhs.m31,
                       lhs.m31*rhs.m12 + lhs.m32*rhs.m22 + lhs.m33*rhs.m32,
                       lhs.m31*rhs.m13 + lhs.m32*rhs.m23 + lhs.m33*rhs.m33);
    }

    [[nodiscard]] friend constexpr Vector3<T> operator*(Matrix3 const& m, Vector3<T> const& v)
    {
        return Vector3<T>(m.m11*v.x + m.m12*v.y + m.m13*v.z,
                          m.m21*v.x + m.m22*v.y + m.m23*v.z,
                          m.m31*v.x + m.m32*v.y + m.m33*v.z);
    }

};



template<typename T>
[[nodiscard]] constexpr inline Matrix3<T> matrix_from_row_vectors(Vector3<T> const& r1,
                                                                  Vector3<T> const& r2,
                                                                  Vector3<T> const& r3)
{
    return Matrix3<T>(r1.x, r1.y, r1.z,
                      r2.x, r2.y, r2.z,
                      r3.x, r3.y, r3.z);
}

template<typename T>
[[nodiscard]] constexpr inline Matrix3<T> matrix_from_column_vectors(Vector3<T> const& c1,
                                                                     Vector3<T> const& c2,
                                                                     Vector3<T> const& c3)
{
    return Matrix3<T>(c1.x, c2.x, c3.x,
                      c1.y, c2.y, c3.y,
                      c1.z, c2.z, c3.z);
}


template<typename T>
[[nodiscard]] constexpr inline Matrix3<T> transpose(Matrix3<T> const& m)
{
    return Matrix3<T>(m.m11, m.m21, m.m31,
                      m.m12, m.m22, m.m32,
                      m.m13, m.m23, m.m33);
}

template<typename T>
[[nodiscard]] constexpr inline T determinant(Matrix3<T> const& m)
{
    return (m.m11 * (m.m22 * m.m33 - m.m23 * m.m32)) +
           (m.m12 * (m.m23 * m.m31 - m.m21 * m.m33)) +
           (m.m13 * (m.m21 * m.m32 - m.m22 * m.m31));
}

template<typename T>
[[nodiscard]] constexpr inline Matrix3<T> adjugate(Matrix3<T> const& m)
{
    Vector3<T> const a = m.column(0);
    Vector3<T> const b = m.column(1);
    Vector3<T> const c = m.column(2);

    Vector3<T> const r0 = cross(b, c);
    Vector3<T> const r1 = cross(c, a);
    Vector3<T> const r2 = cross(a, b);

    return Matrix3<T>(r0.x, r0.y, r0.z,
                      r1.x, r1.y, r1.z,
                      r2.x, r2.y, r2.z);
}

/** Represents a matrix together with a 1/n scaling factor.
 * Use this to model matrices with fractional indices using integral types.
 */
template<typename T>
struct ScaledMatrix3
{
    Matrix3<T> m;
    T inverse_scale_factor;

    constexpr ScaledMatrix3() = default;
    constexpr ScaledMatrix3(ScaledMatrix3 const&) = default;
    constexpr ScaledMatrix3& operator=(ScaledMatrix3 const&) = default;

    constexpr ScaledMatrix3(Matrix3<T> const& mat, T n_inverse_scale_factor)
        :m(mat), inverse_scale_factor(n_inverse_scale_factor)
    {}

    template<typename U>
    [[nodiscard]] constexpr Matrix3<U> evaluate() const
    {
        Matrix3<U> ret(m);
        ret /= static_cast<U>(inverse_scale_factor);
        return ret;
    }
};

/** Computes the inverse of a matrix.
 * To allow lossless computation of the inverse for integral types, the resulting inverse matrix is given
 * as a ScaledMatrix, where the scaling factor is stored separately from the matrix itself.
 * To obtain the true inverse, call ScaledMatrix3::evaluate() on the return value.
 * The matrix portion of the ScaledMatrix is the adjugate of the input matrix.
 * The inverse scale factor of the ScaledMatrix is the determinant of the input matrix.
 */
template<typename T>
[[nodiscard]] constexpr inline ScaledMatrix3<T> inverse_scaled(Matrix3<T> const& m)
{
    Vector3<T> const a = m.column(0);
    Vector3<T> const b = m.column(1);
    Vector3<T> const c = m.column(2);

    Vector3<T> const r0 = cross(b, c);
    Vector3<T> const r1 = cross(c, a);
    Vector3<T> const r2 = cross(a, b);

    T const det = dot(r2, c);
    return ScaledMatrix3<T>(Matrix3<T>(r0.x, r0.y, r0.z,
                                       r1.x, r1.y, r1.z,
                                       r2.x, r2.y, r2.z),
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
[[nodiscard]] constexpr inline Matrix3<T> inverse(Matrix3<T> const& m)
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    Vector3<T> const a = m.column(0);
    Vector3<T> const b = m.column(1);
    Vector3<T> const c = m.column(2);

    Vector3<T> const r0 = cross(b, c);
    Vector3<T> const r1 = cross(c, a);
    Vector3<T> const r2 = cross(a, b);

    T const invDet = Constants<T>::One() / dot(r2, c);
    return Matrix3<T>(r0.x*invDet, r0.y*invDet, r0.z*invDet,
                      r1.x*invDet, r1.y*invDet, r1.z*invDet,
                      r2.x*invDet, r2.y*invDet, r2.z*invDet);
}

template<typename T>
[[nodiscard]] constexpr inline Matrix3<T> identity3()
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    return Matrix3<T>(Constants<T>::One(),  Constants<T>::Zero(), Constants<T>::Zero(),
                      Constants<T>::Zero(), Constants<T>::One(),  Constants<T>::Zero(),
                      Constants<T>::Zero(), Constants<T>::Zero(), Constants<T>::One());
}
}
#endif
