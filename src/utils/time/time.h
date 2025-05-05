#include <format>
#include <stdexcept>
#include <string>

#include "../messages.h"

#ifndef TIME_H
#define TIME_H

class Time {
   private:
    using time_t = unsigned int;
    time_t minutes_;

   public:
    inline static constexpr size_t NORMAL_STRING_TIME_SIZE = 5;
    Time();
    explicit Time(time_t minutes);
    time_t      getMinutes() const noexcept;
    static Time parse(const std::string& timeString);
    std::string format() const;
    Time        operator-(const Time& other) const noexcept;
    Time        operator+(const Time& other) const noexcept;
    friend auto operator<=>(const Time&, const Time&) = default;
};

#endif