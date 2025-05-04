#include "overseer.h"

std::vector<Revenue> Overseer::getRevenue() const noexcept { return revenues_; }

void Overseer::prepare(unsigned int tableCount) noexcept { revenues_.resize(tableCount); }

bool Overseer::isClientInside(const std::string& clientName) const noexcept { return sessions_.contains(clientName); }

bool Overseer::isClubWorking(Time clientArrivalTime, std::pair<Time, Time> workingHours) const noexcept {
    return workingHours.first <= clientArrivalTime && clientArrivalTime < workingHours.second;
}