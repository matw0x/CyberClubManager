#include "overseer.h"

std::vector<Revenue> Overseer::getRevenue() const noexcept { return revenues_; }

void Overseer::prepare(unsigned int tableCount) noexcept { revenues_.resize(tableCount); }

bool Overseer::isClientInside(const std::string& clientName) const noexcept { return sessionsCT_.contains(clientName); }

bool Overseer::isClubWorking(Time clientArrivalTime, std::pair<Time, Time> workingHours) const noexcept {
    return workingHours.first <= clientArrivalTime && clientArrivalTime < workingHours.second;
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

void startCalculate(unsigned int tableNumber, Time start) noexcept {}

void Overseer::calculateRevenue() noexcept {}