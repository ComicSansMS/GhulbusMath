#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX4_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX4_HPP

/** @file
 *
 * @brief 4D Matrix.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/MatrixPolicies.hpp>
#include <gbMath/Vector3.hpp>
#include <gbMath/Vector4.hpp>

#include <cmath>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Matrix4
{
public:
    T m11, m12, m13, m14;
    T m21, m22, m23, m24;
    T m31, m32, m33, m34;
    T m41, m42, m43, m44;

    Matrix4() = default;
    Matrix4(Matrix4 const&) = default;
    Matrix4& operator=(Matrix4 const&) = default;

    Matrix4(T n11, T n12, T n13, T n14,
            T n21, T n22, T n23, T n24,
            T n31, T n32, T n33, T n34,
            T n41, T n42, T n43, T n44)
        :m11(n11), m12(n12), m13(n13), m14(n14),
         m21(n21), m22(n22), m23(n23), m24(n24),
         m31(n31), m32(n32), m33(n33), m34(n34),
         m41(n41), m42(n42), m43(n43), m44(n44)
    {}

    template<typename U>
    explicit Matrix4(Matrix4<U> const& rhs)
        :m11(static_cast<T>(rhs.m11)), m12(static_cast<T>(rhs.m12)), m13(static_cast<T>(rhs.m13)), m14(static_cast<T>(rhs.m14)),
         m21(static_cast<T>(rhs.m21)), m22(static_cast<T>(rhs.m22)), m23(static_cast<T>(rhs.m23)), m24(static_cast<T>(rhs.m24)),
         m31(static_cast<T>(rhs.m31)), m32(static_cast<T>(rhs.m32)), m33(static_cast<T>(rhs.m33)), m34(static_cast<T>(rhs.m34)),
         m41(static_cast<T>(rhs.m41)), m42(static_cast<T>(rhs.m42)), m43(static_cast<T>(rhs.m43)), m44(static_cast<T>(rhs.m44))
    {}

    explicit Matrix4(T const* arr, MatrixPolicies::InputOrder_RowMajor)
        :m11(arr[0]), m12(arr[1]), m13(arr[2]), m14(arr[3]),
         m21(arr[4]), m22(arr[5]), m23(arr[6]), m24(arr[7]),
         m31(arr[8]), m32(arr[9]), m33(arr[10]), m34(arr[11]),
         m41(arr[12]), m42(arr[13]), m43(arr[14]), m44(arr[15])
    {}

    explicit Matrix4(T const* arr, MatrixPolicies::InputOrder_ColumnMajor)
        :m11(arr[0]), m12(arr[4]), m13(arr[8]), m14(arr[12]),
         m21(arr[1]), m22(arr[5]), m23(arr[9]), m24(arr[13]),
         m31(arr[2]), m32(arr[6]), m33(arr[10]), m34(arr[14]),
         m41(arr[3]), m42(arr[7]), m43(arr[11]), m44(arr[15])
    {}

    T& operator[](std::size_t idx)
    {
        return (&m11)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&m11)[idx];
    }

    Vector4<T> row(std::size_t idx) const
    {
        auto const& m = *this;
        return Vector4<T>(m[idx*4], m[idx*4 + 1], m[idx*4 + 2], m[idx*4 + 3]);
    }

    Vector4<T> column(std::size_t idx) const
    {
        auto const& m = *this;
        return Vector4<T>(m[idx], m[idx + 4], m[idx + 8], m[idx + 12]);
    }

    Matrix4<T>& operator+=(Matrix4<T> const& rhs)
    {
        m11 += rhs.m11;  m12 += rhs.m12;  m13 += rhs.m13;  m14 += rhs.m14;
        m21 += rhs.m21;  m22 += rhs.m22;  m23 += rhs.m23;  m24 += rhs.m24;
        m31 += rhs.m31;  m32 += rhs.m32;  m33 += rhs.m33;  m34 += rhs.m34;
        m41 += rhs.m41;  m42 += rhs.m42;  m43 += rhs.m43;  m44 += rhs.m44;
        return *this;
    }

    Matrix4<T>& operator-=(Matrix4<T> const& rhs)
    {
        m11 -= rhs.m11;  m12 -= rhs.m12;  m13 -= rhs.m13;  m14 -= rhs.m14;
        m21 -= rhs.m21;  m22 -= rhs.m22;  m23 -= rhs.m23;  m24 -= rhs.m24;
        m31 -= rhs.m31;  m32 -= rhs.m32;  m33 -= rhs.m33;  m34 -= rhs.m34;
        m41 -= rhs.m41;  m42 -= rhs.m42;  m43 -= rhs.m43;  m44 -= rhs.m44;
        return *this;
    }

    Matrix4<T>& operator*=(T f)
    {
        m11 *= f;  m12 *= f;  m13 *= f;  m14 *= f;
        m21 *= f;  m22 *= f;  m23 *= f;  m24 *= f;
        m31 *= f;  m32 *= f;  m33 *= f;  m34 *= f;
        m41 *= f;  m42 *= f;  m43 *= f;  m44 *= f;
        return *this;
    }

    Matrix4<T>& operator/=(T f)
    {
        m11 /= f;  m12 /= f;  m13 /= f;  m14 /= f;
        m21 /= f;  m22 /= f;  m23 /= f;  m24 /= f;
        m31 /= f;  m32 /= f;  m33 /= f;  m34 /= f;
        m41 /= f;  m42 /= f;  m43 /= f;  m44 /= f;
        return *this;
    }

    Matrix4<T>& operator*=(Matrix4<T> const& rhs)
    {
        *this = (*this) * rhs;
        return *this;
    }
};


template<typename T>
inline bool operator==(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return ((lhs.m11 == rhs.m11) && (lhs.m12 == rhs.m12) && (lhs.m13 == rhs.m13) && (lhs.m14 == rhs.m14) &&
            (lhs.m21 == rhs.m21) && (lhs.m22 == rhs.m22) && (lhs.m23 == rhs.m23) && (lhs.m24 == rhs.m24) &&
            (lhs.m31 == rhs.m31) && (lhs.m32 == rhs.m32) && (lhs.m33 == rhs.m33) && (lhs.m34 == rhs.m34) &&
            (lhs.m41 == rhs.m41) && (lhs.m42 == rhs.m42) && (lhs.m43 == rhs.m43) && (lhs.m44 == rhs.m44));
}

template<typename T>
inline bool operator<(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    std::size_t i;
    for(i = 0; (i < 15) && (lhs[i] == rhs[i]); ++i) ;
    return (lhs[i] < rhs[i]);
}

template<typename T>
inline bool operator!=(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline bool operator<=(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T>
inline bool operator>(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator>=(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
inline Matrix4<T> operator+(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return Matrix4<T>(lhs.m11 + rhs.m11, lhs.m12 + rhs.m12, lhs.m13 + rhs.m13, lhs.m14 + rhs.m14,
                      lhs.m21 + rhs.m21, lhs.m22 + rhs.m22, lhs.m23 + rhs.m23, lhs.m24 + rhs.m24,
                      lhs.m31 + rhs.m31, lhs.m32 + rhs.m32, lhs.m33 + rhs.m33, lhs.m34 + rhs.m34,
                      lhs.m41 + rhs.m41, lhs.m42 + rhs.m42, lhs.m43 + rhs.m43, lhs.m44 + rhs.m44);
}

template<typename T>
inline Matrix4<T> operator-(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return Matrix4<T>(lhs.m11 - rhs.m11, lhs.m12 - rhs.m12, lhs.m13 - rhs.m13, lhs.m14 - rhs.m14,
                      lhs.m21 - rhs.m21, lhs.m22 - rhs.m22, lhs.m23 - rhs.m23, lhs.m24 - rhs.m24,
                      lhs.m31 - rhs.m31, lhs.m32 - rhs.m32, lhs.m33 - rhs.m33, lhs.m34 - rhs.m34,
                      lhs.m41 - rhs.m41, lhs.m42 - rhs.m42, lhs.m43 - rhs.m43, lhs.m44 - rhs.m44);
}

template<typename T>
inline Matrix4<T> operator*(Matrix4<T> const& lhs, T f)
{
    return Matrix4<T>(lhs.m11 * f, lhs.m12 * f, lhs.m13 * f, lhs.m14 * f,
                      lhs.m21 * f, lhs.m22 * f, lhs.m23 * f, lhs.m24 * f,
                      lhs.m31 * f, lhs.m32 * f, lhs.m33 * f, lhs.m34 * f,
                      lhs.m41 * f, lhs.m42 * f, lhs.m43 * f, lhs.m44 * f);
}

template<typename T>
inline Matrix4<T> operator*(T f, Matrix4<T> const& rhs)
{
    return Matrix4<T>(f * rhs.m11, f * rhs.m12, f * rhs.m13, f * rhs.m14,
                      f * rhs.m21, f * rhs.m22, f * rhs.m23, f * rhs.m24,
                      f * rhs.m31, f * rhs.m32, f * rhs.m33, f * rhs.m34,
                      f * rhs.m41, f * rhs.m42, f * rhs.m43, f * rhs.m44);
}

template<typename T>
inline Matrix4<T> operator/(Matrix4<T> const& lhs, T f)
{
    return Matrix4<T>(lhs.m11 / f, lhs.m12 / f, lhs.m13 / f, lhs.m14 / f,
                      lhs.m21 / f, lhs.m22 / f, lhs.m23 / f, lhs.m24 / f,
                      lhs.m31 / f, lhs.m32 / f, lhs.m33 / f, lhs.m34 / f,
                      lhs.m41 / f, lhs.m42 / f, lhs.m43 / f, lhs.m44 / f);
}

template<typename T>
inline Matrix4<T> operator*(Matrix4<T> const& lhs, Matrix4<T> const& rhs)
{
    return Matrix4<T>(lhs.m11*rhs.m11 + lhs.m12*rhs.m21 + lhs.m13*rhs.m31 + lhs.m14*rhs.m41,
                      lhs.m11*rhs.m12 + lhs.m12*rhs.m22 + lhs.m13*rhs.m32 + lhs.m14*rhs.m42,
                      lhs.m11*rhs.m13 + lhs.m12*rhs.m23 + lhs.m13*rhs.m33 + lhs.m14*rhs.m43,
                      lhs.m11*rhs.m14 + lhs.m12*rhs.m24 + lhs.m13*rhs.m34 + lhs.m14*rhs.m44,
                      lhs.m21*rhs.m11 + lhs.m22*rhs.m21 + lhs.m23*rhs.m31 + lhs.m24*rhs.m41,
                      lhs.m21*rhs.m12 + lhs.m22*rhs.m22 + lhs.m23*rhs.m32 + lhs.m24*rhs.m42,
                      lhs.m21*rhs.m13 + lhs.m22*rhs.m23 + lhs.m23*rhs.m33 + lhs.m24*rhs.m43,
                      lhs.m21*rhs.m14 + lhs.m22*rhs.m24 + lhs.m23*rhs.m34 + lhs.m24*rhs.m44,
                      lhs.m31*rhs.m11 + lhs.m32*rhs.m21 + lhs.m33*rhs.m31 + lhs.m34*rhs.m41,
                      lhs.m31*rhs.m12 + lhs.m32*rhs.m22 + lhs.m33*rhs.m32 + lhs.m34*rhs.m42,
                      lhs.m31*rhs.m13 + lhs.m32*rhs.m23 + lhs.m33*rhs.m33 + lhs.m34*rhs.m43,
                      lhs.m31*rhs.m14 + lhs.m32*rhs.m24 + lhs.m33*rhs.m34 + lhs.m34*rhs.m44,
                      lhs.m41*rhs.m11 + lhs.m42*rhs.m21 + lhs.m43*rhs.m31 + lhs.m44*rhs.m41,
                      lhs.m41*rhs.m12 + lhs.m42*rhs.m22 + lhs.m43*rhs.m32 + lhs.m44*rhs.m42,
                      lhs.m41*rhs.m13 + lhs.m42*rhs.m23 + lhs.m43*rhs.m33 + lhs.m44*rhs.m43,
                      lhs.m41*rhs.m14 + lhs.m42*rhs.m24 + lhs.m43*rhs.m34 + lhs.m44*rhs.m44);
}

template<typename T>
inline Matrix4<T> matrixFromRowVectors(Vector4<T> const& r1, Vector4<T> const& r2,
                                       Vector4<T> const& r3, Vector4<T> const& r4)
{
    return Matrix4<T>(r1.x, r1.y, r1.z, r1.w,
                      r2.x, r2.y, r2.z, r2.w,
                      r3.x, r3.y, r3.z, r3.w,
                      r4.x, r4.y, r4.z, r4.w);
}

template<typename T>
inline Matrix4<T> matrixFromColumnVectors(Vector4<T> const& c1, Vector4<T> const& c2,
                                          Vector4<T> const& c3, Vector4<T> const& c4)
{
    return Matrix4<T>(c1.x, c2.x, c3.x, c4.x,
                      c1.y, c2.y, c3.y, c4.y,
                      c1.z, c2.z, c3.z, c4.z,
                      c1.w, c2.w, c3.w, c4.w);
}

template<typename T>
inline Vector4<T> operator*(Matrix4<T> const& m, Vector4<T> const& v)
{
    return Vector4<T>(m.m11*v.x + m.m12*v.y + m.m13*v.z + m.m14*v.w,
                      m.m21*v.x + m.m22*v.y + m.m23*v.z + m.m24*v.w,
                      m.m31*v.x + m.m32*v.y + m.m33*v.z + m.m34*v.w,
                      m.m41*v.x + m.m42*v.y + m.m43*v.z + m.m44*v.w);
}

template<typename T>
inline Matrix4<T> transpose(Matrix4<T> const& m)
{
    return Matrix4<T>(m.m11, m.m21, m.m31, m.m41,
                      m.m12, m.m22, m.m32, m.m42,
                      m.m13, m.m23, m.m33, m.m43,
                      m.m14, m.m24, m.m34, m.m44);
}

template<typename T>
inline T determinant(Matrix4<T> const& m)
{
    Vector3<T> const a(m.m11, m.m21, m.m31);
    Vector3<T> const b(m.m12, m.m22, m.m32);
    Vector3<T> const c(m.m13, m.m23, m.m33);
    Vector3<T> const d(m.m14, m.m24, m.m34);

    T const x = m.m41;
    T const y = m.m42;
    T const z = m.m43;
    T const w = m.m44;

    Vector3<T> const s = cross(a, b);
    Vector3<T> const t = cross(c, d);
    Vector3<T> const u = a*y - b*x;
    Vector3<T> const v = c*w - d*z;

    return dot(s, v) + dot(t, u);
}

/** Represents a matrix together with a 1/n scaling factor.
 * Use this to model matrices with fractional indices using integral types.
 */
template<typename T>
struct ScaledMatrix4
{
    Matrix4<T> m;
    T inverse_scale_factor;

    ScaledMatrix4() = default;
    ScaledMatrix4(ScaledMatrix4 const&) = default;
    ScaledMatrix4& operator=(ScaledMatrix4 const&) = default;

    ScaledMatrix4(Matrix4<T> const& mat, T n_inverse_scale_factor)
        :m(mat), inverse_scale_factor(n_inverse_scale_factor)
    {}

    template<typename U>
    Matrix4<U> evaluate() const
    {
        Matrix4<U> ret(m);
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
inline ScaledMatrix4<T> inverse_scaled(Matrix4<T> const& m)
{
    Vector3<T> const a(m.m11, m.m21, m.m31);
    Vector3<T> const b(m.m12, m.m22, m.m32);
    Vector3<T> const c(m.m13, m.m23, m.m33);
    Vector3<T> const d(m.m14, m.m24, m.m34);

    T const x = m.m41;
    T const y = m.m42;
    T const z = m.m43;
    T const w = m.m44;

    Vector3<T> const s = cross(a, b);
    Vector3<T> const t = cross(c, d);
    Vector3<T> const u = a*y - b*x;
    Vector3<T> const v = c*w - d*z;

    Vector3<T> const r0 = cross(b, v) + t*y;
    Vector3<T> const r1 = cross(v, a) - t*x;
    Vector3<T> const r2 = cross(d, u) + s*w;
    Vector3<T> const r3 = cross(u, c) - s*z;

    T const det = dot(s, v) + dot(t, u);
    return ScaledMatrix4<T>(Matrix4<T>(r0.x, r0.y, r0.z, -dot(b, t),
                                       r1.x, r1.y, r1.z,  dot(a, t),
                                       r2.x, r2.y, r2.z, -dot(d, s),
                                       r3.x, r3.y, r3.z,  dot(c, s)),
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
inline std::enable_if_t<!std::is_integral<T>::value, Matrix4<T>> inverse(Matrix4<T> const& m)
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    Vector3<T> const a(m.m11, m.m21, m.m31);
    Vector3<T> const b(m.m12, m.m22, m.m32);
    Vector3<T> const c(m.m13, m.m23, m.m33);
    Vector3<T> const d(m.m14, m.m24, m.m34);

    T const x = m.m41;
    T const y = m.m42;
    T const z = m.m43;
    T const w = m.m44;

    Vector3<T> s = cross(a, b);
    Vector3<T> t = cross(c, d);
    Vector3<T> u = a*y - b*x;
    Vector3<T> v = c*w - d*z;

    T const invDet = Constants<T>::One() / (dot(s, v) + dot(t, u));
    s *= invDet;
    t *= invDet;
    u *= invDet;
    v *= invDet;

    Vector3<T> const r0 = cross(b, v) + t*y;
    Vector3<T> const r1 = cross(v, a) - t*x;
    Vector3<T> const r2 = cross(d, u) + s*w;
    Vector3<T> const r3 = cross(u, c) - s*z;

    return Matrix4<T>(r0.x, r0.y, r0.z, -dot(b, t),
                      r1.x, r1.y, r1.z,  dot(a, t),
                      r2.x, r2.y, r2.z, -dot(d, s),
                      r3.x, r3.y, r3.z,  dot(c, s));
}

template<typename T>
inline Matrix4<T> identity4()
{
    using ::GHULBUS_MATH_NAMESPACE::traits::Constants;
    return Matrix4<T>(Constants<T>::One(),  Constants<T>::Zero(), Constants<T>::Zero(), Constants<T>::Zero(),
                      Constants<T>::Zero(), Constants<T>::One(),  Constants<T>::Zero(), Constants<T>::Zero(),
                      Constants<T>::Zero(), Constants<T>::Zero(), Constants<T>::One(),  Constants<T>::Zero(),
                      Constants<T>::Zero(), Constants<T>::Zero(), Constants<T>::Zero(), Constants<T>::One());
}
}
#endif
