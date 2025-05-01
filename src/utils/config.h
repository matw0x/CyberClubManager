#ifndef CONFIG_H
#define CONFIG_H

#include <utility>
#include <vector>

#include "event.h"
#include "time.h"

struct IConfig {
    unsigned int          tableCount;
    std::pair<Time, Time> workingHours;
    unsigned int          hourCost;
};

struct OConfig {
    std::pair<Time, Time> workingHours;
    std::vector<Event>    events;
};

#endif