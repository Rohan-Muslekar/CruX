#include "server.h"

Rule::Rule(std::string jsonString) {

}

void Rule::setPriority(int priority) {
    this->priority = priority;
}

void Rule::setName(std::string& name) {
    this->name = name;
}

void Rule::setConditions(std::vector<Condition>& conditions) {
    this->conditions = conditions;
}

int Rule::getPriority() {
    return priority;
}

std::string& Rule::getName() {
    return name;
}

std::vector<Condition>& Rule::getConditions() {
    return conditions;
}

void Rule::setEngine(Engine *engine) {
    this->engine = engine;
}

RuleResult Rule::evaluate(Almanac& almanac) {
    // this->almanac = std::make_shared<Almanac>(almanac);
    // RuleResult ruleResult(conditions, ruleEvent, priority, name);

    // if (conditions.empty()) {
    //     throw std::runtime_error("Rule: evaluate requires conditions");
    // }

    // std::map<int, std::vector<Condition>> prioritizedConditions = prioritizeConditions(conditions);

    // for (auto& [priority, conditions] : prioritizedConditions) {
    //     std::string method = conditions[0].getOperator();
    //     bool result = prioritizeAndRun(conditions, method);

    //     ruleResult = processResult(result, ruleResult);
    // }

    // return ruleResult;
}

std::map<int, std::vector<Condition>> Rule::prioritizeConditions(std::vector<Condition>& conditions) {
    std::map<int, std::vector<Condition>> prioritizedConditions;

    // for (auto& condition : conditions) {
    //     int priority = condition.getPriority();

    //     if (prioritizedConditions.find(priority) == prioritizedConditions.end()) {
    //         prioritizedConditions[priority] = std::vector<Condition>();
    //     }

    //     prioritizedConditions[priority].push_back(condition);
    // }

    return prioritizedConditions;
}

bool Rule::evaluateCondition(Condition& condition) {
    // std::string factId = condition.getFact();
    // std::string operator_ = condition.getOperator();
    // std::string value = condition.getValue();

    // double factValue = almanac->factValue(factId);

    return true;
}

bool Rule::evaluateConditions(std::vector<Condition>& conditions, std::string& method) {
    // for (auto& condition : conditions) {
    //     bool result = evaluateCondition(condition);

    //     if (method == "any" && result) {
    //         return true;
    //     } else if (method == "all" && !result) {
    //         return false;
    //     }
    // }

    return method == "all";
}

bool Rule::prioritizeAndRun(std::vector<Condition>& conditions, std::string& method) {
    // std::sort(conditions.begin(), conditions.end(), [](const Condition& a, const Condition& b) {
    //     return a.getPriority() < b.getPriority();
    // });

    return evaluateConditions(conditions, method);
}

bool Rule::_any(std::vector<Condition>& conditions) {
    return true;
}

bool Rule::_all(std::vector<Condition>& conditions) {
    return true;
}

bool Rule::_not(Condition& condition) {
    return !evaluateCondition(condition);
}

RuleResult Rule::processResult(bool result, RuleResult& ruleResult) {
    // if (result) {
    //     ruleResult.addResult(ruleResult.getEvent());
    // }

    return ruleResult;
}
