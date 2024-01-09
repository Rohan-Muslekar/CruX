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
private:
    ConditionType conditionType;
    std::string booleanOperator;
    int priority;
    std::vector<Condition> subConditions;
    bool result;
    bool factResult;

public:
    // ructor
    Condition();
    Condition( std::map<std::string, std::string>& properties);

    // Function to get the conditions
     std::vector<Condition>& getSubConditions() ;


    ConditionType getConditionType( std::map<std::string, std::string>& properties) ;

    void setBooleanOperator( std::map<std::string, std::string>& properties);

    void parseSubConditions( std::string& subConditionsStr);

    void setNonBooleanCondition( std::map<std::string, std::string>& properties);

    // Function to evaluate the condition
    std::map<std::string, double> evaluate(Almanac& almanac);


    // Function to get the value of the condition
    double getValue(Almanac& almanac);
    
    void setFactResult(bool factResult);

    // Function to get the boolean operator for the condition
    static std::string& getBooleanOperator(Condition& condition);

    std::string getBooleanOperator() ;
    // Function to check if the operator is a boolean operator
    bool isBooleanOperator() ;

    // Function to get the condition's priority
    int getPriority() ;

    // Function to set Result
    void setResult(bool result);
};

// Function to compare the fact result with the condition value using the operator