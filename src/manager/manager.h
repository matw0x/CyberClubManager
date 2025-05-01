#ifndef MANAGER_H
#define MANAGER_H

#include "../parser/parser.h"
#include "../validator/validator.h"

class Manager {
   private:
    Parser    parser;
    Validator validator;
};

#endif