#ifndef REVENUE_H
#define REVENUE_H

#include "time.h"

struct Revenue {
    inline static unsigned int id = 1;
    unsigned int               cost;
    Time                       spentTime;
};

#endif