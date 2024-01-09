#include "server.h"

Engine::Engine(std::vector<Rule>& rules, std::map<std::string, std::shared_ptr<Fact>>& facts, bool allowUndefinedFacts)  {
    this->rules = rules;
    this->facts = facts;
    this->status = Engine::Status::READY;
    this->allowUndefinedFacts = allowUndefinedFacts;
    Logger::Log(INFO, "Engine::Engine: Engine created");
}

void Engine::addRule(Rule& rule) {
    rule.setEngine(this);
    rules.push_back(rule);
    prioritizeRules(); // You may need to call prioritizeRules after adding a rule
    Logger::Log(INFO, "Engine::addRule: Rule added");
}

void Engine::updateRule(Rule& rule) {
    // Find the rule in the rules vector and update it
    for (auto& r: rules) {
        if (r.getName() == rule.getName()) {
            r = rule;
            break;
        }
    }
    Logger::Log(INFO, "Engine::updateRule: Rule updated");
}

void Engine::addOperator(Operator& op) {
    operators[op.getName()] = op;
    Logger::Log(INFO, "Engine::addOperator: Operator added");
}

bool Engine::removeOperator(Operator::OperatorName opName) {
    // Implementation to remove an operator
    operators.erase(opName);
    Logger::Log(INFO, "Engine::removeOperator: Operator removed");
    return true; // Return true if the operator was removed, false otherwise
}

void Engine::addFact(std::shared_ptr<Fact>& fact) {
    facts[fact->getId()] = fact;
    Logger::Log(INFO, "Engine::addFact: Fact added");
}

bool Engine::removeFact(std::string& factId) {
    // Implementation to remove a fact
    facts.erase(factId);
    Logger::Log(INFO, "Engine::removeFact: Fact removed");
    return true; // Return true if the fact was removed, false otherwise
}

std::shared_ptr<Fact> Engine::getFact(std::string& factId) {
    // Implementation to get a fact by factId
    auto it = facts.find(factId);
    if (it != facts.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void Engine::prioritizeRules() {
    for (auto& rule: rules) {
        int priority = rule.getPriority();
        if (prioritizedRules.find(priority) == prioritizedRules.end()) {
            prioritizedRules[priority] = {};
        }
        prioritizedRules[priority].push_back(rule);
    }

    // Sort the rules in each priority
    for (auto& ruleArray: prioritizedRules) {
        std::sort(ruleArray.second.begin(), ruleArray.second.end(), [](Rule& a, Rule& b) {
            return a.getPriority() < b.getPriority();
        });
    }
}

void Engine::stop() {
    status = Engine::Status::FINISHED;
    Logger::Log(INFO, "Engine::stop");
}

void Engine::evaluateRules(std::vector<Rule>& ruleArray, Almanac& almanac) {
    if (status == Engine::Status::FINISHED) {
        Logger::Log(INFO, "Engine::evaluateRules skipping remaining rules: Engine is finished");
        return;
    }
    for (auto& rule: ruleArray) {
        RuleResult ruleResult = rule.evaluate(almanac);
        almanac.addResult(ruleResult);
        if (ruleResult.getResult()) {
            almanac.addEvent(ruleResult.getEvent(), Almanac::EventType::SUCCESS);
        } else {
            almanac.addEvent(ruleResult.getEvent(), Almanac::EventType::FAILURE);
        }
    }
}

IRunReturn Engine::run(std::map<std::string, std::shared_ptr<Fact>>& runtimeFacts) {
    this->status = Engine::Status::RUNNING;

    Almanac almanac(facts, runtimeFacts, AlmanacOptions { allowUndefinedFacts });

    prioritizeRules();

    for (auto& ruleArray: this->prioritizedRules) {
        evaluateRules(ruleArray.second, almanac);
    }

    status = Engine::Status::FINISHED;
    std::vector<RuleResult> ruleResult = almanac.getResults();
    IRunReturn runReturn = { almanac };
    for (auto& ruleResult: ruleResult) {
        if (ruleResult.getResult()) {
            runReturn.successResults.emplace_back(ruleResult);
        } else {
            runReturn.failureResults.emplace_back(ruleResult);
        }
    }
    
    runReturn.successEvents = almanac.getEvents(Almanac::EventType::SUCCESS);
    runReturn.failureEvents = almanac.getEvents(Almanac::EventType::FAILURE);

    return runReturn;
}