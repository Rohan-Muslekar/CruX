#include "server.h"

Fact::Fact(std::string& id, ValueType value, FactOptions options) {
    this->id = id;
    this->value = value;
    this->type = CONSTANT;
    this->options = options;
    this->priority = options.priority;
}

bool Fact::isConstant()  {
    return this->type == CONSTANT;
}

bool Fact::isDynamic()  {
    return this->type == DYNAMIC;
}

ValueType Fact::calculate(Almanac& almanac)  {
    return this->value;
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

ValueType Fact::getValue() {
    return this->value;
}

std::string Fact::hash(std::string& id) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(id));
}

std::string Fact::getCacheKey() {
    if (this->options.cache) {
        std::string cacheKey = Fact::hash(this->id);
        return cacheKey;
    } else {
        Logger::Log(ALERT, "Fact::getCacheKey: called on uncached fact");
        return "";
    }
}