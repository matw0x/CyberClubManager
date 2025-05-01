#include "validator.h"

void Validator::validateArgsCmd(int argc, const char *const argv[]) {
    validateArgCount(argc, argv[0]);
    validateFile(argv[1]);
}

void Validator::validateArgCount(int argc, const std::string &executableName) const {
    if (argc != 2) {
        throw std::invalid_argument(getUsageMessage(executableName));
    }
}

std::string Validator::getUsageMessage(const std::string &executableName) const noexcept {
    return "Usage: " + executableName + " input" + FILE_EXTENSION;
}

void Validator::validateFile(const std::filesystem::path &inputPath) const {
    validateFileHasExtension(inputPath);
    validateFileExtension(inputPath);
    validateFileExists(inputPath);
    validateFileContent(inputPath);
}

void Validator::validateFileExists(const std::filesystem::path &inputPath) const {
    if (!std::filesystem::exists(inputPath)) {
        throw std::runtime_error(MESSAGE_FILE_NOT_FOUND);
    }
}

void Validator::validateFileHasExtension(const std::filesystem::path &inputPath) const {
    if (!inputPath.has_extension()) {
        throw std::runtime_error(MESSAGE_NO_EXTENSION);
    }
}

void Validator::validateFileExtension(const std::filesystem::path &inputPath) const {
    if (inputPath.extension() != FILE_EXTENSION) {
        throw std::runtime_error(MESSAGE_INVALID_EXTENSION);
    }
}

void Validator::validateFileContent(const std::filesystem::path &inputPath) const {
    //
}