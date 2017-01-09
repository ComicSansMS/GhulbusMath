#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR4_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR4_HPP

/** @file
 *
 * @brief 4D Vector.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <cmath>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
class Vector4 {
public:
    T x;
    T y;
    T z;
    T w;

    Vector4() = default;
    Vector4(Vector4<T> const&) = default;
    Vector4<T>& operator=(Vector4<T> const&) = default;

    Vector4(T vx, T vy, T vz, T vw)
        :x(vx), y(vy), z(vz), w(vw)
    {}

    Vector4(T const* arr)
        :x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3])
    {}

    template<typename U>
    explicit Vector4(Vector4<U> const& v)
        :x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(static_cast<T>(v.w))
    {}

    T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    Vector4<T>& operator+=(Vector4<T> const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    Vector4<T>& operator-=(Vector4<T> const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    Vector4<T>& operator*=(T s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }

    Vector4<T>& operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
        return *this;
    }
};

template<typename T>
inline bool operator==(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return (lhs.x == rhs.x) &&
           (lhs.y == rhs.y) &&
           (lhs.z == rhs.z) &&
           (lhs.w == rhs.w);
}

template<typename T>
inline bool operator<(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    if(lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    } else if(lhs.y != rhs.y) {
        return lhs.y < rhs.y;
    } else if(lhs.z != rhs.z) {
        return lhs.z < rhs.z;
    } else {
        return lhs.w < rhs.w;
    }
}

template<typename T>
inline bool operator!=(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline bool operator<=(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return !(rhs < lhs);
}

template<typename T>
inline bool operator>(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return rhs < lhs;
}

template<typename T>
inline bool operator>=(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return !(lhs < rhs);
}

template<typename T>
inline Vector4<T> operator+(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return Vector4<T>(lhs.x + rhs.x,
                      lhs.y + rhs.y,
                      lhs.z + rhs.z,
                      lhs.w + rhs.w);
}

template<typename T>
inline Vector4<T> operator-(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return Vector4<T>(lhs.x - rhs.x,
                      lhs.y - rhs.y,
                      lhs.z - rhs.z,
                      lhs.w - rhs.w);
}

template<typename T>
inline Vector4<T> operator*(Vector4<T> const& v, T s)
{
    return Vector4<T>(v.x * s, v.y * s, v.z * s, v.w * s);
}

template<typename T>
inline Vector4<T> operator*(T s, Vector4<T> const& v)
{
    return Vector4<T>(s * v.x, s * v.y, s * v.z, s * v.w);
}

template<typename T>
inline Vector4<T> operator/(Vector4<T> const& v, T s)
{
    return Vector4<T>(v.x / s, v.y / s, v.z / s,  v.w / s);
}

template<typename T>
inline T dot(Vector4<T> const& lhs, Vector4<T> const& rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
}

template<typename T>
inline double length(Vector4<T> const& v)
{
    return std::sqrt(static_cast<double>(dot(v, v)));
}

inline float length(Vector4<float> const& v)
{
    return std::sqrt(dot(v, v));
}

inline long double length(Vector4<long double> const& v)
{
    return std::sqrt(dot(v, v));
}

template<typename T>
inline std::enable_if_t<std::is_floating_point<T>::value, Vector4<T>> normalized(Vector4<T> const& v)
{
    T const len = length(v);
    return Vector4<T>(v.x / len, v.y / len, v.z / len, v.w / len);
}
}

#endif
