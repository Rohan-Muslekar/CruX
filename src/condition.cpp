#include "server.h"

Condition::Condition(BooleanOperator booleanOperator, std::vector<Condition>& subConditions, int priority) {
    this->booleanOperator = booleanOperator;
    this->subConditions = subConditions;
    this->priority = priority;
}

Condition::Condition(std::string factId, Operator::OperatorName op, ValueType value, int priority) {
    this->factId = factId;
    this->op = Operators[op];
    this->value = value;
    this->priority = priority;
}

std::vector<Condition>& Condition::getSubConditions() {
    return subConditions;
}

bool Condition::evaluate(Almanac& almanac) {
    bool result = false;
    Operator::OperatorName opName = op.getName();
    ValueType factValue = getValue(almanac);
    result = op.evaluate(factValue, value);
    return result;
}

ValueType Condition::getValue(Almanac& almanac) {
    return almanac.getFact(factId)->getValue();
}

Condition::BooleanOperator Condition::getBooleanOperator() {
    return booleanOperator;
}

bool Condition::isBooleanOperator() {
    return booleanOperator == BooleanOperator::ALL || booleanOperator == BooleanOperator::ANY || booleanOperator == BooleanOperator::NOT;
}

int Condition::getPriority() {
    return priority;
}

void Condition::setResult(bool result) {
    this->result = result;
}