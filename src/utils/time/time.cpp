#include "time.h"

#include "../exception.h"

Time::Time() : minutes_{} {}

Time::Time(time_t minutes) : minutes_(minutes) {}

Time Time::parse(const std::string& timeString) {
    time_t hours   = 0;
    time_t minutes = 0;

    if (sscanf(timeString.c_str(), "%u:%u", &hours, &minutes) == 2 && hours < 24 && minutes < 60) {
        return Time(hours * 60 + minutes);
    }

    throwRuntimeError();
}

Time Time::operator-(const Time& other) const noexcept {
    if (minutes_ >= other.minutes_) {
        return Time(minutes_ - other.minutes_);
    }

    return Time((24 * 60 - other.minutes_) + minutes_);
}

Time Time::operator+(const Time& other) const noexcept { return Time(minutes_ + other.minutes_); }

std::string Time::format() const {
    time_t hours   = minutes_ / 60;
    time_t minutes = minutes_ % 60;

    return std::format("{:02d}:{:02d}", hours, minutes);
}

unsigned int Time::getMinutes() const noexcept { return minutes_; }