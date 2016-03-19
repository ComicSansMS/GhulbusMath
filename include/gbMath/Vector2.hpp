#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR2_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR2_HPP

/** @file
*
* @brief 2D Vector.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <cmath>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Vector2 {
public:
    T x;
    T y;

    Vector2() = default;
    Vector2(Vector2<T> const&) = default;
    Vector2<T>& operator=(Vector2<T> const&) = default;

    Vector2(T vx, T vy)
        :x(vx), y(vy)
    {}

    template<typename U>
    explicit Vector2(Vector2<U> const& v)
        :x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
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

template<typename T>
inline T dot(Vector2<T> const& lhs, Vector2<T> const& rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

template<typename T>
inline double length(Vector2<T> const& v)
{
    return std::sqrt(static_cast<double>(dot(v, v)));
}

inline float length(Vector2<float> const& v)
{
    return std::sqrt(dot(v, v));
}

inline long double length(Vector2<long double> const& v)
{
    return std::sqrt(dot(v, v));
}

template<typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, Vector2<T>>::type normalized(Vector2<T> const& v)
{
    T const len = length(v);
    return Vector2<T>(v.x / len, v.y / len);
}
}

#endif