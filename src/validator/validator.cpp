#include "validator.h"

#include <cctype>
#include <optional>

void Validator::validateArgsCmd(int argc, const char *const argv[]) const {
    validateArgCount(argc, argv[0]);
    validateFile(argv[1]);
}

void Validator::validateArgCount(int argc, const char *executableName) const {
    if (argc != 2) {
        throwInvalidArgument(ValidatorMessages::getUsageMessage(executableName, FILE_EXTENSION));
    }
}

void Validator::validateFile(const std::filesystem::path &inputPath) const {
    validateFileHasExtension(inputPath);
    validateFileExtension(inputPath);
    validateFileExists(inputPath);
}

void Validator::validateFileExists(const std::filesystem::path &inputPath) const {
    if (!std::filesystem::exists(inputPath)) {
        throwRuntimeError(ValidatorMessages::FILE_NOT_FOUND);
    }
}

void Validator::validateFileHasExtension(const std::filesystem::path &inputPath) const {
    if (!inputPath.has_extension()) {
        throwRuntimeError(ValidatorMessages::NO_EXTENSION);
    }
}

void Validator::validateFileExtension(const std::filesystem::path &inputPath) const {
    if (inputPath.extension() != FILE_EXTENSION) {
        throwRuntimeError(ValidatorMessages::INVALID_EXTENSION);
    }
}

unsigned int Validator::validatePositiveNumber(std::string_view numberLine) const {
    validateEmptyLine(numberLine);

    const char firstSymbol = *numberLine.begin();
    if (!std::isdigit(firstSymbol) || firstSymbol == '0') {
        throwRuntimeError(std::format("{} {} {}", ParserMessages::NOT_NUMBER, ParserMessages::BAD_LINE, numberLine));
    }

    for (auto it = numberLine.begin() + 1; it != numberLine.end(); ++it) {
        if (!std::isdigit(*it)) {
            throwRuntimeError(
                std::format("{} {} {}", ParserMessages::NOT_NUMBER, ParserMessages::BAD_LINE, numberLine));
        }
    }

    try {
        auto result = std::stoul(numberLine.data());
        if (result > std::numeric_limits<unsigned int>::max()) {
            throwRuntimeError(
                std::format("{} {} {}", ParserMessages::OUT_OF_RANGE, ParserMessages::BAD_LINE, numberLine));
        }

        return static_cast<unsigned int>(result);
    } catch (const std::exception &) {
        throwRuntimeError(std::format("{} {} {}", ParserMessages::OUT_OF_RANGE, ParserMessages::BAD_LINE, numberLine));
    }
}

void Validator::validateEmptyLine(std::string_view line) const {
    if (line.empty()) {
        throwRuntimeError(std::format("{}", ParserMessages::EMPTY_LINE));
    }
}

void Validator::validateTimeFormatSize(std::string_view maybeTime, std::string_view exceptionPhrase) const {
    if (maybeTime.size() != Time::NORMAL_STRING_TIME_SIZE) {
        throwInvalidArgument(
            std::format("{} {} {}", ParserMessages::INVALID_FORMAT, ParserMessages::BAD_LINE, exceptionPhrase));
    }
}

std::pair<Time, Time> Validator::validateWorkingHours(std::string_view workingHoursLine) const {
    validateEmptyLine(workingHoursLine);

    std::istringstream stream(workingHoursLine.data());
    std::string        begin, end;

    stream >> begin >> end;

    validateTimeFormatSize(begin, workingHoursLine);
    validateTimeFormatSize(end, workingHoursLine);

    try {
        auto open  = Time::parse(begin);
        auto close = Time::parse(end);

        if (close <= open) {
            throwRuntimeError();
        }

        return {open, close};
    } catch (const std::exception &) {
        throwInvalidArgument(
            std::format("{} {} {}", ParserMessages::INVALID_FORMAT, ParserMessages::BAD_LINE, workingHoursLine));
    }
}

EventType Validator::validateIEventType(std::string_view maybeIEventType, std::string_view exceptionPhrase) const {
    EventType eventType;

    try {
        eventType = static_cast<EventType>(validatePositiveNumber(maybeIEventType));
    } catch (const std::exception &) {
        throwRuntimeError(std::format("{} {}", ParserMessages::BAD_LINE, exceptionPhrase));
    }

    switch (eventType) {
        case EventType::INPUT_CLIENT_ARRIVED:
        case EventType::INPUT_CLIENT_SAT:
        case EventType::INPUT_CLIENT_WAITING:
        case EventType::INPUT_CLIENT_LEFT:
            return eventType;
        default:
            throwRuntimeError(
                std::format("{} {} {}", ParserMessages::NO_INPUT_DATA, ParserMessages::BAD_LINE, exceptionPhrase));
    }
}

std::string Validator::validateClientName(const std::string &maybeClientName, std::string_view exceptionPhrase) const {
    for (const char symbol : maybeClientName) {
        if (!(std::isdigit(symbol) || std::islower(symbol) || symbol == '_' || symbol == '-')) {
            throwInvalidArgument(
                std::format("{} {} {}", ParserMessages::INVALID_FORMAT, ParserMessages::BAD_LINE, exceptionPhrase));
        }
    }

    return maybeClientName;
}

std::optional<unsigned int> Validator::validateTableNumber(std::string_view maybeTableNumber, EventType eventType,
                                                           std::string_view exceptionPhrase) const {
    std::optional<unsigned int> tableNumber{};

    if (eventType == EventType::INPUT_CLIENT_SAT) {
        if (maybeTableNumber.empty()) {
            throwInvalidArgument(
                std::format("{} {} {}", ParserMessages::INVALID_FORMAT, ParserMessages::BAD_LINE, exceptionPhrase));
        }

        try {
            return validatePositiveNumber(maybeTableNumber);
        } catch (const std::exception &) {
            throwRuntimeError(
                std::format("{} {} {}", ParserMessages::INVALID_FORMAT, ParserMessages::BAD_LINE, exceptionPhrase));
        }
    }

    if (!maybeTableNumber.empty()) {
        throwInvalidArgument(
            std::format("{} {} {}", ParserMessages::INVALID_FORMAT, ParserMessages::BAD_LINE, exceptionPhrase));
    }

    return tableNumber;
}

Event Validator::validateIEvent(std::string_view eventLine) const {
    validateEmptyLine(eventLine);
    Event              event;
    std::istringstream stream(eventLine.data());
    std::string        maybeTime, maybeEventType, maybeClientName, maybeTableNum;

    stream >> maybeTime >> maybeEventType >> maybeClientName >> maybeTableNum;

    validateTimeFormatSize(maybeTime, eventLine);

    try {
        event.time = Time::parse(maybeTime);
    } catch (const std::exception &) {
        throwInvalidArgument(
            std::format("{} {} {}", ParserMessages::INVALID_FORMAT, ParserMessages::BAD_LINE, eventLine));
    }

    event.type        = validateIEventType(maybeEventType, eventLine);
    event.clientName  = validateClientName(maybeClientName, eventLine);
    event.tableNumber = validateTableNumber(maybeTableNum, event.type, eventLine);
    event.message     = {};

    return event;
}