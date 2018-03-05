#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_TRANSFORM3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_TRANSFORM3_HPP

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

#include <type_traits>

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
};

/** A homogeneous 2D transformation.
 */
template<typename T>
class Transform3
{
public:
    Matrix4<T> m;
public:
    Transform3()
        :m(identity4<T>())
    {}

    Transform3(T n11, T n12, T n13, T n14,
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
    TransformReciprocal3<T> reciprocal()
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
    TransformReciprocal3<T> reciprocal(assume_orthogonal_t)
    {
        Matrix3<T> const upper_left(m.m11, m.m12, m.m13,
                                    m.m21, m.m22, m.m23,
                                    m.m31, m.m32, m.m33);
        return TransformReciprocal3<T>{ transpose(upper_left) };
    }
};

template<typename T, typename VectorTag_T>
inline std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector3Impl<T, VectorTag_T>>
operator*(Transform3<T> const& t, Vector3Impl<T, VectorTag_T> const& v)
{
    Matrix4<T> const& m = t.m;
    return Vector3Impl<T, VectorTag_T>(m.m11*v.x + m.m12*v.y + m.m13*v.z,
                                       m.m21*v.x + m.m22*v.y + m.m23*v.z,
                                       m.m31*v.x + m.m32*v.y + m.m33*v.z);
}

template<typename T, typename VectorTag_T>
inline std::enable_if_t<VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector3Impl<T, VectorTag_T>>
operator*(Transform3<T> const& t, Vector3Impl<T, VectorTag_T> const& p)
{
    Matrix4<T> const& m = t.m;
    return Vector3Impl<T, VectorTag_T>(m.m11*p.x + m.m12*p.y + m.m13*p.z + m.m14,
                                       m.m21*p.x + m.m22*p.y + m.m23*p.z + m.m24,
                                       m.m31*p.x + m.m32*p.y + m.m33*p.z + m.m34);
}

template<typename T, typename VectorTag_T>
inline std::enable_if_t<VectorTraits::IsReciprocal<VectorTag_T>::value &&
                        !VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector3Impl<T, VectorTag_T>>
operator*(Vector3Impl<T, VectorTag_T> const& n, TransformReciprocal3<T> const& rt)
{
    Matrix3<T> const& m = rt.m;
    return Vector3Impl<T, VectorTag_T>(n.x*m.m11 + n.y*m.m21 + n.z*m.m31,
                                       n.x*m.m12 + n.y*m.m22 + n.z*m.m32,
                                       n.x*m.m13 + n.y*m.m23 + n.z*m.m33);
}

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, Point3<T>>
project(Transform3<T> const& t, Point3<T> const& p)
{
    Matrix4<T> const& m = t.m;
    T const w = m.m41*p.x + m.m42*p.y + m.m43*p.z + m.m44;
    return Point3<T>((m.m11*p.x + m.m12*p.y + m.m13*p.z + m.m14) / w,
                     (m.m21*p.x + m.m22*p.y + m.m23*p.z + m.m24) / w,
                     (m.m31*p.x + m.m32*p.y + m.m33*p.z + m.m34) / w);
}

template<typename T>
Point3<T> project(Transform3<T> const& t, Point3<T> const& p, T& w)
{
    Matrix4<T> const& m = t.m;
    T const p_w = w;
    w = m.m41*p.x + m.m42*p.y + m.m43*p.z + m.m44*w;
    return Point3<T>((m.m11*p.x + m.m12*p.y + m.m13*p.z + m.m14*p_w),
                     (m.m21*p.x + m.m22*p.y + m.m23*p.z + m.m24*p_w),
                     (m.m31*p.x + m.m32*p.y + m.m33*p.z + m.m34*p_w));
}

template<typename T>
inline Transform3<T> make_scale(T scale_x, T scale_y, T scale_z)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform3<T>(scale_x, z,       z,       z,
                         z,       scale_y, z,       z,
                         z,       z,       scale_z, z,
                         z,       z,       z,       o);
}
}

#endif
