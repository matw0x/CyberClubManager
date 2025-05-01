#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <filesystem>
#include <iostream>
#include <string>
#include <string_view>

class Validator {
   private:
    inline static const std::string FILE_EXTENSION            = ".txt";
    inline static const std::string MESSAGE_FILE_NOT_FOUND    = "File does not exist";
    inline static const std::string MESSAGE_INVALID_EXTENSION = "Invalid file extension. Expected: " + FILE_EXTENSION;
    inline static const std::string MESSAGE_NO_EXTENSION      = "File does not have an extension";

    void        validateArgCount(int argc, const std::string& executableName) const;
    std::string getUsageMessage(const std::string& executableName) const noexcept;
    void        validateFile(const std::filesystem::path& inputPath) const;
    void        validateFileHasExtension(const std::filesystem::path& inputPath) const;
    void        validateFileExtension(const std::filesystem::path& inputPath) const;
    void        validateFileExists(const std::filesystem::path& inputPath) const;
    void        validateFileContent(const std::filesystem::path& inputPath) const;

   public:
    Validator() = default;

    void validateArgsCmd(int argc, const char* const argv[]);
};

#endif