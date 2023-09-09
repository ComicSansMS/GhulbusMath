#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR3_SWIZZLE_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR3_SWIZZLE_HPP

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
template<typename T, typename VectorTag_T>
class Vec3Swizzler {
private:
    Vector3Impl<T, VectorTag_T> const& v_;
public:
    constexpr explicit Vec3Swizzler(Vector3Impl<T, VectorTag_T> const& v)
        :v_(v)
    {}

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xxx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.x, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xxy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.x, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xxz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.x, v_.z);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xyx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.y, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xyy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.y, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xyz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.y, v_.z);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xzx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.z, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xzy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.z, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> xzz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.x, v_.z, v_.z);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yxx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.x, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yxy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.x, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yxz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.x, v_.z);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yyx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.y, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yyy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.y, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yyz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.y, v_.z);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yzx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.z, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yzy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.z, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> yzz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.y, v_.z, v_.z);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zxx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.x, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zxy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.x, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zxz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.x, v_.z);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zyx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.y, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zyy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.y, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zyz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.y, v_.z);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zzx() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.z, v_.x);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zzy() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.z, v_.y);
    }

    [[nodiscard]] constexpr Vector3Impl<T, VectorTag_T> zzz() const
    {
        return Vector3Impl<T, VectorTag_T>(v_.z, v_.z, v_.z);
    }
};
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline swizzler::Vec3Swizzler<T, VectorTag_T> swizzle(Vector3Impl<T, VectorTag_T> const& v)
{
    return swizzler::Vec3Swizzler<T, VectorTag_T>(v);
}
}

#endif
