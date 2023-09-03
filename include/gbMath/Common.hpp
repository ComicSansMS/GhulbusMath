#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_COMMON_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_COMMON_HPP

/** @file
 *
 * @brief Common types and definitons.
 * @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
 */

#include <gbMath/config.hpp>

namespace GHULBUS_MATH_NAMESPACE
{
    /** Tag indicating that an operation will leave certain data members uninitialized.
     */
    struct DoNotInitialize_Tag {};

    inline constinit const DoNotInitialize_Tag doNotInitialize;
}

#endif
