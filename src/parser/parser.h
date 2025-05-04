#ifndef PARSER_H
#define PARSER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "../utils/config.h"
#include "../validator/validator.h"

class Parser {
   public:
    IConfig parseInputConfig(const std::filesystem::path& inputFile, Validator& validator) const;

   private:
    unsigned int          parsePositiveNumber(std::ifstream& inputFile, const Validator& validator) const;
    std::pair<Time, Time> parseWorkingHours(std::ifstream& inputFile, const Validator& validator) const;
    std::vector<Event>    parseEvents(std::ifstream& inputFile, Validator& validator) const;
};

#endif