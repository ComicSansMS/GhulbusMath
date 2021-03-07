#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_BASIS3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_BASIS3_HPP

/** @file
*
* @brief 3D Vector Basis.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <gbMath/ComponentVector3.hpp>
#include <gbMath/Matrix3.hpp>
#include <gbMath/Vector3.hpp>

namespace GHULBUS_MATH_NAMESPACE
{

template<typename T>
class Basis3 {
private:
    Matrix3<T> m_rowMatrix;
public:
    Basis3()
        :m_rowMatrix(identity3<T>())
    {}

    Basis3(Vector3<T> const& x, Vector3<T> const& y, Vector3<T> const& z)
        :m_rowMatrix(x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z)
    {}

    Vector3<T> x() const {
        return m_rowMatrix.row(0);
    }

    Vector3<T> y() const {
        return m_rowMatrix.row(1);
    }

    Vector3<T> z() const {
        return m_rowMatrix.row(2);
    }

    Matrix3<T> rowMatrix() const {
        return m_rowMatrix;
    }

    Matrix3<T> columnMatrix() const {
        return transpose(m_rowMatrix);
    }

    Vector3<T> fromComponentVector(ComponentVector3<T> const& cv) const {
        return (cv.x * x() + cv.y * y() + cv.z * z());
    }

    template <typename TT>
    friend inline Basis3<TT> contravariant(Basis3<TT> const& b) {
        Basis3<TT> ret;
        ret.m_rowMatrix = inverse(b.m_rowMatrix);
        return ret;
    }
};



}
#endif
