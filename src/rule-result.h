#pragma once

#include <vector>
#include <string>

#include "condition.h"
#include "rules.h"
#include "types.dto.h"
#include "fwd.h"

class RuleResult {
public:
    RuleResult(std::vector<Condition>& conditions, IEvent& event, int priority, std::string& name);

    void setResult(bool result);
    bool getResult();
    std::string getBooleanOperator();
    std::vector<Condition> getConditions();
    IEvent getEvent();

private:
    std::vector<Condition> conditions;
    std::string booleanOperator;
    int priority;
    std::string name;
    bool result;
    IEvent event;
};

