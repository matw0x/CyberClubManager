#ifndef OVERSEER_H
#define OVERSEER_H

#include <unordered_map>
#include <vector>

#include "../revenue.h"

class Overseer {
   private:
    std::unordered_map<std::string, std::optional<unsigned int>> sessionsCT_;
    std::unordered_map<unsigned int, std::string>                sessionsTC_;
    std::vector<Revenue>                                         revenues_;

    std::optional<unsigned int> getTable(const std::string& clientName) const noexcept;
    void                        freeTable(const std::string& clientName) noexcept;

   public:
    std::vector<Revenue> getRevenue() const noexcept;
    void                 prepare(unsigned int tableCount) noexcept;
    void                 createClientSession(const std::string& clientName) noexcept;
    bool                 isClientInside(const std::string& clientName) const noexcept;
    bool                 isClubWorking(Time clientArrivalTime, std::pair<Time, Time> workingHours) const noexcept;
    std::string          whoSitting(unsigned int tableNumber) const noexcept;
    void                 putClient(const std::string& clientName, unsigned int tableNumber) noexcept;
    bool                 anyTablesFree() const noexcept;
};

#endif