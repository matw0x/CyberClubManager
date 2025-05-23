#include "manager.h"

void Manager::run(int argc, const char* const argv[]) {
    validator_.validateArgsCmd(argc, argv);
    inputConfig_ = parser_.parseInputConfig(argv[1], validator_);
    overseer_.prepare(inputConfig_.tableCount, inputConfig_.hourCost);
    monitor();
}

void Manager::printBeginWorkingTime() const noexcept {
    std::cout << inputConfig_.workingHours.first.format() << std::endl;
}

void Manager::printEndWorkingTime() const noexcept {
    std::cout << inputConfig_.workingHours.second.format() << std::endl;
}

void Manager::printRevenue() const noexcept {
    auto revenues = overseer_.getRevenue();
    for (size_t i = 0; i != revenues.size(); ++i) {
        std::cout << std::format("{} {} {}\n", i + 1, revenues[i].cost, revenues[i].spentTime.format());
    }
}

void Manager::handleClientArrived(Event& event) noexcept {
    if (!overseer_.isClubWorking(event.time, inputConfig_.workingHours)) {
        event.clientNameOrMsg = EventMessages::NotOpenYet;
        event.type            = EventType::OUTPUT_ERROR;
        return;
    }

    if (overseer_.isClientInside(event.clientNameOrMsg)) {
        event.clientNameOrMsg = EventMessages::YouShallNotPass;
        event.type            = EventType::OUTPUT_ERROR;
        return;
    }

    overseer_.createClientSession(event.clientNameOrMsg);
}

void Manager::handleClientSat(Event& event) noexcept {
    if (!overseer_.isClientInside(event.clientNameOrMsg)) {
        event.clientNameOrMsg = EventMessages::ClientUnknown;
        event.type            = EventType::OUTPUT_ERROR;
        return;
    }

    auto oldTableNumber = overseer_.getTable(event.clientNameOrMsg);
    auto clientName     = overseer_.whoSitting(*event.tableNumber);
    if (!clientName.empty()) {
        event.clientNameOrMsg = EventMessages::PlaceIsBusy;
        event.type            = EventType::OUTPUT_ERROR;
        return;
    }

    if (oldTableNumber) {
        overseer_.calculateRevenue(*oldTableNumber, event.time);
        overseer_.freeTable(event.clientNameOrMsg);
    }

    overseer_.putClient(event.clientNameOrMsg, *event.tableNumber);
    overseer_.startCalculate(*event.tableNumber, event.time);
}

void Manager::handleClientWaiting(Event& event) noexcept {
    if (overseer_.anyTablesFree()) {
        event.clientNameOrMsg = EventMessages::ICanWaitNoLonger;
        event.type            = EventType::OUTPUT_ERROR;
        return;
    }

    if (overseer_.isWaitingQueueOverflow()) {
        overseer_.eraseFromClub(event.clientNameOrMsg);
        event.type = EventType::OUTPUT_CLIENT_KICK;
        return;
    }

    overseer_.addWaitingQueue(event.clientNameOrMsg);
}

void Manager::handleClientLeft(Event& event) noexcept {
    if (!overseer_.isClientInside(event.clientNameOrMsg)) {
        event.clientNameOrMsg = EventMessages::ClientUnknown;
        event.type            = EventType::OUTPUT_ERROR;
        return;
    }

    auto tableNumber = overseer_.getTable(event.clientNameOrMsg);
    if (tableNumber) {
        overseer_.calculateRevenue(*tableNumber, event.time);
        overseer_.freeTable(event.clientNameOrMsg);
    }

    overseer_.freeSession(event.clientNameOrMsg);

    if (auto clientName = overseer_.getFirstWaiter(); !clientName.empty() && tableNumber) {
        overseer_.putClient(clientName, *tableNumber);
        overseer_.startCalculate(*tableNumber, event.time);
        event.type            = EventType::OUTPUT_CLIENT_SAT;
        event.clientNameOrMsg = clientName;
        event.tableNumber     = tableNumber;
    }
}

void Manager::analyzeEvent(Event& event) noexcept {
    switch (event.type) {
        case EventType::INPUT_CLIENT_ARRIVED:
            return handleClientArrived(event);
        case EventType::INPUT_CLIENT_SAT:
            return handleClientSat(event);
        case EventType::INPUT_CLIENT_WAITING:
            return handleClientWaiting(event);
        case EventType::INPUT_CLIENT_LEFT:
            return handleClientLeft(event);
        default:
            return;
    }
}

void Manager::printEvent(const Event& event, bool error) const noexcept {
    if (event.type == EventType::INPUT_CLIENT_SAT || event.type == EventType::OUTPUT_CLIENT_SAT) {
        std::cout << std::format("{} {} {} {}\n", event.time.format(), static_cast<unsigned int>(event.type),
                                 event.clientNameOrMsg, *event.tableNumber);
        return;
    }

    if (error || !event.tableNumber) {
        std::cout << std::format("{} {} {}\n", event.time.format(), static_cast<unsigned int>(event.type),
                                 event.clientNameOrMsg);
    }
}

void Manager::printEventIfError(const Event& originalEvent, const Event& maybeErrorEvent) const noexcept {
    if (originalEvent.clientNameOrMsg != maybeErrorEvent.clientNameOrMsg ||
        originalEvent.type != maybeErrorEvent.type) {
        printEvent(maybeErrorEvent, true);
    }
}

void Manager::processEvents() noexcept {
    for (const auto& event : inputConfig_.events) {
        printEvent(event);
        auto maybeErrorEvent = event;
        analyzeEvent(maybeErrorEvent);
        printEventIfError(event, maybeErrorEvent);
    }
}

void Manager::monitor() noexcept {
    printBeginWorkingTime();
    processEvents();
    printRemainings();
    printEndWorkingTime();
    printRevenue();
}

void Manager::printRemainings() noexcept {
    overseer_.processRemainings(inputConfig_.workingHours.second);

    auto       totalRemainings = overseer_.getRemainings();
    const auto endTime         = inputConfig_.workingHours.second.format();
    const auto eventType       = static_cast<unsigned int>(EventType::OUTPUT_CLIENT_KICK);

    auto realRemainings = std::set(totalRemainings.begin(), totalRemainings.end());

    for (std::string_view clientName : realRemainings) {
        std::cout << std::format("{} {} {}\n", endTime, eventType, clientName);
    }
}