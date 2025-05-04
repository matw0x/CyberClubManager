#ifndef OVERSEER_H
#define OVERSEER_H

#include <unordered_map>
#include <vector>

#include "../revenue.h"

class Overseer {
   private:
    std::unordered_map<std::string, std::optional<unsigned int>> sessions_;
    std::vector<Revenue>                                         revenues_;

   public:
    std::vector<Revenue> getRevenue() const noexcept;
    void                 prepare(unsigned int tableCount) noexcept;
    bool                 isClientInside(const std::string& clientName) const noexcept;
    bool                 isClubWorking(Time clientArrivalTime, std::pair<Time, Time> workingHours) const noexcept;
};

#endif