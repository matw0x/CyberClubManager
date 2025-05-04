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

void Manager::handleClientArrived(Event& event) const noexcept {
    if (!overseer_.isClubWorking(event.time, inputConfig_.workingHours)) {
        event.clientNameOrMsg = EventMessages::NotOpenYet;
        event.type            = EventType::OUTPUT_ERROR;
    } else if (overseer_.isClientInside(event.clientNameOrMsg)) {
        event.clientNameOrMsg = EventMessages::YouShallNotPass;
        event.type            = EventType::OUTPUT_ERROR;
    }
}

void Manager::analyzeEvent(Event& event) const noexcept {
    switch (event.type) {
        case EventType::INPUT_CLIENT_ARRIVED:
            handleClientArrived(event);
            return;
        case EventType::INPUT_CLIENT_SAT:
            return;
        case EventType::INPUT_CLIENT_WAITING:
            return;
        case EventType::INPUT_CLIENT_LEFT:
            return;
        default:
            return;
    }
}

void Manager::printEvent(const Event& event) const noexcept {
    std::cout << std::format("{} {} {}\n", event.time.format(), static_cast<unsigned int>(event.type),
                             event.clientNameOrMsg);
}

void Manager::printEventIfError(const Event& originalEvent, const Event& maybeErrorEvent) const noexcept {
    if (originalEvent.clientNameOrMsg != maybeErrorEvent.clientNameOrMsg) {
        printEvent(maybeErrorEvent);
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