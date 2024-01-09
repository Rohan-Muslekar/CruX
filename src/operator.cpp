#include "server.h"

Operator::Operator(OperatorName name, std::function<bool(double, double)> callback, std::function<bool(double)> factValueValidato) {
    this->name = name;
    this->callback = callback;
    this->factValueValidator = factValueValidator;
}

Operator::Operator() {
    this->name = OperatorName::EQUAL;
    this->callback = [](double factValue, double jsonValue) { return factValue == jsonValue; };
    this->factValueValidator = nullptr;
}

bool Operator::evaluate(double factValue, double jsonValue) {
    if (factValueValidator != nullptr) {
        if (!factValueValidator(factValue)) {
            throw std::runtime_error("Fact value is invalid");
        }
    }
    return callback(factValue, jsonValue);
}

Operator::OperatorName Operator::getName() {
    return this->name;
}