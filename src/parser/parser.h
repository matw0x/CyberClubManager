#ifndef PARSER_H
#define PARSER_H

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

#include "../utils/config.h"
#include "../validator/validator.h"

class Parser {
   public:
    Parser() = default;
    IConfig parseInputConfig(const std::filesystem::path& inputFile, const Validator& validator) const;

   private:
    unsigned int          parsePositiveNumber(std::ifstream& inputFile, const Validator& validator) const;
    std::pair<Time, Time> parseWorkingHours(std::ifstream& inputFile, const Validator& validator) const;
    std::vector<Event>    parseEvents(std::ifstream& inputFile, const Validator& validator) const;
};

#endif