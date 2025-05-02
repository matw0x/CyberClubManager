#ifndef CONFIG_H
#define CONFIG_H

#include <utility>
#include <vector>

#include "event.h"

struct IConfig {
    unsigned int          tableCount;
    std::pair<Time, Time> workingHours;
    unsigned int          hourCost;
    std::vector<Event>    events;
};

struct OConfig {
    Time               begin;
    std::vector<Event> events;
    Time               end;
    // класс для выручки
};

#endif