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

void Almanac::addRuntimeFact( std::string& factId, double value) {
    
}

double Almanac::factValue( std::string& factId,  std::map<std::string, std::string>& params, std::string& path) {
    return 0;
}

void Almanac::_addConstantFact(std::shared_ptr<Fact> fact) {
    this->factMap[fact->getId()] = fact;
}

double Almanac::_setFactValue(std::shared_ptr<Fact> fact, std::map<std::string, std::string>& params, double value) {
    return 0;
}

std::vector<double> Almanac::defaultPathResolver(double value, std::string path) {
    return {};
}

