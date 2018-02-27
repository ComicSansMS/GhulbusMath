#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_TRANSFORM2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_TRANSFORM2_HPP

/** @file
 *
 * @brief 2D Transformations.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Matrix3.hpp>
#include <gbMath/NumberTypeTraits.hpp>
#include <gbMath/Vector2.hpp>

#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
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
