#include "server.h"

int main(int argc, char** argv) {
    Logger::Log(INFO, "Testing project!");
    std::vector<Condition> conditions;
    Condition condition = Condition (
        "number_of_tests",
        Operator::OperatorName::EQUAL,
        10,
        1
    );
    conditions.push_back(condition);
    Rule::RuleArg arg = {
        .conditionName = "test",
        .booleanOperator = Condition::BooleanOperator::ALL,
        .conditions = conditions,
        .event = IEvent(),
        .priority = 1,
        .onSuccess = [](){},
        .onFailure = [](){}
    };

    Rule rule = Rule(arg);
    
    std::map<std::string, std::shared_ptr<Fact>> facts;
    std::string factId = "number_of_tests";
    std::shared_ptr<Fact> fact = std::make_shared<Fact>(Fact {
        factId,
        11
    });

    facts[factId] = fact;

    std::vector<Rule> rules;
    rules.push_back(rule);

    Engine engine = Engine(rules, facts, false);

    IRunReturn runReturn = engine.run(facts);

    if (runReturn.successResults.size() == 1) {
        Logger::Log(INFO, "Test passed!");
        for (auto& result: runReturn.successResults) {
            std::cout << result.getResult() << std::endl;
        }
    } else {
        Logger::Log(ERROR, "Test failed!");
    }

    return 0;
}