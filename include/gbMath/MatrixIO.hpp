#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX_IO_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX_IO_HPP

/** @file
*
* @brief ostream inserter functions for Matrix types.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>
#include <gbMath/Matrix2.hpp>

#include <ostream>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix2<T> const& rhs)
{
    os << "[ [" << rhs.m11 << " " << rhs.m12 << "] [" << rhs.m21 << " " << rhs.m22 << "] ]";
    return os;
}
}

#endif