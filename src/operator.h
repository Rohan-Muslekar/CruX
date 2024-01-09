// operator.h
#pragma once 
#include <functional>
#include <stdexcept>

#include "fwd.h"


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
    Operator(OperatorName name, std::function<bool(double, double)> callback, std::function<bool(double)> factValueValidator);

    // Function to evaluate the operator
    bool evaluate(double factValue, double jsonValue);

    // Function to get the operator's name
    OperatorName getName();

private:
    OperatorName name;
    std::function<bool(double, double)> callback;
    std::function<bool(double)> factValueValidator;
};