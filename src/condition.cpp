#include "server.h"

Condition::Condition(std::map<std::string, std::string>& properties) {
    if (properties.empty()) throw std::runtime_error("Condition: constructor options required");

    conditionType = getConditionType(properties);

    if (conditionType == ConditionType::BOOLEAN) {
        setBooleanOperator(properties);
    } else {
        setNonBooleanCondition(properties);
    }
}

std::vector<Condition>& Condition::getSubConditions() {
    return subConditions;
}

ConditionType Condition::getConditionType(std::map<std::string, std::string>& properties) {
    if (properties.find("operator") != properties.end()) {
        return ConditionType::BOOLEAN;
    }
    return ConditionType::NON_BOOLEAN;
}

void Condition::setBooleanOperator(std::map<std::string, std::string>& properties) {
    // if (properties.find("operator") == properties.end()) {
    //     throw std::runtime_error("Condition: boolean operator required");
    // }

    // booleanOperator = properties["operator"];

    // if (properties.find("priority") != properties.end()) {
    //     priority = std::stoi(properties["priority"]);
    // }

    // if (properties.find("conditions") != properties.end()) {
    //     parseSubConditions(properties["conditions"]);
    // }
}

void Condition::parseSubConditions(std::string& subConditionsStr) {
    // std::vector<std::string> subConditionsJson = split(subConditionsStr, "&&");

    // for (auto& subConditionJson : subConditionsJson) {
    //     std::map<std::string, std::string> subConditionProperties = jsonToMap(subConditionJson);
    //     subConditions.push_back(Condition(subConditionProperties));
    // }
}

void Condition::setNonBooleanCondition(std::map<std::string, std::string>& properties) {
    // if (properties.find("fact") == properties.end()) {
    //     throw std::runtime_error("Condition: fact required");
    // }

    // fact = properties["fact"];

    // if (properties.find("operator") == properties.end()) {
    //     throw std::runtime_error("Condition: operator required");
    // }

    // operatorName = properties["operator"];

    // if (properties.find("value") == properties.end()) {
    //     throw std::runtime_error("Condition: value required");
    // }

    // value = std::stod(properties["value"]);

    // if (properties.find("priority") != properties.end()) {
    //     priority = std::stoi(properties["priority"]);
    // }
}

bool Condition::evaluate(Almanac& almanac) {
    // if (conditionType == ConditionType::BOOLEAN) {
    //     return evaluateBoolean(almanac);
    // } else {
    //     return evaluateNonBoolean(almanac);
    // }
    return true;
}

double Condition::getValue(Almanac& almanac) {
    // if (conditionType == ConditionType::BOOLEAN) {
    //     throw std::runtime_error("Condition: getValue is not supported for boolean conditions");
    // }

    // return almanac.factValue(fact);
    return 0;
}

void Condition::setFactResult(bool factResult) {
    // this->factResult = factResult;
}

std::string& Condition::getBooleanOperator(Condition& condition) {
    // return condition.booleanOperator;
}

Condition::BooleanOperator Condition::getBooleanOperator() {
    return booleanOperator;
}

bool Condition::isBooleanOperator() {
    return booleanOperator == BooleanOperator::ALL || booleanOperator == BooleanOperator::ANY || booleanOperator == BooleanOperator::NOT;
}

int Condition::getPriority() {
    // return priority;
    return 0;
}

void Condition::setResult(bool result) {
    // this->result = result;
}