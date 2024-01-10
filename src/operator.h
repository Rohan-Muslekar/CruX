// operator.h
#pragma once 
#include <iostream>
#include <functional>
#include <stdexcept>

#include "fwd.h"
#include "types.dto.h"

// Define the Operator class
class Operator {
public:

    enum struct OperatorName: short int {
        EQUAL,
        NOT_EQUAL,
        IN,
        NOT_IN,
        CONTAINS,
        DOES_NOT_CONTAIN,
        LESS_THAN,
        LESS_THAN_INCLUSIVE,
        GREATER_THAN,
        GREATER_THAN_INCLUSIVE
    };
    // Constructor
    Operator();
    Operator(Operator::OperatorName name, Callable_t callback, CallableFactValue factValueValidator);

    // Function to evaluate the operator
    bool evaluate(ValueType factValue, ValueType conditionValue);

    // Function to get the operator's name
    OperatorName getName();

    private:
    OperatorName name;
    Callable_t callback;
    CallableFactValue factValueValidator;
};