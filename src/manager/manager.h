#ifndef MANAGER_H
#define MANAGER_H

#include "../parser/parser.h"
#include "../validator/validator.h"

class Manager {
   private:
    Validator validator_;
    Parser    parser_;

   public:
    Manager() = default;
    void run(int argc, const char* const argv[]) const;
};

#endif