#include "server.h"

Rule::Rule(RuleArg ruleArg) {
    this->priority = ruleArg.priority;
    this->name = ruleArg.conditionName;
    this->conditions = ruleArg.conditions;
    this->booleanOperator = ruleArg.booleanOperator;
    this->ruleEvent = ruleArg.event;
    this->engine = nullptr;
}

void Rule::setPriority(int priority) {
    if (priority < 1) {
        throw std::runtime_error("Rule: priority must be greater than 0");
    }
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
    this->almanac = std::make_shared<Almanac>(almanac);
    RuleResult ruleResult = RuleResult(conditions, ruleEvent, priority, name);
    if (booleanOperator == Condition::BooleanOperator::ALL) {
        processResult(ruleResult, _all(conditions));
    } else if (booleanOperator == Condition::BooleanOperator::ANY) {
        processResult(ruleResult, _any(conditions));
    } else if (booleanOperator == Condition::BooleanOperator::NOT) {
        processResult(ruleResult, _not(conditions));
    } else {
        throw std::runtime_error("Rule: unknown boolean operator " + booleanOperator);
    }

    return ruleResult;
}

std::map<int, std::vector<Condition>> Rule::prioritizeConditions(std::vector<Condition>& conditions) {
    std::map<int, std::vector<Condition>> prioritizedConditions;

    for (auto& condition : conditions) {
        int priority = condition.getPriority();

        if (prioritizedConditions.find(priority) == prioritizedConditions.end()) {
            prioritizedConditions[priority] = std::vector<Condition>();
        }

        prioritizedConditions[priority].push_back(condition);
    }

    for (auto& [priority, conditions] : prioritizedConditions) {
        std::sort(conditions.begin(), conditions.end(), [](Condition& a, Condition& b) {
            return a.getPriority() < b.getPriority();
        });
    }

    return prioritizedConditions;
}

bool Rule::evaluateCondition(Condition& condition) {
    if (condition.isBooleanOperator()) {
        std::vector<Condition> subConditions = condition.getSubConditions();
        Condition::BooleanOperator bop = condition.getBooleanOperator();
        if (bop == Condition::BooleanOperator::ALL) {
            return _all(subConditions);
        } else if (bop == Condition::BooleanOperator::ANY) {
            return _any(subConditions);
        } else if (bop == Condition::BooleanOperator::NOT) {
            return _not(subConditions);
        } else {
            throw std::runtime_error("Rule: unknown boolean operator " + bop);
        }
    } else {
        return condition.evaluate(*almanac);
    }
    return true;
}

bool Rule::evaluateConditions(std::vector<Condition>& conditions, Condition::BooleanOperator method) {
    bool result;
    std::vector<bool> evaluationResults = std::vector<bool>();
    if (method == Condition::BooleanOperator::ANY) {
        result = std::any_of(conditions.begin(), conditions.end(), [this](Condition& condition) {
            return evaluateCondition(condition);
        });
    } else if (method == Condition::BooleanOperator::ALL) {
        result = std::all_of(conditions.begin(), conditions.end(), [this](Condition& condition) {
            return evaluateCondition(condition);
        });
    } else if (method == Condition::BooleanOperator::NOT) {
        result = std::none_of(conditions.begin(), conditions.end(), [this](Condition& condition) {
            return evaluateCondition(condition);
        });
    } else {
        throw std::runtime_error("Rule: unknown method " + method);
    }
    return result;
}

bool Rule::prioritizeAndRun(std::vector<Condition>& conditions, Condition::BooleanOperator method) {
    
    if (conditions.size() == 1) {
        return evaluateCondition(conditions[0]);
    } else if (conditions.size() == 0) {
        Logger::Log(ALERT, "Rule: no conditions found");
        return true;
    }

    prioritizeConditions(conditions);
    return evaluateConditions(conditions, method);
}

bool Rule::_any(std::vector<Condition>& conditions) {
    return prioritizeAndRun(conditions, Condition::BooleanOperator::ANY);
}

bool Rule::_all(std::vector<Condition>& conditions) {
    return prioritizeAndRun(conditions, Condition::BooleanOperator::ALL);
}

bool Rule::_not(std::vector<Condition>& condition) {
    return prioritizeAndRun(conditions, Condition::BooleanOperator::NOT);
}

void Rule::processResult(RuleResult& ruleResult, bool result) {
    ruleResult.setResult(result);
}
