#include "manager.h"

void Manager::run(int argc, const char* const argv[]) {
    validator_.validateArgsCmd(argc, argv);
    inputConfig_ = parser_.parseInputConfig(argv[1], validator_);
}