#ifndef REVENUE_H
#define REVENUE_H

#include "time/time.h"

struct Revenue {
    unsigned int cost{};
    Time         spentTime{};
};

#endif