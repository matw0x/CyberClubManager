cmake_minimum_required(VERSION 3.10)
project(ccm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    ccm 
    src/main.cpp
    src/manager/manager.cpp
    src/parser/parser.cpp
    src/validator/validator.cpp
    src/utils/time/time.cpp
    src/utils/overseer/overseer.cpp
)

option(BUILD_TESTS "Build and configure tests" ON)

if(BUILD_TESTS)
    find_package(Python3 QUIET)
    if(Python3_FOUND)
        enable_testing()
        add_subdirectory(tests)
    else()
        message(WARNING "Python 3 not found. Tests are enabled in configuration but cannot be built/run.")
    endif()
endif()