#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#include "../utils/config.h"
#include "../utils/exception.h"
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
    void                  validateEmptyLine(std::string_view line) const;
    unsigned int          validatePositiveNumber(std::string_view numberLine) const;
    std::pair<Time, Time> validateWorkingHours(std::string_view workingHoursLine) const;
    Event                 validateIEvent(std::string_view eventLine) const;
    void                  validateTimeFormatSize(std::string_view maybeTime, std::string_view exceptionPhrase) const;
    EventType             validateIEventType(std::string_view maybeIEventType, std::string_view exceptionPhrase) const;
    std::string validateClientName(const std::string& maybeClientName, std::string_view exceptionPhrase) const;
    std::optional<unsigned int> validateTableNumber(std::string_view maybeTableNumber, EventType eventType,
                                                    std::string_view exceptionPhrase) const;

   public:
    Validator() = default;
    void validateArgsCmd(int argc, const char* const argv[]) const;
};

#endif