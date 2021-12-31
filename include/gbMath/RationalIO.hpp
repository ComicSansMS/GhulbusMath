#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_RATIONAL_IO_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_RATIONAL_IO_HPP

/** @file
 *
 * @brief ostream inserter functions for rational type.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>
#include <gbMath/Rational.hpp>

#include <ostream>

namespace GHULBUS_MATH_NAMESPACE
{
template<typename T>
std::ostream& operator<<(std::ostream& os, Rational<T> const& rhs)
{
    os << rhs.numerator() << '/' << rhs.denominator();
    return os;
}
}

#endif
