#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include <memory>
#include <limits>

#include "fact.h"
#include "rules.h"
#include "rule-result.h"
#include "types.dto.h"
#include "fwd.h"

struct AlmanacOptions {
    bool allowUndefinedFacts = false;
};


class Almanac {
private:
    std::map<std::string, std::shared_ptr<Fact>> factMap;
    std::map<std::string, double> factResultsCache;
    bool allowUndefinedFacts;
    std::function<std::vector<double>(double, std::string)> pathResolver;
    std::vector<IEvent> success;
    std::vector<IEvent> failure;
    std::vector<RuleResult> ruleResults;

public:
    enum EventType {
        SUCCESS,
        FAILURE
    };
    Almanac();
    Almanac(std::map<std::string, std::shared_ptr<Fact>> factMap, std::map<std::string, std::shared_ptr<Fact>> runtimeFacts = {}, AlmanacOptions options = {});

    void addEvent(IEvent event, EventType outcome);

    std::vector<IEvent> getEvents(EventType outcome = EventType::SUCCESS);

    void addResult(RuleResult& ruleResult);

    std::vector<RuleResult> getResults();

    std::shared_ptr<Fact> getFact( std::string& factId) ;

    void addRuntimeFact( std::string& factId, double value);

    double factValue( std::string& factId,  std::map<std::string, std::string>& params, std::string& path);

private:
    void _addConstantFact(std::shared_ptr<Fact> fact);

    double _setFactValue(std::shared_ptr<Fact> fact, std::map<std::string, std::string>& params, double value);

    static std::vector<double> defaultPathResolver(double value, std::string path);
};
