#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR3_HPP

/** @file
*
* @brief 3D Vector.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <cmath>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Vector3 {
public:
    T x;
    T y;
    T z;

    Vector3() = default;
    Vector3(Vector3<T> const&) = default;
    Vector3<T>& operator=(Vector3<T> const&) = default;

    Vector3(T vx, T vy, T vz)
        :x(vx), y(vy), z(vz)
    {}

    template<typename U>
    explicit Vector3(Vector3<U> const& v)
        :x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
    {}

    T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    Vector3<T>& operator+=(Vector3<T> const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector3<T>& operator-=(Vector3<T> const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vector3<T>& operator*=(T s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    Vector3<T>& operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
};

template<typename T>
inline bool operator==(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return (lhs.x == rhs.x) &&
           (lhs.y == rhs.y) &&
           (lhs.z == rhs.z);
}

template<typename T>
inline bool operator<(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    if(lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    } else if(lhs.y != rhs.y) {
        return lhs.y < rhs.y;
    } else {
        return lhs.z < rhs.z;
    }
}

template<typename T>
inline bool operator!=(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline bool operator<=(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T>
inline bool operator>(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator>=(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
inline Vector3<T> operator+(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return Vector3<T>(lhs.x + rhs.x,
                      lhs.y + rhs.y,
                      lhs.z + rhs.z);
}

template<typename T>
inline Vector3<T> operator-(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return Vector3<T>(lhs.x - rhs.x,
                      lhs.y - rhs.y,
                      lhs.z - rhs.z);
}

template<typename T>
inline Vector3<T> operator*(Vector3<T> const& v, T s)
{
    return Vector3<T>(v.x * s, v.y * s, v.z * s);
}

template<typename T>
inline Vector3<T> operator*(T s, Vector3<T> const& v)
{
    return Vector3<T>(s * v.x, s * v.y, s * v.z);
}

template<typename T>
inline Vector3<T> operator/(Vector3<T> const& v, T s)
{
    return Vector3<T>(v.x / s, v.y / s, v.z / s);
}

template<typename T>
inline T dot(Vector3<T> const& lhs, Vector3<T> const& rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}
}

#endif
