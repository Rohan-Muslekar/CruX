#include "server.h"

Fact::Fact(std::string& id, double value, FactOptions options) {
    this->id = id;
    this->value = value;
    this->type = CONSTANT;
}

bool Fact::isConstant()  {
    return this->type == CONSTANT;
}

bool Fact::isDynamic()  {
    return this->type == DYNAMIC;
}

double Fact::calculate( std::map<std::string, std::string>& params,  Almanac& almanac)  {
    if (this->type == CONSTANT) {
        return this->value;
    } else {
        return this->calculationMethod(params, almanac);
    }
}

std::string Fact::hashFromObject( std::map<std::string, std::string>& obj) {
    std::string hash = "";

    for (auto& [key, value] : obj) {
        hash += key + ":" + value + ";";
    }

    return hash;
}

std::map<std::string, std::string> Fact::defaultCacheKeys( std::map<std::string, std::string>& params)  {
    if (this->type == CONSTANT) {
        return {};
    } else {
        return this->defaultCacheKeysImpl(params);
    }
}

std::string Fact::getCacheKey( std::map<std::string, std::string>& params)  {
    std::map<std::string, std::string> cacheKeys = this->defaultCacheKeys(params);

    return Fact::hashFromObject(cacheKeys);
}

std::string Fact::getId() {
    return this->id;
}

std::string Fact::getType()  {
    if (this->type == CONSTANT) {
        return "CONSTANT";
    } else {
        return "DYNAMIC";
    }
}

double Fact::getValue() {
    return this->value;
}

std::map<std::string, std::string> Fact::defaultCacheKeysImpl( std::map<std::string, std::string>& params)  {
    return {};
}

