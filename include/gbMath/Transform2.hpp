#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_TRANSFORM2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_TRANSFORM2_HPP

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

#include <type_traits>

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
};

struct assume_orthogonal_t {};
//inline assume_orthogonal_t assume_orthogonal;

/** A homogeneous 2D transformation.
 */
template<typename T>
class Transform2
{
public:
    Matrix3<T> m;
public:
    Transform2()
        :m(identity3<T>())
    {}

    Transform2(T n11, T n12, T n13,
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
    TransformReciprocal2<T> reciprocal()
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
    TransformReciprocal2<T> reciprocal(assume_orthogonal_t)
    {
        Matrix2<T> const upper_left(m.m11, m.m12,
                                    m.m21, m.m22);
        return TransformReciprocal2<T>{ transpose(upper_left) };
    }
};

template<typename T, typename VectorTag_T>
inline std::enable_if_t<!VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector2Impl<T, VectorTag_T>>
operator*(Transform2<T> const& t, Vector2Impl<T, VectorTag_T> const& v)
{
    Matrix3<T> const& m = t.m;
    return Vector2Impl<T, VectorTag_T>(m.m11*v.x + m.m12*v.y,
                                       m.m21*v.x + m.m22*v.y);
}

template<typename T, typename VectorTag_T>
inline std::enable_if_t<VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector2Impl<T, VectorTag_T>>
operator*(Transform2<T> const& t, Vector2Impl<T, VectorTag_T> const& p)
{
    Matrix3<T> const& m = t.m;
    return Vector2Impl<T, VectorTag_T>(m.m11*p.x + m.m12*p.y + m.m13,
                                       m.m21*p.x + m.m22*p.y + m.m23);
}

template<typename T, typename VectorTag_T>
inline std::enable_if_t<VectorTraits::IsReciprocal<VectorTag_T>::value && !VectorTraits::IsFinitePoint<VectorTag_T>::value, Vector2Impl<T, VectorTag_T>>
operator*(Vector2Impl<T, VectorTag_T> const& n, TransformReciprocal2<T> const& rt)
{
    Matrix2<T> const& m = rt.m;
    return Vector2Impl<T, VectorTag_T>(n.x*m.m11 + n.y*m.m21,
                                       n.x*m.m12 + n.y*m.m22);
}

template<typename T>
inline Transform2<T> make_scale(T scale_x, T scale_y)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform2<T>(scale_x, z,       z,
                         z,       scale_y, z,
                         z,       z,       o);
}
}

#endif
