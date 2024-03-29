#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <stdexcept>
#include <variant>
#include "fwd.h"
#include "types.dto.h"


class Fact {
public:

    enum FactType {
        CONSTANT,
        DYNAMIC
    };

    struct FactOptions {
        bool cache;
        int priority = 1;
    };

    // Overloaded constructors
    Fact(std::string& id, ValueType value, FactOptions options = { true, 1 });

    bool isConstant();
    bool isDynamic();
    ValueType calculate(Almanac& almanac);
    static std::string hash(std::string& id);
    std::string getCacheKey() ;

    // Function to get the fact's ID
    std::string getId();

    // Function to get the fact's options
    FactOptions getOptions()  {
        return options;
    }

    // Function to get the fact's type
    std::string getType();

    // Function to get the fact's value
    ValueType getValue();

private:
    std::string id;
    ValueType value;
    FactType type;
    FactOptions options;
    int priority;
};