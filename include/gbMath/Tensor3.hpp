#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_TENSOR3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_TENSOR3_HPP

/** @file
*
* @brief 3D Tensor.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/Basis3.hpp>
#include <gbMath/Matrix3.hpp>

namespace GHULBUS_MATH_NAMESPACE
{

template<typename T>
class Tensor3 {
public:
    Matrix3<T> m;
public:
    constexpr Tensor3()
        :m(identity3<T>())
    {}

    constexpr explicit Tensor3(Basis3<T> const& basis)
    {
        Vector3<T> const x = basis.x();
        Vector3<T> const y = basis.y();
        Vector3<T> const z = basis.z();

        m.m11 = dot(x, x);
        m.m12 = dot(x, y);
        m.m13 = dot(x, z);

        m.m21 = m.m12;
        m.m22 = dot(y, y);
        m.m23 = dot(y, z);

        m.m31 = m.m13;
        m.m32 = m.m23;
        m.m33 = dot(z, z);
    }
};

template<typename T>
[[nodiscard]] constexpr inline Tensor3<T> contravariant(Tensor3<T> const& t)
{
    Tensor3<T> ret;
    ret.m = inverse(t.m);
    return ret;
}

}
#endif
