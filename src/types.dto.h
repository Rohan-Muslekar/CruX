#pragma once
#include <string>
#include <vector>

#include "fwd.h"

struct IEvent {
    std::string name;
    std::string message;
};

struct IRunReturn {
    Almanac& almanac;
    std::vector<RuleResult> successResults;
    std::vector<RuleResult> failureResults;
    std::vector<IEvent> successEvents;
    std::vector<IEvent> failureEvents;

    IRunReturn(Almanac& almanac)
        : almanac(almanac), successResults(), failureResults(), successEvents(), failureEvents() {
    }
};