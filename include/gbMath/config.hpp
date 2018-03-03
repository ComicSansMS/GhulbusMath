#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_GBMATH_CONFIG_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_GBMATH_CONFIG_HPP

/** @file
 *
 * @brief General configuration for Math.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

/** \namespace GhulbusMath Namespace for the Ghulbus library.
 * The implementation internally always uses this macro `GHULBUS_MATH_NAMESPACE` to refer to the namespace.
 * When using GhulbusMath yourself, you can globally redefine this macro to move to a different namespace.
 */
#ifndef GHULBUS_MATH_NAMESPACE
#   define GHULBUS_MATH_NAMESPACE GhulbusMath
#endif

#endif
