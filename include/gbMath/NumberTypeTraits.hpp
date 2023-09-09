#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_NUMBER_TYPE_TRAITS_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_NUMBER_TYPE_TRAITS_HPP

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

    template<typename T>
    struct Pi;

    template<>
    struct Pi<float>
    {
        static constexpr float value = 3.1415926535897932384626433832795f;
    };

    template<>
    struct Pi<double>
    {
        static constexpr double value = 3.1415926535897932384626433832795;
    };
}
}
#endif
