#include "parser.h"

IConfig Parser::parseInputConfig(const std::filesystem::path& inputPath, const Validator& validator) const {
    std::ifstream inputFile(inputPath, std::ios::in);
    IConfig       inputConfig;

    inputConfig.tableCount   = parsePositiveNumber(inputFile, validator);
    inputConfig.workingHours = parseWorkingHours(inputFile, validator);
    inputConfig.hourCost     = parsePositiveNumber(inputFile, validator);
    inputConfig.events       = parseEvents(inputFile, validator);

    return inputConfig;
}

unsigned int Parser::parsePositiveNumber(std::ifstream& inputFile, const Validator& validator) const {
    std::string line;
    std::getline(inputFile, line);

    return validator.validatePositiveNumber(line);
}

std::pair<Time, Time> Parser::parseWorkingHours(std::ifstream& inputFile, const Validator& validator) const {
    std::string line;
    std::getline(inputFile, line);

    return validator.validateWorkingHours(line);
}

std::vector<Event> Parser::parseEvents(std::ifstream& inputFile, const Validator& validator) const {
    std::vector<Event> events;
    std::string        line;

    while (std::getline(inputFile, line)) {
        events.push_back(validator.validateIEvent(line));
    }

    return events;
}