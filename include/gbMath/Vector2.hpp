#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR2_HPP

/** @file
*
* @brief 2D Vector.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>
#include <gbMath/Common.hpp>

#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Vector2 {
public:
    T x;
    T y;

    Vector2()
        :x(), y()
    {}

    Vector2(leave_uninitialized const&)
    {}

    Vector2(T vx, T vy)
        :x(vx), y(vy)
    {}

    T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    Vector2<T>& operator+=(Vector2<T> const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2<T>& operator-=(Vector2<T> const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2<T>& operator*=(T s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    Vector2<T>& operator/=(T s)
    {
        x /= s;
        y /= s;
        return *this;
    }
};

template<typename T>
inline bool operator==(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return (lhs.x == rhs.x) &&
           (lhs.y == rhs.y);
}

template<typename T>
inline bool operator<(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return (lhs.x != rhs.x) ? (lhs.x < rhs.x) : (lhs.y < rhs.y);
}

template<typename T>
inline bool operator!=(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline bool operator<=(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T>
inline bool operator>(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator>=(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
inline Vector2<T> operator+(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return Vector2<T>(lhs.x + rhs.x,
                      lhs.y + rhs.y);
}

template<typename T>
inline Vector2<T> operator-(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return Vector2<T>(lhs.x - rhs.x,
                      lhs.y - rhs.y);
}

template<typename T>
inline Vector2<T> operator*(Vector2<T> const& v, T s)
{
    return Vector2<T>(v.x * s, v.y * s);
}

template<typename T>
inline Vector2<T> operator*(T s, Vector2<T> const& v)
{
    return Vector2<T>(s * v.x, s * v.y);
}

template<typename T>
inline Vector2<T> operator/(Vector2<T> const& v, T s)
{
    return Vector2<T>(v.x / s, v.y / s);
}
}

#endif
