#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_SWIZZLE_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_SWIZZLE_HPP

/** @file
*
* @brief Vector Swizzling.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>
#include <gbMath/Vector2.hpp>

namespace GHULBUS_MATH_NAMESPACE
{
namespace swizzler {
template<typename T>
class Vec2Swizzler {
private:
    Vector2<T> const& v_;
public:
    Vec2Swizzler(Vector2<T> const& v)
        :v_(v)
    {}

    Vector2<T> xx() const
    {
        return Vector2<T>(v_.x, v_.x);
    }

    Vector2<T> xy() const
    {
        return Vector2<T>(v_.x, v_.y);
    }

    Vector2<T> yx() const
    {
        return Vector2<T>(v_.y, v_.x);
    }

    Vector2<T> yy() const
    {
        return Vector2<T>(v_.y, v_.y);
    }
};
}

template<typename T>
inline swizzler::Vec2Swizzler<T> swizzle(Vector2<T> const& v)
{
    return swizzler::Vec2Swizzler<T>(v);
}
}

#endif
