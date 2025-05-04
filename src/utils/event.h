#ifndef EVENT_H
#define EVENT_H

#include <optional>
#include <string>

#include "time/time.h"

enum class EventType {
    INPUT_CLIENT_ARRIVED = 1,
    INPUT_CLIENT_SAT,
    INPUT_CLIENT_WAITING,
    INPUT_CLIENT_LEFT,

    OUTPUT_CLIENT_KICK = 11,
    OUTPUT_CLIENT_SAT,
    OUTPUT_ERROR
};

struct Event {
    Time                        time;
    EventType                   type;
    std::string                 clientNameOrMsg;
    std::optional<unsigned int> tableNumber;
};

#endif