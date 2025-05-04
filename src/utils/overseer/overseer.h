#ifndef OVERSEER_H
#define OVERSEER_H

#include <queue>
#include <unordered_map>
#include <vector>

#include "../revenue.h"

class Overseer {
   private:
    std::unordered_map<std::string, std::optional<unsigned int>> sessionsCT_;
    std::unordered_map<unsigned int, std::string>                sessionsTC_;
    std::vector<Revenue>                                         revenues_;
    std::queue<std::string>                                      waitingQueue_;

    void freeSession(const std::string& clientName) noexcept;

   public:
    void                        freeTable(const std::string& clientName) noexcept;
    std::optional<unsigned int> getTable(const std::string& clientName) const noexcept;
    std::vector<Revenue>        getRevenue() const noexcept;
    std::vector<std::string>    getRemainings() const noexcept;
    void                        prepare(unsigned int tableCount) noexcept;
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