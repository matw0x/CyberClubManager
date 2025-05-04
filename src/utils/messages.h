#ifndef MESSAGES_H
#define MESSAGES_H

#include <format>
#include <string>
#include <string_view>

namespace ValidatorMessages {
inline static constexpr const char* FILE_NOT_FOUND    = "File does not exist";
inline static constexpr const char* INVALID_EXTENSION = "Invalid file extension";
inline static constexpr const char* NO_EXTENSION      = "File does not have an extension";

static inline std::string getUsageMessage(std::string_view executableName, std::string_view fileExtension) {
    return std::format("Usage: {} input{}", executableName, fileExtension);
}
}  // namespace ValidatorMessages

namespace ParserMessages {
inline static constexpr const char* BAD_LINE       = "Bad line =";
inline static constexpr const char* NOT_NUMBER     = "This is not number.";
inline static constexpr const char* INVALID_FORMAT = "Invalid format.";
inline static constexpr const char* OUT_OF_RANGE   = "The number is out of range.";
inline static constexpr const char* EMPTY_LINE     = "Empty line.";
inline static constexpr const char* NO_INPUT_DATA  = "This is not input data.";
}  // namespace ParserMessages

namespace EventMessages {
inline static constexpr const char* YouShallNotPass  = "YouShallNotPass";
inline static constexpr const char* NotOpenYet       = "NotOpenYet";
inline static constexpr const char* PlaceIsBusy      = "PlaceIsBusy";
inline static constexpr const char* ClientUnknown    = "ClientUnknown";
inline static constexpr const char* ICanWaitNoLonger = "ICanWaitNoLonger!";
}  // namespace EventMessages

#endif