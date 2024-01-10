#include "server.h"

RuleResult::RuleResult(std::vector<Condition>& conditions, IEvent& event, int priority, std::string& name) {
    this->conditions = conditions;
    this->event = event;
    this->priority = priority;
    this->name = name;
}

void RuleResult::setResult(bool result) {
    this->result = result;
}

bool RuleResult::getResult() {
    return result;
}

std::vector<Condition> RuleResult::getConditions() {
    return conditions;
}

IEvent RuleResult::getEvent() {
    return event;
}