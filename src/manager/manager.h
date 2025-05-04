#ifndef MANAGER_H
#define MANAGER_H

#include "../parser/parser.h"
#include "../utils/config.h"
#include "../utils/overseer/overseer.h"
#include "../validator/validator.h"

class Manager {
   private:
    Validator validator_;
    Parser    parser_;
    IConfig   inputConfig_;
    Overseer  overseer_;

    void monitor() noexcept;
    void printBeginWorkingTime() const noexcept;
    void printEndWorkingTime() const noexcept;
    void printRevenue() const noexcept;
    void printEvent(const Event& event) const noexcept;
    void processEvents() noexcept;
    void analyzeEvent(Event& event) noexcept;
    void printEventIfError(const Event& originalEvent, const Event& maybeErrorEvent) const noexcept;
    void handleClientArrived(Event& event) noexcept;
    void handleClientSat(Event& event) noexcept;
    void handleClientWaiting(Event& event) const noexcept;
    void handleClientLeft(Event& event) const noexcept;

   public:
    void run(int argc, const char* const argv[]);
};

#endif