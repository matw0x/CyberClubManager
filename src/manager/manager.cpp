#include "manager.h"

void Manager::run(int argc, const char* const argv[]) {
    validator_.validateArgsCmd(argc, argv);
    inputConfig_ = parser_.parseInputConfig(argv[1], validator_);
    overseer_.prepare(inputConfig_.tableCount);
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

    auto clientName = overseer_.whoSitting(*event.tableNumber);
    if (!clientName.empty()) {
        event.clientNameOrMsg = EventMessages::PlaceIsBusy;
        event.type            = EventType::OUTPUT_ERROR;
        return;
    }

    overseer_.putClient(event.clientNameOrMsg, *event.tableNumber);
}

void Manager::handleClientWaiting(Event& event) noexcept {
    if (overseer_.anyTablesFree()) {
        event.clientNameOrMsg = EventMessages::ICanWaitNoLonger;
        event.type            = EventType::OUTPUT_ERROR;
        return;
    }

    if (overseer_.isWaitingQueueOverflow()) {
        overseer_.freeSession(event.clientNameOrMsg);
        event.type = EventType::OUTPUT_CLIENT_KICK;
    }
}

void Manager::handleClientLeft(Event& event) const noexcept {}

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
    if (error || !event.tableNumber) {
        std::cout << std::format("{} {} {}\n", event.time.format(), static_cast<unsigned int>(event.type),
                                 event.clientNameOrMsg);
        return;
    }

    std::cout << std::format("{} {} {} {}\n", event.time.format(), static_cast<unsigned int>(event.type),
                             event.clientNameOrMsg, *event.tableNumber);
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
    printEndWorkingTime();
    printRevenue();
}