#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "../utils/config.h"
#include "../utils/messages.h"

class Validator {
    friend class Parser;

   private:
    inline static constexpr const char* FILE_EXTENSION = ".txt";

    void                  validateArgCount(int argc, const char* executableName) const;
    void                  validateFile(const std::filesystem::path& inputPath) const;
    void                  validateFileHasExtension(const std::filesystem::path& inputPath) const;
    void                  validateFileExtension(const std::filesystem::path& inputPath) const;
    void                  validateFileExists(const std::filesystem::path& inputPath) const;
    unsigned int          validateTableCount(const std::string& tableCountLine) const;
    std::pair<Time, Time> validateWorkingHours(const std::string& workingHoursLine) const;

   public:
    Validator() = default;
    void validateArgsCmd(int argc, const char* const argv[]) const;
};

#endif