#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR3_SWIZZLE_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR3_SWIZZLE_HPP

/** @file
*
* @brief Vector3 Swizzling.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>
#include <gbMath/Vector3.hpp>

namespace GHULBUS_MATH_NAMESPACE
{
namespace swizzler {
template<typename T>
class Vec3Swizzler {
private:
    Vector3<T> const& v_;
public:
    Vec3Swizzler(Vector3<T> const& v)
        :v_(v)
    {}

    Vector3<T> xxx() const
    {
        return Vector3<T>(v_.x, v_.x, v_.x);
    }

    Vector3<T> xxy() const
    {
        return Vector3<T>(v_.x, v_.x, v_.y);
    }

    Vector3<T> xxz() const
    {
        return Vector3<T>(v_.x, v_.x, v_.z);
    }

    Vector3<T> xyx() const
    {
        return Vector3<T>(v_.x, v_.y, v_.x);
    }

    Vector3<T> xyy() const
    {
        return Vector3<T>(v_.x, v_.y, v_.y);
    }

    Vector3<T> xyz() const
    {
        return Vector3<T>(v_.x, v_.y, v_.z);
    }

    Vector3<T> xzx() const
    {
        return Vector3<T>(v_.x, v_.z, v_.x);
    }

    Vector3<T> xzy() const
    {
        return Vector3<T>(v_.x, v_.z, v_.y);
    }

    Vector3<T> xzz() const
    {
        return Vector3<T>(v_.x, v_.z, v_.z);
    }

    Vector3<T> yxx() const
    {
        return Vector3<T>(v_.y, v_.x, v_.x);
    }

    Vector3<T> yxy() const
    {
        return Vector3<T>(v_.y, v_.x, v_.y);
    }

    Vector3<T> yxz() const
    {
        return Vector3<T>(v_.y, v_.x, v_.z);
    }

    Vector3<T> yyx() const
    {
        return Vector3<T>(v_.y, v_.y, v_.x);
    }

    Vector3<T> yyy() const
    {
        return Vector3<T>(v_.y, v_.y, v_.y);
    }

    Vector3<T> yyz() const
    {
        return Vector3<T>(v_.y, v_.y, v_.z);
    }

    Vector3<T> yzx() const
    {
        return Vector3<T>(v_.y, v_.z, v_.x);
    }

    Vector3<T> yzy() const
    {
        return Vector3<T>(v_.y, v_.z, v_.y);
    }

    Vector3<T> yzz() const
    {
        return Vector3<T>(v_.y, v_.z, v_.z);
    }

    Vector3<T> zxx() const
    {
        return Vector3<T>(v_.z, v_.x, v_.x);
    }

    Vector3<T> zxy() const
    {
        return Vector3<T>(v_.z, v_.x, v_.y);
    }

    Vector3<T> zxz() const
    {
        return Vector3<T>(v_.z, v_.x, v_.z);
    }

    Vector3<T> zyx() const
    {
        return Vector3<T>(v_.z, v_.y, v_.x);
    }

    Vector3<T> zyy() const
    {
        return Vector3<T>(v_.z, v_.y, v_.y);
    }

    Vector3<T> zyz() const
    {
        return Vector3<T>(v_.z, v_.y, v_.z);
    }

    Vector3<T> zzx() const
    {
        return Vector3<T>(v_.z, v_.z, v_.x);
    }

    Vector3<T> zzy() const
    {
        return Vector3<T>(v_.z, v_.z, v_.y);
    }

    Vector3<T> zzz() const
    {
        return Vector3<T>(v_.z, v_.z, v_.z);
    }
};
}

template<typename T>
inline swizzler::Vec3Swizzler<T> swizzle(Vector3<T> const& v)
{
    return swizzler::Vec3Swizzler<T>(v);
}
}

#endif
