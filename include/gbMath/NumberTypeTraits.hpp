#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_NUMBER_TYPE_TRAITS_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_NUMBER_TYPE_TRAITS_HPP

/** @file
*
* @brief Type traits used for adapting arbitrary number types as template arguments for math classes.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

#include <type_traits>

namespace GHULBUS_MATH_NAMESPACE
{
namespace traits
{
    template<typename T>
    struct Constants
    {
        static_assert(std::is_convertible<int, T>::value,
                      "Constants cannot be deduced for T. Please provide a specialization.");
        static inline T constexpr Zero()
        {
            return 0;
        }

        static inline T constexpr One()
        {
            return 1;
        }
    };
}
}
#endif
