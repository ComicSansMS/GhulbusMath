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

template<typename T>
Vector2<T> operator*(Transform2<T> const& t, Vector2<T> const& v) {
    Matrix3<T> const& m = t.m;
    return Vector2<T>(v.x*m.m11 + v.y*m.m12,
                      v.x*m.m21 + v.y*m.m22);
}

template<typename T>
Point2<T> operator*(Transform2<T> const& t, Point2<T> const& p) {
    Matrix3<T> const& m = t.m;
    return Point2<T>(p.x*m.m11 + p.y*m.m12 + m.m13,
                     p.x*m.m21 + p.y*m.m22 + m.m23);
}

template<typename T>
Transform2<T> make_scale(T scale_x, T scale_y)
{
    T const z = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::Zero();
    T const o = ::GHULBUS_MATH_NAMESPACE::traits::Constants<T>::One();
    return Transform2<T>(scale_x, z,       z,
                         z,       scale_y, z,
                         z,       z,       o);
}
}

#endif
