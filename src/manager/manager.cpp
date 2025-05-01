#include "manager.h"

void Manager::run(int argc, const char* const argv[]) const { validator_.validateArgsCmd(argc, argv); }