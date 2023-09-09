#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR2_SWIZZLE_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_VECTOR2_SWIZZLE_HPP

/** @file
 *
 * @brief Vector2 Swizzling.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Vector2.hpp>

namespace GHULBUS_MATH_NAMESPACE
{
namespace swizzler {
template<typename T, typename VectorTag_T>
class Vec2Swizzler {
private:
    Vector2Impl<T, VectorTag_T> const& v_;
public:
    constexpr explicit Vec2Swizzler(Vector2Impl<T, VectorTag_T> const& v)
        :v_(v)
    {}

    [[nodiscard]] constexpr Vector2Impl<T, VectorTag_T> xx() const
    {
        return Vector2Impl<T, VectorTag_T>(v_.x, v_.x);
    }

    [[nodiscard]] constexpr Vector2Impl<T, VectorTag_T> xy() const
    {
        return Vector2Impl<T, VectorTag_T>(v_.x, v_.y);
    }

    [[nodiscard]] constexpr Vector2Impl<T, VectorTag_T> yx() const
    {
        return Vector2Impl<T, VectorTag_T>(v_.y, v_.x);
    }

    [[nodiscard]] constexpr Vector2Impl<T, VectorTag_T> yy() const
    {
        return Vector2Impl<T, VectorTag_T>(v_.y, v_.y);
    }
};
}

template<typename T, typename VectorTag_T>
[[nodiscard]] constexpr inline swizzler::Vec2Swizzler<T, VectorTag_T> swizzle(Vector2Impl<T, VectorTag_T> const& v)
{
    return swizzler::Vec2Swizzler<T, VectorTag_T>(v);
}
}

#endif
