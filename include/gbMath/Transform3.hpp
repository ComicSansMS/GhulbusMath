#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_TRANSFORM3_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_TRANSFORM3_HPP

/** @file
 *
 * @brief 3D Transformations.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Matrix3.hpp>
#include <gbMath/Matrix4.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector3.hpp>

#include <cmath>
#include <concepts>

namespace GHULBUS_MATH_NAMESPACE
{
/** The reciprocal of a Transform3.
 * Normals and other reciprocal vectors can only be transformed through a reciprocal transform, which is equal to
 * the inverse of the original transform.
 * Unlike transforms, reciprocal transforms are multiplied from the right (alternatively, we would have to transpose
 * before multiplying from the left).
 * Since normals are points at infinity, we omit the translation portion and only store a Matrix3 to speed up
 * calculation of the inverse.
 * The reciprocal transformation matrix does not preserve scale. Reciprocally transformed vectors can be re-normalized
 * by dividing by the determinant of the original transformation matrix.
 */
template<typename T>
class TransformReciprocal3
{
public:
    Matrix3<T> m;

    template<typename VectorTag_T>
    [[nodiscard]] friend constexpr Vector3Impl<T, VectorTag_T> operator*(Vector3Impl<T, VectorTag_T> const& n,
                                                                         TransformReciprocal3 const& rt)
        requires(VectorTraits::IsReciprocal<VectorTag_T>::value && !VectorTraits::IsFinitePoint<VectorTag_T>::value)
    {
        Matrix3<T> const& m = rt.m;
        return Vector3Impl<T, VectorTag_T>(n.x*m.m11 + n.y*m.m21 + n.z*m.m31,
                                           n.x*m.m12 + n.y*m.m22 + n.z*m.m32,
                                           n.x*m.m13 + n.y*m.m23 + n.z*m.m33);
    }
};

/** A homogeneous 2D transformation.
 */
template<typename T>
class Transform3
{
public:
    Matrix4<T> m;
public:
    constexpr Transform3()
        :m(identity4<T>())
    {}

    constexpr explicit Transform3(Matrix4<T> const& transform_matrix)
        :m(transform_matrix)
    {}

    constexpr Transform3(T n11, T n12, T n13, T n14,
                         T n21, T n22, T n23, T n24,
                         T n31, T n32, T n33, T n34,
                         T n41, T n42, T n43, T n44)
        :m(n11, n12, n13, n14,
           n21, n22, n23, n24,
           n31, n32, n33, n34,
           n41, n42, n43, n44)
    {}

    /** Retrieve the reciprocal of the current transform.
     * Normals and other reciprocal vectors are transformed by multiplying the inverse transpose of the original
     * transformation. We follow Lengyel's suggestion here by using the adjugate to properly mirror normals if the
     * winding order changed and instead of transposing, multiply it from the right.
     */
    [[nodiscard]] constexpr TransformReciprocal3<T> reciprocal()
    {
        Matrix3<T> const upper_left(m.m11, m.m12, m.m13,
                                    m.m21, m.m22, m.m23,
                                    m.m31, m.m32, m.m33);
        return TransformReciprocal3<T>{ adjugate(upper_left) };
    }

    /** Retrieve the reciprocal under the assumption that the transform is orthogonal.
     * For orthogonal matrices, the inverse is equal to the transpose. Since transposing is way less computationally
     * expensive than proper inverting, use this function as a more efficient means of obtaining a reciprocal
     * if you know beforehand that the transform is in fact orthogonal.
     * @pre this->m * transpose(this->m) ~= identity4()
     */
    [[nodiscard]] constexpr TransformReciprocal3<T> reciprocal(assume_orthogonal_t)
    {
        Matrix3<T> const upper_left(m.m11, m.m12, m.m13,
                                    m.m21, m.m22, m.m23,
                                    m.m31, m.m32, m.m33);
        return TransformReciprocal3<T>{ transpose(upper_left) };
    }

    constexpr Transform3& operator*=(Transform3 const& rhs) {
        m *= rhs.m;
        return *this;
    }

    [[nodiscard]] friend constexpr Transform3 operator*(Transform3 const& lhs, Transform3 const& rhs) {
        return Transform3(lhs.m * rhs.m);
    }

    template<typename VectorTag_T>
    [[nodiscard]] friend constexpr Vector3Impl<T, VectorTag_T> operator*(Transform3 const& t,
                                                                         Vector3Impl<T, VectorTag_T> const& v)
        requires(!VectorTraits::IsFinitePoint<VectorTag_T>::value)
    {
        Matrix4<T> const& m = t.m;
        return Vector3Impl<T, VectorTag_T>(m.m11*v.x + m.m12*v.y + m.m13*v.z,
                                           m.m21*v.x + m.m22*v.y + m.m23*v.z,
                                           m.m31*v.x + m.m32*v.y + m.m33*v.z);
    }

    template<typename VectorTag_T>
    [[nodiscard]] friend constexpr Vector3Impl<T, VectorTag_T> operator*(Transform3<T> const& t,
                                                                          Vector3Impl<T, VectorTag_T> const& p)
        requires(VectorTraits::IsFinitePoint<VectorTag_T>::value)
    {
        Matrix4<T> const& m = t.m;
        return Vector3Impl<T, VectorTag_T>(m.m11*p.x + m.m12*p.y + m.m13*p.z + m.m14,
                                           m.m21*p.x + m.m22*p.y + m.m23*p.z + m.m24,
                                           m.m31*p.x + m.m32*p.y + m.m33*p.z + m.m34);
    }
};

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> inverse(Transform3<T> const& t)
{
    return Transform3<T>(inverse(t.m));
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Point3<T> project(Transform3<T> const& t, Point3<T> const& p)
{
    Matrix4<T> const& m = t.m;
    T const w = m.m41*p.x + m.m42*p.y + m.m43*p.z + m.m44;
    return Point3<T>((m.m11*p.x + m.m12*p.y + m.m13*p.z + m.m14) / w,
                     (m.m21*p.x + m.m22*p.y + m.m23*p.z + m.m24) / w,
                     (m.m31*p.x + m.m32*p.y + m.m33*p.z + m.m34) / w);
}

template<typename T>
[[nodiscard]] constexpr inline Point3<T> project(Transform3<T> const& t, Point3<T> const& p, T& w)
{
    Matrix4<T> const& m = t.m;
    T const p_w = w;
    w = m.m41*p.x + m.m42*p.y + m.m43*p.z + m.m44*w;
    return Point3<T>((m.m11*p.x + m.m12*p.y + m.m13*p.z + m.m14*p_w),
                     (m.m21*p.x + m.m22*p.y + m.m23*p.z + m.m24*p_w),
                     (m.m31*p.x + m.m32*p.y + m.m33*p.z + m.m34*p_w));
}

template<typename T>
[[nodiscard]] constexpr inline Transform3<T> make_scale3(T scale)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform3<T>(scale, z,     z,     z,
                         z,     scale, z,     z,
                         z,     z,     scale, z,
                         z,     z,     z,     o);
}

template<typename T>
[[nodiscard]] constexpr inline Transform3<T> make_scale(T scale_x, T scale_y, T scale_z)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform3<T>(scale_x, z,       z,       z,
                         z,       scale_y, z,       z,
                         z,       z,       scale_z, z,
                         z,       z,       z,       o);
}

template<typename T>
[[nodiscard]] constexpr inline Transform3<T> make_scale(Vector3<T> const& scale_v)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform3<T>(scale_v.x, z,         z,         z,
                         z,         scale_v.y, z,         z,
                         z,         z,         scale_v.z, z,
                         z,         z,         z,         o);
}

template<typename T>
[[nodiscard]] constexpr inline Transform3<T> make_translation(T translate_x, T translate_y, T translate_z)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform3<T>(o, z, z, translate_x,
                         z, o, z, translate_y,
                         z, z, o, translate_z,
                         z, z, z, o);
}

template<typename T>
[[nodiscard]] constexpr inline Transform3<T> make_translation(Vector3<T> const& translate_v)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform3<T>(o, z, z, translate_v.x,
                         z, o, z, translate_v.y,
                         z, z, o, translate_v.z,
                         z, z, z, o);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_rotation_x(T angle)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    T const sin = std::sin(angle);
    T const cos = std::cos(angle);
    return Transform3<T>(o,   z,    z, z,
                         z, cos, -sin, z,
                         z, sin,  cos, z,
                         z,   z,    z, o);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_rotation_y(T angle)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    T const sin = std::sin(angle);
    T const cos = std::cos(angle);
    return Transform3<T>( cos, z, sin, z,
                            z, o,   z, z,
                         -sin, z, cos, z,
                            z, z,   z, o);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_rotation_z(T angle)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    T const sin = std::sin(angle);
    T const cos = std::cos(angle);
    return Transform3<T>(cos, -sin, z, z,
                         sin,  cos, z, z,
                           z,    z, o, z,
                           z,    z, z, o);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_rotation(T angle, Vector3<T> axis)
{
    axis = normalized(axis);
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    T const cos = std::cos(angle);
    T const one_cos = o - cos;
    T const sin = std::sin(angle);
    return Transform3<T>( cos + one_cos*axis.x*axis.x,
                          one_cos*axis.x*axis.y - sin*axis.z,
                          one_cos*axis.x*axis.z + sin*axis.y,
                          z,
                          one_cos*axis.x*axis.y + sin*axis.z,
                          cos + one_cos*axis.y*axis.y,
                          one_cos*axis.y*axis.z - sin*axis.x,
                          z,
                          one_cos*axis.x*axis.z - sin*axis.y,
                          one_cos*axis.y*axis.z + sin*axis.x,
                          cos + one_cos*axis.z*axis.z,
                          z,
                          z, z, z, o);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_perspective_projection(T width, T height, T z_near, T z_far)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform3<T>(2*z_near/width,               z,                    z,                            z,
                                      z, 2*z_near/height,                    z,                            z,
                                      z,               z, z_far/(z_far-z_near), z_near*z_far/(z_near-z_far),
                                      z,               z,                    o,                            z);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_perspective_projection_fov(T fov, T aspect_ratio, T z_near, T z_far)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    T const yscale = o / std::tan(fov / T{ 2 });
    T const xscale = yscale / aspect_ratio;
    return Transform3<T>(xscale,      z,                    z,                           z,
                              z, yscale,                    z,                           z,
                              z,      z, z_far/(z_far-z_near), z_near*z_far/(z_near-z_far),
                              z,      z,                    o,                           z);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_perspective_projection_frustum(T left, T right, T bottom,
                                                                                 T top, T z_near, T z_far)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    T const width = right - left;
    T const height = top - bottom;
    T const lr = left + right;
    T const tb = top + bottom;
    return Transform3<T>(2*z_near/width,               z,                    z,                           z,
                                      z, 2*z_near/height,                    z,                           z,
                            lr/(-width),    tb/(-height), z_far/(z_far-z_near), z_near*z_far/(z_near-z_far),
                                      z,               z,                    o,                           z);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_perspective_projection_orthographic(T width, T height, T z_near, T z_far)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform3<T>(2/width,        z,                z,                     z,
                               z, 2/height,                z,                     z,
                               z,        z, o/(z_far-z_near), z_near/(z_near-z_far),
                               z,        z,                z,                     o);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_perspective_projection_orthographic_frustum(T left, T right, T bottom,
                                                                                              T top, T z_near, T z_far)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    T const width = right - left;
    T const height = top - bottom;
    T const lr = left + right;
    T const tb = top + bottom;
    return Transform3<T>(2/width,        z,                z,           lr/(-width),
                               z, 2/height,                z,          tb/(-height),
                               z,        z, o/(z_far-z_near), z_near/(z_near-z_far),
                               z,        z,                z,                     o);
}

template<std::floating_point T>
[[nodiscard]] constexpr inline Transform3<T> make_view_look_at(Vector3<T> position_eye,
                                                               Vector3<T> target_center,
                                                               Vector3<T> up)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    Vector3<T> const v_view = normalized(target_center - position_eye);
    Vector3<T> const v_right = normalized(cross(up, v_view));
    Vector3<T> const v_up = cross(v_view, v_right);

    return Transform3<T>(v_right.x, v_right.y, v_right.z, -dot(v_right, position_eye),
                            v_up.x,    v_up.y,    v_up.z,    -dot(v_up, position_eye),
                          v_view.x,  v_view.y,  v_view.z,  -dot(v_view, position_eye),
                                 z,         z,         z,                           o);
}

}

#endif
