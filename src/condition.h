#pragma once


#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <stdexcept>
#include <memory>

#include "operator.h"
#include "almanac.h"
#include "default-operators.h"
#include "fact.h"
#include "almanac.h"
#include "fwd.h"


enum class ConditionType {
    BOOLEAN,
    NON_BOOLEAN
};

// Define the Condition class
class Condition {
public:
    enum BooleanOperator {
        ALL,
        ANY,
        NOT
    };

    Condition(BooleanOperator booleanOperator, std::vector<Condition>& subConditions, int priority = 1);
    Condition(std::string factId, Operator::OperatorName op, ValueType value, int priority = 1);

    // Function to get the conditions
    std::vector<Condition>& getSubConditions() ;

    // Function to evaluate the condition
    bool evaluate(Almanac& almanac);


    // Function to get the value of the condition
    ValueType getValue(Almanac& almanac);
    
    void setFactResult(bool factResult);


    BooleanOperator getBooleanOperator();
    // Function to check if the operator is a boolean operator
    bool isBooleanOperator() ;

    // Function to get the condition's priority
    int getPriority() ;

    // Function to set Result
    void setResult(bool result);
private:
    ConditionType conditionType;
    BooleanOperator booleanOperator;
    int priority;
    std::vector<Condition> subConditions;
    bool result;
    bool factResult;

    std::string factId;
    Operator op;
    ValueType value;
};

// Function to compare the fact result with the condition value using the operator