#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_IO_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_IO_HPP

/** @file
*
* @brief ostream inserter functions for Vector types.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>
#include <gbMath/Vector2.hpp>

#include <ostream>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
std::ostream& operator<<(std::ostream& os, Vector2<T> const& rhs)
{
    os << '[' << rhs.x << ' ' << rhs.y << ']';
    return os;
}
}

#endif
