#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_COMPONENT_VECTOR3_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_COMPONENT_VECTOR3_HPP

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

    constexpr ComponentVector3(T vx, T vy, T vz)
        :x(vx), y(vy), z(vz)
    {}

    constexpr explicit ComponentVector3(T const* arr)
        :x(arr[0]), y(arr[1]), z(arr[2])
    {}

    [[nodiscard]] constexpr T& operator[](std::size_t idx)
    {
        return (&x)[idx];
    }

    [[nodiscard]] constexpr T const& operator[](std::size_t idx) const
    {
        return (&x)[idx];
    }

    constexpr ComponentVector3& operator+=(ComponentVector3 const& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    constexpr ComponentVector3& operator-=(ComponentVector3 const& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    constexpr ComponentVector3& operator*=(T s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    constexpr ComponentVector3& operator/=(T s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    [[nodiscard]] friend constexpr bool operator==(ComponentVector3 const&, ComponentVector3 const&) = default;

    [[nodiscard]] friend constexpr ComponentVector3 operator+(ComponentVector3 const& lhs,
                                                              ComponentVector3 const& rhs)
    {
        return ComponentVector3(lhs.x + rhs.x,
                                lhs.y + rhs.y,
                                lhs.z + rhs.z);
    }

    [[nodiscard]] friend constexpr ComponentVector3 operator-(ComponentVector3 const& lhs,
                                                              ComponentVector3 const& rhs)
    {
        return ComponentVector3(lhs.x - rhs.x,
                                lhs.y - rhs.y,
                                lhs.z - rhs.z);
    }

    [[nodiscard]] friend constexpr ComponentVector3 operator*(ComponentVector3 const& v, T s)
    {
        return ComponentVector3<T>(v.x * s, v.y * s, v.z * s);
    }

    [[nodiscard]] friend constexpr ComponentVector3 operator*(T s, ComponentVector3 const& v)
    {
        return ComponentVector3<T>(s * v.x, s * v.y, s * v.z);
    }

    [[nodiscard]] friend constexpr ComponentVector3 operator/(ComponentVector3 const& v, T s)
    {
        return ComponentVector3<T>(v.x / s, v.y / s, v.z / s);
    }
};

}

#endif
