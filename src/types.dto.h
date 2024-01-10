#pragma once
#include <string>
#include <vector>
#include <variant>
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

using ValueType = std::variant<std::string, double, bool, int>;

using Callable_t = std::function<bool(ValueType, ValueType)>;
using CallableFactValue = std::function<bool(ValueType)>;

