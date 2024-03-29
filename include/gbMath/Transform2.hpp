#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_TRANSFORM2_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_TRANSFORM2_HPP

/** @file
 *
 * @brief 2D Transformations.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Matrix2.hpp>
#include <gbMath/Matrix3.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector2.hpp>

#include <cmath>
#include <concepts>

namespace GHULBUS_MATH_NAMESPACE
{
/** The reciprocal of a Transform2.
 * Normals and other reciprocal vectors can only be transformed through a reciprocal transform, which is equal to
 * the inverse of the original transform.
 * Unlike transforms, reciprocal transforms are multiplied from the right (alternatively, we would have to transpose
 * before multiplying from the left).
 * Since normals are points at infinity, we omit the translation portion and only store a Matrix2 to speed up
 * calculation of the inverse.
 * The reciprocal transformation matrix does not preserve scale. Reciprocally transformed vectors can be re-normalized
 * by dividing by the determinant of the original transformation matrix.
 */
template<typename T>
class TransformReciprocal2
{
public:
    Matrix2<T> m;

    template<typename VectorTag_T>
    [[nodiscard]] friend constexpr Vector2Impl<T, VectorTag_T> operator*(Vector2Impl<T, VectorTag_T> const& n,
                                                                         TransformReciprocal2<T> const& rt)
        requires(VectorTraits::IsReciprocal<VectorTag_T>::value && !VectorTraits::IsFinitePoint<VectorTag_T>::value)
    {
        Matrix2<T> const& m = rt.m;
        return Vector2Impl<T, VectorTag_T>(n.x*m.m11 + n.y*m.m21,
                                           n.x*m.m12 + n.y*m.m22);
    }
};

/** A homogeneous 2D transformation.
 */
template<typename T>
class Transform2
{
public:
    Matrix3<T> m;
public:
    constexpr Transform2()
        :m(identity3<T>())
    {}

    constexpr explicit Transform2(Matrix3<T> const& transform_matrix)
        :m(transform_matrix)
    {}

    constexpr Transform2(T n11, T n12, T n13,
                         T n21, T n22, T n23,
                         T n31, T n32, T n33)
        :m(n11, n12, n13,
           n21, n22, n23,
           n31, n32, n33)
    {}

    /** Retrieve the reciprocal of the current transform.
     * Normals and other reciprocal vectors are transformed by multiplying the inverse transpose of the original
     * transformation. We follow Lengyel's suggestion here by using the adjugate to properly mirror normals if the
     * winding order changed and instead of transposing, multiply it from the right.
     */
    [[nodiscard]] constexpr TransformReciprocal2<T> reciprocal()
    {
        Matrix2<T> const upper_left(m.m11, m.m12,
                                    m.m21, m.m22);
        return TransformReciprocal2<T>{ adjugate(upper_left) };
    }

    /** Retrieve the reciprocal under the assumption that the transform is orthogonal.
     * For orthogonal matrices, the inverse is equal to the transpose. Since transposing is way less computationally
     * expensive than proper inverting, use this function as a more efficient means of obtaining a reciprocal
     * if you know beforehand that the transform is in fact orthogonal.
     * @pre this->m * transpose(this->m) ~= identity3()
     */
    [[nodiscard]] constexpr TransformReciprocal2<T> reciprocal(assume_orthogonal_t)
    {
        Matrix2<T> const upper_left(m.m11, m.m12,
                                    m.m21, m.m22);
        return TransformReciprocal2<T>{ transpose(upper_left) };
    }

    /** Retrieve the translation component of the transform.
     */
    [[nodiscard]] constexpr Vector2<T> translation() const {
        return Vector2<T>(m.m13, m.m23);
    }

    constexpr Transform2& operator*=(Transform2 const& rhs) {
        m *= rhs.m;
        return *this;
    }

    [[nodiscard]] friend constexpr Transform2 operator*(Transform2 const& lhs, Transform2 const& rhs) {
        return Transform2<T>(lhs.m * rhs.m);
    }

    template<typename VectorTag_T>
    [[nodiscard]] friend constexpr Vector2Impl<T, VectorTag_T> operator*(Transform2 const& t,
                                                                         Vector2Impl<T, VectorTag_T> const& v)
        requires(!VectorTraits::IsFinitePoint<VectorTag_T>::value)
    {
        Matrix3<T> const& m = t.m;
        return Vector2Impl<T, VectorTag_T>(m.m11*v.x + m.m12*v.y,
                                           m.m21*v.x + m.m22*v.y);
    }

    template<typename VectorTag_T>
    [[nodiscard]] friend constexpr Vector2Impl<T, VectorTag_T> operator*(Transform2 const& t,
                                                                         Vector2Impl<T, VectorTag_T> const& p)
        requires(VectorTraits::IsFinitePoint<VectorTag_T>::value)
    {
        Matrix3<T> const& m = t.m;
        return Vector2Impl<T, VectorTag_T>(m.m11*p.x + m.m12*p.y + m.m13,
                                           m.m21*p.x + m.m22*p.y + m.m23);
    }
};

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform2<T> inverse(Transform2<T> const& t)
{
    return Transform2<T>(inverse(t.m));
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Point2<T> project(Transform2<T> const& t, Point2<T> const& p)
{
    Matrix3<T> const& m = t.m;
    T const w = m.m31*p.x + m.m32*p.y + m.m33;
    return Point2<T>((m.m11*p.x + m.m12*p.y + m.m13) / w,
                     (m.m21*p.x + m.m22*p.y + m.m23) / w);
}

template<typename T>
[[nodiscard]] constexpr inline Point2<T> project(Transform2<T> const& t, Point2<T> const& p, T& w)
{
    Matrix3<T> const& m = t.m;
    T const p_w = w;
    w = m.m31*p.x + m.m32*p.y + m.m33*w;
    return Point2<T>((m.m11*p.x + m.m12*p.y + m.m13*p_w),
                     (m.m21*p.x + m.m22*p.y + m.m23*p_w));
}

template<typename T>
[[nodiscard]] constexpr inline Transform2<T> make_scale2(T scale)
{
    T const z = traits::Constants<T>::Zero();
    T const o = traits::Constants<T>::One();
    return Transform2<T>(scale, z,     z,
                         z,     scale, z,
                         z,     z,     o);
}


template<typename T>
[[nodiscard]] constexpr inline Transform2<T> make_scale(T scale_x, T scale_y)
{
    T const z = traits::Constants<T>::Zero();
    T const o = traits::Constants<T>::One();
    return Transform2<T>(scale_x, z,       z,
                         z,       scale_y, z,
                         z,       z,       o);
}

template<typename T>
[[nodiscard]] constexpr inline Transform2<T> make_scale(Vector2<T> const& scale_v)
{
    T const z = traits::Constants<T>::Zero();
    T const o = traits::Constants<T>::One();
    return Transform2<T>(scale_v.x, z,         z,
                         z,         scale_v.y, z,
                         z,         z,         o);
}

template<typename T>
[[nodiscard]] constexpr inline Transform2<T> make_translation(T translate_x, T translate_y)
{
    T const z = traits::Constants<T>::Zero();
    T const o = traits::Constants<T>::One();
    return Transform2<T>(o, z, translate_x,
                         z, o, translate_y,
                         z, z, o);
}

template<typename T>
[[nodiscard]] constexpr inline Transform2<T> make_translation(Vector2<T> const& translate_v)
{
    T const z = traits::Constants<T>::Zero();
    T const o = traits::Constants<T>::One();
    return Transform2<T>(o, z, translate_v.x,
                         z, o, translate_v.y,
                         z, z, o);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform2<T> make_rotation(T angle)
{
    T const z = traits::Constants<T>::Zero();
    T const o = traits::Constants<T>::One();
    T const sin = std::sin(angle);
    T const cos = std::cos(angle);
    return Transform2<T>(cos, -sin, z,
                         sin,  cos, z,
                           z,    z, o);
}
}

#endif
