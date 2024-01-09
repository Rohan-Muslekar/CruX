#include "server.h"

Almanac::Almanac() {

}

Almanac::Almanac(std::map<std::string, std::shared_ptr<Fact>> factMap, std::map<std::string, std::shared_ptr<Fact>> runtimeFacts, AlmanacOptions options) {
    // TODO: create a new map of facts

    for (auto& fact: factMap) {
        this->factMap[fact.first] = fact.second;
    }

    this->allowUndefinedFacts = options.allowUndefinedFacts;
    this->success = {};
    this->failure = {};
    this->ruleResults = {};

    if (runtimeFacts.size() > 0) {
        for (auto& fact: runtimeFacts) {
            this->factMap[fact.first] = fact.second;
        }
    }

    Logger::Log(INFO, "Almanac::Almanac");
}

void Almanac::addEvent(IEvent event, EventType outcome) {
    if (outcome == EventType::SUCCESS) {
        this->success.push_back(event);
    } else {
        this->failure.push_back(event);
    }
}

std::vector<IEvent> Almanac::getEvents(EventType outcome) {
    if (outcome == EventType::SUCCESS) {
        return this->success;
    } else {
        return this->failure;
    }
}

void Almanac::addResult(RuleResult& ruleResult) {
    this->ruleResults.push_back(ruleResult);
}

std::vector<RuleResult> Almanac::getResults() {
    return this->ruleResults;
}

std::shared_ptr<Fact> Almanac::getFact( std::string& factId) {
    return this->factMap[factId];
}

void Almanac::addRuntimeFact(std::string& factId, ValueType value) {
    _addConstantFact(std::make_shared<Fact>(factId, value, Fact::FactOptions { true, 1 }));
}

ValueType Almanac::factValue(std::string& factId) {
    auto fact = this->factMap[factId];
    if (fact->isConstant()) {
        return fact->getValue();
    } else {
        std::string cacheKey = fact->getCacheKey();
        if (cacheKey != "") {
            auto it = this->factResultsCache.find(cacheKey);
            if (it != this->factResultsCache.end()) {
                return it->second;
            }
        }
        return fact->calculate(*this);
    }
}

void Almanac::_addConstantFact(std::shared_ptr<Fact> fact) {
    this->factMap[fact->getId()] = fact;
}

ValueType Almanac::_setFactValue(std::shared_ptr<Fact> fact, ValueType value) {
    std::string cacheKey = fact->getCacheKey();
    if (cacheKey != "") {
        this->factResultsCache[cacheKey] = value;
    }
    return value;
}

std::vector<double> Almanac::defaultPathResolver(double value, std::string path) {
    return {};
}

