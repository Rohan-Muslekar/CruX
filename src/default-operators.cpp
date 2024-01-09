#include "server.h"

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

std::map<Operator::OperatorName, Operator> Operators = {
    {Operator::OperatorName::EQUAL, Operator(Operator::OperatorName::EQUAL, [](double factValue, double jsonValue) { return factValue == jsonValue; }, [] (double value) { return true;})},
    {Operator::OperatorName::NOT_EQUAL, Operator(Operator::OperatorName::NOT_EQUAL, [](double factValue, double jsonValue) { return factValue != jsonValue; }, [] (double value) { return true;})},
    {Operator::OperatorName::IN, Operator(Operator::OperatorName::IN, [](double factValue, double jsonValue) { return false; }, [] (double value) { return true;})},
    {Operator::OperatorName::NOT_IN, Operator(Operator::OperatorName::NOT_IN, [](double factValue, double jsonValue) { return false; }, [] (double value) { return true;})},
    {Operator::OperatorName::CONTAINS, Operator(Operator::OperatorName::CONTAINS, [](double factValue, double jsonValue) { return false; }, [] (double value) { return true;})},
    {Operator::OperatorName::DOES_NOT_CONTAIN, Operator(Operator::OperatorName::DOES_NOT_CONTAIN, [](double factValue, double jsonValue) { return false; }, [] (double value) { return true;})},
    {Operator::OperatorName::LESS_THAN, Operator(Operator::OperatorName::LESS_THAN, [](double factValue, double jsonValue) { return false; }, [] (double value) { return true;})},
    {Operator::OperatorName::LESS_THAN_INCLUSIVE, Operator(Operator::OperatorName::LESS_THAN_INCLUSIVE, [](double factValue, double jsonValue) { return false; }, [] (double value) { return true;})},
    {Operator::OperatorName::GREATER_THAN, Operator(Operator::OperatorName::GREATER_THAN, [](double factValue, double jsonValue) { return false; }, [] (double value) { return true;})},
    {Operator::OperatorName::GREATER_THAN_INCLUSIVE, Operator(Operator::OperatorName::GREATER_THAN_INCLUSIVE, [](double factValue, double jsonValue) { return false; }, [] (double value) { return true;})}
};
