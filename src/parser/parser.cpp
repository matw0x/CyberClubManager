#include "parser.h"

IConfig Parser::parseInputConfig(const std::filesystem::path& inputPath, const Validator& validator) const {
    std::ifstream inputFile(inputPath, std::ios::in);
    IConfig       inputConfig;

    inputConfig.tableCount   = parseTableCount(inputFile, validator);
    inputConfig.workingHours = parseWorkingHours(inputFile, validator);
    inputConfig.hourCost     = parseHourCost(inputFile, validator);
    inputConfig.events       = parseEvents(inputFile, validator);

    return inputConfig;
}

unsigned int Parser::parseTableCount(std::ifstream& inputFile, const Validator& validator) const {
    std::string line;
    std::getline(inputFile, line);

    return validator.validateTableCount(line);
}

std::pair<Time, Time> Parser::parseWorkingHours(std::ifstream& inputFile, const Validator& validator) const {
    return {};
}

unsigned int Parser::parseHourCost(std::ifstream& inputFile, const Validator& validator) const { return {}; }

std::vector<Event> Parser::parseEvents(std::ifstream& inputFile, const Validator& validator) const { return {}; }