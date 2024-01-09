#pragma once// engine.h

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <memory>

#include "rules.h"
#include "operator.h"
#include "almanac.h"
#include "fact.h"
#include "fwd.h"
#include "types.dto.h"

class Engine {
public:

    enum struct Status {
        READY,
        RUNNING,
        FINISHED
    };


    Engine(std::vector<Rule>& rules, std::map<std::string, std::shared_ptr<Fact>>& facts, bool allowUndefinedFacts = false);

    void addRule(Rule& rule);
    void updateRule(Rule& rule);

    void addOperator(Operator& op);
    bool removeOperator(Operator::OperatorName opName);

    void addFact(std::shared_ptr<Fact>& fact);
    bool removeFact(std::string& factId);

    std::shared_ptr<Fact> getFact(std::string& factId);

    void prioritizeRules();
    void stop();
    void evaluateRules(std::vector<Rule>& ruleArray, Almanac& almanac);

    IRunReturn run(std::map<std::string, std::shared_ptr<Fact>>& runtimeFacts);

private:
    std::vector<Rule> rules;
    std::map<std::string, std::shared_ptr<Fact>> facts;
    std::map<Operator::OperatorName, Operator> operators;
    Status status;
    bool allowUndefinedFacts;
    std::map<int, std::vector<Rule>> prioritizedRules;
};