#include "server.h"

Operator::Operator(Operator::OperatorName name, Callable_t callback, CallableFactValue factValueValidator) {
    this->name = name;
    this->callback = callback;
    this->factValueValidator = factValueValidator;
}

Operator::Operator() {

}

Operator::OperatorName Operator::getName() {
    return this->name;
}

bool Operator::evaluate(ValueType factValue, ValueType conditionValue) {
    return callback(factValue, conditionValue) && factValueValidator(factValue);
}