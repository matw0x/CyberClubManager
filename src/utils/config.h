#ifndef CONFIG_H
#define CONFIG_H

#include <utility>
#include <vector>

#include "event.h"
#include "revenue.h"

struct IConfig {
    unsigned int          tableCount;
    std::pair<Time, Time> workingHours;
    unsigned int          hourCost;
    std::vector<Event>    events;

    IConfig()                          = default;
    IConfig(const IConfig&)            = default;
    IConfig(IConfig&&)                 = default;
    IConfig& operator=(const IConfig&) = default;
    IConfig& operator=(IConfig&&)      = default;
    ~IConfig()                         = default;
};

struct OConfig {
    Time                 begin;
    std::vector<Event>   events;
    Time                 end;
    std::vector<Revenue> revenues;

    OConfig()                          = default;
    OConfig(const OConfig&)            = default;
    OConfig(OConfig&&)                 = default;
    OConfig& operator=(const OConfig&) = default;
    OConfig& operator=(OConfig&&)      = default;
    ~OConfig()                         = default;
};

#endif