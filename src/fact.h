#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <stdexcept>
#include <variant>
#include "fwd.h"

using valueType = std::variant<std::string, double, bool, int>;

class Fact {
public:

    enum FactType {
        CONSTANT,
        DYNAMIC
    };

    struct FactOptions {
        bool cache;
    };

    // Overloaded constructors
    Fact(std::string& id, double value, FactOptions options = {});

    bool isConstant();
    bool isDynamic();
    double calculate( std::map<std::string, std::string>& params,  Almanac& almanac) ;
    static std::string hashFromObject( std::map<std::string, std::string>& obj);
    std::map<std::string, std::string> defaultCacheKeys( std::map<std::string, std::string>& params) ;
    std::string getCacheKey( std::map<std::string, std::string>& params) ;

    // Function to get the fact's ID
    std::string getId();

    // Function to get the fact's options
    std::map<std::string, std::string> getOptions()  {
        return options;
    }

    // Function to get the fact's type
    std::string getType() ;

    // Function to get the fact's value
    double getValue();

private:
    std::string id;
    double value;
    std::function<double( std::map<std::string, std::string>&,  Almanac&)> calculationMethod;
    FactType type;
    std::map<std::string, std::string> options;

    std::map<std::string, std::string> defaultCacheKeysImpl( std::map<std::string, std::string>& params) ;
};