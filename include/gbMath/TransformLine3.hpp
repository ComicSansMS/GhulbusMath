#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_TRANSFORMLINE3_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_TRANSFORMLINE3_HPP

/** @file
 *
 * @brief Transformation of 3D Lines.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <gbMath/Line3.hpp>
#include <gbMath/Transform3.hpp>

namespace GHULBUS_MATH_NAMESPACE
{

template<typename T>
[[nodiscard]] constexpr inline Line3<T> operator*(Transform3<T> const& transform, Line3<T> const& line) {
    return Line3<T>(
        transform * line.p,
        transform * line.v
    );
}

}

#endif
