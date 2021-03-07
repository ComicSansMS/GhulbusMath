#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_COMPONENT_VECTOR3_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_COMPONENT_VECTOR3_HPP

/** @file
*
* @brief 3D Component Vector.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <cmath>
#include <cstdint>
#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{

template<typename T>
class ComponentVector3 {
public:
    using ValueType = T;

    T x;
    T y;
    T z;

    ComponentVector3(T vx, T vy, T vz)
        :x(vx), y(vy), z(vz)
    {}

    explicit ComponentVector3(T const* arr)
        :x(arr[0]), y(arr[1]), z(arr[2])
    {}

    T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    ComponentVector3& operator+=(ComponentVector3 const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    ComponentVector3& operator-=(ComponentVector3 const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    ComponentVector3& operator*=(T s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    ComponentVector3& operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
};

template<typename T>
inline bool operator==(ComponentVector3<T> const& lhs, ComponentVector3<T> const& rhs)
{
    return (lhs.x == rhs.x) &&
           (lhs.y == rhs.y) &&
           (lhs.z == rhs.z);
}

template<typename T>
inline bool operator!=(ComponentVector3<T> const& lhs, ComponentVector3<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
inline ComponentVector3<T> operator+(ComponentVector3<T> const& lhs,
                                     ComponentVector3<T> const& rhs)
{
    return ComponentVector3<T>(lhs.x + rhs.x,
                               lhs.y + rhs.y,
                               lhs.z + rhs.z);
}

template<typename T>
inline ComponentVector3<T> operator-(ComponentVector3<T> const& lhs,
                                     ComponentVector3<T> const& rhs)
{
    return ComponentVector3<T>(lhs.x - rhs.x,
                               lhs.y - rhs.y,
                               lhs.z - rhs.z);
}

template<typename T>
inline ComponentVector3<T> operator*(ComponentVector3<T> const& v, T s)
{
    return ComponentVector3<T>(v.x * s, v.y * s, v.z * s);
}

template<typename T>
inline ComponentVector3<T> operator*(T s, ComponentVector3<T> const& v)
{
    return ComponentVector3<T>(s * v.x, s * v.y, s * v.z);
}

template<typename T>
inline ComponentVector3<T> operator/(ComponentVector3<T> const& v, T s)
{
    return ComponentVector3<T>(v.x / s, v.y / s, v.z / s);
}

}

#endif
