#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_TRAITS_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_VECTOR_TRAITS_HPP

/** @file
 *
 * @brief Vector Traits.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
/** Tags used for discerning different vector types.
 */
namespace VectorTag
{
/** Vector tag.
 * A Vector marks a point at infinity (homogeneous component = 0).
 * Vectors are indifferent to translation, but can be added and subtracted both from each other and from Points.
 */
struct Vector {};

/** Point tag.
 * A regular Point in space (homogeneous component = 1).
 * Points can be translated via Transformation or Vector, but cannot be added together.
 * Subtracting two points results in a Vector.
 */
struct Point {};

/** Normal tag.
 * A Normal is a vector of reciprocal distances. Typically Normals express vector that is perpendicular to some Vector.
 * To preserve this perpendicularity across Transformations, Normals are transformed by the inverse transpose.
 */
struct Normal {};
}

namespace VectorTraits
{
/** Indicates whether a vector is a point at infinity (homogeneous component = 0).
 */
template<typename Tag> struct IsFinitePoint : std::false_type {};
template<> struct IsFinitePoint<VectorTag::Point> : std::true_type {};

/** Indicates whether a vector is measuring reciprocal distances (like Normals).
 */
template<typename Tag> struct IsReciprocal : std::false_type {};
template<> struct IsReciprocal<VectorTag::Normal> : std::true_type {};
}
}

#endif
