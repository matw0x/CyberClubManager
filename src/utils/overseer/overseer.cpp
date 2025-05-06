#include "overseer.h"

std::vector<Revenue> Overseer::getRevenue() const noexcept { return revenues_; }

void Overseer::prepare(unsigned int tableCount, unsigned int costHour) noexcept {
    revenues_.resize(tableCount);
    costHour_ = costHour;
}

bool Overseer::isClientInside(const std::string& clientName) const noexcept { return sessionsCT_.contains(clientName); }

bool Overseer::isClubWorking(Time clientArrivalTime, std::pair<Time, Time> workingHours) const noexcept {
    return workingHours.first <= clientArrivalTime && clientArrivalTime <= workingHours.second;
}

void Overseer::createClientSession(const std::string& clientName) noexcept { sessionsCT_[clientName] = {}; }

void Overseer::freeTable(const std::string& clientName) noexcept {
    if (auto currentTable = getTable(clientName); currentTable) {
        sessionsTC_.erase(*currentTable);
    }
}

void Overseer::eraseFromClub(const std::string& clientName) noexcept {
    freeTable(clientName);
    freeSession(clientName);
}

void Overseer::freeSession(const std::string& clientName) noexcept { sessionsCT_.erase(clientName); }

void Overseer::addWaitingQueue(const std::string& clientName) noexcept { waitingQueue_.push(clientName); }

bool Overseer::isWaitingQueueOverflow() const noexcept { return waitingQueue_.size() > revenues_.size(); }

void Overseer::putClient(const std::string& clientName, unsigned int tableNumber) noexcept {
    sessionsCT_[clientName]  = tableNumber;
    sessionsTC_[tableNumber] = clientName;
}

std::optional<unsigned int> Overseer::getTable(const std::string& clientName) const noexcept {
    if (auto it = sessionsCT_.find(clientName); it != sessionsCT_.end()) {
        return it->second;
    }

    return {};
}

std::string Overseer::whoSitting(unsigned int tableNumber) const noexcept {
    if (auto it = sessionsTC_.find(tableNumber); it != sessionsTC_.end()) {
        return it->second;
    }

    return {};
}

bool Overseer::anyTablesFree() const noexcept { return revenues_.size() > sessionsTC_.size(); }

std::string Overseer::getFirstWaiter() noexcept {
    if (waitingQueue_.empty()) {
        return {};
    }

    auto clientName = waitingQueue_.front();
    waitingQueue_.pop();

    return clientName;
}

void Overseer::processRemainings(Time end) noexcept {
    for (const auto& pair : sessionsTC_) {
        calculateRevenue(pair.first, end);
    }
}

std::vector<std::string> Overseer::getRemainings() const noexcept {
    std::vector<std::string> remainings(sessionsCT_.size() + waitingQueue_.size());
    size_t                   currentIndex = 0;

    for (const auto& pair : sessionsCT_) {
        remainings[currentIndex++] = pair.first;
    }

    auto tempQueue = waitingQueue_;
    while (!tempQueue.empty()) {
        remainings[currentIndex++] = tempQueue.front();
        tempQueue.pop();
    }

    return remainings;
}

void Overseer::startCalculate(unsigned int tableNumber, Time start) noexcept { startSessionsTC_[tableNumber] = start; }

void Overseer::calculateRevenue(unsigned int tableNumber, Time end) noexcept {
    auto it    = startSessionsTC_.find(tableNumber);
    auto start = it->second;
    startSessionsTC_.erase(it);

    auto duration        = end - start;
    auto durationMinutes = duration.getMinutes();

    int roundedHours = 0;
    if (durationMinutes > 0) {
        roundedHours = (durationMinutes + 59) / 60;
    }

    size_t tableIndex = tableNumber - 1;
    revenues_[tableNumber - 1].cost += static_cast<unsigned int>(roundedHours * costHour_);
    revenues_[tableNumber - 1].spentTime = duration + revenues_[tableNumber - 1].spentTime;
}