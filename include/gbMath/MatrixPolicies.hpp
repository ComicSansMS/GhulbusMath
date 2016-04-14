#ifndef GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX_POLICIES_HPP
#define GHULBUS_LIBRARY_INCLUDE_GUARD_MATH_MATRIX_POLICIES_HPP

/** @file
*
* @brief Policies shared by all Matrix types.
* @author Andreas Weis (der_ghulbus@ghulbus-inc.de)
*/

#include <gbMath/config.hpp>

namespace GHULBUS_MATH_NAMESPACE
{
namespace MatrixPolicies
{
enum class Order
{
    RowMajor,
    ColumnMajor
};

template<Order order>
struct InputOrder_T {
    static constexpr Order const value = order;
};

using InputOrder_RowMajor = InputOrder_T<Order::RowMajor>;
using InputOrder_ColumnMajor = InputOrder_T<Order::ColumnMajor>;
}
}
#endif
