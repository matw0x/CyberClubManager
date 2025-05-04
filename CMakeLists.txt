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
)