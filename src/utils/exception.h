#ifndef EXC_H
#define EXC_H

#include <stdexcept>
#include <string_view>

[[noreturn]] inline void throwRuntimeError(std::string_view message = {}) { throw std::runtime_error(message.data()); }

[[noreturn]] inline void throwInvalidArgument(std::string_view message = {}) {
    throw std::invalid_argument(message.data());
}

#endif