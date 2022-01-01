#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_IO_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_IO_HPP

/** @file
 *
 * @brief ostream inserter functions for Vector types.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Vector2.hpp>
#include <gbMath/Vector3.hpp>
#include <gbMath/Vector4.hpp>

#include <ostream>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T, typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector2Impl<T, VectorTag_T> const& rhs)
{
    os << '[' << rhs.x << ' ' << rhs.y << ']';
    return os;
}

template<typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector2Impl<char, VectorTag_T> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ']';
    return os;
}

template<typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector2Impl<signed char, VectorTag_T> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ']';
    return os;
}

template<typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector2Impl<unsigned char, VectorTag_T> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ']';
    return os;
}

template<typename T, typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector3Impl<T, VectorTag_T> const& rhs)
{
    os << '[' << rhs.x << ' ' << rhs.y << ' ' << rhs.z << ']';
    return os;
}

template<typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector3Impl<char, VectorTag_T> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ']';
    return os;
}

template<typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector3Impl<signed char, VectorTag_T> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ']';
    return os;
}

template<typename VectorTag_T>
inline std::ostream& operator<<(std::ostream& os, Vector3Impl<unsigned char, VectorTag_T> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ']';
    return os;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Vector4<T> const& rhs)
{
    os << '[' << rhs.x << ' ' << rhs.y << ' ' << rhs.z << ' ' << rhs.w << ']';
    return os;
}

inline std::ostream& operator<<(std::ostream& os, Vector4<char> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ' ' << static_cast<int>(rhs.w) << ']';
    return os;
}


inline std::ostream& operator<<(std::ostream& os, Vector4<signed char> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ' ' << static_cast<int>(rhs.w) << ']';
    return os;
}


inline std::ostream& operator<<(std::ostream& os, Vector4<unsigned char> const& rhs)
{
    os << '[' << static_cast<int>(rhs.x) << ' ' << static_cast<int>(rhs.y) << ' ' << static_cast<int>(rhs.z) << ' ' << static_cast<int>(rhs.w) << ']';
    return os;
}
}

#endif
