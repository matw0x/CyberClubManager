#ifndef OVERSEER_H
#define OVERSEER_H

#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

#include "../revenue.h"

class Overseer {
   private:
    std::unordered_map<std::string, std::optional<unsigned int>> sessionsCT_;
    std::unordered_map<unsigned int, std::string>                sessionsTC_;
    std::unordered_map<unsigned int, Time>                       startSessionsTC_;
    std::vector<Revenue>                                         revenues_;
    std::queue<std::string>                                      waitingQueue_;
    unsigned int                                                 costHour_;

   public:
    void                        freeSession(const std::string& clientName) noexcept;
    std::vector<unsigned int>   getOccupiedTableNumbers() const noexcept;
    void                        startCalculate(unsigned int tableNumber, Time start) noexcept;
    void                        calculateRevenue(unsigned int tableNumber, Time end) noexcept;
    void                        processRemainings(Time end) noexcept;
    void                        freeTable(const std::string& clientName) noexcept;
    std::optional<unsigned int> getTable(const std::string& clientName) const noexcept;
    std::vector<Revenue>        getRevenue() const noexcept;
    std::vector<std::string>    getRemainings() const noexcept;
    void                        prepare(unsigned int tableCount, unsigned int costHour) noexcept;
    void                        createClientSession(const std::string& clientName) noexcept;
    bool                        isClientInside(const std::string& clientName) const noexcept;
    bool        isClubWorking(Time clientArrivalTime, std::pair<Time, Time> workingHours) const noexcept;
    std::string whoSitting(unsigned int tableNumber) const noexcept;
    void        putClient(const std::string& clientName, unsigned int tableNumber) noexcept;
    bool        anyTablesFree() const noexcept;
    bool        isWaitingQueueOverflow() const noexcept;
    void        addWaitingQueue(const std::string& clientName) noexcept;
    std::string getFirstWaiter() noexcept;
    void        eraseFromClub(const std::string& clientName) noexcept;
};

#endif