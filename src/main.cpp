#include "validator/validator.h"

int main(int argc, char* argv[]) {
    Validator validator;
    try {
        validator.validateArgsCmd(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}