#ifndef MANAGER_H
#define MANAGER_H

#include "../parser/parser.h"
#include "../utils/config.h"
#include "../validator/validator.h"

class Manager {
   private:
    Validator validator_;
    Parser    parser_;
    IConfig   inputConfig_;
    OConfig   outputConfig_;

   public:
    void run(int argc, const char* const argv[]);
};

#endif