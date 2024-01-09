// Rule.h

#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <memory>

#include "almanac.h"
#include "condition.h"
#include "rule-result.h"
#include "default-operators.h"
#include "json.h"
#include "json.fwd.h"
#include "engine.h"
#include "types.dto.h"
#include "fwd.h"

class Rule {
public:
    Rule(std::string jsonString);

    void setPriority(int priority);
    void setName(std::string& name);
    void setConditions(std::vector<Condition>& conditions);

    int getPriority();
    std::string& getName();
    std::vector<Condition>& getConditions();

    void setEngine(Engine *engine);

    RuleResult evaluate(Almanac& almanac);

private:
    int priority;
    std::string name;
    std::vector<Condition> conditions;
    IEvent ruleEvent;
    std::shared_ptr<Almanac> almanac;
    Engine* engine;

    
    std::map<int, std::vector<Condition>> prioritizeConditions(std::vector<Condition>& conditions);
    bool evaluateCondition(Condition& condition);
    bool evaluateConditions(std::vector<Condition>& conditions, std::string& method);
    bool prioritizeAndRun(std::vector<Condition>& conditions, std::string& method);

    bool _any(std::vector<Condition>& conditions);
    bool _all(std::vector<Condition>& conditions);
    bool _not(Condition& condition);

    RuleResult processResult(bool result, RuleResult& ruleResult);
};
