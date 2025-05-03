#include "validator.h"

#include <cctype>
#include <complex>
#include <stdexcept>
#include <string>

void Validator::validateArgsCmd(int argc, const char *const argv[]) const {
    validateArgCount(argc, argv[0]);
    validateFile(argv[1]);
}

void Validator::validateArgCount(int argc, const char *executableName) const {
    if (argc != 2) {
        throw std::invalid_argument(ValidatorMessages::getUsageMessage(executableName, FILE_EXTENSION));
    }
}

void Validator::validateFile(const std::filesystem::path &inputPath) const {
    validateFileHasExtension(inputPath);
    validateFileExtension(inputPath);
    validateFileExists(inputPath);
}

void Validator::validateFileExists(const std::filesystem::path &inputPath) const {
    if (!std::filesystem::exists(inputPath)) {
        throw std::runtime_error(ValidatorMessages::FILE_NOT_FOUND);
    }
}

void Validator::validateFileHasExtension(const std::filesystem::path &inputPath) const {
    if (!inputPath.has_extension()) {
        throw std::runtime_error(ValidatorMessages::NO_EXTENSION);
    }
}

void Validator::validateFileExtension(const std::filesystem::path &inputPath) const {
    if (inputPath.extension() != FILE_EXTENSION) {
        throw std::runtime_error(ValidatorMessages::INVALID_EXTENSION);
    }
}

unsigned int Validator::validateTableCount(const std::string &tableCountLine) const {
    const char firstSymbol = *tableCountLine.begin();
    if (!std::isdigit(firstSymbol) || firstSymbol == '0') {
        throw std::runtime_error(
            std::format("{} {} {}", ParserMessages::NOT_NUMBER, ParserMessages::BAD_LINE, tableCountLine));
    }

    for (auto it = tableCountLine.begin() + 1; it != tableCountLine.end(); ++it) {
        if (!std::isdigit(*it)) {
            throw std::runtime_error(
                std::format("{} {} {}", ParserMessages::NOT_NUMBER, ParserMessages::BAD_LINE, tableCountLine));
        }
    }

    try {
        auto result = std::stoul(tableCountLine);
        if (result > std::numeric_limits<unsigned int>::max()) {
            throw std::runtime_error(
                std::format("{} {} {}", ParserMessages::OUT_OF_RANGE, ParserMessages::BAD_LINE, tableCountLine));
        }

        return static_cast<unsigned int>(result);
    } catch (const std::exception &) {
        throw std::runtime_error(
            std::format("{} {} {}", ParserMessages::OUT_OF_RANGE, ParserMessages::BAD_LINE, tableCountLine));
    }
}

std::pair<Time, Time> Validator::validateWorkingHours(const std::string &workingHoursLine) const {
    std::istringstream stream(workingHoursLine);
    std::string        begin, end;

    stream >> begin >> end;

    if (begin.size() != Time::NORMAL_STRING_TIME_SIZE || end.size() != Time::NORMAL_STRING_TIME_SIZE) {
        throw std::invalid_argument(
            std::format("{} {} {}", ParserMessages::INVALID_FORMAT, ParserMessages::BAD_LINE, workingHoursLine));
    }

    return {Time::parse(begin), Time::parse(end)};
}