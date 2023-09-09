#ifndef INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_TEST_UTILS_MULTIPLICATION_ORDER_AWARE_OPERAND_HPP
#define INCLUDE_GUARD_GHULBUS_LIBRARY_MATH_TEST_UTILS_MULTIPLICATION_ORDER_AWARE_OPERAND_HPP

#include <vector>

/* Helper type to track order of operands in multiplication operations */
struct MultiplicationOrderAwareOperand {
private:
    int id_;
    std::vector<int>* lhsIds_;
    std::vector<int>* rhsIds_;
public:
    MultiplicationOrderAwareOperand()
        :id_(-1)
    {}
    MultiplicationOrderAwareOperand(int id, std::vector<int>& lhsIds, std::vector<int>& rhsIds)
        :id_(id), lhsIds_(&lhsIds), rhsIds_(&rhsIds)
    {}

    int id() const {
        return id_;
    }

    MultiplicationOrderAwareOperand operator*(MultiplicationOrderAwareOperand const& rhs) const {
        lhsIds_->push_back(id());
        rhsIds_->push_back(rhs.id());
        return MultiplicationOrderAwareOperand(id_ + 10, *lhsIds_, *rhsIds_);
    }
};

#endif
